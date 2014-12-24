
#include "PreComp.h"
#include <Windows.h>
#include "khook2.h"
#include "hde.h"
#include "KHookMgr.h"

#pragma comment(lib, "hde.lib")



KHOOK::KHOOK()
{

}


KHOOK::~KHOOK()
{

}


int KHOOK::IsShortFunc( LPCVOID addr ){
    int res=0;

    DWORD code_len=0;
    BYTE* pcode = (BYTE*)addr;

    while(code_len<5){
        HDE_STRUCT hdestr={0};
        DWORD instr_len = hde_disasm(pcode, &hdestr);
        BYTE Opcode = *pcode;
        code_len += instr_len;
        pcode    += instr_len;
        if(Opcode==0xC3 || Opcode==0xC2){//RETN , RETN NN
            res=1;
            break;
        }
    }

    if( res == 0 ){//Long function
        return 0;
    }

    if( code_len >= 5 ){//5 bytes len function
        return 0;
    }

    DWORD CheckLen = 5 - code_len;
    DWORD FilledWithCC = 1;
    for( DWORD i = 0; i < CheckLen; i++ ){
        if( (pcode[i] != 0xCC) && (pcode[i] != 0x90) ){//Check for 0xCC or 0x90 after RETN -> compiler code alignment
            FilledWithCC = 0;
        }
    }
    if( FilledWithCC ){
        res = 0;
    }
    return res;
}



BOOL KHOOK::Hook( 
    LPVOID TargetAddr, 
    LPCVOID PrologueHandler,
    LPCVOID MainHandler,
    KStub*  pDstStub,
    DWORD   FuncId_,
    DWORD&  ErrCode
    )
{
    if( IsBadReadPtr( TargetAddr, sizeof( KJmpToStub ) ) ){//Code not readable
        ErrCode = ERR_PAGE_ACCESS;
        return FALSE;
    }


    if( IsShortFunc( TargetAddr ) ){
        ErrCode = ERR_SMALL_FUNC;
        return FALSE;
    }


    DWORD dwOldProt = 0;
    if( ! ::VirtualProtectEx( (HANDLE)(-1), (LPVOID)TargetAddr, 32, PAGE_EXECUTE_READWRITE, &dwOldProt ) )
    {
        ErrCode = ERR_VIRT_PROT;
        return FALSE;
    }


    this->TargetAddr      = TargetAddr;
    this->PrologueHandler = PrologueHandler;
    this->FuncId          = FuncId_;
    this->MainHandler     = MainHandler;

    code_len = 0;
    DWORD ReassembledCodeLen = 0;

    BYTE* pDst  = (BYTE*)pDstStub->ReassembledInstr;//dst
    BYTE *pcode = (BYTE*)TargetAddr;                //src

    while( code_len < 5 ){
        HDE_STRUCT hdestr = {0};
        DWORD instr_len = hde_disasm(pcode, &hdestr);
        
        //reassemble instruction and copy
        DWORD NewInstrLen = ReAssembleInstr( (BYTE*)TargetAddr, pcode, pDst, instr_len );

        code_len += instr_len;
        ReassembledCodeLen += NewInstrLen;
        pcode += instr_len;
        pDst  += NewInstrLen;
    }

    //Save original bytes for restore hook
    memcpy( orig_bytes, TargetAddr, code_len);


    //Prepare stub code
    //push id   0x68 xx xx xx xx
    //jmp Stub  0xE9 yy yy yy yy
    pDstStub->PushIdOpcode = 0x68;    //PUSH opcode
    pDstStub->FuncId = FuncId;

    pDstStub->JmpOpcode = 0xE9;    //JMP opcode
    pDstStub->JmpOperand = (DWORD)( (BYTE*)PrologueHandler - ( (BYTE*)&pDstStub->JmpOpcode + 5 ) );

    Unhooked = pDstStub->ReassembledInstr;

    //Add JMP to continue code in Reassembled instructions end
    BYTE *dst = pDstStub->ReassembledInstr + ReassembledCodeLen;
    *(BYTE*)dst = 0xE9;//JMP opcode
    *(DWORD*)(dst+1) = (DWORD) ( (DWORD)((BYTE*)TargetAddr + code_len) - ( (DWORD)dst + 5 ) );


    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Set hook
    //Write jmp stub to function start address

    JmpTo.Opcode = 0xE9;
    if( FuncId == 0xFFFFFFFF ){//jump to PrologueAddr
        JmpTo.Operand=(DWORD)((BYTE*)MainHandler - ( (BYTE*)TargetAddr + 5) );
    }
    else{// jump to push id
        JmpTo.Operand=(DWORD)( &pDstStub->PushIdOpcode - ( (BYTE*)TargetAddr + 5 ) );
    }

    //Patch function
    memcpy( TargetAddr, &JmpTo, sizeof( JmpTo ) );
    ErrCode = ERR_NO_ERR;
    return TRUE;
}


BOOL KHOOK::Unhook(){

    if( IsBadWritePtr( TargetAddr, sizeof( KJmpToStub ) ) ){//Code not readable
        return FALSE;
    }
    
    memcpy((void*)TargetAddr, orig_bytes, code_len);
    return FALSE;
}


DWORD KHOOK::ReAssembleInstr(BYTE* Base, BYTE *src, BYTE* dst, DWORD len){
    DWORD retlen=len;

    if(*src==0xE8 || *src==0xE9){//CALL or JMP
        int src_addr = (int)src;
        int Operand  = *(int*)&src[1];
        int dst_addr = src_addr + Operand + 5;

        *dst = *src;    //copy instruction opcode
        *(DWORD*)&dst[1] = (DWORD)dst_addr - (DWORD)dst - 5;
    }
    else if( *src >= 0x70 && *src <= 0x7F ){//Short JXX instruction
        DWORD src_addr = (DWORD)src;
        char Operand  = *(char*)&src[1];
        DWORD dst_addr = src_addr + Operand + 2;

        if(dst_addr > (DWORD)Base + 5){//FIX: OPERAND RANGE CHECK
            *(WORD*)&dst[0]=GetLongAnalog(src[0]);
            *(DWORD*)&dst[2] = (DWORD)dst_addr - (DWORD)dst - 6;
            retlen = 6;//instr len
        }
        else{//jmp in 5 byte block - copy without changes
            memcpy(dst, src, len);
        }
    }
    else if( *src==0xEB ){//JMP SHORT-> JMP LONG
        DWORD src_addr = (DWORD)src;
        char Operand  = *(char*)&src[1];
        DWORD dst_addr = src_addr + Operand + 2;

        if(dst_addr > (DWORD)Base + 5){//FIX: OPERAND RANGE CHECK
            *dst = 0xE9;
            *(DWORD*)&dst[1] = (DWORD)dst_addr - (DWORD)dst - 5;
            retlen = 5;
        }
        else{
            memcpy(dst, src, len);
        }
    }
    else{
        memcpy(dst, src, len);
    }
    return retlen;
}

WORD KHOOK::GetLongAnalog(BYTE cc){
    WORD r=0;

    //75 -> 85 0F
    r = 0x800F;

    r |= (cc & 0x0F)<<8;
    
    return r;
};


/*
//Creates stub function. And jump to target+5 bytes
void* GetSafeFuncStart(void *addr){
    //malloc for code
    void *p=MemAlloc(32);
    if(!p) return 0;

    DWORD dwTemp;
    safe_VirtualProtectEx((HANDLE)(-1), (LPVOID)p, 32, PAGE_EXECUTE_READWRITE, &dwTemp);    
    
    BYTE *pcode=(BYTE*)addr;
    DWORD code_len=0;
    while(code_len<5){
        HDE_STRUCT hdestr={0};
        DWORD instr_len=hde_disasm(pcode, &hdestr);
        code_len+=instr_len;
        pcode+=instr_len;
        //FIX: opcode tests here
    }
    memcpy((void*)p, addr, code_len);
    pcode=(BYTE*)p+code_len;
    *pcode=0xE9;
    *(DWORD*)(pcode+1)=(DWORD)((DWORD)((BYTE*)addr+code_len)-(DWORD)pcode-5);
    return p;
}

//Creates stub function. And jump to target+5 bytes
void* GetSafeFuncStartOrig(void *addr){
    //malloc for code
    void *p = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 32);
    if(!p) return 0;

    //Damn antivirals trick
    PFN_VirtualProtectEx pVirtualProtectEx = (PFN_VirtualProtectEx)(GetProcAddress( g_hKernel32, "VirtualProtectEx" ) );

    DWORD dwTemp;
    pVirtualProtectEx((HANDLE)(-1), (LPVOID)p, 32, PAGE_EXECUTE_READWRITE, &dwTemp);    

    BYTE *pcode=(BYTE*)addr;
    DWORD code_len=0;
    while(code_len<5){
        HDE_STRUCT hdestr={0};
        DWORD instr_len=hde_disasm(pcode, &hdestr);
        code_len+=instr_len;
        pcode+=instr_len;
        //FIX: opcode tests here
    }
    memcpy((void*)p, addr, code_len);
    pcode=(BYTE*)p+code_len;
    *pcode=0xE9;
    *(DWORD*)(pcode+1)=(DWORD)((DWORD)((BYTE*)addr+code_len)-(DWORD)pcode-5);
    return p;
}

*/

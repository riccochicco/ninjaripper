
#include "PreComp.h"
#include "khook.h"
#include "hde.h"
#pragma comment(lib, "hde.lib")

#include "intruder.h"


void KHook::CheckHookConflict( LPCVOID FuncAddr, LPCTSTR szErrMsg ){
    if( addr != FuncAddr ){
//        g_log.Write( TEXT("New: 0x%08X   Old: 0x%08X  %s\n"), FuncAddr, addr, szErrMsg );
        FatalErrorMsg( szErrMsg );
    }
}


KHook::KHook(LPCVOID addr, LPCVOID stub){
    this->addr = addr;
    this->stub = stub;
}

KHook::~KHook(){

}


void KHook::SetHook(){
    DWORD    total_len=0, cmd_len, dwTemp;
    BOOL foo1 = VirtualProtect((LPVOID)addr,     32, PAGE_EXECUTE_READWRITE, &dwTemp);
    BOOL foo2 = VirtualProtect((LPVOID)exec_buf, 32, PAGE_EXECUTE_READWRITE, &dwTemp);

    if( (foo1==FALSE) || (foo2==FALSE) ){

        FatalErrorMsg( TEXT("KHook VirtualProtect error ") );
    }

    PBYTE eip=(PBYTE)addr;    //Function address
    PBYTE dst=&exec_buf[0];
    exec=dst;

    HDE_STRUCT hdestr;

    //Calculate code len for hook
    while(1){
        ZeroMemory(&hdestr, sizeof(HDE_STRUCT));
        cmd_len = hde_disasm(eip, &hdestr);
        //Opcode tests here
        memcpy(dst, eip, cmd_len);
        dst+=cmd_len;
        eip+=cmd_len;

        total_len+=cmd_len;
        if(total_len>=5) break;
    }
    code_len=total_len;

    *(BYTE*)dst=0xE9;//JMP opcode
    //JMP from exec_buf to addr+5
    *(DWORD*)(dst+1)=(DWORD)((BYTE*)addr+5-(dst+5));

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Set hook
    //Write jmp stub to function begin address
    BYTE cmds[32];

    cmds[0]=0xE9;
    for(DWORD i=1; i<code_len; i++){
        cmds[i]=0x90;    //Fill with nops
    }
    *(DWORD*)((BYTE*)cmds+1)=(DWORD)((BYTE*)stub-((BYTE*)addr+5));
    memcpy((void*)addr, cmds, code_len);
}


void KHook::Unhook(){
    memcpy((void*)addr, exec_buf, code_len);
}
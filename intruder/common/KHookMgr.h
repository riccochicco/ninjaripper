#pragma once

// x32 bit hooks manager



#define STUB_MEM_SIZE 4 * 1024 * 1024 //4 M

class KHOOK;
struct SPROXYENTRYSTRUCT;

void ProxyProlog( void );
void __stdcall ProxyEntrySafe( SPROXYENTRYSTRUCT *pInfo, DWORD dwEnterTacts );

typedef LPVOID (__cdecl *PFN_PREHANDLER)( SPROXYENTRYSTRUCT*, KHOOK* pHook );


void stub_0();
void stub_1();
void stub_2();
void stub_3();
void stub_4();
void stub_5();
void stub_6();
void stub_7();
void stub_8();
void stub_9();
void stub_10();
void stub_11();
void stub_12();
void stub_13();
void stub_14();


#pragma pack(push,1)
struct SPROXYENTRYSTRUCT{
    DWORD    edi;
    DWORD    esi;
    DWORD    ebp;
    DWORD    esp;
    DWORD    ebx;
    DWORD    edx;
    DWORD    ecx;
    DWORD    eax;
    DWORD    eflags;
    DWORD    funcid;
    DWORD    retaddr;
    DWORD    parameters[32];
};
#pragma pack(pop)


#pragma pack(push,1)
struct SPROXYEXIT{
    DWORD result;
};
#pragma pack(pop)



/*
 Reassembled code are not shown

 target1 -> jmp stub1 -> push id1;jmp Handler1 --> Handler1
                                                  /
 target2 -> jmp stub2 -> push id2 jmp Handler1----
 
 target3 -> jmp stub3 -> push id3;jmp Handler2 --> Handler2

 Target
    jmp stub;  //E9 xx xx xx xx   5 bytes

 stub:
    push Id; //68 xx xx xx xx      5 bytes
    push Retaddr;//68 xx xx xx xx  5 bytes
    retn                           1 byte
                                   11 bytes per hook

*/



//Function start patch code
struct KJmpToStub{
    BYTE  Opcode;
    DWORD Operand;
};


struct KStub{
    BYTE  PushIdOpcode;
    DWORD FuncId;
    BYTE  JmpOpcode;
    DWORD JmpOperand;//Jmp to ProxyPrologue

    BYTE ReassembledInstr[ 32 ];
};


class KHookMgr{

public:

    KHookMgr();
    virtual ~KHookMgr();
    

    //Set hook if already not set
    //Return: new KHOOK obj or NULL
    KHOOK* Hook( LPVOID TargetAddr, LPCVOID Handler, DWORD& Error );
    KHOOK* Hook( LPVOID TargetAddr, LPCVOID Handler ){
        DWORD Err;
        return Hook( TargetAddr, Handler, Err );
    }

    KHOOK* GetHookById( DWORD Id ){
        return InstalledHooks[ Id ];
    }

private:
    KHOOK* Hook1( LPVOID TargetAddr, LPCVOID MainHandler, DWORD& Error );
    
    //*** hook v2.0
    DWORD StubsInBuffer;//Free stubs count
    DWORD CurrentFuncId;//Current FuncId
    KStub* pStubs;      //Base address of stubs
    
    std::vector < KHOOK* > InstalledHooks;

    BOOL IsJumpStubInDB( const KJmpToStub* pJmpStub, DWORD& Id );

    CRITICAL_SECTION cs;
};


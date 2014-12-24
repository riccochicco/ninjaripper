
#pragma once

char*    GetHookErrorText(int);
int        IsShortFunc(LPVOID);
WORD    GetLongAnalog(BYTE cc);
void*    GetSafeFuncStart(void *addr);
void*    GetSafeFuncStartOrig(void *addr);


struct KStub;
struct KHookInfo;


class KHOOK{

private:
    DWORD   ReAssembleInstr( BYTE*pBase, BYTE *src, BYTE* dst, DWORD len );
    WORD    GetLongAnalog( BYTE cc );
    int     IsShortFunc( LPCVOID addr );

    BYTE    orig_bytes[32];
    DWORD   code_len;//Patched code len ( orig_bytes len )

    DWORD   FuncId;
    LPVOID  TargetAddr;      //Function address
    LPCVOID MainHandler;     //Main action handler "mine_XXX"
    LPCVOID PrologueHandler;
    
    LPVOID  Unhooked;

    KJmpToStub JmpTo;

public:
    enum{
        ERR_NO_ERR = 0,
        ERR_ALREADY_HOOKED,
        ERR_PAGE_ACCESS,
        ERR_SMALL_FUNC,
        ERR_VIRT_PROT
    };
    
    KHOOK();
    ~KHOOK();

    LPCVOID GetMainHandler(){
        return MainHandler;
    }

    const void* GetJmpTo(){
        return &JmpTo;
    }

    LPVOID GetTargetAddr(){
        return TargetAddr;
    }

    DWORD GetFuncId(){
        return FuncId;
    }

    LPVOID GetUnhooked(){
        return Unhooked;
    }
    
    BOOL Hook( 
        LPVOID  TargetAddr, 
        LPCVOID PrologueHandler,
        LPCVOID MainHandler,
        KStub*  pDstStub,
        DWORD   FuncID,
        DWORD&  ErrCode
        );

    BOOL Unhook();

/*
    Target   JMP STUB;

    STUB:    PUSH ID
             PUSH PROLOGUE
             RET

    ;Unhooked here
    REASSEMBLED:

*/

};


#include "PreComp.h"
#include "KHookMgr.h"
#include "KIntruder.h"
#include "khook2.h"


KHookMgr::KHookMgr():
CurrentFuncId( 0 ),
StubsInBuffer( 0 )
{
    pStubs = ( KStub* ) ::VirtualAlloc( NULL, STUB_MEM_SIZE, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE );
    if( !pStubs ){
        FatalErrorMsg( L"VirtualAlloc(). Error in memory alloc for hooks" );
    }

    StubsInBuffer = STUB_MEM_SIZE / sizeof( KStub );

    ::InitializeCriticalSection( &cs );
}


 KHookMgr::~KHookMgr(){
     ::DeleteCriticalSection( &cs );
 }


BOOL KHookMgr::IsJumpStubInDB( const KJmpToStub* pJmpStub, DWORD& Id ){
    for( size_t i = 0; i < InstalledHooks.size(); i++ ){
        KHOOK* pHook = InstalledHooks[ i ];
        if( !memcmp( pHook->GetJmpTo(), pJmpStub, sizeof( KJmpToStub ) ) ){
            Id = pHook->GetFuncId();
            return TRUE;
        }
    }
    return FALSE;
}



KHOOK* KHookMgr::Hook( LPVOID TargetAddr, LPCVOID MainHandler, DWORD& Error ){
    ::EnterCriticalSection( &cs );
    KHOOK* p = Hook1( TargetAddr, MainHandler, Error );
    if( Error != KHOOK::ERR_NO_ERR ){//Hook are not set. Delete obj
        SAFE_DELETE( p );
    }
    ::LeaveCriticalSection( &cs );
    return p;
}


//FIXME: additional checks add
KHOOK* KHookMgr::Hook1( LPVOID TargetAddr, LPCVOID MainHandler, DWORD& Error )
{
    if( IsBadReadPtr( TargetAddr, sizeof( KJmpToStub ) ) ){//Code not readable
        Error = KHOOK::ERR_PAGE_ACCESS;
        return NULL;
    }

    KJmpToStub* FirstOpcode = ( KJmpToStub* )TargetAddr;
    
    DWORD Id = -1;
    KHOOK* pHook = NULL;
    if( IsJumpStubInDB( FirstOpcode, Id ) ){//Function already hooked
        //Check handler address
        pHook = InstalledHooks[ Id ];
        if( pHook->GetMainHandler() == MainHandler ){
            Error = KHOOK::ERR_ALREADY_HOOKED;
            return NULL;//Already hooked. No need hook
        }
        else{//ERROR: Function already hooked and have ANOTHER handler
            //Add more informative msg
            //Need additional research
            ::FatalErrorMsg( L"Function already hooked and have ANOTHER handler" );
        }
    }
    else{//New hook
        
        pHook = new KHOOK;

        BOOL foo = pHook->Hook
            (
            TargetAddr, 
            ProxyProlog, 
            MainHandler, 
            &pStubs[ CurrentFuncId ], 
            CurrentFuncId, 
            Error 
            );


        if( !foo ){//Error
            SAFE_DELETE( pHook );
            return NULL;
        }
        else{//Add to db
            InstalledHooks.push_back( pHook );
            CurrentFuncId++;
            StubsInBuffer--;
            if( !StubsInBuffer ){
                ::FatalErrorMsg( L"No free memory for hooks" );
            }
        }

    }
    return pHook;
}


DWORD OverHead = 0;
__declspec(naked) void ProxyProlog(void){
    __asm{
        pushfd
        pushad

        rdtsc
        shrd    eax, edx, 8
        push    eax
        sub        eax, OverHead
        push    eax
        lea        eax, [esp + 8]
        push    eax
        call    ProxyEntrySafe
        pop        ecx
        rdtsc
        shrd    eax, edx, 8
        sub        eax, ecx
        add        OverHead, eax

        popad
        popfd
        retn
    }
}



void __stdcall ProxyEntrySafe( SPROXYENTRYSTRUCT *pInfo, DWORD dwEnterTacts ){    
    DWORD id = pInfo->funcid;

    KHOOK* pHook = g_pHookMgr->GetHookById( id ); 
    PFN_PREHANDLER PreHandler = (PFN_PREHANDLER)pHook->GetMainHandler();

    LPVOID FakeFuncAddr = PreHandler( pInfo, pHook );

    //Return address
    pInfo->funcid = (DWORD)FakeFuncAddr;//Change function address from plug in value
}





void __declspec(naked) stub_0(){
    __asm{
        retn    
    }
}

void __declspec(naked) stub_1(){
    __asm{
        retn    4
    }
}
void __declspec(naked) stub_2(){
    __asm{
        retn    8
    }
}
void __declspec(naked) stub_3(){
    __asm{
        retn    0Ch
    }
}
void __declspec(naked) stub_4(){
    __asm{
        retn    10h
    }
}
void __declspec(naked) stub_5(){
    __asm{
        retn    14h
    }
}
void __declspec(naked) stub_6(){
    __asm{
        retn    18h
    }
}
void __declspec(naked) stub_7(){
    __asm{
        retn    1Ch
    }
}
void __declspec(naked) stub_8(){
    __asm{
        retn    20h
    }
}
void __declspec(naked) stub_9(){
    __asm{
        retn    24h
    }
}
void __declspec(naked) stub_10(){
    __asm{
        retn    28h
    }
}

void __declspec(naked) stub_11(){
    __asm{
        retn    2Ch
    }
}

void __declspec(naked) stub_12(){
    __asm{
        retn    30h
    }
}

void __declspec(naked) stub_13(){
    __asm{
        retn    34h
    }
}

void __declspec(naked) stub_14(){
    __asm{
        retn    38h
    }
}


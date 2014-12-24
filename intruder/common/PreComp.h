#pragma

//Use unicode
#if !defined UNICODE
#define UNICODE
#endif

#if !defined _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <list>
#include <map>


void    FatalErrorMsg( LPCTSTR );

#include "klog.h"
#include "KHookMgr.h"
#include "KIntruder.h"
#include "khook2.h"
#include "TDXRef.h"


//void* GetMethodAddr( DWORD **pvtbl, DWORD idx );

std::wstring StringToWString( const std::string &s );
void StrCopy( char* pDst, DWORD BufSize, const char* pSrc );
void* GetMethodAddr( void* pvtbl, DWORD idx );

//-----------------------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

struct SPROXYENTRYSTRUCT;
class KHOOK;



extern KLog*      g_pLog;
extern KIntruder* g_pIntruder;
extern KHookMgr*  g_pHookMgr;

typedef  DWORD REGTYPE;
typedef std::vector < UINT > KUINTVec;
typedef std::vector < std::string > KStringVec;
typedef std::vector < DWORD > KDWORDVec;


#include "CodeMacroses.h"
#include "CodeMacroses2.h"



#define HOOKED_STR L" hooked"
#define HOOK_ERR_STR L" hook error: %d"
#define HOOK_ADDR_STR L" Address: 0x%p\n"


#define HOOK( FuncName, Num, pVtbl )\
    PFN_##FuncName true_##FuncName = \
    ( PFN_##FuncName )GetMethodAddr( pVtbl, Num );\
    DWORD Err_##FuncName = 0;\
    KHOOK* pHook_##FuncName = g_pHookMgr->Hook( true_##FuncName, Pre_##FuncName, Err_##FuncName );\
    if( pHook_##FuncName ){\
        g_pLog->Write( L#FuncName );\
        g_pLog->Write( HOOKED_STR );\
        g_pLog->Write( HOOK_ADDR_STR,  true_##FuncName);\
    }\
    else if( Err_##FuncName != KHOOK::ERR_ALREADY_HOOKED ){\
        g_pLog->Write( L#FuncName );\
        g_pLog->Write( HOOK_ERR_STR, Err_##FuncName );\
        g_pLog->Write( HOOK_ADDR_STR,  true_##FuncName);\
    }



template < class T >
class TInitedVal{
public:
    TInitedVal():
    Inited( false )
    {
    }

    void Set( const T& t ){
        Inited = true;
        val = t;
    }

    T Get()const{
        return val;
    }

    bool IsInited()const{
        return Inited;
    }

private:
    T val;
    bool Inited;
};



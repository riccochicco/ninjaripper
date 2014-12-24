// intruder.cpp : Defines the entry point for the DLL application.
//

#include "PreComp.h"
#include <shlwapi.h>
#include "intruder.h"
#include "kintruder.h"
#include "dx9/Pre9.h"
#include "dx8/Pre8.h"
#include "dx11/Pre11.h"
#include "KHookMgr.h"
#include "..\injector\kinject.h"

#pragma comment (lib, "shlwapi.lib")

static const std::wstring DXR_VER 
    ( L"Ninja Ripper v1.1.2\n(c)2004-2012 black_ninja\n\n" );


//        __asm _emit 0xeb
//        __asm _emit 0xfe


static KRipper9*  g_pRipper9  = NULL;
static KRipper8*  g_pRipper8  = NULL;
static KRipper11* g_pRipper11 = NULL;


static void    Install(HINSTANCE);
static void    Uninstall();
static HINSTANCE Get_D3D9_DLL_Base();
static HINSTANCE Get_D3D8_DLL_Base();
static HINSTANCE Get_D3D11_DLL_Base();


//Global vars
KLog*      g_pLog      = NULL;
KIntruder* g_pIntruder = NULL;
KHookMgr*  g_pHookMgr  = NULL;
//Dx detecting
KHOOK* pHook_LdrLoadDll = NULL;
KHOOK* pHook_LdrUnloadDll=NULL;

//Child process hook
static KHOOK* pHook_CreateProcessA = NULL;
static KHOOK* pHook_CreateProcessW = NULL;

static HMODULE hIntruderDll = NULL;


void FatalErrorMsg(LPCTSTR msg){
    MessageBox(0, msg, TEXT("intruder.dll"), MB_ICONERROR|MB_TOPMOST);
    ExitProcess(-1);
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){
    hIntruderDll = (HMODULE)hModule;

    switch (ul_reason_for_call){
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls((HMODULE)hModule);
            ::Install( (HINSTANCE)hModule );
        break;
        case DLL_PROCESS_DETACH:
            ::Uninstall();
        break;
    }
    return TRUE;
}


static void Install( HINSTANCE hIntruder )
{

    // Create directory in intruder
    g_pIntruder = new KIntruder(hIntruder);
    g_pIntruder->Init();


    wchar_t szBuf[ MAX_PATH ] = { 0 };
    wchar_t szExeName[ MAX_PATH ] = { 0 };
    GetModuleFileName(0, szBuf, MAX_PATH);
    for (DWORD i=(DWORD)lstrlen(szBuf); i>0; i--)
    {
        if (szBuf[i-1]==L'\\')
        {
            memcpy( szExeName, &szBuf[ i ], sizeof( wchar_t ) * lstrlen( &szBuf[ i ] ) );
            break;
        }
    }
    lstrcatW(szExeName, L".log.txt" );

    std::wstring LogFile;
    LogFile = g_pIntruder->GetOutputDir();
    LogFile += szExeName;

    g_pLog = new KLog;
    if( g_pLog->Open( LogFile.c_str() ) == -1 ){
        ::FatalErrorMsg( L"Can't open log file" );
    }
    g_pLog->Write( DXR_VER.c_str() );
    g_pLog->WriteTime();
    g_pLog->Write( L"\n\nLOG START\n\n" );

    g_pHookMgr = new KHookMgr;


    HINSTANCE hD3D9 = Get_D3D9_DLL_Base();
    if( hD3D9 && !g_pRipper9 ){
        g_pRipper9 = ::Create_KRipper9( hD3D9 );
    }

    HINSTANCE hD3D8 = ::Get_D3D8_DLL_Base();
    if( hD3D8 && !g_pRipper8 ){
        g_pRipper8 = ::Create_KRipper8( hD3D8 );
    }

    HINSTANCE hD3D11 = ::Get_D3D11_DLL_Base();
    if( hD3D11 && !g_pRipper11 ){
        g_pRipper11 = ::Create_KRipper11( hD3D11 );
    }

    HMODULE hntdll = ::GetModuleHandle( L"ntdll.dll" );
    PFN_LdrLoadDll orig_LdrLoadDll = (PFN_LdrLoadDll)GetProcAddress(hntdll, "LdrLoadDll" );
    if( !orig_LdrLoadDll ){
        ::FatalErrorMsg( L"GetProcAddress( ntdll.LdrLoadDll ) == NULL" );
    }
    pHook_LdrLoadDll = g_pHookMgr->Hook( orig_LdrLoadDll, Pre_LdrLoadDll );


    PFN_LdrUnloadDll orig_LdrUnloadDll = (PFN_LdrUnloadDll)GetProcAddress(hntdll, "LdrUnloadDll" );
    if( !orig_LdrUnloadDll ){
        ::FatalErrorMsg( L"GetProcAddress( ntdll.LdrUnloadDll ) == NULL" );
    }
    pHook_LdrUnloadDll = g_pHookMgr->Hook( orig_LdrUnloadDll, Pre_LdrUnloadDll );
    


    HMODULE hKernel32 = ::GetModuleHandle( L"kernel32.dll" );
    PFN_CreateProcessA orig_CreateProcessA = (PFN_CreateProcessA)GetProcAddress(hKernel32, "CreateProcessA" );
    if( !orig_CreateProcessA ){
        ::FatalErrorMsg( L"GetProcAddress( kernel32.CreateProcessA ) == NULL" );
    }
    pHook_CreateProcessA = g_pHookMgr->Hook( orig_CreateProcessA, Pre_CreateProcessA );


    PFN_CreateProcessW orig_CreateProcessW = (PFN_CreateProcessW)GetProcAddress(hKernel32, "CreateProcessW" );
    if( !orig_CreateProcessW ){
        ::FatalErrorMsg( L"GetProcAddress( kernel32.CreateProcessW ) == NULL" );
    }
    pHook_CreateProcessW = g_pHookMgr->Hook( orig_CreateProcessW, Pre_CreateProcessW );

}


static void Uninstall(){
    //Need unhook LdrLoadDll,LdrUnloadDll
    pHook_LdrLoadDll->Unhook();
    pHook_LdrUnloadDll->Unhook();


    ::Delete_KRipper8( g_pRipper8 );
    ::Delete_KRipper9( g_pRipper9 );
    ::Delete_KRipper11( g_pRipper11 );

    SAFE_DELETE( g_pHookMgr );

    g_pIntruder->Uninit();
    SAFE_DELETE( g_pIntruder );

    PrintModules();

    g_pLog->Write( L"\n\nLOG END\n\n" );
    g_pLog->WriteTime();
    g_pLog->Write( L"\n" );
    g_pLog->Close();
    SAFE_DELETE( g_pLog );
}



static HINSTANCE Get_D3D11_DLL_Base(){
    wchar_t szBuffer[MAX_PATH];
    ::GetSystemDirectory(szBuffer, MAX_PATH);
    ::lstrcatW( szBuffer, L"\\d3d11.dll" );
    HINSTANCE hDLL = ::GetModuleHandle( szBuffer );
    return hDLL;
}


static HINSTANCE Get_D3D9_DLL_Base(){
    wchar_t szBuffer[MAX_PATH];
    ::GetSystemDirectory(szBuffer, MAX_PATH);
    ::lstrcatW( szBuffer, L"\\d3d9.dll" );
    HINSTANCE hDLL = ::GetModuleHandle( szBuffer );
    return hDLL;
}


static HINSTANCE Get_D3D8_DLL_Base(){
    wchar_t szBuffer[MAX_PATH];
    ::GetSystemDirectory(szBuffer, MAX_PATH);
    ::lstrcatW( szBuffer, L"\\d3d8.dll" );
    HINSTANCE hDLL = ::GetModuleHandle( szBuffer );
    return hDLL;
}



static LPVOID Pre_LdrLoadDll( 
    SPROXYENTRYSTRUCT* pEntry, 
    KHOOK* pHook 
    )
{
    pEntry->eax = (REGTYPE)_LdrLoadDll(
        (PFN_LdrLoadDll)pHook->GetUnhooked(),
        (WORD*)pEntry->parameters[0],
        (DWORD*)pEntry->parameters[1],
        (KUNICODE_STRING*)pEntry->parameters[2],
        (DWORD*)pEntry->parameters[3]
        );
    return stub_4;
}


static DWORD _LdrLoadDll( 
    PFN_LdrLoadDll e,
    WORD* a1, 
    DWORD* pError, 
    KUNICODE_STRING* pUnicode, 
    DWORD* pResInst 
    )
{
    DWORD xxx = e( a1, pError, pUnicode, pResInst );

    static BOOL InitRipper9 = FALSE;
    HINSTANCE hD3D9 = ::Get_D3D9_DLL_Base();
    if( hD3D9 && !g_pRipper9 && !InitRipper9 ){
        InitRipper9 = TRUE;
        g_pLog->Write( L"D3D9.DLL loaded\n" );
        g_pRipper9 = ::Create_KRipper9( hD3D9 );
        InitRipper9 = FALSE;
    }

    static BOOL InitRipper8 = FALSE;
    HINSTANCE hD3D8 = ::Get_D3D8_DLL_Base();
    if( hD3D8 && !g_pRipper8 && !InitRipper8 ){
        InitRipper8 = TRUE;
        g_pLog->Write( L"D3D8.DLL loaded\n" );
        g_pRipper8 = ::Create_KRipper8( hD3D8 );
        InitRipper8 = FALSE;
    }


    static BOOL InitRipper11 = FALSE;
    HINSTANCE hD3D11 = ::Get_D3D11_DLL_Base();
    if( hD3D11 && !g_pRipper11 && !InitRipper11 ){
        InitRipper11 = TRUE;
        g_pLog->Write( L"D3D11.DLL loaded\n" );
        g_pRipper11 = ::Create_KRipper11( hD3D11 );
        InitRipper11 = FALSE;
    }

    return xxx;
}



static LPVOID Pre_LdrUnloadDll( 
    SPROXYENTRYSTRUCT* pEntry, 
    KHOOK* pHook 
    )
{
    pEntry->eax = (REGTYPE)_LdrUnloadDll(
        (PFN_LdrUnloadDll)pHook->GetUnhooked(),
        (HINSTANCE)pEntry->parameters[ 0 ]
        );
    return stub_1;
}


static DWORD  _LdrUnloadDll( PFN_LdrUnloadDll e, HINSTANCE hMod ){
    DWORD xxx = 0;

    xxx = e( hMod );

    HINSTANCE hD3d9 = ::Get_D3D9_DLL_Base();
    if( !hD3d9 && g_pRipper9 ){//DLL unloaded. Can't unhook
        g_pLog->Write( L"D3D9.DLL unloaded\n" );
        ::Delete_KRipper9( g_pRipper9 );
        g_pRipper9 = NULL;
    }

    HINSTANCE hD3d8 = ::Get_D3D8_DLL_Base();
    if( !hD3d8 && g_pRipper8 ){
        g_pLog->Write( L"D3D8.DLL unloaded\n" );
        ::Delete_KRipper8( g_pRipper8 );
        g_pRipper8 = NULL;
    }

    HINSTANCE hD3D11 = ::Get_D3D11_DLL_Base();
    if( !hD3D11 && g_pRipper11 ){
        g_pLog->Write( L"D3D11.DLL unloaded\n" );
        ::Delete_KRipper11( g_pRipper11 );
        g_pRipper11 = NULL;
    }

    return xxx;
}



static LPVOID Pre_CreateProcessA( 
    SPROXYENTRYSTRUCT* pEntry, 
    KHOOK* pHook 
    )
{
    pEntry->eax = (REGTYPE)_CreateProcessA(
        (PFN_CreateProcessA)pHook->GetUnhooked(),
        (const char*)          pEntry->parameters[ 0 ],
        (char*)                pEntry->parameters[ 1 ],
        (LPSECURITY_ATTRIBUTES)pEntry->parameters[ 2 ],
        (LPSECURITY_ATTRIBUTES)pEntry->parameters[ 3 ] ,
        (BOOL)                 pEntry->parameters[ 4 ],
        (DWORD)                pEntry->parameters[ 5 ],
        (LPVOID)               pEntry->parameters[ 6 ],
        (const char*)          pEntry->parameters[ 7 ],
        (LPSTARTUPINFO)        pEntry->parameters[ 8 ],
        (LPPROCESS_INFORMATION)pEntry->parameters[ 9 ]
    );
    return stub_10;
}


DWORD  _CreateProcessA( PFN_CreateProcessA e, 
    const char* lpApplicationName,
    char* lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    const char* lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    )
{
/*
    BOOL SuspendedProcess = FALSE;
    if( dwCreationFlags & CREATE_SUSPENDED ){
        SuspendedProcess = TRUE;
    }
    dwCreationFlags |= CREATE_SUSPENDED;
*/

    DWORD Foo = e( 
        lpApplicationName,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation
        );

    char* pStr = NULL;
    if( lpApplicationName ){ pStr = (char*)lpApplicationName; }
    else if( lpCommandLine ){ pStr = lpCommandLine; }
    g_pLog->Write( L"CreateProcessA( %s ) ret: 0x%08X\n", ::StringToWString( pStr ).c_str(), Foo );
/*
    if( Foo ){//Process successfully created
        KInject inj;
        char Dll[ MAX_PATH ];
        ::GetModuleFileNameA( hIntruderDll, Dll, MAX_PATH );

        inj.Inject2( lpProcessInformation->hProcess, lpProcessInformation->hThread, Dll );

        if( !SuspendedProcess ){
            ::ResumeThread( lpProcessInformation->hThread );
        }
    }
*/
    return Foo;
}





static LPVOID Pre_CreateProcessW( 
    SPROXYENTRYSTRUCT* pEntry, 
    KHOOK* pHook 
    )
{
    pEntry->eax = (REGTYPE)_CreateProcessW(
        (PFN_CreateProcessW)pHook->GetUnhooked(),
        (const wchar_t*)       pEntry->parameters[ 0 ],
        (wchar_t*)             pEntry->parameters[ 1 ],
        (LPSECURITY_ATTRIBUTES)pEntry->parameters[ 2 ],
        (LPSECURITY_ATTRIBUTES)pEntry->parameters[ 3 ] ,
        (BOOL)                 pEntry->parameters[ 4 ],
        (DWORD)                pEntry->parameters[ 5 ],
        (LPVOID)               pEntry->parameters[ 6 ],
        (const wchar_t*)       pEntry->parameters[ 7 ],
        (LPSTARTUPINFO)        pEntry->parameters[ 8 ],
        (LPPROCESS_INFORMATION)pEntry->parameters[ 9 ]
    );
    return stub_10;
}

DWORD  _CreateProcessW( PFN_CreateProcessW e, 
    const wchar_t* lpApplicationName,
    wchar_t* lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    const wchar_t* lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    )
{
    /*
    BOOL SuspendedProcess = FALSE;
    if( dwCreationFlags & CREATE_SUSPENDED ){
        SuspendedProcess = TRUE;
    }
    dwCreationFlags |= CREATE_SUSPENDED;
    */

    DWORD Foo = e( 
        lpApplicationName,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation
        );

    wchar_t* pStr = NULL;
    if( lpApplicationName ){ pStr = (wchar_t*)lpApplicationName; }
    else if( lpCommandLine ){ pStr = lpCommandLine; }
    g_pLog->Write( L"CreateProcessW( %s ) ret: 0x%08X\n", pStr, Foo );
/*   
    if( Foo ){//Process successfully created
        KInject inj;
        char Dll[ MAX_PATH ];
        ::GetModuleFileNameA( hIntruderDll, Dll, MAX_PATH );
        inj.Inject2( lpProcessInformation->hProcess, lpProcessInformation->hThread, Dll );
        if( !SuspendedProcess ){
            ::ResumeThread( lpProcessInformation->hThread );
        }
    }
*/    
    return Foo;
}




void PrintModules()
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;
    wchar_t szModName[MAX_PATH];

    HMODULE hPSAPI = ::LoadLibrary(L"psapi.dll");
    PFN_EnumProcessModules aEnumProcessModules = NULL;
    PFN_GetModuleFileNameExW aGetModuleFileNameExW = NULL;
    if (hPSAPI)
    {
        aEnumProcessModules  = (PFN_EnumProcessModules)
            GetProcAddress(hPSAPI, "EnumProcessModules");
        
        aGetModuleFileNameExW= (PFN_GetModuleFileNameExW)
            GetProcAddress(hPSAPI, "GetModuleFileNameExW");
    }

    if (!hPSAPI || !aEnumProcessModules || !aGetModuleFileNameExW)
    {
        g_pLog->Write(L"\n\npsapi.dll load error\n\n");
    }
    else
    {
        g_pLog->Write(L"\nLoaded Modules List\n");
        hProcess = (HANDLE)(-1);
        if (aEnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)){
            for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ ){
                if ( aGetModuleFileNameExW( hProcess, hMods[i],
                    szModName,sizeof(szModName)))
                
                {
                    g_pLog->Write(L"0x%p %s\n", hMods[i], szModName);
                }
            }
        }
    }
}

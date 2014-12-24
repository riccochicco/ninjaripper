
#include "PreComp.h"
#include "types.h"
#include "predisp.h"
#include "intruder.h"
#include "dip.h"
#include "dp.h"
#include "dipup.h"
#include "dpup.h"
#include "shaders.h"


//************************************************************************
// DirectX 9
//************************************************************************


//D3D9 Ripper Global Vars
KHook *phook_Direct3DCreate9=NULL;
KHook *phook_IDirect3D9_Direct3DCreate9=NULL;
KHook *phook_IDirect3DDevice9_SetTexture=NULL;
KHook *phook_IDirect3DDevice9_DrawIndexedPrimitive=NULL;
KHook *phook_IDirect3DDevice9_DrawPrimitive=NULL;
KHook *phook_IDirect3DDevice9_DrawIndexedPrimitiveUP=NULL;
KHook *phook_IDirect3DDevice9_DrawPrimitiveUP=NULL;
KHook *phook_IDirect3DDevice9_Present=NULL;
KHook *phook_IDirect3DDevice9_SetPixelShader=NULL;
KHook *phook_IDirect3DDevice9_SetVertexShader=NULL;
KHook *phook_IDirect3DSwapChain9_Persent=NULL;
KHook *phook_IDirect3DDevice9_GetSwapChain=NULL;
KHook *phook_IDirect3DDevice9_CreateVertexBuffer=NULL;
KHook *phook_IDirect3DDevice9_CreateIndexBuffer=NULL;


//PFN_D3D9_D3DXSaveTextureToFile D3D9_D3DXSaveTextureToFile = NULL;
//PFN_D3D9_D3DXDisassembleShader D3D9_D3DXDisassembleShader = NULL;


void Init_D3D9_Ripper( HINSTANCE hD3d9 ){
    static DWORD Hooked = 0;
/*
    if( !Hooked ){
        Hooked = 1;

        PFN_Direct3DCreate9 true_Direct3DCreate9=(PFN_Direct3DCreate9)GetProcAddress(hD3d9, "Direct3DCreate9");
        if( true_Direct3DCreate9==0 )
            FatalErrorMsg(TEXT("Can't get address of Direct3DCreate9"));

        //Set hook to Direct3DCreate9
        phook_Direct3DCreate9 = new KHook( true_Direct3DCreate9, mine_Direct3DCreate9 );

        g_log.Write(TEXT("d3d9.Direct3DCreate9() hooked\n") );
    }
    */
}


IDirect3D9 * __stdcall mine_Direct3DCreate9(UINT SDKVER){
    /*
    static    DWORD fEntry=0;    //Hook only once
    
    HINSTANCE    hD3dx9=0;

    PFN_Direct3DCreate9 e=(PFN_Direct3DCreate9)phook_Direct3DCreate9->exec;

    IDirect3D9 * pid3d9 = e( SDKVER );
    if( ( pid3d9 != 0 ) && ( fEntry == 0 ) ){
        fEntry = 1;
        PFN_IDirect3D9_CreateDevice true_CreateDevice=(PFN_IDirect3D9_CreateDevice)GetMethodAddr((DWORD**)pid3d9, 16);
        phook_IDirect3D9_Direct3DCreate9 = new KHook(true_CreateDevice, mine_IDirect3D9_CreateDevice);

        //Load helper DLL
        hD3dx9 = LoadLibrary(TEXT("d3dx9_36.dll"));
        if( hD3dx9 == 0 )
            FatalErrorMsg(TEXT("d3dx9_36.dll not found"));


        D3D9_D3DXSaveTextureToFile=(PFN_D3D9_D3DXSaveTextureToFile)GetProcAddress(hD3dx9, "D3DXSaveTextureToFileW");
        if( D3D9_D3DXSaveTextureToFile == 0 )
            FatalErrorMsg(TEXT("Can't get address of D3DXSaveTextureToFile(A\\W)"));


        D3D9_D3DXDisassembleShader=(PFN_D3D9_D3DXDisassembleShader)GetProcAddress(hD3dx9, "D3DXDisassembleShader");
        if( D3D9_D3DXDisassembleShader == 0 )
            FatalErrorMsg(TEXT("Can't get address of D3DXDisassembleShader"));
    }

    g_log.Write(TEXT("d3d9.Direct3DCreate9(%d) ret: 0x%08X\n"),SDKVER, pid3d9);
    return pid3d9;

    */
    return 0;
}


HRESULT __stdcall mine_IDirect3D9_CreateDevice(IDirect3D9 * pid3d9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS * pPresentationParameters, IDirect3DDevice9 ** ppReturnedDeviceInterface){
    static    DWORD fEntry=0;
/*
    PFN_IDirect3D9_CreateDevice e=(PFN_IDirect3D9_CreateDevice)phook_IDirect3D9_Direct3DCreate9->exec;

    //__asm _emit 0xCC

    if( Options.fForceWindowed ){
        pPresentationParameters->Windowed=TRUE;
        pPresentationParameters->FullScreen_RefreshRateInHz=0;
    }

    HRESULT res=e(pid3d9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

    if((*ppReturnedDeviceInterface!=0)&&(fEntry==0)){
        
        fEntry = 1;

        //Hook IDirect3DDevice9::SetTexture
        PFN_IDirect3DDevice9_SetTexture true_SetTexture=(PFN_IDirect3DDevice9_SetTexture)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 65);
        phook_IDirect3DDevice9_SetTexture = new KHook(true_SetTexture, mine_IDirect3DDevice9_SetTexture);

        //Hook IDirect3DDevice9::DrawIndexedPrimitive
        PFN_IDirect3DDevice9_DrawIndexedPrimitive true_DrawIndexedPrimitive=(PFN_IDirect3DDevice9_DrawIndexedPrimitive)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 82);
        phook_IDirect3DDevice9_DrawIndexedPrimitive = new KHook(true_DrawIndexedPrimitive, mine_IDirect3DDevice9_DrawIndexedPrimitive );

        //Hook IDirect3DDevice9::DrawPrimitive
        PFN_IDirect3DDevice9_DrawPrimitive true_DrawPrimitive=(PFN_IDirect3DDevice9_DrawPrimitive)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 81);
        phook_IDirect3DDevice9_DrawPrimitive = new KHook(true_DrawPrimitive, mine_IDirect3DDevice9_DrawPrimitive);

        //Hook IDirect3DDevice9::DrawIndexedPrimitiveUP
        PFN_IDirect3DDevice9_DrawIndexedPrimitiveUP true_DrawIndexedPrimitiveUP=(PFN_IDirect3DDevice9_DrawIndexedPrimitiveUP)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 84);
        phook_IDirect3DDevice9_DrawIndexedPrimitiveUP = new KHook(true_DrawIndexedPrimitiveUP, mine_IDirect3DDevice9_DrawIndexedPrimitiveUP );

        //Hook IDirect3DDevice9::DrawPrimitiveUP
        PFN_IDirect3DDevice9_DrawPrimitiveUP true_DrawPrimitiveUP=(PFN_IDirect3DDevice9_DrawPrimitiveUP)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 83);
        phook_IDirect3DDevice9_DrawPrimitiveUP = new KHook(true_DrawPrimitiveUP, mine_IDirect3DDevice9_DrawPrimitiveUP );

        //Hook IDirect3DDevice9::Present
        PFN_IDirect3DDevice9_Present true_Present=(PFN_IDirect3DDevice9_Present)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 17);
        phook_IDirect3DDevice9_Present = new KHook(true_Present, mine_IDirect3DDevice9_Present);

        //Hook IDirect3DDevice9::SetPixelShader
        PFN_IDirect3DDevice9_SetPixelShader true_SetPixelShader=(PFN_IDirect3DDevice9_SetPixelShader)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 107);
        phook_IDirect3DDevice9_SetPixelShader = new KHook(true_SetPixelShader, mine_IDirect3DDevice9_SetPixelShader);

        //Hook IDirect3DDevice9::SetVertexShader
        PFN_IDirect3DDevice9_SetVertexShader true_SetVertexShader=(PFN_IDirect3DDevice9_SetVertexShader)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 92);
        phook_IDirect3DDevice9_SetVertexShader = new KHook(true_SetVertexShader, mine_IDirect3DDevice9_SetVertexShader);

        //IDirect3DDevice9::GetSwapChain
        PFN_IDirect3DDevice9_GetSwapChain true_GetSwapChain=(PFN_IDirect3DDevice9_GetSwapChain)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 14);
        phook_IDirect3DDevice9_GetSwapChain = new KHook(true_GetSwapChain, mine_IDirect3DDevice9_GetSwapChain);


        //v1.3
        //IDirect3DDevice9::CreateVertexBuffer
        PFN_IDirect3DDevice9_CreateVertexBuffer true_CreateVertexBuffer=(PFN_IDirect3DDevice9_CreateVertexBuffer)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 26);
        phook_IDirect3DDevice9_CreateVertexBuffer = new KHook(true_CreateVertexBuffer, mine_IDirect3DDevice9_CreateVertexBuffer);

        PFN_IDirect3DDevice9_CreateIndexBuffer true_CreateIndexBuffer=(PFN_IDirect3DDevice9_CreateIndexBuffer)GetMethodAddr((DWORD**)*ppReturnedDeviceInterface, 27);
        phook_IDirect3DDevice9_CreateIndexBuffer = new KHook(true_CreateIndexBuffer, mine_IDirect3DDevice9_CreateIndexBuffer);
    }

    g_log.Write(TEXT("IDirect3D9_CreateDevice(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X) ret: 0x%08X\n"), pid3d9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface, res);
    return res;
    */
    return 0;
}


void FrameHandler(){

    /*
    static    DWORD fOutDirCreated=0;
    wchar_t    szDirName[MAX_PATH];

    SHORT KeyPressed = GetAsyncKeyState( Options.MeshsRipKey );

    if((fRip==0)&&(KeyPressed!=0)){
        g_log.Write(TEXT("Frame Start...#%02d\n"), dwFrames);
        //Create dirs
        if(fOutDirCreated++==0){
            lstrcpy(szDirName, szTargetDir);
            lstrcat(szDirName, szRipDir);        //Add "ripper\\" string
            CreateDirectory(szDirName, 0);

            lstrcat(szDirName, szFramesDir);    //Add "frames\\" string
            CreateDirectory(szDirName, 0);
        }
        _stprintf(szDirName, TEXT("%s%s%s%s%02d"), szTargetDir, szRipDir, szFramesDir , szFrame, dwFrames);
        CreateDirectory(szDirName, 0);
        g_log.Write(TEXT("Directory: %s\n"), szDirName);

        fRip=1;    //rip on
        Sleep(1000);
    }
    else if(fRip==1){
        g_log.Write(TEXT("Frame End...\n\n\n"));
        fRip=0;    //rip off

        dwMeshsTextures=0;
        dwMeshsInFrame=0;

        dwMeshsVS=0;
        dwMeshsPS=0;

        dwFrames++;
    }
    */
}



HRESULT __stdcall mine_IDirect3DDevice9_Present(IDirect3DDevice9 *pDev, CONST RECT * pSourceRect, CONST RECT * pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion){
    PFN_IDirect3DDevice9_Present e = (PFN_IDirect3DDevice9_Present)phook_IDirect3DDevice9_Present->GetUnhookedFunc();
    FrameHandler();
//    g_log.Write("IDirect3DDevice9::Present(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n", pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return e(pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}


HRESULT __stdcall mine_IDirect3DDevice9_GetSwapChain(IDirect3DDevice9 *pDev, 
                                                     UINT iSwapChain,
                                                     IDirect3DSwapChain9 ** ppSwapChain)
{
    /*
    static DWORD fNotFirst = 0;
    PFN_IDirect3DDevice9_GetSwapChain    e=(PFN_IDirect3DDevice9_GetSwapChain)phook_IDirect3DDevice9_GetSwapChain->GetUnhookedFunc();
    HRESULT res = e(pDev, iSwapChain, ppSwapChain);

    if(*ppSwapChain && fNotFirst==0){//Hook IDirect3DSwapChain9::Present
        fNotFirst = 1;
        PFN_IDirect3DSwapChain9_Present f=(PFN_IDirect3DSwapChain9_Present)GetMethodAddr((DWORD**)*ppSwapChain, 3);
        phook_IDirect3DSwapChain9_Persent = new KHook(f, mine_IDirect3DSwapChain9_Present);
    }
    return res;
    */
    return 0;
}


HRESULT __stdcall mine_IDirect3DSwapChain9_Present(IDirect3DDevice9 *pDev, 
                                                   CONST RECT * pSourceRect,
                                                   CONST RECT * pDestRect,
                                                   HWND hDestWindowOverride,
                                                   CONST RGNDATA * pDirtyRegion,
                                                   DWORD dwFlags
                                                   )
{
    /*
    PFN_IDirect3DSwapChain9_Present e = (PFN_IDirect3DSwapChain9_Present)phook_IDirect3DSwapChain9_Persent->GetUnhookedFunc();
    FrameHandler();
//    g_log.Write("IDirect3DSwapChain9::Present(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n", pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
    return e(pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
    */
    return 0;
}


HRESULT    __stdcall mine_IDirect3DDevice9_CreateVertexBuffer(IDirect3DDevice9 *pDev, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle){
    PFN_IDirect3DDevice9_CreateVertexBuffer    e=(PFN_IDirect3DDevice9_CreateVertexBuffer)phook_IDirect3DDevice9_CreateVertexBuffer->GetUnhookedFunc();
    //g_log.Write(TEXT("IDirect3DDevice9_CreateVertexBuffer(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n"), pDev, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );

    //Pool = D3DPOOL_MANAGED;//Force MANGED POOL
    Usage &= (~D3DUSAGE_WRITEONLY);
    HRESULT res = e(pDev, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );
    return res;
}


HRESULT    __stdcall mine_IDirect3DDevice9_CreateIndexBuffer(IDirect3DDevice9 *pDev, UINT Length, DWORD Usage, DWORD Format, D3DPOOL Pool,IDirect3DIndexBuffer9  **ppIndexBuffer, HANDLE *pSharedHandle){
    PFN_IDirect3DDevice9_CreateIndexBuffer    e=(PFN_IDirect3DDevice9_CreateIndexBuffer)phook_IDirect3DDevice9_CreateIndexBuffer->GetUnhookedFunc();
    //g_log.Write(TEXT("IDirect3DDevice9_CreateIndexBuffer(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n"), pDev, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );
    //Pool = D3DPOOL_MANAGED;//Force MANGED POOL
    Usage &= (~D3DUSAGE_WRITEONLY);
    HRESULT res = e(pDev, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );
    return res;
}

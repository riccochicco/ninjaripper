
#include "PreComp.h"
#include "KRipper9.h"
#include "KHookMgr.h"


//************************************************************************
// D3D9 Ripper
//************************************************************************

KRipper9*  KRipper9::this_ = NULL;


void KRipper9::FrameStart(){
    FrameTextures.clear();
}


void KRipper9::FrameEnd(){

}



KRipper9::KRipper9( HINSTANCE hD3D9_ ):
hD3D9( hD3D9_ ),
D3DXSaveTextureToFileW_( NULL ),
D3DXDisassembleShader_( NULL ),
hD3D9X( NULL ),
unhSetTexture( NULL ),
unhDrawPrimitiveUP( NULL ),
unh_SetPixelShader( NULL ),
D3DXCompileShader_( NULL ),
unh_SetDepthStencilSurface( NULL )
{
    this_ = this;
    ::InitializeCriticalSection( &cs );
    Init1();
}


KRipper9::~KRipper9()
{
    ::DeleteCriticalSection( &cs );
    this_ = NULL;
}


void KRipper9::Init()
{

    PFN_Direct3DCreate9 true_Direct3DCreate9 =
        (PFN_Direct3DCreate9)GetProcAddress( this_->hD3D9, "Direct3DCreate9" );
    if( !true_Direct3DCreate9 ){
        ::FatalErrorMsg( L"Can't get address of D3D9.Direct3DCreate9()" );
    }

    g_pHookMgr->Hook( true_Direct3DCreate9, Pre_Direct3DCreate9 );
    g_pLog->Write( L"D3D9.Direct3DCreate9() hooked\n" );
}


void KRipper9::Uninit(){

}


IDirect3D9* KRipper9::_Direct3DCreate9( PFN_Direct3DCreate9 e, UINT SDKVER )
{
    g_pLog->Write( L"AAAAAAA\n");

    if( !hD3D9X )
    {
        //Load helper dll
        HMODULE hMod = ::GetModuleHandle( L"d3dx9_36.dll" );
        if( hMod ){
            hD3D9X = (HINSTANCE)hMod;
        }
        else{
            std::wstring RipperDir = g_pIntruder->GetIntruderDir();
            RipperDir += L"d3dx9_36.dll";

            hD3D9X = ::LoadLibrary( RipperDir.c_str() );
            if( !hD3D9X ){
                ::FatalErrorMsg( L"d3dx9_36.dll load error" );
            }
        }

        D3DXSaveTextureToFileW_=(PFN_D3DXSaveTextureToFileW)GetProcAddress( hD3D9X, "D3DXSaveTextureToFileW" );
        if( !D3DXSaveTextureToFileW_ ){
            ::FatalErrorMsg( L"Can't get address of D3DXSaveTextureToFileW" );
        }

        D3DXDisassembleShader_ = (PFN_D3DXDisassembleShader)GetProcAddress( hD3D9X, "D3DXDisassembleShader" );
        if( !D3DXDisassembleShader_ ){
            ::FatalErrorMsg( L"Can't get address of D3DXDisassembleShader" );
        }

        D3DXCompileShader_ = (PFN_D3DXCompileShader)GetProcAddress( hD3D9X, "D3DXCompileShader" );
        if( !D3DXCompileShader_ ){
            ::FatalErrorMsg( L"Can't get address of D3DXCompileShader" );
        }

    }

    IDirect3D9* pid3d9 = e( SDKVER );
    g_pLog->Write( L"D3D9.Direct3DCreate9(%d) ret: 0x%p\n", SDKVER, pid3d9);

    if( !pid3d9 ){//DX error. Nothing to hook. Return
        return pid3d9;
    }

    PFN_IDirect3D9_CreateDevice true_CreateDevice=
        ( PFN_IDirect3D9_CreateDevice )GetMethodAddr( pid3d9, 16 );

    g_pHookMgr->Hook( true_CreateDevice, Pre_IDirect3D9_CreateDevice );

    return pid3d9;
}




HRESULT KRipper9::_IDirect3D9_CreateDevice(
    PFN_IDirect3D9_CreateDevice e,
    IDirect3D9* pid3d9,
    UINT Adapter, 
    D3DDEVTYPE DeviceType, 
    HWND hFocusWindow, 
    DWORD BehaviorFlags, 
    D3DPRESENT_PARAMETERS* pPresentationParameters, 
    IDirect3DDevice9** ppReturnedDeviceInterface
    )
{
    HRESULT res = e(pid3d9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
    if ( FAILED(res) || !(*ppReturnedDeviceInterface) )
    {//DX return error. Nothing to do
        return res;
    }

    g_pLog->Write( L"IDirect3D9_CreateDevice(0x%p, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X) ret: 0x%08X\n", pid3d9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface, res);

    HOOK( IDirect3DDevice9_SetTexture, 65, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_SetTexture )
    {
        unhSetTexture = (PFN_IDirect3DDevice9_SetTexture)pHook_IDirect3DDevice9_SetTexture->GetUnhooked();
    }

    HOOK( IDirect3DDevice9_DrawPrimitiveUP, 83, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_DrawPrimitiveUP )
    {
        unhDrawPrimitiveUP = (PFN_IDirect3DDevice9_DrawPrimitiveUP)pHook_IDirect3DDevice9_DrawPrimitiveUP->GetUnhooked();
    }

    HOOK( IDirect3DDevice9_DrawIndexedPrimitive, 82, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice9_CreateVertexBuffer, 26, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice9_CreateIndexBuffer, 27, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice9_Present, 17, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice9_GetSwapChain, 14, *ppReturnedDeviceInterface );
    
    HOOK( IDirect3DDevice9_DrawIndexedPrimitiveUP, 84, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice9_DrawPrimitive, 81, *ppReturnedDeviceInterface );

    HOOK( IDirect3DDevice9_SetPixelShader, 107, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_SetPixelShader )
    {
        unh_SetPixelShader = (PFN_IDirect3DDevice9_SetPixelShader)pHook_IDirect3DDevice9_SetPixelShader->GetUnhooked();
    }

/*
    HOOK( IDirect3DDevice9_SetRenderState, 57, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_SetRenderState )
    {
        unh_SetRenderState = (PFN_IDirect3DDevice9_SetRenderState)pHook_IDirect3DDevice9_SetRenderState->GetUnhooked();
    }


    HOOK( IDirect3DDevice9_SetSamplerState, 69, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_SetSamplerState )
    {
        unh_SetSamplerState = (PFN_IDirect3DDevice9_SetSamplerState)pHook_IDirect3DDevice9_SetSamplerState->GetUnhooked();
    }


    HOOK( IDirect3DDevice9_SetTextureStageState, 67, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_SetTextureStageState )
    {
        unh_SetTextureStageState = (PFN_IDirect3DDevice9_SetTextureStageState)pHook_IDirect3DDevice9_SetTextureStageState->GetUnhooked();
    }
*/

    HOOK( IDirect3DDevice9_SetDepthStencilSurface, 39, *ppReturnedDeviceInterface );
    if( pHook_IDirect3DDevice9_SetDepthStencilSurface )
    {
        unh_SetDepthStencilSurface = (PFN_IDirect3DDevice9_SetDepthStencilSurface)pHook_IDirect3DDevice9_SetDepthStencilSurface->GetUnhooked();
    }


    HOOK ( IDirect3DDevice9_SetGammaRamp, 21, *ppReturnedDeviceInterface);
    if (pHook_IDirect3DDevice9_SetGammaRamp)
    {
        unh_SetGammaRamp = (PFN_IDirect3DDevice9_SetGammaRamp)pHook_IDirect3DDevice9_SetGammaRamp->GetUnhooked();
    }

    return res;
}



HRESULT    KRipper9::_IDirect3DDevice9_CreateVertexBuffer(
    PFN_IDirect3DDevice9_CreateVertexBuffer e, 
    IDirect3DDevice9 *pDev, 
    UINT Length, 
    DWORD Usage, 
    DWORD FVF, 
    D3DPOOL Pool,
    IDirect3DVertexBuffer9 **ppVertexBuffer, 
    HANDLE *pSharedHandle
    )
{
    Usage &= (~D3DUSAGE_WRITEONLY);
    return e(pDev, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );
}


HRESULT    KRipper9::_IDirect3DDevice9_CreateIndexBuffer(
    PFN_IDirect3DDevice9_CreateIndexBuffer e,
    IDirect3DDevice9 *pDev, 
    UINT Length, 
    DWORD Usage, 
    DWORD Format, 
    D3DPOOL Pool,
    IDirect3DIndexBuffer9  **ppIndexBuffer, 
    HANDLE *pSharedHandle
    )
{
    Usage &= (~D3DUSAGE_WRITEONLY);
    return e(pDev, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );
}




HRESULT KRipper9::_IDirect3DDevice9_Present(
    PFN_IDirect3DDevice9_Present e, 
    IDirect3DDevice9 *pDev, 
    CONST RECT * pSourceRect, 
    CONST RECT * pDestRect, 
    HWND hDestWindowOverride, 
    CONST RGNDATA *pDirtyRegion
    )
{
    g_pIntruder->FrameHandler( this_ );
//    g_pLog->Write("IDirect3DDevice9::Present(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n", pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return e(pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}




HRESULT KRipper9::_IDirect3DDevice9_GetSwapChain(
    PFN_IDirect3DDevice9_GetSwapChain e,
    IDirect3DDevice9 *pDev, 
    UINT iSwapChain,
    IDirect3DSwapChain9 ** ppSwapChain
    )
{
    HRESULT res = e( pDev, iSwapChain, ppSwapChain );
    if( *ppSwapChain ){
        HOOK( IDirect3DSwapChain9_Present, 3, *ppSwapChain );
        g_pLog->Write( L"IDirect3DSwapChain9_Present hooked\n" );
    }
    return res;
}



HRESULT KRipper9::_IDirect3DSwapChain9_Present(
    PFN_IDirect3DSwapChain9_Present e,
    IDirect3DSwapChain9 *pSwapChain, 
    CONST RECT * pSourceRect,
    CONST RECT * pDestRect,
    HWND hDestWindowOverride,
    CONST RGNDATA * pDirtyRegion,
    DWORD dwFlags
)
{
    g_pIntruder->FrameHandler( this_ );
//    g_log.Write("IDirect3DSwapChain9::Present(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n", pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
    return e( pSwapChain, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags );
}


KDumper::EPrimitiveType KRipper9::D3DPRIMITIVETYPE_to_EPrimitiveType( D3DPRIMITIVETYPE pt ){
    switch( pt ){

    case D3DPT_TRIANGLELIST:
        return KDumper::eTriangleList;

    case D3DPT_TRIANGLESTRIP:
        return KDumper::eTriangleStrip;

    default:
        return KDumper::eUnknownPrimitiveType;
    }
}


void KRipper9::D3DDECLUSAGE_to_UsageSemantic( DWORD usage, char* pOut, DWORD BufSize ){

    switch( usage ){
    case D3DDECLUSAGE_POSITION:
        ::StrCopy( pOut, BufSize, "POSITION" );
        break;

    case D3DDECLUSAGE_BLENDWEIGHT:
        ::StrCopy( pOut, BufSize, "BLENDWEIGHT" );
        break;

    case D3DDECLUSAGE_BLENDINDICES:
        ::StrCopy( pOut, BufSize, "BLENDINDICES" );
        break;

    case D3DDECLUSAGE_NORMAL:
        ::StrCopy( pOut, BufSize, "NORMAL" );
        break;

    case D3DDECLUSAGE_PSIZE:
        ::StrCopy( pOut, BufSize, "PSIZE" );
        break;

    case D3DDECLUSAGE_TEXCOORD:
        ::StrCopy( pOut, BufSize, "TEXCOORD" );
        break;

    case D3DDECLUSAGE_TANGENT:
        ::StrCopy( pOut, BufSize, "TANGENT" );
        break;

    case D3DDECLUSAGE_BINORMAL:
        ::StrCopy( pOut, BufSize, "BINORMAL" );
        break;

    case D3DDECLUSAGE_TESSFACTOR:
        ::StrCopy( pOut, BufSize, "TESSFACTOR" );
        break;

    case D3DDECLUSAGE_POSITIONT:
        ::StrCopy( pOut, BufSize, "POSITIONT" );
        break;

    case D3DDECLUSAGE_COLOR:
        ::StrCopy( pOut, BufSize, "COLOR" );
        break;

    case D3DDECLUSAGE_FOG:
        ::StrCopy( pOut, BufSize, "FOG" );
        break;

    case D3DDECLUSAGE_DEPTH:
        ::StrCopy( pOut, BufSize, "DEPTH" );
        break;

    case D3DDECLUSAGE_SAMPLE:
        ::StrCopy( pOut, BufSize, "SAMPLE" );
        break;

    default:
        ::StrCopy( pOut, BufSize, "UNKNOWN" );
    }
}


//Convert from d3d9 to ripper type enum
KDumper::EInputType KRipper9::D3DDECLTYPE_to_EInputType( BYTE t ){

    switch( t ){

    case D3DDECLTYPE_FLOAT1:
        return KDumper::eR32_FLOAT;

    case D3DDECLTYPE_FLOAT2:
        return KDumper::eR32G32_FLOAT;

    case D3DDECLTYPE_FLOAT3:
        return KDumper::eR32G32B32_FLOAT;

    case D3DDECLTYPE_FLOAT4:
        return KDumper::eR32G32B32A32_FLOAT;

    case D3DDECLTYPE_D3DCOLOR:// 4 BYTES type
        return KDumper::eR8G8B8A8_UINT;

    case D3DDECLTYPE_UBYTE4:
        return KDumper::eR8G8B8A8_UINT;

    case D3DDECLTYPE_SHORT2:
        return KDumper::eR16G16_SINT;

    case D3DDECLTYPE_SHORT4:
        return KDumper::eR16G16B16A16_SINT;

    case D3DDECLTYPE_UBYTE4N:
        return KDumper::eR8G8B8A8_UNORM;

    case D3DDECLTYPE_SHORT2N:
        return KDumper::eR16G16_SNORM;

    case D3DDECLTYPE_SHORT4N:
        return KDumper::eR16G16B16A16_SNORM;

    case D3DDECLTYPE_USHORT2N:
        return KDumper::eR16G16_UNORM;

    case D3DDECLTYPE_USHORT4N:
        return KDumper::eR16G16B16A16_UNORM;

    case D3DDECLTYPE_UDEC3:
        return KDumper::eUDEC3;

    case D3DDECLTYPE_DEC3N:
        return KDumper::eDEC3N;

    case D3DDECLTYPE_FLOAT16_2:
        return KDumper::eR16G16_FLOAT;

    case D3DDECLTYPE_FLOAT16_4:
        return KDumper::eR16G16B16A16_FLOAT;

    default:
        return KDumper::eUnknownInputType;
    }

}



HRESULT KRipper9::GetVertexDeclarations( 
    IDirect3DDevice9 *pDev,
    KDumper::KInputVertexDeclaration&  InputDecl,
    KDumper::KOutputVertexDeclaration& OutputDecl
    )
{
    HRESULT hr;

    IDirect3DVertexDeclaration9* pVertexDeclaration = NULL;
    UINT numElements = 0;
    hr = pDev->GetVertexDeclaration( &pVertexDeclaration );
    if( FAILED( hr ) ){
        g_pLog->Write( L"IDirect3DDevice9::GetVertexDeclaration() Error: 0x%08X\n", hr );
        return hr;
    }

    if( !pVertexDeclaration ){
        g_pLog->Write( L"IDirect3DVertexDeclaration9* == NULL Error\n" );
        return E_VERTEXDECL_NOT_SET;//Vertex declaration not set
    }

    pVertexDeclaration->GetDeclaration( NULL, &numElements );

    KD3D9VertexDeclaration D3DDecl;
    D3DDecl.resize( numElements );

    //Get declaration and convert to Ripper declaration type
    pVertexDeclaration->GetDeclaration( &D3DDecl[0], &numElements );


    for( UINT i = 0; i < numElements; i++ ){
        KDumper::KInputVertexElement InputElement;
        D3DVERTEXELEMENT9 D3DElem = D3DDecl[ i ];
        if( IsEndDecl( &D3DElem ) ){
            break;
        }

        Dump_D3DVERTEXELEMENT9_2Log( D3DElem );

        InputElement.Stream       = D3DElem.Stream;
        InputElement.SemanticIndex= D3DElem.UsageIndex;
        InputElement.Offset       = D3DElem.Offset;
        InputElement.Type         = D3DDECLTYPE_to_EInputType( D3DElem.Type );
        D3DDECLUSAGE_to_UsageSemantic( D3DElem.Usage, InputElement.UsageSemantic, SEMANTIC_LEN );
        InputElement.Size = KDumper::GetInputTypeSize( InputElement.Type );

        InputDecl.Decl.push_back( InputElement );
    }

    SAFE_RELEASE( pVertexDeclaration );

    hr = KDumper::CreateKOutputVertexDeclaration( InputDecl, OutputDecl );
    return hr;
}



//Save last used pixel shader. On GeForce9800+  IDirect3DDevice9::GetPixelShader() failed
HRESULT KRipper9::_IDirect3DDevice9_SetPixelShader(
    PFN_IDirect3DDevice9_SetPixelShader e, 
    IDirect3DDevice9 *pDev, 
    IDirect3DPixelShader9* pPS
    )
{
    unh_SetPixelShader = e;//Save last

    HRESULT hr = e( pDev, pPS );

    if( SUCCEEDED( hr ) ){
        LastPS.Set( pPS );
    }
    return hr;
}



void KRipper9::Init1()
{
    TState < D3DRENDERSTATETYPE > InitialRsArr[ RS_SIZE ] = 
    {
        { D3DRS_POINTSPRITEENABLE, FALSE },
        { D3DRS_POINTSCALEENABLE, FALSE },
        { D3DRS_CULLMODE, D3DCULL_NONE },
        { D3DRS_FOGTABLEMODE, D3DFOG_NONE },
        { D3DRS_RANGEFOGENABLE, FALSE },
        { D3DRS_FOGVERTEXMODE, D3DFOG_NONE },
        { D3DRS_CLIPPING, FALSE },
        { D3DRS_LIGHTING, FALSE },
        { D3DRS_LOCALVIEWER, FALSE },
        { D3DRS_VERTEXBLEND, D3DVBF_DISABLE },
        { D3DRS_CLIPPLANEENABLE, 0 },
        { D3DRS_MULTISAMPLEANTIALIAS, FALSE },
        { D3DRS_MULTISAMPLEMASK, 0xffffffff },
        { D3DRS_PATCHEDGESTYLE, D3DPATCHEDGE_DISCRETE },
        { D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE },
        { D3DRS_ENABLEADAPTIVETESSELLATION, FALSE },
        { D3DRS_ALPHABLENDENABLE, FALSE },
        { D3DRS_COLORWRITEENABLE, 0xF },
        { D3DRS_ALPHATESTENABLE, FALSE },
        { D3DRS_STENCILENABLE, 0 },
        { D3DRS_SEPARATEALPHABLENDENABLE, 0 },
        { D3DRS_ZENABLE, FALSE },
        { D3DRS_ZWRITEENABLE, FALSE },
        { D3DRS_DITHERENABLE, FALSE },
        { D3DRS_SPECULARENABLE, FALSE },
        { D3DRS_FOGENABLE, FALSE },
        { D3DRS_RANGEFOGENABLE, FALSE },
        { D3DRS_SCISSORTESTENABLE, FALSE },
        { D3DRS_ANTIALIASEDLINEENABLE, FALSE },
        { D3DRS_SRGBWRITEENABLE, 0 },
        { D3DRS_WRAP0, 0 },
        { D3DRS_DEPTHBIAS, 0 },
        { D3DRS_SLOPESCALEDEPTHBIAS, 0 },
        { D3DRS_FILLMODE, D3DFILL_SOLID },
        { D3DRS_SHADEMODE, D3DSHADE_GOURAUD }
    };
    for( int i = 0; i < RS_SIZE; i++ ){
        RenderStates[ i ] = InitialRsArr[ i ];
    }



    TState < D3DSAMPLERSTATETYPE > InitialSsArr[ SS_SIZE ] = 
    {
        { D3DSAMP_DMAPOFFSET, 256 },
        { D3DSAMP_MAGFILTER, D3DTEXF_POINT },
        { D3DSAMP_MINFILTER, D3DTEXF_POINT },
        { D3DSAMP_MIPFILTER, D3DTEXF_POINT },
        { D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP },
        { D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP },
        { D3DSAMP_ADDRESSW,  D3DTADDRESS_WRAP },
        { D3DSAMP_MAXANISOTROPY, 0x1 },
        { D3DSAMP_MIPMAPLODBIAS, 0 },
        { D3DSAMP_BORDERCOLOR, 0 }
    };
    for( int i = 0; i < SS_SIZE; i++ ){
        SamplerStates[ i ] = InitialSsArr[ i ];
    }



    TState < D3DTEXTURESTAGESTATETYPE > InitialTssArr[ TSS_SIZE ] =
    {
        { D3DTSS_TEXCOORDINDEX, 0 },
        { D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE },
        { D3DTSS_COLOROP,   D3DTOP_MODULATE },
        { D3DTSS_COLORARG1, D3DTA_TEXTURE },
        { D3DTSS_COLORARG2, D3DTA_CURRENT },
    };
    for( int i = 0; i < TSS_SIZE; i++ ){
        TextureStageStates[ i ] = InitialTssArr[ i ];
    }


}



/*
HRESULT KRipper9::_IDirect3DDevice9_SetRenderState(
    PFN_IDirect3DDevice9_SetRenderState e, 
    IDirect3DDevice9 *pDev, 
    D3DRENDERSTATETYPE State, 
    DWORD Value
    )
{
    unh_SetRenderState = e;

    HRESULT hr = e( pDev, State, Value );
    
    //g_pLog->Write( L"IDirect3DDevice9_SetRenderState( %s, 0x%08X )\n", D3DRENDERSTATETYPE_2Str( State ), Value );
    
    return hr;
}



HRESULT KRipper9::_IDirect3DDevice9_SetSamplerState(
    PFN_IDirect3DDevice9_SetSamplerState e, 
    IDirect3DDevice9 *pDev, 
    DWORD Sampler,
    D3DSAMPLERSTATETYPE Type,
    DWORD Value
    )
{
    unh_SetSamplerState = e;

    HRESULT hr = e( pDev, Sampler, Type, Value );

    //g_pLog->Write( L"IDirect3DDevice9_SetSamplerState( 0x%08X, %s, 0x%08X )\n", Sampler, D3DSAMPLERSTATETYPE_2Str( Type ), Value );

    return hr;
}


HRESULT KRipper9::_IDirect3DDevice9_SetTextureStageState(
    PFN_IDirect3DDevice9_SetTextureStageState e, 
    IDirect3DDevice9 *pDev, 
    DWORD Stage,
    D3DTEXTURESTAGESTATETYPE Type,
    DWORD Value
    )
{
    unh_SetTextureStageState = e;

    HRESULT hr = e( pDev, Stage, Type, Value );

    //g_pLog->Write( L"IDirect3DDevice9_SetTextureStageState( 0x%08X, %s, 0x%08X )\n", Stage, D3DTEXTURESTAGESTATETYPE_2Str( Type ), Value );

    return hr;
}
*/


HRESULT KRipper9::_IDirect3DDevice9_SetDepthStencilSurface(
    PFN_IDirect3DDevice9_SetDepthStencilSurface e, 
    IDirect3DDevice9 *pDev, 
    IDirect3DSurface9* pDsSurface
    )
{
    unh_SetDepthStencilSurface = e;

    HRESULT hr = e( pDev, pDsSurface );

    if( SUCCEEDED( hr ) ){
        LastDepthStencilSurface.Set( pDsSurface );
    }
    return hr;
}


void KRipper9::_IDirect3DDevice9_SetGammaRamp(
    PFN_IDirect3DDevice9_SetGammaRamp e,
    IDirect3DDevice9* pDev,
    UINT  iSwapChain,
    DWORD Flags,
    const D3DGAMMARAMP* pRamp
    )
{
    unh_SetGammaRamp = e;

    e(pDev, iSwapChain, Flags, pRamp);

    GammaHelper gh;
    gh.swapChain = iSwapChain;
    gh.flags = Flags;
    gh.gammaRamp = *pRamp;
    lastGamma.Set(gh);

}


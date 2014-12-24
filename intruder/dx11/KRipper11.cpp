
#include "PreComp.h"
#include "KRipper11.h"
#include "KHookMgr.h"

#pragma comment( lib, "winmm.lib" )


//************************************************************************
// D3D11 Ripper
//************************************************************************

//    __asm _emit 0xeb
//    __asm _emit 0xfe

KRipper11*  KRipper11::this_ = NULL;//'this'


KRipper11::KRipper11( HINSTANCE hD3D11_ ):
hD3D11( hD3D11_ ),
hD3DX( NULL ),
D3DX11SaveTextureToFileW_( NULL ),
D3DX11CompileFromMemory_( NULL ),
unhDrawIndexed( NULL ),
unhPSSetShaderResources( NULL )
{
    this_ = this;
    ::InitializeCriticalSection( &cs );
}


KRipper11::~KRipper11(){
    this_ = NULL;
    ::DeleteCriticalSection( &cs );
}


void KRipper11::FrameStart(){
    FrameTextures.clear();
}


HRESULT KRipper11::_IDXGIFactory_CreateSwapChain(
    PFN_IDXGIFactory_CreateSwapChain e,
    IDXGIFactory* pFactory,
    IUnknown *pDevice,
    DXGI_SWAP_CHAIN_DESC *pDesc,
    IDXGISwapChain **ppSwapChain
    )
{
    g_pLog->Write( L"IDXGIFactory_CreateSwapChain()\n" );
    HRESULT hr = e( pFactory, pDevice, pDesc, ppSwapChain );
    HookSwapChain( ppSwapChain );
    return hr;
}


HRESULT KRipper11::_CreateDXGIFactory(
    PFN_CreateDXGIFactory e,
    void* refiid,
    void** ppFactory
    )
{
    g_pLog->Write( L"DXGI.CreateDXGIFactory()\n" );
    HRESULT hr = e( refiid, ppFactory );
    if( SUCCEEDED( hr ) ){
        IDXGIFactory** ppIDXGI = (IDXGIFactory**)ppFactory;
        HOOK( IDXGIFactory_CreateSwapChain, 10, *ppIDXGI );
    }
    return hr;
}


HRESULT KRipper11::_CreateDXGIFactory1(
    PFN_CreateDXGIFactory1 e,
    void* refiid,
    void** ppFactory
    )
{
    g_pLog->Write( L"DXGI.CreateDXGIFactory1()\n" );
    HRESULT hr = e( refiid, ppFactory );
    if( SUCCEEDED( hr ) ){
        IDXGIFactory1** ppIDXGI = (IDXGIFactory1**)ppFactory;
        HOOK( IDXGIFactory_CreateSwapChain, 10, *ppIDXGI );
    }
    return hr;
}


void KRipper11::Init(){

    //Set hook to D3D11CreateDeviceAndSwapChain()
    PFN_D3D11CreateDeviceAndSwapChain true_D3D11CreateDeviceAndSwapChain = 
        (PFN_D3D11CreateDeviceAndSwapChain)GetProcAddress( this_->hD3D11, "D3D11CreateDeviceAndSwapChain" );

    if( !true_D3D11CreateDeviceAndSwapChain ){
        ::FatalErrorMsg( L"Can't get address of D3D11.D3D11CreateDeviceAndSwapChain()" );
    }
    g_pLog->Write( L"D3D11.D3D11CreateDeviceAndSwapChain() hooked\n" );
    g_pHookMgr->Hook( true_D3D11CreateDeviceAndSwapChain, Pre_D3D11CreateDeviceAndSwapChain );



    //Set hook to D3D11CreateDevice()
    PFN_D3D11CreateDevice true_D3D11CreateDevice = 
        (PFN_D3D11CreateDevice)GetProcAddress( this_->hD3D11, "D3D11CreateDevice" );
    if( !true_D3D11CreateDevice ){
        ::FatalErrorMsg( L"Can't get address of D3D11.D3D11CreateDevice()" );
    }
    g_pLog->Write( L"D3D11.D3D11CreateDevice() hooked\n" );
    g_pHookMgr->Hook( true_D3D11CreateDevice, Pre_D3D11CreateDevice );


    HMODULE hDXGI = ::GetModuleHandle( L"dxgi.dll" );
    if( !hDXGI ){
        hDXGI = ::LoadLibrary( L"dxgi.dll" );
    }
        
    if( hDXGI ){

        //Set hook to DXGI.CreateDXGIFactory()
        PFN_CreateDXGIFactory true_CreateDXGIFactory = 
            (PFN_CreateDXGIFactory)GetProcAddress( hDXGI, "CreateDXGIFactory" );
        if( !true_CreateDXGIFactory ){
            ::FatalErrorMsg( L"Can't get address of DXGI.CreateDXGIFactory()" );
        }
        g_pLog->Write( L"DXGI.CreateDXGIFactory() hooked\n" );
        g_pHookMgr->Hook( true_CreateDXGIFactory, Pre_CreateDXGIFactory );


        //Set hook to DXGI.CreateDXGIFactory1()
        PFN_CreateDXGIFactory1 true_CreateDXGIFactory1 = 
            (PFN_CreateDXGIFactory1)GetProcAddress( hDXGI, "CreateDXGIFactory1" );
        if( !true_CreateDXGIFactory1 ){
            ::FatalErrorMsg( L"Can't get address of DXGI.CreateDXGIFactory1()" );
        }
        g_pLog->Write( L"DXGI.CreateDXGIFactory1() hooked\n" );
        g_pHookMgr->Hook( true_CreateDXGIFactory1, Pre_CreateDXGIFactory1 );

    }
    else{
        ::FatalErrorMsg( L"dxgi.dll load failed" );
    }

}


void KRipper11::Uninit()
{

}


void KRipper11::HelperDllsInit(){

    if( !hD3DX ){
        HMODULE hMod = GetModuleHandle( L"d3dx11_43.dll" );
        if( hMod ){
            hD3DX = (HINSTANCE)hMod;
        }
        else{
            std::wstring RipperDir = g_pIntruder->GetIntruderDir();
            RipperDir += L"d3dx11_43.dll";

            hD3DX = LoadLibrary( RipperDir.c_str() );
            if( !hD3DX ){
                FatalErrorMsg( L"d3dx11_43.dll load error" );
            }
        }

        D3DX11SaveTextureToFileW_ = ( PFN_D3DX11SaveTextureToFileW )GetProcAddress( hD3DX, "D3DX11SaveTextureToFileW" );
        if( !D3DX11SaveTextureToFileW_ ){
            FatalErrorMsg( L"Can't get address of D3DX11.D3DXSaveTextureToFileW" );
        }

        D3DX11CompileFromMemory_ = (PFN_D3DX11CompileFromMemory)GetProcAddress( hD3DX, "D3DX11CompileFromMemory" );
        if( !D3DX11CompileFromMemory_ ){
            FatalErrorMsg( L"Can't get address of D3DX11.D3DX11CompileFromMemory" );
        }
    }

}



//Hook ID3D11DeviceContext Interface
void KRipper11::HookDeviceContext( ID3D11DeviceContext** ppImmediateContext ){
    
    //Check for NULL pointers in params
    if( !ppImmediateContext ){
        return;
    }
    if( !(*ppImmediateContext ) ){
        return;
    }

    HOOK( ID3D11DeviceContext_Draw, 13, *ppImmediateContext );
    HOOK( ID3D11DeviceContext_DrawAuto, 38, *ppImmediateContext );

    HOOK( ID3D11DeviceContext_DrawIndexed, 12, *ppImmediateContext );
    if( pHook_ID3D11DeviceContext_DrawIndexed ){
        unhDrawIndexed = (PFN_ID3D11DeviceContext_DrawIndexed)pHook_ID3D11DeviceContext_DrawIndexed->GetUnhooked();
    }

    HOOK( ID3D11DeviceContext_DrawIndexedInstanced,         20, *ppImmediateContext );
    HOOK( ID3D11DeviceContext_DrawIndexedInstancedIndirect, 39, *ppImmediateContext );
    HOOK( ID3D11DeviceContext_DrawInstanced,                21, *ppImmediateContext );

    //One addr of two funcs. Same handler must be!!!
    //PFN_ID3D11DeviceContext_DrawInstancedIndirect true_DrawInstancedIndirect = 
    //    ( PFN_ID3D11DeviceContext_DrawInstancedIndirect )GetMethodAddr1( *ppImmediateContext, 40 );
    //this_->pHookMgr->AddHook( true_DrawInstancedIndirect, mine_ID3D11DeviceContext_DrawInstancedIndirect, *ppImmediateContext );


    //--------------------------------------------
    //Forced to save texture handling
    //--------------------------------------------
    HOOK( ID3D11DeviceContext_PSSetShaderResources, 8, *ppImmediateContext );
    if( pHook_ID3D11DeviceContext_PSSetShaderResources ){
        unhPSSetShaderResources = (PFN_ID3D11DeviceContext_PSSetShaderResources)pHook_ID3D11DeviceContext_PSSetShaderResources->GetUnhooked();
    }

//    HOOK( ID3D11DeviceContext_VSSetShaderResources, 25, *ppImmediateContext );
//    HOOK( ID3D11DeviceContext_GSSetShaderResources, 31, *ppImmediateContext );

}


void KRipper11::HookDevice( ID3D11Device** ppDev ){
    if( !ppDev ){
        return;
    }
    if( !( *ppDev ) ){
        return;
    }


//    PFN_ID3D11Device_CreateInputLayout true_CreateInputLayout = 
//        ( PFN_ID3D11Device_CreateInputLayout )GetMethodAddr1( *ppDev, 11 );
//    g_pHookMgr->Hook( true_CreateInputLayout, Pre_ID3D11Device_CreateInputLayout );

    HOOK( ID3D11Device_CreateInputLayout, 11, *ppDev );
}


void KRipper11::HookSwapChain( IDXGISwapChain** ppSwapChain ){
    if( !ppSwapChain ){
        return;
    }
    if( !( *ppSwapChain ) ){
        return;
    }

//    PFN_IDXGISwapChain_Present true_Present = 
//        ( PFN_IDXGISwapChain_Present )GetMethodAddr1( *ppSwapChain, 8 );
//    g_pHookMgr->Hook( true_Present, Pre_IDXGISwapChain_Present );

    HOOK( IDXGISwapChain_Present, 8, *ppSwapChain );
}


HRESULT KRipper11::_D3D11CreateDeviceAndSwapChain(
    PFN_D3D11CreateDeviceAndSwapChain e,
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext )
{
    HRESULT hr;

    HelperDllsInit();
    
    hr = e(//D3D11CreateDeviceAndSwapChain(...)
        pAdapter,
        DriverType,
        Software,
        Flags,
        pFeatureLevels,
        FeatureLevels,
        SDKVersion,
        pSwapChainDesc,
        ppSwapChain,
        ppDevice,
        pFeatureLevel,
        ppImmediateContext
        );

    g_pLog->Write( L"D3D11.D3D11CreateDeviceAndSwapChain() ret: 0x%08X\n", hr );

    if( SUCCEEDED( hr ) ){
        
        g_pLog->Write( L"DriverType  : %s\nFeatureLevel: %s\n\n", 
            D3D_DRIVER_TYPE_2_Str( DriverType ),
            (pFeatureLevel)?D3D_FEATURE_LEVEL_2_Str( *pFeatureLevel ):L"NULL"
            );


        HookDeviceContext( ppImmediateContext );
        HookSwapChain( ppSwapChain );
        HookDevice( ppDevice );
    }

    return hr;
}



HRESULT KRipper11::_D3D11CreateDevice(
    PFN_D3D11CreateDevice e,
    IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device **ppDevice,
    D3D_FEATURE_LEVEL *pFeatureLevel,
    ID3D11DeviceContext **ppImmediateContext
    )
{
    HRESULT hr;
    HelperDllsInit();

    hr = e( 
        pAdapter,
        DriverType,
        Software,
        Flags,
        pFeatureLevels,
        FeatureLevels,
        SDKVersion,
        ppDevice,
        pFeatureLevel,
        ppImmediateContext
        );

    g_pLog->Write( L"D3D11.D3D11CreateDevice() ret: 0x%08X\n", hr );

    if( SUCCEEDED( hr ) ){

        g_pLog->Write( L"DriverType  : %s\nFeatureLevel: %s\n\n", 
            D3D_DRIVER_TYPE_2_Str( DriverType ),
            (pFeatureLevel)?D3D_FEATURE_LEVEL_2_Str( *pFeatureLevel ):L"NULL"
            );

        HookDeviceContext( ppImmediateContext );
        HookDevice( ppDevice );
    }

    return hr;
}


HRESULT KRipper11::_IDXGISwapChain_Present(
    PFN_IDXGISwapChain_Present e,
    IDXGISwapChain* pSwapChain,
    UINT SyncInterval,
    UINT Flags
    )
{
    g_pIntruder->FrameHandler( this );
    //g_pLog->Write( L"IDXGISwapChain_Present( 0x%p, %d, %d )\n", pSwapChain, SyncInterval, Flags );
    return e( pSwapChain, SyncInterval, Flags );
}


HRESULT KRipper11::_ID3D11Device_CreateInputLayout(
    PFN_ID3D11Device_CreateInputLayout e,
    ID3D11Device* pDev,
    const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
    UINT NumElements,
    const void *pShaderBytecodeWithInputSignature,
    SIZE_T BytecodeLength,
    ID3D11InputLayout **ppInputLayout
    )
{
    HRESULT hr;

    hr = e( pDev, pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout );
    if( SUCCEEDED( hr ) ){
        
        ::EnterCriticalSection( &cs );

        KInputLayoutMap::iterator p = InputLayoutMap.find( *ppInputLayout );
        if( p != InputLayoutMap.end() ){//Element exist - erase old. Prepare to add new
            InputLayoutMap.erase( p );
        }


        KD3D11VertexDeclaration ElementsVec;
        
//        g_pLog->Write( L"ID3D11Device_CreateInputLayout()\n---------------\n" );

        for( UINT i = 0; i < NumElements; i++ ){
            D3D11_INPUT_ELEMENT_DESC Elem = pInputElementDescs[ i ];
            
            KD3D11InputElement D3D11Elem;
            ::StrCopy( D3D11Elem.SemanticName, SEMANTIC_LEN, Elem.SemanticName );
            D3D11Elem.AlignedByteOffset    = Elem.AlignedByteOffset;
            D3D11Elem.Format               = Elem.Format;
            D3D11Elem.InputSlot            = Elem.InputSlot;
            D3D11Elem.InputSlotClass       = Elem.InputSlotClass;
            D3D11Elem.InstanceDataStepRate = Elem.InstanceDataStepRate;
            D3D11Elem.SemanticIndex        = Elem.SemanticIndex;
            ElementsVec.push_back( D3D11Elem );//Save Element

/*
            std::string SemanticName = Elem.SemanticName;
            g_pLog->Write( L"Element: %s\n", StringToWString( SemanticName ).c_str() );
            g_pLog->Write( L"Index: %d\n", Elem.SemanticIndex );
            g_pLog->Write( L"Format : %s\n", DXGI_FORMAT_2_Str( Elem.Format ) );
            g_pLog->Write( L"InputSlot: %d\n", Elem.InputSlot );
            g_pLog->Write( L"AlignOffs: %d\n", Elem.AlignedByteOffset );
            g_pLog->Write( L"InputSlotClass: %d\n", Elem.InputSlotClass );
            g_pLog->Write( L"InstanceDataStepRate: %d\n\n", Elem.InstanceDataStepRate );
            */
        }//for

//        g_pLog->Write( L"---------------\n\n" );

        //Register new input layout in db
        InputLayoutMap.insert( std::pair < ID3D11InputLayout*, KD3D11VertexDeclaration > ( *ppInputLayout, ElementsVec ) );

        ::LeaveCriticalSection( &cs );

    }//if(SUCCEEDED())

    return hr;
}


KDumper::EPrimitiveType KRipper11::D3D11_PRIMITIVE_TOPOLOGY_to_EPrimitiveType( D3D11_PRIMITIVE_TOPOLOGY PrimTopology ){
    if( PrimTopology == D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ){
        return KDumper::eTriangleList;
    }
    return KDumper::eTriangleStrip;
}



HRESULT KRipper11::CopyBuffer( 
    ID3D11DeviceContext* pDevCont, 
    ID3D11Buffer* pSrcBuffer, 
    ID3D11Buffer** ppDstBuffer 
    )
{
    
    D3D11_BUFFER_DESC SrcDesc;
    D3D11_BUFFER_DESC DstDesc;
    //ID3D11Buffer* pDstBuffer = NULL;

    TDXRef <ID3D11Device> pDevRef;
    HRESULT hr;

    *ppDstBuffer = NULL;

    pSrcBuffer->GetDesc( &SrcDesc );

    DstDesc = SrcDesc;
    DstDesc.Usage          = D3D11_USAGE_STAGING;
    DstDesc.BindFlags      = 0;
    DstDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

    pDevCont->GetDevice( &pDevRef );
    hr = pDevRef->CreateBuffer( &DstDesc, NULL, ppDstBuffer );
    if (FAILED( hr ))
    {
        return hr;
    }

    pDevCont->CopyResource( *ppDstBuffer, pSrcBuffer );
    return S_OK;
}


KDumper::EInputType KRipper11::DXGI_FORMAT_to_EInputType ( DXGI_FORMAT Format ){
    
    switch( Format ){
    
    case DXGI_FORMAT_R32G32B32A32_TYPELESS:
        return KDumper::eR32G32B32A32_TYPELESS;
    
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return KDumper::eR32G32B32A32_FLOAT;

    case DXGI_FORMAT_R32G32B32A32_UINT:
        return KDumper::eR32G32B32A32_UINT;

    case DXGI_FORMAT_R32G32B32A32_SINT:
        return KDumper::eR32G32B32A32_SINT;

    //////////////////////////////////////////////////////////////////////////
    
    case DXGI_FORMAT_R32G32B32_TYPELESS:
        return KDumper::eR32G32B32_TYPELESS;

    case DXGI_FORMAT_R32G32B32_FLOAT:
        return KDumper::eR32G32B32_FLOAT;

    case DXGI_FORMAT_R32G32B32_UINT:
        return KDumper::eR32G32B32_UINT;

    case DXGI_FORMAT_R32G32B32_SINT:
        return KDumper::eR32G32B32_SINT;

    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R16G16B16A16_TYPELESS:
        return KDumper::eR16G16B16A16_TYPELESS;

    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return KDumper::eR16G16B16A16_FLOAT;

    case DXGI_FORMAT_R16G16B16A16_UNORM:
        return KDumper::eR16G16B16A16_UNORM;

    case DXGI_FORMAT_R16G16B16A16_UINT:
        return KDumper::eR16G16B16A16_UINT;

    case DXGI_FORMAT_R16G16B16A16_SNORM:
        return KDumper::eR16G16B16A16_SNORM;

    case DXGI_FORMAT_R16G16B16A16_SINT:
        return KDumper::eR16G16B16A16_SINT;
        
    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R32G32_TYPELESS:
        return KDumper::eR32G32_TYPELESS;

    case DXGI_FORMAT_R32G32_FLOAT:
        return KDumper::eR32G32_FLOAT;

    case DXGI_FORMAT_R32G32_UINT:
        return KDumper::eR32G32_UINT;

    case DXGI_FORMAT_R32G32_SINT:
        return KDumper::eR32G32_SINT;

    //////////////////////////////////////////////////////////////////////////


    case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        return KDumper::eR8G8B8A8_TYPELESS;

    case DXGI_FORMAT_R8G8B8A8_UNORM:
        return KDumper::eR8G8B8A8_UNORM;

    case DXGI_FORMAT_R8G8B8A8_UINT:
        return KDumper::eR8G8B8A8_UINT;

    case DXGI_FORMAT_R8G8B8A8_SNORM:
        return KDumper::eR8G8B8A8_SNORM;

    case DXGI_FORMAT_R8G8B8A8_SINT:
        return KDumper::eR8G8B8A8_SINT;

    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R16G16_TYPELESS:
        return KDumper::eR16G16_TYPELESS;
        
    case DXGI_FORMAT_R16G16_FLOAT:
        return KDumper::eR16G16_FLOAT;

    case DXGI_FORMAT_R16G16_UNORM:
        return KDumper::eR16G16_UNORM;

    case DXGI_FORMAT_R16G16_UINT:
        return KDumper::eR16G16_UINT;

    case DXGI_FORMAT_R16G16_SNORM:
        return KDumper::eR16G16_SNORM;

    case DXGI_FORMAT_R16G16_SINT:
        return KDumper::eR16G16_SINT;

    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R32_TYPELESS:
        return KDumper::eR32_TYPELESS;

    case DXGI_FORMAT_R32_FLOAT:
        return KDumper::eR32_FLOAT;

    case DXGI_FORMAT_R32_UINT:
        return KDumper::eR32_UINT;

    case DXGI_FORMAT_R32_SINT:
        return KDumper::eR32_SINT;

    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R8G8_TYPELESS:
        return KDumper::eR8G8_TYPELESS;

    case DXGI_FORMAT_R8G8_UNORM:
        return KDumper::eR8G8_UNORM;

    case DXGI_FORMAT_R8G8_UINT:
        return KDumper::eR8G8_UINT;

    case DXGI_FORMAT_R8G8_SNORM:
        return KDumper::eR8G8_SNORM;

    case DXGI_FORMAT_R8G8_SINT:
        return KDumper::eR8G8_SINT;

    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R16_TYPELESS:
        return KDumper::eR16_TYPELESS;

    case DXGI_FORMAT_R16_FLOAT:
        return KDumper::eR16_FLOAT;

    case DXGI_FORMAT_R16_UNORM:
        return KDumper::eR16_UNORM;

    case DXGI_FORMAT_R16_UINT:
        return KDumper::eR16_UINT;

    case DXGI_FORMAT_R16_SNORM:
        return KDumper::eR16_SNORM;

    case DXGI_FORMAT_R16_SINT:
        return KDumper::eR16_SINT;

    //////////////////////////////////////////////////////////////////////////

    case DXGI_FORMAT_R8_TYPELESS:
        return KDumper::eR8_TYPELESS;

    case DXGI_FORMAT_R8_UNORM:
        return KDumper::eR8_UNORM;

    case DXGI_FORMAT_R8_UINT:
        return KDumper::eR8_UINT;

    case DXGI_FORMAT_R8_SNORM:
        return KDumper::eR8_SNORM;

    case DXGI_FORMAT_R8_SINT:
        return KDumper::eR8_SINT;

    case DXGI_FORMAT_R10G10B10A2_UNORM:
        return KDumper::eR10G10B10A2_UNORM;

    case DXGI_FORMAT_B8G8R8A8_UNORM:
        return KDumper::eB8G8R8A8_UNORM;
    }

    return KDumper::eUnknownInputType;
}



HRESULT KRipper11::GetVertexDeclarations( 
    ID3D11DeviceContext* pDevCont,
    KDumper::KInputVertexDeclaration&  InputDecl,
    KDumper::KOutputVertexDeclaration& OutputDecl
    )
{
    KD3D11VertexDeclaration  D3D11VertDecl;
    HRESULT hr;

    hr = GetInputLayout( pDevCont, D3D11VertDecl );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"Input layout get failed: 0x%08X\n", hr );
        return hr;
    }

    for( size_t i = 0; i < D3D11VertDecl.size(); i++ )
    {
        KD3D11InputElement D3DElem = D3D11VertDecl[ i ];
        KDumper::KInputVertexElement InputElem;
        Dump_KD3D11InputElement2Log( D3DElem );

        KDumper::EInputType InputType = DXGI_FORMAT_to_EInputType( D3DElem.Format );
        if( InputType == KDumper::eUnknownInputType )
        {
            g_pLog->Write( L"Error unknown vertex type: %s\n", DXGI_FORMAT_2_Str( D3DElem.Format ) );
            hr = E_INPUT_TYPE_ERR;
            break;
        }

        InputElem.Type   = InputType;
        InputElem.Stream = D3DElem.InputSlot;
        ::StrCopy( InputElem.UsageSemantic, SEMANTIC_LEN, D3DElem.SemanticName );
        InputElem.SemanticIndex = D3DElem.SemanticIndex;
        InputElem.Size = KDumper::GetInputTypeSize( InputElem.Type );
        InputElem.Offset = D3DElem.AlignedByteOffset;
        InputDecl.Decl.push_back( InputElem );
    }


    //Correct "Offset"
    // Get unique stream numbers
    std::vector < DWORD > uniqueStreams;
    for ( size_t i = 0; i < InputDecl.Decl.size(); i++ )
    {
        DWORD Stream = InputDecl.Decl[ i ].Stream;
        BOOL streamFound = FALSE;
        for ( size_t j = 0; j < uniqueStreams.size(); j++ )
        {
            if (uniqueStreams[j] != Stream)
            {
                streamFound = TRUE;
                break;
            }// if
        }// for

        if( !streamFound )
        {
            uniqueStreams.push_back( Stream );
        }
    }


    for (size_t i = 0; i < uniqueStreams.size(); i++)
    {
        DWORD Offset = 0;
        for (size_t j = 0; j < InputDecl.Decl.size(); j++ )
        {
            if ( InputDecl.Decl[j].Stream == uniqueStreams[i] )
            {
                if( InputDecl.Decl[j].Offset == D3D11_APPEND_ALIGNED_ELEMENT )
                {
                    InputDecl.Decl[j].Offset = Offset;
                }//if
                Offset += InputDecl.Decl[j].Size;
            }//if
        }//for
    }//for


    if( SUCCEEDED( hr ) )
    {
        hr = KDumper::CreateKOutputVertexDeclaration( InputDecl, OutputDecl );
    }
    return hr;
}

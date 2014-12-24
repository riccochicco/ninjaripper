
#include "PreComp.h"
#include "KRipper8.h"
#include "KHookMgr.h"


//************************************************************************
// D3D8 Ripper
//************************************************************************


KRipper8*  KRipper8::this_ = NULL;//'this'


KRipper8::KRipper8( HINSTANCE hD3D8_ ):
hD3D8( hD3D8_ ),
hD3DX( NULL ),
D3DXSaveTextureToFileW_( NULL ),
D3DXGetFVFVertexSize_( NULL ),
LastShader( 0 ),
D3DXDeclaratorFromFVF_( NULL )
{
    this_ = this;
    ::InitializeCriticalSection( &cs );
}


KRipper8::~KRipper8(){
    this_ = NULL;
    ::DeleteCriticalSection( &cs );
}


void KRipper8::Init(){


    PFN_Direct3DCreate8 true_Direct3DCreate8 = 
        (PFN_Direct3DCreate8)GetProcAddress( this_->hD3D8, "Direct3DCreate8" );

    if( !true_Direct3DCreate8 ){
        ::FatalErrorMsg( L"Can't get address of D3D8.Direct3DCreate8()" );
    }

    //Set hook to Direct3DCreate8()
    g_pHookMgr->Hook( true_Direct3DCreate8, Pre_Direct3DCreate8 );
    g_pLog->Write( L"D3D8.Direct3DCreate8() hooked\n" );
}


void KRipper8::Uninit(){

}



IDirect3D8* KRipper8::_Direct3DCreate8(
    PFN_Direct3DCreate8 e,
    UINT SDKVER )
{
    if( !hD3DX ){
        HMODULE hMod = ::GetModuleHandle( L"d3dx8d.dll" );
        if( hMod ){
            hD3DX = (HINSTANCE)hMod;
        }
        else{
            std::wstring RipperDir = g_pIntruder->GetIntruderDir();
            RipperDir += L"d3dx8d.dll";

            hD3DX = ::LoadLibrary( RipperDir.c_str() );
            if( !hD3DX ){
                ::FatalErrorMsg( L"d3dx8d.dll load error" );
            }
        }

        D3DXSaveTextureToFileW_ = ( PFN_D3DXSaveTextureToFileW )GetProcAddress( hD3DX, "D3DXSaveTextureToFileW" );
        if( !D3DXSaveTextureToFileW_ ){
            ::FatalErrorMsg( L"Can't get address of D3DX8.D3DXSaveTextureToFileW" );
        }

        D3DXGetFVFVertexSize_ = ( PFN_D3DXGetFVFVertexSize )GetProcAddress( hD3DX, "D3DXGetFVFVertexSize" );
        if( !D3DXGetFVFVertexSize_ ){
            ::FatalErrorMsg( L"Can't get address of D3DX8.D3DXGetFVFVertexSize" );
        }


        D3DXDeclaratorFromFVF_ = (PFN_D3DXDeclaratorFromFVF)GetProcAddress( hD3DX, "D3DXDeclaratorFromFVF" );
        if( !D3DXDeclaratorFromFVF_ ){
            ::FatalErrorMsg( L"Can't get address of D3DX8.D3DXDeclaratorFromFVF" );
        }

    }

    IDirect3D8* pid3d8 = e( SDKVER );//Direct3DCreate8( SDKVER )
    g_pLog->Write( L"D3D8.Direct3DCreate8( %d ) ret: 0x%08X\n", SDKVER, pid3d8 );    
    if( !pid3d8 ){//Function return error
        return pid3d8;
    }

    HOOK( IDirect3D8_CreateDevice, 15, pid3d8 );
    return pid3d8;
}



HRESULT KRipper8::_IDirect3D8_CreateDevice (
    PFN_IDirect3D8_CreateDevice e,
    IDirect3D8* pD3D8, 
    UINT Adapter,
    D3DDEVTYPE DeviceType,
    HWND hFocusWindow,
    DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS* pPresentationParameters,
    IDirect3DDevice8** ppReturnedDeviceInterface
    )
{

    HRESULT res = e( pD3D8, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface );
    if( res ){//DX return error. Nothing to do
        return res;
    }

    g_pLog->Write( L"IDirect3D8_CreateDevice( 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X ) ret: 0x%08X\n", pD3D8, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface, res );
    
    HOOK( IDirect3DDevice8_SetTexture, 61, *ppReturnedDeviceInterface );

    //IDirect3DDevice8::Present
    HOOK( IDirect3DDevice8_Present, 15, *ppReturnedDeviceInterface );

    //13    STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain) PURE;

    //Draw*****
    HOOK( IDirect3DDevice8_DrawPrimitive, 70, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice8_DrawIndexedPrimitive, 71, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice8_DrawPrimitiveUP, 72, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice8_DrawIndexedPrimitiveUP, 73, *ppReturnedDeviceInterface );
    
    //Buffer "WRITE" flag overwrite
    HOOK( IDirect3DDevice8_CreateVertexBuffer, 23, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice8_CreateIndexBuffer, 24, *ppReturnedDeviceInterface );

    //Vertex/Pixel Shader
    HOOK( IDirect3DDevice8_CreateVertexShader, 75, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice8_DeleteVertexShader, 78, *ppReturnedDeviceInterface );

    HOOK( IDirect3DDevice8_CreatePixelShader, 87, *ppReturnedDeviceInterface );
    HOOK( IDirect3DDevice8_DeletePixelShader, 90, *ppReturnedDeviceInterface );


    HOOK( IDirect3DDevice8_SetVertexShader, 76, *ppReturnedDeviceInterface );

    return res;
}



KDumper::EPrimitiveType KRipper8::D3DPRIMITIVETYPE_to_EPrimitiveType( D3DPRIMITIVETYPE pt ){

    switch( pt ){
    
    case D3DPT_POINTLIST:
        return KDumper::ePointList;

    case D3DPT_LINELIST:
        return KDumper::eLineList;

    case D3DPT_LINESTRIP:
        return KDumper::eLineStrip;

    case D3DPT_TRIANGLELIST:
        return KDumper::eTriangleList;

    case D3DPT_TRIANGLESTRIP:
        return KDumper::eTriangleStrip;
    
    case  D3DPT_TRIANGLEFAN:
        return KDumper::eTriangleFan;
    
    default:
        return KDumper::eUnknownPrimitiveType;
    }
}


HRESULT KRipper8::_IDirect3DDevice8_Present(
    PFN_IDirect3DDevice8_Present e,
    IDirect3DDevice8 *pDev, 
    CONST RECT * pSourceRect, 
    CONST RECT * pDestRect, 
    HWND hDestWindowOverride, 
    CONST RGNDATA *pDirtyRegion
    )
{
    g_pIntruder->FrameHandler( this );

//    g_pLog->Write("IDirect3DDevice8::Present(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n", pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return e(pDev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}




HRESULT KRipper8::_IDirect3DDevice8_CreateVertexBuffer(
    PFN_IDirect3DDevice8_CreateVertexBuffer e,
    IDirect3DDevice8* pDev, 
    UINT Length,
    DWORD Usage,
    DWORD FVF,
    D3DPOOL Pool,
    IDirect3DVertexBuffer8** ppVertexBuffer
    )
{
    Usage &= (~D3DUSAGE_WRITEONLY);
    return e( pDev, Length, Usage, FVF, Pool, ppVertexBuffer );
}


HRESULT KRipper8::_IDirect3DDevice8_CreateIndexBuffer(
    PFN_IDirect3DDevice8_CreateIndexBuffer e,
    IDirect3DDevice8* pDev,
    UINT Length,
    DWORD Usage,
    D3DFORMAT Format,
    D3DPOOL Pool,
    IDirect3DIndexBuffer8** ppIndexBuffer
    )
{
    Usage &= (~D3DUSAGE_WRITEONLY);
    return e( pDev, Length, Usage, Format, Pool, ppIndexBuffer );
}



HRESULT KRipper8::_IDirect3DDevice8_CreateVertexShader(
    PFN_IDirect3DDevice8_CreateVertexShader e,
    IDirect3DDevice8* pDev,
    CONST DWORD* pDeclaration,
    CONST DWORD* pFunction,
    DWORD* pHandle,
    DWORD Usage
    )
{
    HRESULT hr = e( pDev, pDeclaration, pFunction, pHandle, Usage );
    if( FAILED( hr ) ){
        return hr;//Error happen in API. Return
    }

    g_pLog->Write( L"IDirect3DDevice8_CreateVertexShader(): Handle: 0x%08X\n", *pHandle );

    ::EnterCriticalSection( &cs );
    
    KVertexShaderMap::iterator p = VSDb.find( *pHandle );
    if( p != VSDb.end() ){//Element exist - erase old. Prepare to add new
        VSDb.erase( p );
    }

    KVertexShader8 Vs8;

    //Copy declaration to db
    if( pDeclaration ){

        DWORD Idx = 0;
        for(;;){
            DWORD x = pDeclaration[ Idx ];
            Vs8.Declaration[ Idx ] = x;
            if( ( x == D3DVSD_END() ) || ( Idx >= 256 ) ){//DECL_END token or out of array
                break;
            }
            Idx++;
        }
    }

    
    //Add shader copy
    //....

    VSDb.insert( std::pair < DWORD, KVertexShader8 > ( *pHandle, Vs8 ) );

    ::LeaveCriticalSection( &cs );

    return hr;
}



HRESULT KRipper8::_IDirect3DDevice8_DeleteVertexShader(
    PFN_IDirect3DDevice8_DeleteVertexShader e,
    IDirect3DDevice8* pDev,
    DWORD Handle
    )
{
    HRESULT hr = e( pDev, Handle );
    if( FAILED( hr ) ){
        return hr;
    }
    
    g_pLog->Write( L"IDirect3DDevice8_DeleteVertexShader(): Handle: 0x%08X\n", Handle );

    ::EnterCriticalSection( &cs );

    KVertexShaderMap::iterator p = VSDb.find( Handle );
    if( p != VSDb.end() ){//Element exist - erase
        VSDb.erase( p );
    }
    ::LeaveCriticalSection( &cs );

    return hr;
}



HRESULT KRipper8::_IDirect3DDevice8_CreatePixelShader(
    PFN_IDirect3DDevice8_CreatePixelShader e,
    IDirect3DDevice8 * pDev,
    CONST DWORD* pFunction,
    DWORD* pHandle
    )
{
    HRESULT hr = e( pDev, pFunction, pHandle );
    if( FAILED( hr ) ){
        return hr;//Error happen in API. Return
    }
    g_pLog->Write( L"IDirect3DDevice8_CreatePixelShader(): Handle: 0x%08X\n", *pHandle );

    //Add shader saving

    return hr;
}



HRESULT KRipper8::_IDirect3DDevice8_DeletePixelShader(
    PFN_IDirect3DDevice8_DeletePixelShader e,
    IDirect3DDevice8* pDev,
    DWORD Handle
    )
{
    HRESULT hr = e( pDev, Handle );
    if( FAILED( hr ) ){
        return hr;
    }

    g_pLog->Write( L"IDirect3DDevice8_DeletePixelShader(): Handle: 0x%08X\n", Handle );

    ::EnterCriticalSection( &cs );

    KPixelShaderMap::iterator p = PSDb.find( Handle );
    if( p != PSDb.end() ){//Element exist - erase
        PSDb.erase( p );
    }
    ::LeaveCriticalSection( &cs );

    return hr;
}



// D3DXGetFVFVertexSize
// D3DXDeclaratorFromFVF


/*
0x20000000 STREAM(0)
0x40020000 Stream Data Definition
0x40020003 Stream Data Definition
0x40040005 Stream Data Definition
0x40010007 Stream Data Definition
0xFFFFFFFF


0x20000000
0x40020000
0x40020003
0x40010007
0xFFFFFFFF
*/



HRESULT KRipper8::GetVertexDeclarations( 
    IDirect3DDevice8* pDev, 
    KDumper::KInputVertexDeclaration& InputDecl,
    KDumper::KOutputVertexDeclaration& OutputDecl
    )
{
    HRESULT hr;
    DWORD VertShader = 0;
    hr = pDev->GetVertexShader( &VertShader );
    if( FAILED( hr ) ){//If function failed -> get saved value
        VertShader = LastShader;
//        g_pLog->Write( L"IDirect3DDevice8::GetVertexShader() error: 0x%08X\n", hr );
//        return hr;
    }

    g_pLog->Write( L"VertexShader/FVF: 0x%08X\n", VertShader );
    if( !VertShader ){
        g_pLog->Write( L"FVF==NULL\n" );
        hr = E_FVF_NULL;
        return hr;
    }

    ::EnterCriticalSection( &cs );
    KVertexShaderMap::iterator p = VSDb.find( VertShader );
    if( p == VSDb.end() ){//Shader with handle not found
        //FVF set. Crack it
        DWORD Decl[ 256 ] = { 0 };
        hr = D3DXDeclaratorFromFVF_( VertShader, Decl );
        if( FAILED( hr ) ){
            g_pLog->Write( L"D3DX8.D3DXDeclaratorFromFVF() failed: 0x%08X\n", hr );
            ::LeaveCriticalSection( &cs );
            return hr;
        }
        hr = CreateDecl( Decl, InputDecl );
    }
    else{//Vertex shader is set. Parse declaration
        KVertexShader8 vs = p->second;
        hr = CreateDecl( vs.Declaration, InputDecl );
    }
    ::LeaveCriticalSection( &cs );

    if( SUCCEEDED( hr ) ){
        hr = KDumper::CreateKOutputVertexDeclaration( InputDecl, OutputDecl );
    }

    return hr;
}


HRESULT KRipper8::CreateDecl( 
    const DWORD* pDecl, 
    KDumper::KInputVertexDeclaration& InputDecl
    )
{
    HRESULT hr;

    DWORD Idx = 0;
    g_pLog->Write( L"--------D3D8 vertex shader declaration--------\n" );
    for(;;){
        DWORD Token = pDecl[ Idx ];
        g_pLog->Write( L"0x%08X\n", Token );
        if( Token == D3DVSD_END() ){
            break;
        }
        Idx++;
    }
    g_pLog->Write( L"----------------------------------------------\n\n" );


    Idx = 0;
    DWORD StreamNum = 0;
    DWORD Offset = 0;
    while( TRUE ){
        DWORD Add = 0;
        KDumper::KInputVertexElement InputElem;


        DWORD Token = pDecl[ Idx ];

        if( Token == D3DVSD_END() ){ 
            hr = S_OK;
            break;
        }

        if( Token == D3DVSD_NOP() ){
            Idx++;
            continue;
        }

        DWORD TokenType = ( Token >> D3DVSD_TOKENTYPESHIFT ) & 0x7;

        if( TokenType == D3DVSD_TOKEN_STREAM ){
            StreamNum = Token & 0xF;
            Offset = 0;
        }
        else if( TokenType == D3DVSD_TOKEN_STREAMDATA ){
            Add = 1;
            if( !( Token & D3DVSD_DATALOADTYPEMASK ) ){
                //Vertex Input Register Load
                DWORD TypeDim = ( Token & D3DVSD_DATATYPEMASK ) >> D3DVSD_DATATYPESHIFT;

                DWORD RegAddr = Token & 0xF;

                if( RegAddr == 0 ){
                    ::StrCopy( InputElem.UsageSemantic, SEMANTIC_LEN, "POSITION" );
                }
                else if( RegAddr == 3 ){
                    ::StrCopy( InputElem.UsageSemantic, SEMANTIC_LEN, "NORMAL" );
                }
                else if( TypeDim == D3DVSDT_D3DCOLOR ){
                    ::StrCopy( InputElem.UsageSemantic, SEMANTIC_LEN, "COLOR" );//???
                }
                else{
                    ::StrCopy( InputElem.UsageSemantic, SEMANTIC_LEN, "TEXCOORD" );
                }


                if( TypeDim == D3DVSDT_FLOAT1 ){
                    InputElem.Type = KDumper::eR32_FLOAT;
                }
                else if( TypeDim == D3DVSDT_FLOAT2 ){
                    InputElem.Type = KDumper::eR32G32_FLOAT;
                }
                else if( TypeDim == D3DVSDT_FLOAT3 ){
                    InputElem.Type = KDumper::eR32G32B32_FLOAT;
                }
                else if( TypeDim == D3DVSDT_FLOAT4 ){
                    InputElem.Type = KDumper::eR32G32B32A32_FLOAT;
                }
                else if( TypeDim == D3DVSDT_D3DCOLOR ){
                    InputElem.Type = KDumper::eR8G8B8A8_UINT;;
                }
                else if( TypeDim == D3DVSDT_UBYTE4 ){
                    InputElem.Type = KDumper::eR8G8B8A8_UINT;
                }
                else if( TypeDim == D3DVSDT_SHORT2 ){
                    InputElem.Type = KDumper::eR16G16_SINT;
                }
                else if( TypeDim == D3DVSDT_SHORT4 ){
                    InputElem.Type = KDumper::eR16G16B16A16_SINT;
                }
            }
            else{
                //Data Skip Flag Set
                hr = E_NOTREALIZED;
                break;
            }
        }
        else{
            hr = E_NOTREALIZED;
            break;
        }
        

        if( Add ){

            //Calculate size of type
            InputElem.Size = KDumper::GetInputTypeSize( InputElem.Type );
            InputElem.Stream = StreamNum;
            InputElem.Offset = Offset;
            InputDecl.Decl.push_back( InputElem );

            Offset += InputElem.Size;
        }

        Idx++;
    }
    return hr;
}



HRESULT KRipper8::_IDirect3DDevice8_SetVertexShader(
    PFN_IDirect3DDevice8_SetVertexShader e,
    IDirect3DDevice8* pDev,
    DWORD Handle
    )
{
    HRESULT hr;
    hr = e( pDev, Handle );
    if( SUCCEEDED( hr ) ){
        ::EnterCriticalSection( &cs );
        LastShader = Handle;
        ::LeaveCriticalSection( &cs );
    }
    return hr;
}

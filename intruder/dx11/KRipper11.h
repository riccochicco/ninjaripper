#pragma once

#include "Types.h"
#include "KIntruder.h"
#include "KHookMgr.h"
#include "IRipper.h"
#include "Output.h"
#include "KDumper.h"


class KRipper11: public IRipper{
public:
    static KRipper11* Create( HINSTANCE hD3D11 ){
        g_pLog->Write( L"D3D11 Ripper Init\n" );
        KRipper11* p = new KRipper11( hD3D11 );
        p->Init();
        return p;
    }

    static void Delete( KRipper11* & p ){
        if( !p )
            return;

        g_pLog->Write( L"D3D11 Ripper Uninit\n\n" );
        p->Uninit( );
        SAFE_DELETE( p );
    }

    //IRipper
    virtual void FrameStart();
    virtual void FrameEnd(){}
    virtual void TextureRipStart(){}
    virtual void TextureRipEnd(){}

protected:
    virtual ~KRipper11();
    KRipper11( HINSTANCE );

private:

    //Hold already saved frame texture
    struct KFrameTexture{
        ID3D11ShaderResourceView* pTexture;
        std::string TextureFile;

        KFrameTexture():
        pTexture( NULL )
        {
        }

    };
    typedef std::vector < KFrameTexture > KFrameTextureVec;
    
    KFrameTextureVec FrameTextures;

    static KRipper11* this_;//Pointer to self
    
    HINSTANCE  hD3D11;
    HINSTANCE  hD3DX;
    PFN_D3DX11SaveTextureToFileW D3DX11SaveTextureToFileW_;
    PFN_D3DX11CompileFromMemory  D3DX11CompileFromMemory_;

    //Function Prototypes
    static void Init();
    static void Uninit();

    PREGEN_12( D3D11CreateDeviceAndSwapChain,
        IDXGIAdapter*,
        D3D_DRIVER_TYPE,
        HMODULE,
        UINT,
        CONST D3D_FEATURE_LEVEL*,
        UINT,
        UINT,
        CONST DXGI_SWAP_CHAIN_DESC*,
        IDXGISwapChain**,
        ID3D11Device**,
        D3D_FEATURE_LEVEL*,
        ID3D11DeviceContext**
        );


    //DXGI.CreateDXGIFactory
    PREGEN_2( CreateDXGIFactory, 
        void*,
        void**);


    //DXGI.CreateDXGIFactory1
    PREGEN_2( CreateDXGIFactory1, 
        void*,
        void**);

    PREGEN_4( IDXGIFactory_CreateSwapChain,
        IDXGIFactory*,
        IUnknown*,
        DXGI_SWAP_CHAIN_DESC*,
        IDXGISwapChain**
        );

    PREGEN_10( D3D11CreateDevice,
        IDXGIAdapter*,
        D3D_DRIVER_TYPE,
        HMODULE,
        UINT,
        const D3D_FEATURE_LEVEL*,
        UINT,
        UINT,
        ID3D11Device**,
        D3D_FEATURE_LEVEL*,
        ID3D11DeviceContext**
        );

    VPREGEN_4( ID3D11DeviceContext_PSSetShaderResources,
        ID3D11DeviceContext*,
        UINT,
        UINT,
        ID3D11ShaderResourceView *const *
        );

    VPREGEN_3( ID3D11DeviceContext_Draw,
        ID3D11DeviceContext*,
        UINT,
        UINT
        );

    VPREGEN_1( ID3D11DeviceContext_DrawAuto, ID3D11DeviceContext* );

    VPREGEN_4( ID3D11DeviceContext_DrawIndexed,
        ID3D11DeviceContext*,
        UINT,
        UINT,
        INT
        );

    VPREGEN_6( ID3D11DeviceContext_DrawIndexedInstanced,
        ID3D11DeviceContext*,
        UINT,
        UINT,
        UINT,
        INT,
        UINT
        );

    VPREGEN_3( ID3D11DeviceContext_DrawIndexedInstancedIndirect,
        ID3D11DeviceContext*,
        ID3D11Buffer *,
        UINT
        );

    VPREGEN_5( ID3D11DeviceContext_DrawInstanced,
        ID3D11DeviceContext*,
        UINT,
        UINT,
        UINT,
        UINT
        );

    VPREGEN_3( ID3D11DeviceContext_DrawInstancedIndirect,
        ID3D11DeviceContext*,
        ID3D11Buffer *,
        UINT        
        );

    PREGEN_3( IDXGISwapChain_Present,
        IDXGISwapChain*,
        UINT,
        UINT
        );


    std::vector < ID3D11ShaderResourceView* > TexturesVec;
    
/*
    VPREGEN_4( ID3D11DeviceContext_VSSetShaderResources,
        ID3D11DeviceContext*,
        UINT,
        UINT,
        ID3D11ShaderResourceView *const *    
        );

    VPREGEN_4( ID3D11DeviceContext_GSSetShaderResources,
        ID3D11DeviceContext*,
        UINT,
        UINT,
        ID3D11ShaderResourceView *const *    
        );
*/

    PREGEN_6( ID3D11Device_CreateInputLayout,
        ID3D11Device*,
        const D3D11_INPUT_ELEMENT_DESC *,
        UINT,
        const void*,
        SIZE_T,
        ID3D11InputLayout**
        );


    void HandleTexture(
        ID3D11DeviceContext* pDevCont,
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews
        );

    void DumpShaderResourceView( ID3D11ShaderResourceView* );
    const wchar_t* DXGI_FORMAT_2_Str( DXGI_FORMAT Format );
    const wchar_t* D3D11_SRV_DIMENSION_2_Str( D3D11_SRV_DIMENSION );

    HRESULT CompileShaderFromMemory( 
        LPCSTR pData, 
        SIZE_T Len, 
        LPCSTR szEntryPoint, 
        LPCSTR szShaderModel, 
        ID3DBlob** ppBlobOut 
        );

    HRESULT SaveTexture2File( 
        const wchar_t* szFile, 
        ID3D11DeviceContext* pImmediateContext, 
        ID3D11ShaderResourceView* pShaderResView 
        );


    DWORD IsTextureSaved( ID3D11ShaderResourceView* pTex );

    HRESULT SaveTexture2FileMain( 
        const wchar_t* szFile, 
        ID3D11DeviceContext* pDevCont, 
        ID3D11ShaderResourceView* pShaderResView  
        );


    
    const wchar_t* D3D_DRIVER_TYPE_2_Str( D3D_DRIVER_TYPE dt );
    const wchar_t* D3D_FEATURE_LEVEL_2_Str( D3D_FEATURE_LEVEL fl );
    
    PFN_ID3D11DeviceContext_DrawIndexed          unhDrawIndexed;
    PFN_ID3D11DeviceContext_PSSetShaderResources unhPSSetShaderResources;


    const wchar_t* D3D11_PRIMITIVE_TOPOLOGY_to_Str( D3D11_PRIMITIVE_TOPOLOGY );


    void HelperDllsInit();
    void HookDeviceContext( ID3D11DeviceContext** ppImmediateContext );
    void HookSwapChain( IDXGISwapChain** ppSwapChain );
    void HookDevice( ID3D11Device** ppDev );


    //Input layout helpers
    struct KD3D11InputElement{
        char                       SemanticName[ SEMANTIC_LEN ];
        UINT                       SemanticIndex;
        DXGI_FORMAT                Format;
        UINT                       InputSlot;
        UINT                       AlignedByteOffset;
        D3D11_INPUT_CLASSIFICATION InputSlotClass;
        UINT                       InstanceDataStepRate;

        KD3D11InputElement():
        SemanticIndex( 0 ),
        Format( DXGI_FORMAT_UNKNOWN ),
        InputSlot( 0 ),
        AlignedByteOffset( 0 ),
        InputSlotClass( D3D11_INPUT_PER_VERTEX_DATA  ),
        InstanceDataStepRate( 0 )
        {
            ZeroMemory( SemanticName, SEMANTIC_LEN );
        }
    };
    typedef std::vector < KD3D11InputElement > KD3D11VertexDeclaration;
    typedef std::map < ID3D11InputLayout*, KD3D11VertexDeclaration > KInputLayoutMap;
    
    //Input Layout DB
    KInputLayoutMap InputLayoutMap;


    ::CRITICAL_SECTION cs;
    
    KDumper::EPrimitiveType D3D11_PRIMITIVE_TOPOLOGY_to_EPrimitiveType( D3D11_PRIMITIVE_TOPOLOGY );


    void RipDI( 
        ID3D11DeviceContext* pDevCont,
        UINT IndexCount,
        UINT StartIndexLocation,
        INT  BaseVertexLocation
        );


    HRESULT CopyBuffer( ID3D11DeviceContext* pDevCont, ID3D11Buffer* pSrc, ID3D11Buffer** ppDst );

    HRESULT DumpIndexBuffer( 
        ID3D11DeviceContext* pDevCont, 
        KFACES* pFACES,
        UINT StartIndexLocation,
        INT  BaseVertexLocation,
        KDumper::EPrimitiveType PrimType
        );


    HRESULT GetInputLayout( 
        ID3D11DeviceContext* pDevCont,
        KD3D11VertexDeclaration& D3D11ElemVec
        );


    KDumper::EPrimitiveType GetPrimTopology( ID3D11DeviceContext* pDevCont );


    HRESULT DumpVertexBuffer(
        ID3D11DeviceContext* pDevCont,
        const KVERTICES* pVERTICES,
        const KFACES* pFACES,
        const KDumper::KInputVertexDeclaration&  InputVertDecl,
        const KDumper::KOutputVertexDeclaration& OutputVertDecl,
        INT BaseVertexIndex
        );


    KDumper::EInputType DXGI_FORMAT_to_EInputType ( DXGI_FORMAT Format );

    void Dump_KD3D11InputElement2Log( const KD3D11InputElement& Elem );


    //Mesh textures
    std::string IsMeshTextureAlreadySaved( 
        ID3D11ShaderResourceView* pTexture, 
        const std::string&     TextureFile
        );

    HRESULT SaveMeshTextures( 
        ID3D11DeviceContext* pDevCont,
        KMeshTextures2& TextureHeader 
        );


    typedef std::vector < ID3D11ShaderResourceView* > KShaderResourceVec;

    HRESULT GetVertexDeclarations( 
        ID3D11DeviceContext* pDevCont,
        KDumper::KInputVertexDeclaration&  InputVertexDecl,
        KDumper::KOutputVertexDeclaration& OutputVertDecl
        );

    const wchar_t* D3D11_USAGE_2_Str( D3D11_USAGE t );
};


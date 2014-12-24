#pragma once

#include "Types.h"
#include "KIntruder.h"
#include "KHookMgr.h"
#include "Output.h"
#include "KDumper.h"
#include "IRipper.h"


class KRipper9: public IRipper
{
public:
    
    //Hold already saved frame texture
    struct KFrameTexture{
        IDirect3DBaseTexture9* pTexture;
        std::string TextureFile;

        KFrameTexture():
        pTexture( NULL )
        {
        }

    };
    typedef std::vector < KFrameTexture > KFrameTextureVec;


    static KRipper9* Create( HINSTANCE hD3D9 ){
        g_pLog->Write( L"D3D9 Ripper Init\n" );
        KRipper9* p = new KRipper9( hD3D9 );
        p->Init();
        return p;
    }

    static void Delete( KRipper9* & p ){
        if( !p )
            return;

        g_pLog->Write( L"D3D9 Ripper Uninit\n\n" );
        p->Uninit();
        
        SAFE_DELETE( p );
    }


    //IRipper
    virtual void FrameStart();
    virtual void FrameEnd();
    virtual void TextureRipStart(){
        TexturesVec.clear();
    }
    virtual void TextureRipEnd(){}

protected:
    virtual ~KRipper9();
    KRipper9( HINSTANCE );

private:
    static KRipper9*  this_;

    HINSTANCE  hD3D9;
    PFN_D3DXSaveTextureToFileW D3DXSaveTextureToFileW_;
    PFN_D3DXDisassembleShader  D3DXDisassembleShader_;

    std::vector < IDirect3DBaseTexture9* > TexturesVec;//Forced to save textures

    HINSTANCE    hD3D9X;

    //Function prototypes
    static void Init();
    static void Uninit();
    

    PRE_1( Direct3DCreate9, UINT );
    IDirect3D9* _Direct3DCreate9( PFN_Direct3DCreate9, UINT SDKVER );


    PREGEN_7( IDirect3D9_CreateDevice, IDirect3D9*, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*, IDirect3DDevice9** );
    PREGEN_3( IDirect3DDevice9_SetTexture, IDirect3DDevice9*, DWORD, IDirect3DBaseTexture9* );


    DWORD IsTextureSaved( IDirect3DBaseTexture9* pTex );

    HRESULT SaveTexture2File( 
        LPCTSTR szFile, 
        IDirect3DDevice9* pDev, 
        IDirect3DBaseTexture9* pTexture  
        );

    DWORD CanSaveTexture( IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture );


    //Draw**
    PREGEN_5( IDirect3DDevice9_DrawPrimitiveUP, IDirect3DDevice9*, D3DPRIMITIVETYPE, UINT, CONST void*, UINT );
    PREGEN_7( IDirect3DDevice9_DrawIndexedPrimitive,
        IDirect3DDevice9 *, 
        D3DPRIMITIVETYPE, 
        INT, 
        UINT, 
        UINT, 
        UINT, 
        UINT );


    PREGEN_9( IDirect3DDevice9_DrawIndexedPrimitiveUP,
        IDirect3DDevice9*, 
        D3DPRIMITIVETYPE, 
        UINT, 
        UINT, 
        UINT, 
        CONST void*, 
        D3DFORMAT, 
        CONST void*, 
        UINT
        );


    PREGEN_4( IDirect3DDevice9_DrawPrimitive,
        IDirect3DDevice9*, 
        D3DPRIMITIVETYPE, 
        UINT, 
        UINT
        );



    //Buffer creation
    PREGEN_7( IDirect3DDevice9_CreateVertexBuffer,
        IDirect3DDevice9 *, 
        UINT, 
        DWORD, 
        DWORD, 
        D3DPOOL,
        IDirect3DVertexBuffer9**, 
        HANDLE*    
        );

    PREGEN_7( IDirect3DDevice9_CreateIndexBuffer,
        IDirect3DDevice9 *, 
        UINT , 
        DWORD , 
        DWORD , 
        D3DPOOL ,
        IDirect3DIndexBuffer9  **, 
        HANDLE *        
        );


    PREGEN_5( IDirect3DDevice9_Present,
        IDirect3DDevice9 *, 
        CONST RECT *, 
        CONST RECT *, 
        HWND, 
        CONST RGNDATA *
        );


    PREGEN_3( IDirect3DDevice9_GetSwapChain, 
        IDirect3DDevice9 *, 
        UINT,
        IDirect3DSwapChain9 **
        );


    PREGEN_6( IDirect3DSwapChain9_Present, 
        IDirect3DSwapChain9 *, 
        CONST RECT *,
        CONST RECT *,
        HWND,
        CONST RGNDATA *,
        DWORD    
        );



    KDumper::EPrimitiveType D3DPRIMITIVETYPE_to_EPrimitiveType( D3DPRIMITIVETYPE pt );
    
    typedef std::vector < D3DVERTEXELEMENT9 > KD3D9VertexDeclaration;

    void D3DDECLUSAGE_to_UsageSemantic( DWORD usage, char* pOut, DWORD BufSize );

    KDumper::EInputType D3DDECLTYPE_to_EInputType( BYTE t );


    KFrameTextureVec FrameTextures;

    DWORD SaveMeshTextures( IDirect3DDevice9*, KMeshTextures2& );
    
    std::string IsMeshTextureAlreadySaved( 
        IDirect3DBaseTexture9 *pTexture, 
        const std::string&     TextureFile
        );

    HRESULT SavePixelShader2File( 
        const wchar_t* szFile, 
        IDirect3DDevice9* pDev, 
        IDirect3DPixelShader9* pPS 
        );


    HRESULT SaveVertexShader2File( 
        const wchar_t* szFile, 
        IDirect3DDevice9* pDev, 
        IDirect3DVertexShader9* pPS 
        );

    PFN_IDirect3DDevice9_SetTexture      unhSetTexture;
    PFN_IDirect3DDevice9_DrawPrimitiveUP unhDrawPrimitiveUP;


    void RipDIP(
        IDirect3DDevice9 *pDev, 
        D3DPRIMITIVETYPE Type, 
        INT BaseVertexIndex, 
        UINT MinIndex, 
        UINT NumVertices, 
        UINT StartIndex, 
        UINT PrimitiveCount
        );

    CRITICAL_SECTION cs;




    HRESULT DumpIndexBuffer(
        IDirect3DDevice9 *pDev, 
        KFACES* pFACES,
        KDumper::EPrimitiveType PrimType,
        UINT StartIndex
        );


    HRESULT GetVertexDeclarations( 
        IDirect3DDevice9 *pDev,
        KDumper::KInputVertexDeclaration&  InputVertexDecl,
        KDumper::KOutputVertexDeclaration& OutputVertDecl
        );


    HRESULT DumpVertexBuffer(
        IDirect3DDevice9 *pDev, 
        const KVERTICES* pVERTICES,
        const KFACES* pFACES,
        const KDumper::KInputVertexDeclaration& InputVertDecl,
        const KDumper::KOutputVertexDeclaration& OutputVertDecl,
        INT BaseVertexIndex 
    );
    
    DWORD IsEndDecl( D3DVERTEXELEMENT9* p );
    void Dump_D3DVERTEXELEMENT9_2Log( const D3DVERTEXELEMENT9& Elem );
    void Dump_TextureDesc2Log( IDirect3DBaseTexture9 *pTexture );
    const wchar_t* D3DRESOURCETYPE_2Str( D3DRESOURCETYPE t );
    const wchar_t* D3DFORMAT_2Str( D3DFORMAT f );
    const wchar_t* D3DDECLTYPE_2Str( D3DDECLTYPE t );
    const wchar_t* D3DDECLUSAGE_2Str( D3DDECLUSAGE t );
    const wchar_t* D3DDECLMETHOD_2Str( D3DDECLMETHOD t );
    const wchar_t* D3DUSAGE_2Str( DWORD t );
    const wchar_t* D3DPOOL_2Str( D3DPOOL t );
    const wchar_t* D3DMULTISAMPLE_2Str( D3DMULTISAMPLE_TYPE x );
    const wchar_t* D3DRENDERSTATETYPE_2Str( D3DRENDERSTATETYPE t );
    const wchar_t* D3DSAMPLERSTATETYPE_2Str( D3DSAMPLERSTATETYPE t );
    const wchar_t* D3DTEXTURESTAGESTATETYPE_2Str( D3DTEXTURESTAGESTATETYPE t );


    PREGEN_2( IDirect3DDevice9_SetPixelShader, 
        IDirect3DDevice9 *, 
        IDirect3DPixelShader9*
        );
    TInitedVal < IDirect3DPixelShader9* > LastPS;
    PFN_IDirect3DDevice9_SetPixelShader unh_SetPixelShader;

    PFN_D3DXCompileShader D3DXCompileShader_;


    enum{
        RS_SIZE = 35,
        SS_SIZE = 10,
        TSS_SIZE = 5
    };

    template < class T >
    struct TState{
        T     State;
        DWORD SetVal;
    };

    TState < D3DRENDERSTATETYPE >  RenderStates [ RS_SIZE ];
    TState < D3DSAMPLERSTATETYPE > SamplerStates[ SS_SIZE ];
    TState < D3DTEXTURESTAGESTATETYPE > TextureStageStates[ TSS_SIZE ];


 
    void Init1();

/*
    PREGEN_3( IDirect3DDevice9_SetRenderState, IDirect3DDevice9*, D3DRENDERSTATETYPE, DWORD );
    PFN_IDirect3DDevice9_SetRenderState unh_SetRenderState;

    PREGEN_4( IDirect3DDevice9_SetSamplerState, IDirect3DDevice9*, DWORD, D3DSAMPLERSTATETYPE, DWORD );
    PFN_IDirect3DDevice9_SetSamplerState unh_SetSamplerState;

    PREGEN_4( IDirect3DDevice9_SetTextureStageState, IDirect3DDevice9*, DWORD, D3DTEXTURESTAGESTATETYPE, DWORD );
    PFN_IDirect3DDevice9_SetTextureStageState unh_SetTextureStageState;
*/

    // Damn bugfix on IDirect3DDevice9::GetDepthStencilSurface() on GeForce9800+
    PREGEN_2( IDirect3DDevice9_SetDepthStencilSurface, IDirect3DDevice9*, IDirect3DSurface9* );
    PFN_IDirect3DDevice9_SetDepthStencilSurface unh_SetDepthStencilSurface;

    TInitedVal < IDirect3DSurface9* > LastDepthStencilSurface;

    void HandleTextureSave(
        IDirect3DDevice9 *pDev, 
        DWORD Sampler, 
        IDirect3DBaseTexture9 *pTexture
        );



    VPREGEN_4(IDirect3DDevice9_SetGammaRamp, IDirect3DDevice9*, UINT,DWORD, const D3DGAMMARAMP *);
    PFN_IDirect3DDevice9_SetGammaRamp unh_SetGammaRamp;

    struct GammaHelper
    {
        UINT swapChain;
        DWORD flags;
        D3DGAMMARAMP gammaRamp;
    };
    TInitedVal <GammaHelper> lastGamma;
};

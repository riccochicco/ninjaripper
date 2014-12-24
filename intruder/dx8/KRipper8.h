#pragma once

#include "Types.h"
#include "KIntruder.h"
#include "KHookMgr.h"
#include "IRipper.h"
#include "Output.h"
#include "KDumper.h"



class KRipper8: public IRipper{
public:

    static KRipper8* Create( HINSTANCE hD3D8 ){
        g_pLog->Write( L"D3D8 Ripper Init\n" );
        KRipper8* p = new KRipper8( hD3D8 );
        p->Init();
        return p;
    }

    static void Delete( KRipper8* & p ){
        if( !p )
            return;

        g_pLog->Write( L"D3D8 Ripper Uninit\n\n" );
        p->Uninit();

        SAFE_DELETE( p );
    }

    //IRipper
    virtual void FrameStart(){}
    virtual void FrameEnd(){}
    virtual void TextureRipStart(){
        TexturesVec.clear();
    }
    virtual void TextureRipEnd(){}


protected:
    virtual ~KRipper8();
    KRipper8( HINSTANCE );

private:

    //Hold already saved frame texture
    struct KFrameTexture{
        IDirect3DBaseTexture8* pTexture;
        std::string TextureFile;

        KFrameTexture():
        pTexture( NULL )
        {
        }
    };
    typedef std::vector < KFrameTexture > KFrameTextureVec;

    static KRipper8* this_;//Pointer to self

    HINSTANCE  hD3D8;
    HINSTANCE  hD3DX;
    PFN_D3DXSaveTextureToFileW D3DXSaveTextureToFileW_;
    PFN_D3DXGetFVFVertexSize   D3DXGetFVFVertexSize_;
    PFN_D3DXDeclaratorFromFVF  D3DXDeclaratorFromFVF_;

    std::vector < IDirect3DBaseTexture8* > TexturesVec;
    
    
    //Function Prototypes
    static void Init();
    static void Uninit();

    PRE_1( Direct3DCreate8, UINT );
    IDirect3D8* _Direct3DCreate8( 
        PFN_Direct3DCreate8 e,
        UINT SDKVER 
    );

    PREGEN_7( IDirect3D8_CreateDevice,
        IDirect3D8*, 
        UINT,
        D3DDEVTYPE,
        HWND,
        DWORD,
        D3DPRESENT_PARAMETERS*,
        IDirect3DDevice8**
        );

    PREGEN_3( IDirect3DDevice8_SetTexture,
        IDirect3DDevice8*, 
        DWORD, 
        IDirect3DBaseTexture8* 
        );

    PREGEN_4( IDirect3DDevice8_DrawPrimitive,
        IDirect3DDevice8*, 
        D3DPRIMITIVETYPE, 
        UINT, 
        UINT
        );

    PREGEN_6( IDirect3DDevice8_DrawIndexedPrimitive,
        IDirect3DDevice8*,  
        D3DPRIMITIVETYPE,
        UINT,
        UINT,
        UINT, 
        UINT
        );

    PREGEN_5(IDirect3DDevice8_DrawPrimitiveUP,
        IDirect3DDevice8*, 
        D3DPRIMITIVETYPE,
        UINT,
        CONST void*, 
        UINT    
        );

    PREGEN_9( IDirect3DDevice8_DrawIndexedPrimitiveUP,
        IDirect3DDevice8*, 
        D3DPRIMITIVETYPE,
        UINT,
        UINT,
        UINT,
        CONST void*,
        D3DFORMAT,
        CONST void*,
        UINT    
        );

    //IDirect3DDevice8::Present
    PREGEN_5( IDirect3DDevice8_Present,
        IDirect3DDevice8*, 
        CONST RECT *, 
        CONST RECT *, 
        HWND, 
        CONST RGNDATA *        
        );


    PREGEN_2( IDirect3DDevice8_SetVertexShader,
        IDirect3DDevice8*,
        DWORD
        );


    DWORD IsTextureSaved( IDirect3DBaseTexture8* pTex );
    HRESULT SaveTexture2File( 
        LPCTSTR szFile, 
        IDirect3DDevice8* pDev, 
        IDirect3DBaseTexture8* pTexture  
        );

    KDumper::EPrimitiveType D3DPRIMITIVETYPE_to_EPrimitiveType( D3DPRIMITIVETYPE pt );


    KFrameTextureVec FrameTextures;

    DWORD SaveMeshTextures( IDirect3DDevice8*, KMeshTextures2& );

    std::string IsMeshTextureAlreadySaved(
        IDirect3DBaseTexture8 *pTexture, 
        const std::string&     TextureFile
        );

    CRITICAL_SECTION cs;

    void RipDIP(
        IDirect3DDevice8* pDev,  
        D3DPRIMITIVETYPE PrimitiveType,
        UINT MinIndex,
        UINT NumVertices,
        UINT StartIndex, 
        UINT PrimitiveCount );


    HRESULT DumpIndexBuffer(
        IDirect3DDevice8* pDev, 
        KFACES* pFACES,
        KDumper::EPrimitiveType PrimType,
        UINT* pBaseVertexIndex,  //Out param
        UINT StartIndex
        );


    HRESULT DumpVertexBuffer(
        IDirect3DDevice8* pDev, 
        const KVERTICES* pVERTICES,
        const KFACES* pFACES,
        const KDumper::KInputVertexDeclaration& InputVertDecl,
        const KDumper::KOutputVertexDeclaration& OutputVertDecl,
        INT BaseVertexIndex
        );




    //IDirect3DDevice8::CreateVertexBuffer
    PREGEN_6( IDirect3DDevice8_CreateVertexBuffer,
        IDirect3DDevice8*,
        UINT,
        DWORD,
        DWORD,
        D3DPOOL,
        IDirect3DVertexBuffer8**
        );

    //IDirect3DDevice8::CreateIndexBuffer
    PREGEN_6( IDirect3DDevice8_CreateIndexBuffer,
        IDirect3DDevice8*,
        UINT,
        DWORD,
        D3DFORMAT,
        D3DPOOL,
        IDirect3DIndexBuffer8**
        );


    struct KVertexShader8{
        DWORD Declaration[ 256 ];//FIX
        DWORD ShaderCode[ 256 ];//FIX

        KVertexShader8(){
            for( DWORD i=0; i<256; i++ ){
                Declaration[ i ] = 0;
                ShaderCode[ i ] = 0;
            }
        }
    };
    typedef std::map < DWORD, KVertexShader8 > KVertexShaderMap;


    struct KPixelShader8{
        DWORD ShaderCode[ 256 ];

        KPixelShader8(){
            for( DWORD i=0; i<256; i++ ){
                ShaderCode[ i ] = 0;
            }
        }
    };
    typedef std::map < DWORD, KPixelShader8 > KPixelShaderMap;

    KVertexShaderMap VSDb;
    KPixelShaderMap  PSDb;

    //Vertex shader
    PREGEN_5(IDirect3DDevice8_CreateVertexShader,
        IDirect3DDevice8*,
        CONST DWORD*,
        CONST DWORD*,
        DWORD*,
        DWORD
        );

    PREGEN_2(IDirect3DDevice8_DeleteVertexShader,
        IDirect3DDevice8*,
        DWORD
        );


    //Pixel shader
    PREGEN_3(IDirect3DDevice8_CreatePixelShader,
        IDirect3DDevice8*,
        CONST DWORD*,
        DWORD*
        );

    PREGEN_2(IDirect3DDevice8_DeletePixelShader,
        IDirect3DDevice8*,
        DWORD
        );


    HRESULT GetVertexDeclarations( 
        IDirect3DDevice8* pDev, 
        KDumper::KInputVertexDeclaration& InputDecl,
        KDumper::KOutputVertexDeclaration& OutputDecl
        );

    HRESULT CreateDecl( const DWORD*, KDumper::KInputVertexDeclaration& );

    DWORD LastShader;

    const wchar_t* D3DFORMAT_2Str( D3DFORMAT f );
    const wchar_t* D3DRESOURCETYPE_2Str( D3DRESOURCETYPE t );
    const wchar_t* D3DMULTISAMPLE_2Str( D3DMULTISAMPLE_TYPE x );
    const wchar_t* D3DPOOL_2Str( D3DPOOL t );
    void Dump_TextureDesc2Log( IDirect3DBaseTexture8 *pTexture );
    const wchar_t* D3DUSAGE_2Str( DWORD t );
    
    void HandleTextureSave( 
        IDirect3DDevice8* pDev, 
        DWORD Stage, 
        IDirect3DBaseTexture8* pTexture 
        );

};

#include "PreComp.h"
#include "KRipper9.h"



struct TLVertex
{
    D3DXVECTOR4 p;
    D3DXVECTOR2 t;
};

static const DWORD FVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_TEX1;


/*
static const char* szPixShader = "\
sampler2D tex0 : register (s0);\
\
struct PS_INPUT {\
    float2 InTex : TEXCOORD0;\
};\
\
struct PS_OUTPUT {\
    float4 diffuse: COLOR0;\
};\
\
\
PS_OUTPUT Main( PS_INPUT input )\
{\
    PS_OUTPUT output = (PS_OUTPUT)0;\
    output.diffuse = tex2D( tex0, input.InTex );\
    return output;\
}\
";
*/




HRESULT KRipper9::SaveTexture2File( 
    LPCTSTR szFile, 
    IDirect3DDevice9* pDev, 
    IDirect3DBaseTexture9* pTexture  
    )
{
    HRESULT hr = S_OK;

    if( !pTexture )
        return E_NULL_TEXTURE;

    Dump_TextureDesc2Log( pTexture );

    if ( !unhSetTexture || !unhDrawPrimitiveUP )
        return E_FUNC_NOT_FOUND;


    D3DRESOURCETYPE Type = pTexture->GetType();
    if( Type != D3DRTYPE_TEXTURE )
    {
        // Not 2D texture -> use standart D3DX
        // 
        HRESULT res1 = D3DXSaveTextureToFileW_(szFile, D3DXIFF_DDS, pTexture, 0);
        if( SUCCEEDED( res1 ) ){
            return S_OK;
        }
        return E_FAIL;
    }

/*
    HRESULT res1 = D3DXSaveTextureToFileW_(szFile, D3DXIFF_DDS, pTexture, 0);
    if( SUCCEEDED( res1 ) ){
        return S_OK;//Saved without help
    }
    return E_FAIL;
*/


/*
    TDXRef < ID3DXBuffer > pShaderRef;
    TDXRef < ID3DXBuffer > pErrorBufferRef;
    TDXRef < ID3DXConstantTable > pCtRef;

    hr = D3DXCompileShader_( 
        szPixShader, 
        strlen( szPixShader ),
        NULL,
        NULL,
        "Main",
        "ps_2_0",
        D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION,
        &pShaderRef,
        &pErrorBufferRef,
        &pCtRef
        );
    if( FAILED( hr ) ){
        ::FatalErrorMsg( L"Shader compile error" );
    }


    TDXRef < IDirect3DPixelShader9 > pMyPsRef;
    hr = pDev->CreatePixelShader( (DWORD*)pShaderRef->GetBufferPointer(), &pMyPsRef );
    if ( FAILED( hr ) ){
        ::FatalErrorMsg( L"Shader create error" );            
    }
*/


    LPDIRECT3DTEXTURE9 pTexD3D = static_cast < LPDIRECT3DTEXTURE9 > ( pTexture );
    if ( !pTexD3D )
    {
        g_pLog->Write( L"pTexture==NULL\n" );
        return E_TEXTURE_FORMAT_ERR;
    }

    D3DSURFACE_DESC desc;
    hr = pTexD3D->GetLevelDesc( 0, &desc );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DTexture9::GetLevelDesc() failed. Error: 0x%08X\n", hr );
        return hr;
    }

    TDXRef < IDirect3DVertexShader9 > pVsRef;
    hr = pDev->GetVertexShader( &pVsRef );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::GetVertexShader() failed. Error: 0x%08X\n", hr  );
        return hr;
    }


    TDXRef < IDirect3DTexture9 > pRtRef;
    hr = pDev->CreateTexture( desc.Width, desc.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pRtRef, NULL );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::CreateTexture() failed. Error: 0x%08X\n", hr  );
        return hr;
    }


    TDXRef < IDirect3DVertexDeclaration9 > pVertDeclRef;
    hr = pDev->GetVertexDeclaration( &pVertDeclRef );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::GetVertexDeclaration() failed. Error: 0x%08X\n", hr  );
        return hr;
    }

    
    DWORD OldFVF = 0;
    hr = pDev->GetFVF( &OldFVF );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::GetFVF() failed. Error: 0x%08X\n", hr  );
        return hr;
    }


    TDXRef < IDirect3DBaseTexture9 > pTex0Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex1Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex2Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex3Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex4Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex5Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex6Ref;
    TDXRef < IDirect3DBaseTexture9 > pTex7Ref;
    hr = pDev->GetTexture( 0, &pTex0Ref );
    hr = pDev->GetTexture( 1, &pTex1Ref );
    hr = pDev->GetTexture( 2, &pTex2Ref );
    hr = pDev->GetTexture( 3, &pTex3Ref );
    hr = pDev->GetTexture( 4, &pTex4Ref );
    hr = pDev->GetTexture( 5, &pTex5Ref );
    hr = pDev->GetTexture( 6, &pTex6Ref );
    hr = pDev->GetTexture( 7, &pTex7Ref );
/*
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::GetTexture() failed. Error: 0x%08X\n", hr  );
        return hr;
    }
*/
    
    TDXRef < IDirect3DSurface9 > pOldSur0Ref;
    TDXRef < IDirect3DSurface9 > pOldSur1Ref;
    TDXRef < IDirect3DSurface9 > pOldSur2Ref;
    TDXRef < IDirect3DSurface9 > pOldSur3Ref;
    hr = pDev->GetRenderTarget( 0, &pOldSur0Ref );
    hr = pDev->GetRenderTarget( 1, &pOldSur1Ref );
    hr = pDev->GetRenderTarget( 2, &pOldSur2Ref );
    hr = pDev->GetRenderTarget( 3, &pOldSur3Ref );
/*
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::GetRenderTarget() failed. Error: 0x%08X\n", hr  );
        return hr;
    }
*/           

    BOOL fGetDepthStencilOk = FALSE;
    TDXRef < IDirect3DSurface9 > pOldDepthStencilSurRef;
    hr = pDev->GetDepthStencilSurface( &pOldDepthStencilSurRef );
    if( SUCCEEDED( hr ) )
    {
        fGetDepthStencilOk = TRUE;
    }


    TDXRef < IDirect3DVertexBuffer9 > pVertexBufferRef;
    UINT Stride = 0;
    UINT Offset = 0;
    hr = pDev->GetStreamSource( 0, &pVertexBufferRef, &Offset, &Stride );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"IDirect3DDevice9::GetStreamSource() failed. Error: 0x%08X\n", hr  );
        return hr;
    }

    
    D3DVIEWPORT9 ViewPort;
    pDev->GetViewport( &ViewPort );

    //////////////////////////////////////////////////////////////////////////
    // Save render states
    //////////////////////////////////////////////////////////////////////////
    DWORD RS[ RS_SIZE ] = { 0 };
    for( int i = 0; i < RS_SIZE; i++ ){
        pDev->GetRenderState( RenderStates[ i ].State, &RS[ i ] );
    }

    
    //////////////////////////////////////////////////////////////////////////
    //Save sampler states
    //////////////////////////////////////////////////////////////////////////
    DWORD SS[ SS_SIZE ] = { 0 };
    for ( int i = 0; i < SS_SIZE; i++ )
    {
        pDev->GetSamplerState( 0, SamplerStates[ i ].State, &SS[ i ] ); 
    }


    //////////////////////////////////////////////////////////////////////////
    // Save texture stage states
    //////////////////////////////////////////////////////////////////////////
    DWORD TSS[ TSS_SIZE ] = { 0 };
    for( int i = 0; i < TSS_SIZE; i++ )
    {
        pDev->GetTextureStageState( 0, TextureStageStates[ i ].State, &TSS[ i ] );
    }


    //----------Render to texture--------------
    TDXRef < IDirect3DSurface9 > pDstSurRef;
    hr = pRtRef->GetSurfaceLevel( 0, &pDstSurRef );
    hr = pDstSurRef->GetDesc( &desc );
           
    D3DVIEWPORT9 vp;
    vp.X      = 0;
    vp.Y      = 0;
    vp.Width  = desc.Width;
    vp.Height = desc.Height;
    vp.MinZ   = 0.0f;
    vp.MaxZ   = 1.0f;
    hr = pDev->SetViewport( &vp );

    //hr = pDev->SetDepthStencilSurface( NULL );
    hr = unh_SetDepthStencilSurface( pDev, NULL );


    hr = pDev->SetRenderTarget( 0, pDstSurRef.get() );
    hr = pDev->SetRenderTarget( 1, NULL );
    hr = pDev->SetRenderTarget( 2, NULL );
    hr = pDev->SetRenderTarget( 3, NULL );

    hr = pDev->SetStreamSource( 0, NULL, 0, 0 );

    pDev->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA( 255, 0, 255, 255 ) , 1.0f, 0 );
    float fWidth  = static_cast< float >( desc.Width )  - 0.5f;
    float fHeight = static_cast< float >( desc.Height ) - 0.5f;

    TLVertex v[4];
    v[0].p = D3DXVECTOR4( -0.5f, -0.5f, 0.0f, 1.0f );
    v[0].t = D3DXVECTOR2( 0.0f, 0.0f );

    v[1].p = D3DXVECTOR4( fWidth, -0.5f, 0.0f, 1.0f );
    v[1].t = D3DXVECTOR2( 1.0f, 0.0f );

    v[2].p = D3DXVECTOR4( -0.5f, fHeight, 0.0f, 1.0f );
    v[2].t = D3DXVECTOR2( 0.0f, 1.0f );

    v[3].p = D3DXVECTOR4( fWidth, fHeight, 0.0f, 1.0f );
    v[3].t = D3DXVECTOR2( 1.0f, 1.0f );


    hr = pDev->SetVertexShader( NULL );

    hr = unh_SetPixelShader( pDev, NULL );
    hr = unhSetTexture( pDev, 0, pTexture );//Set source texture
    hr = unhSetTexture( pDev, 1, NULL );//Set source texture
    hr = unhSetTexture( pDev, 2, NULL );
    hr = unhSetTexture( pDev, 3, NULL );
    hr = unhSetTexture( pDev, 4, NULL );
    hr = unhSetTexture( pDev, 5, NULL );
    hr = unhSetTexture( pDev, 6, NULL );
    hr = unhSetTexture( pDev, 7, NULL );


    //hr = pDev->SetVertexDeclaration( NULL );
    hr = pDev->SetFVF( FVF_TLVERTEX );

    // Set new render states
    for ( int i = 0; i < RS_SIZE; i++ )
    {
        pDev->SetRenderState( RenderStates[ i ].State, RenderStates[ i ].SetVal);
    }

    // Set new sampler states
    for ( int i = 0; i < SS_SIZE; i++ )
    {
        pDev->SetSamplerState( 0, SamplerStates[ i ].State, SamplerStates[ i ].SetVal );
    }

    
    // Set new texture stage states
    for( int i = 0; i < TSS_SIZE; i++ )
    {
        pDev->SetTextureStageState( 0, TextureStageStates[ i ].State, TextureStageStates[ i ].SetVal );
    }

    // v1.1.2
    // Reset gamma ramp
    unh_SetGammaRamp(pDev, 0, 0, NULL);


    hr = unhDrawPrimitiveUP( pDev, D3DPT_TRIANGLESTRIP, 2, v, sizeof( TLVertex ) );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"DrawPrimitiveUP() failed. Error: 0x%08X\n", hr  );
    }

    //--------Save render target to file--------------
    hr = D3DXSaveTextureToFileW_( szFile, D3DXIFF_DDS, pRtRef.get(), 0 );
    if( FAILED( hr ) )
    {
        g_pLog->Write( L"D3DX9.D3DXSaveTextureToFileW() failed. Error: 0x%08X\n", hr  );
    }


    //-----------Restore states---------------
    if (lastGamma.IsInited())
    {
        GammaHelper gh = lastGamma.Get();
        unh_SetGammaRamp(pDev, gh.swapChain, gh.flags, &gh.gammaRamp);
    }


    pDev->SetViewport( &ViewPort );

    hr = unhSetTexture( pDev, 0, pTex0Ref.get() );
    hr = unhSetTexture( pDev, 1, pTex1Ref.get() );
    hr = unhSetTexture( pDev, 2, pTex2Ref.get() );
    hr = unhSetTexture( pDev, 3, pTex3Ref.get() );
    hr = unhSetTexture( pDev, 4, pTex4Ref.get() );
    hr = unhSetTexture( pDev, 5, pTex5Ref.get() );
    hr = unhSetTexture( pDev, 6, pTex6Ref.get() );
    hr = unhSetTexture( pDev, 7, pTex7Ref.get() );

    hr = pDev->SetVertexShader( pVsRef.get() );

    if ( LastPS.IsInited() )
    {
        //hr = pDev->SetPixelShader( LastPS.Get() );
        hr = unh_SetPixelShader( pDev, LastPS.Get() );
    }
    else
    {//Reset shader state
        hr = unh_SetPixelShader( pDev, NULL );
    }

    hr = pDev->SetFVF( OldFVF );
    hr = pDev->SetVertexDeclaration( pVertDeclRef.get() );

    hr = pDev->SetRenderTarget( 0, pOldSur0Ref.get() );
    hr = pDev->SetRenderTarget( 1, pOldSur1Ref.get() );
    hr = pDev->SetRenderTarget( 2, pOldSur2Ref.get() );
    hr = pDev->SetRenderTarget( 3, pOldSur3Ref.get() );


    //hr = pDev->SetDepthStencilSurface( pOldDepthStencilSurRef.get() );
    if ( fGetDepthStencilOk )
    {
        hr = unh_SetDepthStencilSurface( pDev, pOldDepthStencilSurRef.get() );
    }
    else
    {
        if( LastDepthStencilSurface.IsInited() )
        {
            hr = unh_SetDepthStencilSurface( pDev, LastDepthStencilSurface.Get() );
        }
    }


    hr = pDev->SetStreamSource( 0, pVertexBufferRef.get(), Offset, Stride );

    for ( int i = 0; i < RS_SIZE; i++ )
    {
        pDev->SetRenderState( RenderStates[ i ].State, RS[ i ] );
    }
            
    for ( int i = 0; i < SS_SIZE; i++ )
    {
        pDev->SetSamplerState( 0, SamplerStates[ i ].State, SS[ i ] );
    }

    for( int i = 0; i < TSS_SIZE; i++ )
    {
        pDev->SetTextureStageState( 0, TextureStageStates[ i ].State, TSS[ i ] );
    }

    return S_OK;
}


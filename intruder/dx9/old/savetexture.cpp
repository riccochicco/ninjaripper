
#include "PreComp.h"
#include "savetexture.h"
#include "textures.h"
#include "predisp.h"
#include "intruder.h"



struct TLVertex
{
    D3DXVECTOR4 p;
    D3DXVECTOR2 t;
};

static const DWORD FVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_TEX1;

DWORD CanSaveTexture( IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture ){
/*
    if( !pTexture ){
        return 0;
    }

    HRESULT hr;
    D3DRESOURCETYPE Type = pTexture->GetType();
    if( Type == D3DRTYPE_TEXTURE || Type == D3DRTYPE_SURFACE ){
        LPDIRECT3DTEXTURE9 pTex = static_cast <LPDIRECT3DTEXTURE9>( pTexture );
        D3DSURFACE_DESC desc;
        hr = pTex->GetLevelDesc( 0, &desc );
        if( desc.Format == D3DFMT_D16 ){
            return 0;
        }
        return 1;
    }
    return 0;
    */
    return 0;
}


DWORD SaveTexture(LPCTSTR szFileName, IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture){
/*
    DWORD res = 0;
    HRESULT hr;
    wchar_t DDS_File[MAX_PATH];

    if( Options.DDS_Textures ){
        lstrcpy( DDS_File, szFileName );
        for(DWORD i=(DWORD)lstrlen(DDS_File); i>0; i--){if(DDS_File[i-1]==TEXT('.')){ DDS_File[i]=0; break; } }
        lstrcat( DDS_File, TEXT("dds" ) );
    }

    __try{
        if( CanSaveTexture( pDev, pTexture ) ){

            HRESULT res1 = D3D9_D3DXSaveTextureToFile(szFileName, D3DXIFF_BMP, pTexture, 0);
            HRESULT res2;
            if( Options.DDS_Textures ){
                res2 = D3D9_D3DXSaveTextureToFile(DDS_File, D3DXIFF_DDS, pTexture, 0);
            }
            if( res1 == D3D_OK )
                return 0;//OK


            LPDIRECT3DTEXTURE9 pTexD3D = static_cast < LPDIRECT3DTEXTURE9 > (pTexture);
            if( !pTexD3D ){
                g_log.Write( TEXT("IDirect3DBaseTexture9 -> IDirect3DTexture9 failed\n") );
                return 1;
            }

            D3DSURFACE_DESC desc;
            hr = pTexD3D->GetLevelDesc( 0, &desc );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DTexture9::GetLevelDesc failed. 0x%08X\n"), hr );
                return 2;
            }
            
            LPDIRECT3DTEXTURE9 pRT = NULL;
            hr = pDev->CreateTexture( desc.Width, desc.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, (LPDIRECT3DTEXTURE9*)&pRT, NULL );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DDevice9::CreateTexture failed. hr: 0x%08X\n"), hr  );
                return 3;
            }

            LPDIRECT3DVERTEXSHADER9 pVS = NULL;
            hr = pDev->GetVertexShader( &pVS );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DDevice9::GetVertexShader failed. hr: 0x%08X\n"), hr  );
                return 4;
            }

            LPDIRECT3DPIXELSHADER9 pPS = NULL;
            hr = pDev->GetPixelShader( &pPS );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DDevice9::GetPixelShader failed. hr: 0x%08X\n"), hr  );
                return 5;
            }            

            LPDIRECT3DVERTEXDECLARATION9 pVERT_DECL = NULL;
            hr = pDev->GetVertexDeclaration( &pVERT_DECL );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DDevice9::GetVertexDeclaration failed. hr: 0x%08X\n"), hr  );
                return 6;
            }
            
            LPDIRECT3DBASETEXTURE9 pTex = NULL;
            hr = pDev->GetTexture( 0, &pTex );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DDevice9::GetTexture failed. hr: 0x%08X\n"), hr  );
                return 7;
            }

            PDIRECT3DSURFACE9 pOldSur = NULL;
            hr = pDev->GetRenderTarget( 0, &pOldSur );
            if( FAILED( hr ) ){
                g_log.Write( TEXT("IDirect3DDevice9::GetRenderTarget failed. hr: 0x%08X\n"), hr  );
                return 10;
            }

//            RECT ScisRect;
//            hr = pDev->GetScissorRect( &ScisRect );

            //----------Render--------------
            PDIRECT3DSURFACE9 pDstSur = NULL;
            hr = pRT->GetSurfaceLevel( 0, &pDstSur );
            hr = pDstSur->GetDesc( &desc );
            hr = pDev->SetRenderTarget( 0, pDstSur );
            pDev->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0,0,0) , 1.0f, 0 );
            float fWidth = static_cast< float >( desc.Width ) - 0.5f;
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


            PFN_IDirect3DDevice9_SetTexture      unhSetTexture      = (PFN_IDirect3DDevice9_SetTexture)     phook_IDirect3DDevice9_SetTexture->GetUnhookedFunc();
            PFN_IDirect3DDevice9_SetVertexShader unhSetVertexShader = (PFN_IDirect3DDevice9_SetVertexShader)phook_IDirect3DDevice9_SetVertexShader->GetUnhookedFunc();
            PFN_IDirect3DDevice9_SetPixelShader  unhSetPixelShader  = (PFN_IDirect3DDevice9_SetPixelShader) phook_IDirect3DDevice9_SetPixelShader->GetUnhookedFunc();
            PFN_IDirect3DDevice9_DrawPrimitiveUP unhDrawPrimitiveUP = (PFN_IDirect3DDevice9_DrawPrimitiveUP)phook_IDirect3DDevice9_DrawPrimitiveUP->GetUnhookedFunc();

            hr = unhSetVertexShader( pDev, NULL );
            hr = unhSetPixelShader( pDev, NULL );
            hr = unhSetTexture( pDev, 0, pTex );
            hr = pDev->SetVertexDeclaration( NULL );
            hr = pDev->SetFVF( FVF_TLVERTEX );

            hr = unhDrawPrimitiveUP( pDev, D3DPT_TRIANGLESTRIP, 2, v, sizeof( TLVertex ) );


            //--------Save render target to file--------------
            hr = D3D9_D3DXSaveTextureToFile( szFileName, D3DXIFF_BMP, pRT, 0 );
            HRESULT hr2;
            if( Options.DDS_Textures ){
                hr2 =D3D9_D3DXSaveTextureToFile(DDS_File, D3DXIFF_DDS, pRT, 0);
            }
            if( FAILED(hr) )
                res = (DWORD)hr;

            pOldSur->Release();
            pDstSur->Release();//release surface


            //-----------Restore states---------------
//            hr = pDev->SetScissorRect( &ScisRect );
            hr = unhSetTexture( pDev, 0, pTex );
            hr = unhSetVertexShader( pDev, pVS );
            hr = unhSetPixelShader( pDev, pPS );
            hr = pDev->SetVertexDeclaration( pVERT_DECL );
            hr = pDev->SetRenderTarget( 0, pOldSur );

            pRT->Release();//release render target
        }
    }
    __except( EXCEPTION_EXECUTE_HANDLER ){
        g_log.Write( TEXT("SaveTexture(). EXCEPTION_EXECUTE_HANDLER\n") );
    }
    return res;

    */
return 0;
}

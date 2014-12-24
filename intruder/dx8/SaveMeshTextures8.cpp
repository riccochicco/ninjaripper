
#include "PreComp.h"
#include "KRipper8.h"




std::string KRipper8::IsMeshTextureAlreadySaved( 
    IDirect3DBaseTexture8 *pTexture, 
    const std::string&     TextureFile
    )
{
    
    for( size_t i = 0; i < FrameTextures.size(); i++ ){
        if( FrameTextures[i].pTexture == pTexture ){
            return FrameTextures[i].TextureFile;
        }
    }

    KFrameTexture FrameTex;
    FrameTex.pTexture   = pTexture;
    FrameTex.TextureFile= TextureFile;
    FrameTextures.push_back( FrameTex );
    std::string foo;
    return foo;
}



DWORD KRipper8::SaveMeshTextures( IDirect3DDevice8* pDev, KMeshTextures2& MeshTextures ){

    for( DWORD i = 0; i < 8; i++ ){
        IDirect3DBaseTexture8* pTexture = NULL;

        HRESULT hr = pDev->GetTexture(i, &pTexture );
        if( FAILED( hr ) ){
            g_pLog->Write( L"IDirect3DDevice8::GetTexture(%d) Error: 0x%08X\n", i, hr );
        }
        else if ( pTexture ){
            std::string  TextureFileA;
            std::wstring TextureFilePath = g_pIntruder->GetFrameTextureSavePath( TextureFileA, KIntruder::EDDS, i );


            std::string AlreadySavedTexture = IsMeshTextureAlreadySaved( pTexture, TextureFileA );

            if( AlreadySavedTexture.size() ){
                //Already Saved Texture. Copy Texture Name To Header
                MeshTextures.Textures.push_back( AlreadySavedTexture );
                g_pLog->Write( L"Texture Stage #%d Already Saved As: %s\n", i, StringToWString( AlreadySavedTexture.c_str() ).c_str()   );
            }
            else{
                //----------------------
                //New Texture In Model. Copy Texture Name To Header
                //----------------------
                
                hr = SaveTexture2File( TextureFilePath.c_str(), pDev, pTexture );
                if( SUCCEEDED(hr) ){
                    MeshTextures.Textures.push_back( TextureFileA );
                    g_pLog->Write( L"Mesh Texture Stage #%d Saved: %s\n", i, TextureFilePath.c_str() );
                }
                else{
                    g_pLog->Write( L"Mesh Texture Save Error: 0x%08X\n", hr );
                    //LogTextureSaveError( pDev, pTexture );
                }
            }
            SAFE_RELEASE( pTexture );
        }
        else{
            g_pLog->Write( L"Mesh Texture Stage #%d Not Exist\n", i);
        }
    }
    g_pIntruder->IncFrameTextureIdx();
    return 0;
}

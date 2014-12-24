
#include "PreComp.h"
#include "KRipper11.h"


//Return already saved texture file path or empty string if not saved
std::string KRipper11::IsMeshTextureAlreadySaved( 
    ID3D11ShaderResourceView* pTexture, 
    const std::string&     TextureFile
    )
{
    //FIX: use map
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



//**************************************
//WARNING!!!!!!!!!!!!!!
//SOLVE CUBE,ARRAY TEXTURES HANDLING
//**************************************

HRESULT KRipper11::SaveMeshTextures( 
    ID3D11DeviceContext* pDevCont,
    KMeshTextures2& TextureHeader 
    )
{
    HRESULT hr;

    KShaderResourceVec ShaderRes( D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT );
    //Init with NULL
    for( size_t i = 0; i < ShaderRes.size(); i++ ){
        ShaderRes[ i ] = NULL;
    }

    pDevCont->PSGetShaderResources( 0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, &ShaderRes[ 0 ] );
    
    for( size_t i = 0; i < ShaderRes.size(); i++ ){
    
        ID3D11ShaderResourceView* pShaderResView = ShaderRes[ i ];
        if( pShaderResView ){
            //Check resource type for "Texture"
            D3D11_SHADER_RESOURCE_VIEW_DESC  Descr;
            pShaderResView->GetDesc( &Descr );
            if(
                ( Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFER ) ||
                ( Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFEREX )
                ){
                    continue;//Skip buffer resources
            }

            std::string  TextureFileA;
            std::wstring TextureFilePath = g_pIntruder->GetFrameTextureSavePath( TextureFileA, KIntruder::EDDS, i );
            std::string  AlreadySavedTexture = IsMeshTextureAlreadySaved( pShaderResView, TextureFileA );


            if( AlreadySavedTexture.size() ){
                //Already Saved Texture. Copy Texture Name To Header
                TextureHeader.Textures.push_back( AlreadySavedTexture );
                g_pLog->Write( L"Texture Stage #%d Already Saved As: %s\n", i, StringToWString( AlreadySavedTexture.c_str() ).c_str()   );
            }
            else{
                //----------------------
                //New Texture In Model. Copy Texture Name To Header
                //----------------------

                hr = SaveTexture2File( TextureFilePath.c_str(), pDevCont, pShaderResView );
                if( SUCCEEDED(hr) ){
                    TextureHeader.Textures.push_back( TextureFileA );
                    g_pLog->Write( L"Mesh Texture Stage #%d Saved: %s\n", i, TextureFilePath.c_str() );
                }
                else{
                    g_pLog->Write( L"Mesh Texture Save Error: 0x%08X\n", hr );

                    //Dump res description
                    DumpShaderResourceView( pShaderResView );
                }        
            }

        }//if
        else{
            //Resource are not set

        }//else
    }
    
    //RELEASE OBJECTS
    for( size_t i = 0; i < ShaderRes.size(); i++ ){
        SAFE_RELEASE( ShaderRes[ i ] );
    }

    g_pIntruder->IncFrameTextureIdx();
    return S_OK;
}


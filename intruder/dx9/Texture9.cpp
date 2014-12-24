#include "PreComp.h"
#include "KRipper9.h"


DWORD KRipper9::IsTextureSaved( IDirect3DBaseTexture9* pTex ){

    if( !pTex )//Texture unset
        return 1;

    for( size_t i = 0; i < TexturesVec.size(); i++ ){
        if( TexturesVec[ i ] == pTex ){
            return 1;
        }
    }
    return 0;
}



void KRipper9::HandleTextureSave(
    IDirect3DDevice9 *pDev, 
    DWORD Sampler, 
    IDirect3DBaseTexture9 *pTexture
    )
{

    g_pIntruder->KeyHandler( this );
    DWORD RipFlag = g_pIntruder->IsTexturesRipKeyPressed();
    if( RipFlag )
    {
        if( !IsTextureSaved( pTexture ) )
        {
            std::wstring TextureFile = g_pIntruder->GetTextureSavePath( KIntruder::EDDS );
            HRESULT hr = SaveTexture2File( TextureFile.c_str(), pDev, pTexture );
            if( SUCCEEDED( hr ) )
            {
                //Saving success
                TexturesVec.push_back( pTexture );
                g_pIntruder->IncTextureIdx();
                g_pLog->Write( L"Texture saved: %s\n", TextureFile.c_str() );
            }
            else
            {
                //Texture save error
                g_pLog->Write( L"Texture save error: 0x%08X\n", hr );
            }
        }
    }
}


HRESULT KRipper9::_IDirect3DDevice9_SetTexture(
    PFN_IDirect3DDevice9_SetTexture e,
    IDirect3DDevice9 *pDev, 
    DWORD Sampler, 
    IDirect3DBaseTexture9 *pTexture
    )
{
    //g_pLog->Write("SetTexture(0x%08X, 0x%08X, 0x%08X)\n", pDev, Sampler, pTexture);
    unhSetTexture = e;

    ::EnterCriticalSection( &cs );
    __try
    {
        HandleTextureSave( pDev, Sampler, pTexture );
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        g_pLog->Write( L"Error: Exception in KRipper9::HandleTextureSave()\n" );
    }
    ::LeaveCriticalSection( &cs );

    return e( pDev, Sampler, pTexture );
}


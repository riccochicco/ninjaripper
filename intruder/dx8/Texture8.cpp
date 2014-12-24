
#include "PreComp.h"
#include "KRipper8.h"


DWORD KRipper8::IsTextureSaved( IDirect3DBaseTexture8* pTex ){

    if( !pTex )//Texture unset
        return 1;

    for( size_t i = 0; i < TexturesVec.size(); i++ ){
        if( TexturesVec[ i ] == pTex ){
            return 1;
        }
    }
    return 0;
}


void KRipper8::HandleTextureSave( 
    IDirect3DDevice8* pDev, 
    DWORD Stage, 
    IDirect3DBaseTexture8* pTexture 
    )
{
    //g_pLog->Write( "IDirect3DDevice8_SetTexture 0x%08X (0x%08X, 0x%08X)\n", pDev, Stage, pTexture );

    g_pIntruder->KeyHandler( this_ );
    DWORD RipFlag = g_pIntruder->IsTexturesRipKeyPressed();
    if (RipFlag)
    {
        if (!this_->IsTextureSaved( pTexture ))
        {
            std::wstring TextureFile = g_pIntruder->GetTextureSavePath( KIntruder::EDDS );
            HRESULT hr = this_->SaveTexture2File( TextureFile.c_str(), pDev, pTexture );
            if (SUCCEEDED( hr ))
            {
                //Saving success
                this_->TexturesVec.push_back(pTexture);
                g_pIntruder->IncTextureIdx();
                g_pLog->Write(L"Texture saved: %s\n", TextureFile.c_str());
            }
            else
            {
                //Texture save error
                g_pLog->Write( L"Texture save error: 0x%08X\n", hr );
            }
        }
    }
}


HRESULT KRipper8::_IDirect3DDevice8_SetTexture( 
    PFN_IDirect3DDevice8_SetTexture e, 
    IDirect3DDevice8* pDev, 
    DWORD Stage, 
    IDirect3DBaseTexture8* pTexture 
    )
{    
    
    ::EnterCriticalSection( &cs );
    __try
    {
        HandleTextureSave( pDev, Stage, pTexture );
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        g_pLog->Write( L"Error: Exception in KRipper8::HandleTextureSave()\n" );
    }
    ::LeaveCriticalSection( &cs );
    
    return  e( pDev, Stage, pTexture );
}



HRESULT KRipper8::SaveTexture2File( LPCTSTR szFile, IDirect3DDevice8* pDev, IDirect3DBaseTexture8* pTexture  )
{
    Dump_TextureDesc2Log( pTexture );
    HRESULT hr = D3DXSaveTextureToFileW_( szFile, D3DXIFF_DDS, pTexture, NULL );
    return hr;
}

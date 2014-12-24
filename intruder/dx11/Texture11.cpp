#include "PreComp.h"
#include "KRipper11.h"


//Forced to save textures check
DWORD KRipper11::IsTextureSaved( ID3D11ShaderResourceView* pTex ){
    if( !pTex )//NULL
        return 1;

    for( size_t i = 0; i < TexturesVec.size(); i++ ){
        if( TexturesVec[ i ] == pTex ){
            return 1;
        }
    }
    return 0;
}

/*
void KRipper11::_ID3D11DeviceContext_VSSetShaderResources(
    PFN_ID3D11DeviceContext_VSSetShaderResources e,
    ID3D11DeviceContext* pDevCont,
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
//    g_pLog->Write( L"ID3D11DeviceContext_VSSetShaderResources( 0x%p, %d, %d, 0x%p )\n",  pDevCont, StartSlot, NumViews, ppShaderResourceViews );
    HandleTexture( pDevCont, StartSlot, NumViews, ppShaderResourceViews );
    return e( pDevCont, StartSlot, NumViews, ppShaderResourceViews );
}


void KRipper11::_ID3D11DeviceContext_GSSetShaderResources(
    PFN_ID3D11DeviceContext_GSSetShaderResources e,
    ID3D11DeviceContext* pDevCont,
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
//    g_pLog->Write( L"ID3D11DeviceContext_GSSetShaderResources( 0x%p, %d, %d, 0x%p )\n",  pDevCont, StartSlot, NumViews, ppShaderResourceViews );
    HandleTexture( pDevCont, StartSlot, NumViews, ppShaderResourceViews );
    return e( pDevCont, StartSlot, NumViews, ppShaderResourceViews );
}
*/


void KRipper11::_ID3D11DeviceContext_PSSetShaderResources(
    PFN_ID3D11DeviceContext_PSSetShaderResources e,
    ID3D11DeviceContext* pDevCont,
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    unhPSSetShaderResources = e;
//    g_pLog->Write( L"ID3D11DeviceContext_PSSetShaderResources( 0x%p, %d, %d, 0x%p )\n",  pDevCont, StartSlot, NumViews, ppShaderResourceViews );

    ::EnterCriticalSection(&cs);
    __try
    {
        HandleTexture( pDevCont, StartSlot, NumViews, ppShaderResourceViews );
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        g_pLog->Write( L"Error: Exception in KRipper11::HandleTexture()\n" );
    }
    ::LeaveCriticalSection(&cs);

    return e( pDevCont, StartSlot, NumViews, ppShaderResourceViews );
}



void KRipper11::HandleTexture(
    ID3D11DeviceContext* pDevCont,
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView *const *ppShaderResourceViews
    )
{
    g_pIntruder->KeyHandler( this );
    DWORD RipFlag = g_pIntruder->IsTexturesRipKeyPressed();
    if (RipFlag)
    {
        for (UINT j = 0; j < NumViews; j++)
        {
            //Resources loop
            ID3D11ShaderResourceView* pShaderResView = ppShaderResourceViews[ j ];
            if (pShaderResView)
            {
                D3D11_SHADER_RESOURCE_VIEW_DESC  Descr;
                pShaderResView->GetDesc( &Descr );
                if ( 
                    ( Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFER )
                    || 
                    ( Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFEREX )
                   )
                {
                    continue;//Skip buffer resources
                }


                if (!IsTextureSaved( pShaderResView ))
                {
                    std::wstring TextureFile = g_pIntruder->GetTextureSavePath( KIntruder::EDDS );
                    HRESULT hr = SaveTexture2File( TextureFile.c_str(), pDevCont, pShaderResView );
                    if (SUCCEEDED( hr ))
                    {
                        //Saving success
                        TexturesVec.push_back( pShaderResView );
                        g_pIntruder->IncTextureIdx();
                        g_pLog->Write( L"Texture saved: %s\n", TextureFile.c_str() );
                    }
                    else
                    {
                        g_pLog->Write( L"Texture save error: 0x%08X\n", hr );
                    }// else
                }// if( !IsTextureSaved( pShaderResView ) )
            }// if( pShaderResView )
        }// for
    }// if( RipFlag )
}

#include "PreComp.h"
#include "KRipper9.h"



//Delete hook
HRESULT KRipper9::_IDirect3DDevice9_SetPixelShader(
    PFN_IDirect3DDevice9_SetPixelShader e,
    IDirect3DDevice9* pDev, 
    IDirect3DPixelShader9* pShader
    )
{
    unhSetPixelShader = e;

    g_pIntruder->KeyHandler( this );
    
    return e(pDev, pShader);
}



HRESULT KRipper9::_IDirect3DDevice9_SetVertexShader(
    PFN_IDirect3DDevice9_SetVertexShader e,
    IDirect3DDevice9 *pDev, 
    IDirect3DVertexShader9 *pShader
    )
{
    unhSetVertexShader = e;
    return e( pDev, pShader );
}

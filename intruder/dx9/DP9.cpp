
#include "PreComp.h"
#include "KRipper9.h"


HRESULT KRipper9::_IDirect3DDevice9_DrawPrimitive(
    PFN_IDirect3DDevice9_DrawPrimitive e,
    IDirect3DDevice9 *pDev, 
    D3DPRIMITIVETYPE Type, 
    UINT StartVertex, 
    UINT PrimitiveCount
    )
{

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinPrim    = g_pIntruder->GetSettings()->dwMinPrimitives;

    ::EnterCriticalSection( &cs );

    if( RipEnabled && ( PrimitiveCount >= MinPrim ) )
    {
        g_pLog->Write( L"IDirect3DDevice9_DrawPrimitive( 0x%p, %d, %d, %d )\n", 
            pDev, Type, StartVertex, PrimitiveCount );

        __try
        {
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            g_pLog->Write( L"Error: IDirect3DDevice9_DrawPrimitive() exception\n\n\n" );
        }
    }
    ::LeaveCriticalSection( &cs );

    return e(pDev, Type, StartVertex, PrimitiveCount);
}

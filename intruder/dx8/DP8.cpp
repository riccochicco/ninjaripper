
#include "PreComp.h"
#include "KRipper8.h"


HRESULT KRipper8::_IDirect3DDevice8_DrawPrimitive(
    PFN_IDirect3DDevice8_DrawPrimitive e,
    IDirect3DDevice8* pDev, 
    D3DPRIMITIVETYPE PrimitiveType, 
    UINT StartVertex, 
    UINT PrimitiveCount )
{

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinPrim    = g_pIntruder->GetSettings()->dwMinPrimitives;

    ::EnterCriticalSection( &cs );
    if( RipEnabled && ( PrimitiveCount >= MinPrim ) ){

        g_pLog->Write( L"IDirect3DDevice8_DrawPrimitive( 0x%p, %d, %d, %d )\n", pDev, PrimitiveType, StartVertex, PrimitiveCount );

        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error: IDirect3DDevice8_DrawPrimitive() exception\n\n\n" );
        }

    }
    ::LeaveCriticalSection( &cs );

    return e( pDev, PrimitiveType, StartVertex, PrimitiveCount );
}

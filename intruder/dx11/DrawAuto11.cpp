
#include "PreComp.h"
#include "KRipper11.h"



void KRipper11::_ID3D11DeviceContext_DrawAuto( 
    PFN_ID3D11DeviceContext_DrawAuto e,
    ID3D11DeviceContext* pDevCont )
{
//    g_pLog->Write( L"ID3D11DeviceContext_DrawAuto( 0x%p )\n", pDevCont );

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();

    ::EnterCriticalSection( &cs );

    if( RipEnabled ){
        g_pLog->Write( L"ID3D11DeviceContext_DrawAuto( 0x%p )\n", pDevCont );
        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error ID3D11DeviceContext_DrawAuto() exception\n\n\n" );
        }
    }
    ::LeaveCriticalSection( &cs );

    return e( pDevCont );
}


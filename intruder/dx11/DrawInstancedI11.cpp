
#include "PreComp.h"
#include "KRipper11.h"




void  KRipper11::_ID3D11DeviceContext_DrawInstancedIndirect(
    PFN_ID3D11DeviceContext_DrawInstancedIndirect e,
    ID3D11DeviceContext* pDevCont,
    ID3D11Buffer *pBufferForArgs,
    UINT AlignedByteOffsetForArgs
    )
{
//    g_pLog->Write( L"ID3D11DeviceContext_DrawInstancedIndirect( 0x%p, 0x%p, %d )\n", pDevCont, pBufferForArgs, AlignedByteOffsetForArgs );

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();

    ::EnterCriticalSection( &cs );

    if( RipEnabled ){
        g_pLog->Write( L"ID3D11DeviceContext_DrawInstancedIndirect( 0x%p, 0x%p, %d )\n", pDevCont, pBufferForArgs, AlignedByteOffsetForArgs );
        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error ID3D11DeviceContext_DrawInstancedIndirect() exception\n\n\n" );
        }
    }
    ::LeaveCriticalSection( &cs );    
    
    return e( pDevCont, pBufferForArgs, AlignedByteOffsetForArgs );
}



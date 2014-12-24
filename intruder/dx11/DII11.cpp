
#include "PreComp.h"
#include "KRipper11.h"


void KRipper11::_ID3D11DeviceContext_DrawIndexedInstanced(
    PFN_ID3D11DeviceContext_DrawIndexedInstanced e,
    ID3D11DeviceContext* pDevCont,
    UINT IndexCountPerInstance,
    UINT InstanceCount,
    UINT StartIndexLocation,
    INT BaseVertexLocation,
    UINT StartInstanceLocation
    )
{
//    g_pLog->Write( L"ID3D11DeviceContext_DrawIndexedInstanced( 0x%p, %d, %d, %d, %d, %d )\n", pDevCont, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinIndeces = g_pIntruder->GetSettings()->dwMinIndicies;

    ::EnterCriticalSection( &cs );

    if( RipEnabled && ( IndexCountPerInstance >= MinIndeces ) ){
        g_pLog->Write( L"ID3D11DeviceContext_DrawIndexedInstanced( 0x%p, %d, %d, %d, %d, %d )\n", pDevCont, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );

        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error ID3D11DeviceContext_DrawIndexedInstanced() exception\n\n\n" );
        }

    }

    ::LeaveCriticalSection( &cs );

    return e( pDevCont, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );
}

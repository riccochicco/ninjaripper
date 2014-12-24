
#include "PreComp.h"
#include "KRipper11.h"



void KRipper11::_ID3D11DeviceContext_DrawInstanced(
    PFN_ID3D11DeviceContext_DrawInstanced e,
    ID3D11DeviceContext* pDevCont,
    UINT VertexCountPerInstance,
    UINT InstanceCount,
    UINT StartVertexLocation,
    UINT StartInstanceLocation
    )
{
//    g_pLog->Write( L"ID3D11DeviceContext_DrawInstanced( 0x%p, %d, %d, %d, %d )\n", pDevCont, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation );

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinVertCnt = g_pIntruder->GetSettings()->dwMinVertexCount;

    ::EnterCriticalSection( &cs );

    if( RipEnabled && ( VertexCountPerInstance >= MinVertCnt ) ){
        g_pLog->Write( L"ID3D11DeviceContext_DrawInstanced( 0x%p, %d, %d, %d, %d )\n", pDevCont, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation );

        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error ID3D11DeviceContext_DrawInstanced() exception\n\n\n" );
        }
    }
    ::LeaveCriticalSection( &cs );


    return e( pDevCont, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation );
}


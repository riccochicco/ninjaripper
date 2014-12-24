
#include "PreComp.h"
#include "KRipper11.h"


void KRipper11::_ID3D11DeviceContext_Draw (
    PFN_ID3D11DeviceContext_Draw e,
    ID3D11DeviceContext* pDevCont,
    UINT VertexCount,
    UINT StartVertexLocation)
{
//    g_pLog->Write( L"ID3D11DeviceContext_Draw( 0x%p, %d, %d )\n", pDevCont, VertexCount, StartVertexLocation );

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinVertCnt = g_pIntruder->GetSettings()->dwMinVertexCount;

    ::EnterCriticalSection( &cs );

    if( RipEnabled && ( VertexCount >= MinVertCnt ) ){
        g_pLog->Write( L"ID3D11DeviceContext_Draw( 0x%p, %d, %d )\n", pDevCont, VertexCount, StartVertexLocation );

        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error ID3D11DeviceContext_Draw() exception\n\n\n" );
        }
    }
    ::LeaveCriticalSection( &cs );

    return e( pDevCont, VertexCount, StartVertexLocation );
}

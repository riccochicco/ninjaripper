
#include "PreComp.h"
#include "KRipper8.h"


HRESULT KRipper8::_IDirect3DDevice8_DrawIndexedPrimitiveUP( 
    PFN_IDirect3DDevice8_DrawIndexedPrimitiveUP e,
    IDirect3DDevice8* pDev, 
    D3DPRIMITIVETYPE PrimitiveType,
    UINT MinVertexIndex,
    UINT NumVertexIndices,
    UINT PrimitiveCount,
    CONST void* pIndexData,
    D3DFORMAT IndexDataFormat,
    CONST void* pVertexStreamZeroData,
    UINT VertexStreamZeroStride
    )
{
    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinPrim    = g_pIntruder->GetSettings()->dwMinPrimitives;

    ::EnterCriticalSection( &cs );
    if( RipEnabled && ( PrimitiveCount >= MinPrim ) ){

        g_pLog->Write( L"IDirect3DDevice8_DrawIndexedPrimitiveUP( 0x%p, %d, %d, %d, %d 0x%p, %d, 0x%p, %d )\n",
            pDev, PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, 
            pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride
            );

        __try{
            g_pLog->Write( L"Error: Not realized\n\n" );
        }
        __except( EXCEPTION_EXECUTE_HANDLER ){
            g_pLog->Write( L"Error: IDirect3DDevice8_DrawIndexedPrimitiveUP() exception\n\n\n" );
        }

    }
    ::LeaveCriticalSection( &cs );

    return e( pDev, PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride );
}

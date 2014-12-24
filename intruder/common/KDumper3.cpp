
#include "PreComp.h"
#include "Output.h"
#include "KDumper.h"



DWORD KDumper::_eUnknownInputType(const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt)
{
    DWORD OutVal = 0;
    CompCnt = 0;
    return OutVal;
}



DWORD KDumper::_eR32G32B32A32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*         pDstBYTE  = (BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 16 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 4 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 4), 4 );
    memcpy( (pDstBYTE + 8), (pSrcBYTE + 8), 4 );
    memcpy( (pDstBYTE + 12),(pSrcBYTE + 12), 4 );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS32 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR32G32B32A32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT        = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    pDstFLOAT[ 2 ] = *( pSrcFLOAT + 2 );
    pDstFLOAT[ 3 ] = *( pSrcFLOAT + 3 );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR32G32B32A32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const INT*    pSrcSINT  = (INT*)pData;
    INT*   pDstSINT         = (INT*)pUnpacked;
    pDstSINT[ 0 ] = *( pSrcSINT + 0 );
    pDstSINT[ 1 ] = *( pSrcSINT + 1 );
    pDstSINT[ 2 ] = *( pSrcSINT + 2 );
    pDstSINT[ 3 ] = *( pSrcSINT + 3 );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal  = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR32G32B32A32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    pDstUINT[ 0 ] = *( pSrcUINT + 0 );
    pDstUINT[ 1 ] = *( pSrcUINT + 1 );
    pDstUINT[ 2 ] = *( pSrcUINT + 2 );
    pDstUINT[ 3 ] = *( pSrcUINT + 3 );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal  = CompCnt * sizeof( UINT );
    return OutVal;
}





DWORD KDumper::_eR32G32B32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE         = (BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 12 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 4 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 4), 4 );
    memcpy( (pDstBYTE + 8), (pSrcBYTE + 8), 4 );
    CompCnt = 3;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS32 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR32G32B32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    pDstFLOAT[ 2 ] = *( pSrcFLOAT + 2 );
    CompCnt = 3;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR32G32B32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const INT*    pSrcSINT  = (INT*)pData;
    INT*   pDstSINT  = (INT*)pUnpacked;
    pDstSINT[ 0 ] = *( pSrcSINT + 0 );
    pDstSINT[ 1 ] = *( pSrcSINT + 1 );
    pDstSINT[ 2 ] = *( pSrcSINT + 2 );
    CompCnt = 3;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal  = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR32G32B32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    pDstUINT[ 0 ] = *( pSrcUINT + 0 );
    pDstUINT[ 1 ] = *( pSrcUINT + 1 );
    pDstUINT[ 2 ] = *( pSrcUINT + 2 );
    CompCnt = 3;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal  = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR16G16B16A16_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 16 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 2 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 2), 2 );
    memcpy( (pDstBYTE + 8), (pSrcBYTE + 4), 2 );
    memcpy( (pDstBYTE + 12),(pSrcBYTE + 6), 2 );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS16 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR16G16B16A16_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const USHORT* pSrcUSHORT= (USHORT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = halfToFloat( *( pSrcUSHORT + 0 ) );
    pDstFLOAT[ 1 ] = halfToFloat( *( pSrcUSHORT + 1 ) );
    pDstFLOAT[ 2 ] = halfToFloat( *( pSrcUSHORT + 2 ) );
    pDstFLOAT[ 3 ] = halfToFloat( *( pSrcUSHORT + 3 ) );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}


//????????????????????????????
//  dword64      wwzzyyxx
//  mem          xxyyzzww
DWORD KDumper::_eR16G16B16A16_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    INT*   pDstSINT  = (INT*)pUnpacked;
    const SHORT*  pSrcSHORT = (SHORT*)pData;
    pDstSINT[ 0 ] = ( INT )( *( pSrcSHORT + 0 ) );
    pDstSINT[ 1 ] = ( INT )( *( pSrcSHORT + 1 ) );
    pDstSINT[ 2 ] = ( INT )( *( pSrcSHORT + 2 ) );
    pDstSINT[ 3 ] = ( INT )( *( pSrcSHORT + 3 ) );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal = CompCnt * sizeof( INT );
    return OutVal;
}


//????????????????????????????
DWORD KDumper::_eR16G16B16A16_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const USHORT* pSrcUSHORT= (USHORT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    pDstUINT[ 0 ] = ( UINT )( *( pSrcUSHORT + 0 ) );
    pDstUINT[ 1 ] = ( UINT )( *( pSrcUSHORT + 1 ) );
    pDstUINT[ 2 ] = ( UINT )( *( pSrcUSHORT + 2 ) );
    pDstUINT[ 3 ] = ( UINT )( *( pSrcUSHORT + 3 ) );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal = CompCnt * sizeof( UINT );
    return OutVal;
}


//????????????????????????????
DWORD KDumper::_eR16G16B16A16_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT= (UINT*)pData;
    FLOAT* pDstFLOAT      = (FLOAT*)pUnpacked;
    
    UINT packedInput = *(pSrcUINT + 0);
    INT signExtendedBits[2];
    signExtendedBits[ 0 ] =  (INT)(packedInput << 16) >> 16;         // x
    signExtendedBits[ 1 ] =  (INT)(packedInput & 0xffff0000) >> 16;  // y
    pDstFLOAT[ 0 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 0 ], 32767);// x
    pDstFLOAT[ 1 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 1 ], 32767);// y

    packedInput = *(pSrcUINT + 1);
    signExtendedBits[ 0 ] =  (INT)(packedInput << 16) >> 16;         // z
    signExtendedBits[ 1 ] =  (INT)(packedInput & 0xffff0000) >> 16;  // w
    pDstFLOAT[ 2 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 0 ], 32767);// z
    pDstFLOAT[ 3 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 1 ], 32767);// w
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



//????????????????????????????
// mem: xxyy zzww
// d64: yyxx wwzz
DWORD KDumper::_eR16G16B16A16_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    UINT packedInput = *( pSrcUINT + 0 );
    pDstFLOAT[ 0 ] = ( FLOAT )  (packedInput      & 0x0000ffff)  / 65535;// x
    pDstFLOAT[ 1 ] = ( FLOAT )  (packedInput>>16)                / 65535;// y

    packedInput = *( pSrcUINT + 1 );
    pDstFLOAT[ 2 ] = ( FLOAT )  (packedInput      & 0x0000ffff)  / 65535;// z
    pDstFLOAT[ 3 ] = ( FLOAT )  (packedInput>>16)                / 65535;// w

    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR32G32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 8 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 4 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 4), 4 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS32 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR32G32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR32G32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const INT*    pSrcSINT  = (INT*)pData;
    INT*   pDstSINT  = (INT*)pUnpacked;
    pDstSINT[ 0 ] = *( pSrcSINT + 0 );
    pDstSINT[ 1 ] = *( pSrcSINT + 1 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal  = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR32G32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    pDstUINT[ 0 ] = *( pSrcUINT + 0 );
    pDstUINT[ 1 ] = *( pSrcUINT + 1 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal  = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR8G8B8A8_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 16 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 1 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 1), 1 );
    memcpy( (pDstBYTE + 8), (pSrcBYTE + 2), 1 );
    memcpy( (pDstBYTE + 12),(pSrcBYTE + 3), 1 );
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS8 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR8G8B8A8_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    INT*   pDstSINT  = (INT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    pDstSINT[ 0 ] =  (INT) (packedInput << 24) >> 24;
    pDstSINT[ 1 ] =  (INT)((packedInput << 16) & 0xff000000) >> 24;
    pDstSINT[ 2 ] =  (INT)((packedInput <<  8) & 0xff000000) >> 24;
    pDstSINT[ 3 ] =  (INT) (packedInput & 0xff000000) >> 24;
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR8G8B8A8_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    pDstUINT[ 0 ] =  packedInput      & 0x000000ff;
    pDstUINT[ 1 ] = (packedInput>> 8) & 0x000000ff;
    pDstUINT[ 2 ] = (packedInput>>16) & 0x000000ff;
    pDstUINT[ 3 ] =  packedInput>>24;
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR8G8B8A8_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    INT signExtendedBits[ 4 ];
    signExtendedBits[ 0 ] =  (INT)( packedInput << 24) >> 24;
    signExtendedBits[ 1 ] =  (INT)((packedInput << 16) & 0xff000000) >> 24;
    signExtendedBits[ 2 ] =  (INT)((packedInput <<  8) & 0xff000000) >> 24;
    signExtendedBits[ 3 ] =  (INT)( packedInput & 0xff000000) >> 24;
    pDstFLOAT[ 0 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 0 ], 127);
    pDstFLOAT[ 1 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 1 ], 127);
    pDstFLOAT[ 2 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 2 ], 127);
    pDstFLOAT[ 3 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 3 ], 127);
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR8G8B8A8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    pDstFLOAT[ 0 ] = ( FLOAT )  (packedInput      & 0x000000ff)  / 255;
    pDstFLOAT[ 1 ] = ( FLOAT )(((packedInput>> 8) & 0x000000ff)) / 255;
    pDstFLOAT[ 2 ] = ( FLOAT )(((packedInput>>16) & 0x000000ff)) / 255;
    pDstFLOAT[ 3 ] = ( FLOAT )  (packedInput>>24)                / 255;
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR16G16_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 8 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 2 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 2), 2 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS16 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR16G16_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const USHORT* pSrcUSHORT= (USHORT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = halfToFloat( *( pSrcUSHORT + 0 ) );
    pDstFLOAT[ 1 ] = halfToFloat( *( pSrcUSHORT + 1 ) );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR16G16_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    INT*   pDstSINT  = (INT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    pDstSINT[ 0 ] = (INT)(packedInput << 16) >> 16;
    pDstSINT[ 1 ] = (INT)(packedInput & 0xffff0000) >> 16;
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR16G16_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    pDstUINT[ 0 ] =  packedInput      & 0x0000ffff;
    pDstUINT[ 1 ] =  packedInput>>16;     
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR16G16_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    INT signExtendedBits[2];
    signExtendedBits[ 0 ] =  (INT)(packedInput << 16) >> 16;
    signExtendedBits[ 1 ] =  (INT)(packedInput & 0xffff0000) >> 16;
    pDstFLOAT[ 0 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 0 ], 32767);
    pDstFLOAT[ 1 ] = D3DX_INT_to_FLOAT(signExtendedBits[ 1 ], 32767);
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR16G16_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    UINT packedInput = *pSrcUINT;
    pDstFLOAT[ 0 ] = ( FLOAT )  (packedInput      & 0x0000ffff)  / 65535;
    pDstFLOAT[ 1 ] = ( FLOAT )  (packedInput>>16)                / 65535;
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 4 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 4 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS32 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const INT*    pSrcSINT  = (INT*)pData;
    INT*   pDstSINT  = (INT*)pUnpacked;
    pDstSINT[ 0 ] = *( pSrcSINT + 0 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal  = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    pDstUINT[ 0 ] = *( pSrcUINT + 0 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal  = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR8G8_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 8 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 1 );
    memcpy( (pDstBYTE + 4), (pSrcBYTE + 4), 1 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS8 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR8G8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    
    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;

    pDstFLOAT[ 0 ] = (FLOAT)  (packedInput      & 0x000000ff)  / 255;
    pDstFLOAT[ 1 ] = (FLOAT)(((packedInput>> 8) & 0x000000ff)) / 255;
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR8G8_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    UINT*  pDstUINT  = (UINT*)pUnpacked;

    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;
    
    pDstUINT[ 0 ] = (UINT)(  packedInput      & 0x000000ff );
    pDstUINT[ 1 ] = (UINT)( (packedInput>> 8) & 0x000000ff );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal  = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR8G8_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;

    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;

    INT signExtendedBits[ 2 ];
    signExtendedBits[ 0 ] = (INT)(packedInput  << 24) >> 24;
    signExtendedBits[ 1 ] = (INT)((packedInput << 16) & 0xff000000) >> 24;
    pDstFLOAT[ 0 ] = D3DX_INT_to_FLOAT( signExtendedBits[ 0 ], 127 );
    pDstFLOAT[ 1 ] = D3DX_INT_to_FLOAT( signExtendedBits[ 1 ], 127 );
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR8G8_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    INT*          pDstSINT  = (INT*)pUnpacked;
    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;
    pDstSINT[ 0 ] = (INT) (packedInput << 24) >> 24;
    pDstSINT[ 1 ] = (INT)((packedInput << 16) & 0xff000000) >> 24;
    CompCnt = 2;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal  = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR16_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 4 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 2 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS16 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR16_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const USHORT* pSrcUSHORT= (USHORT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = halfToFloat( *( pSrcUSHORT + 0 ) );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR16_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;
    pDstFLOAT[ 0 ] = (FLOAT)  (packedInput & 0x0000ffff)  / 65535;
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR16_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    pDstUINT[ 0 ] =  (UINT)packedInput & 0x0000ffff;
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR16_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;
    INT signExtendedBits[ 1 ];
    signExtendedBits[ 0 ] =  (INT)(packedInput << 16) >> 16;
    pDstFLOAT[ 0 ] = D3DX_INT_to_FLOAT( signExtendedBits[ 0 ], 32767);
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR16_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    INT*   pDstSINT  = (INT*)pUnpacked;
    const USHORT*  pSrcUSHORT  = (USHORT*)pData;
    USHORT Input = *pSrcUSHORT;
    UINT packedInput = (UINT)Input;
    pDstSINT[ 0 ] = (INT)(packedInput << 16) >> 16;
    return OutVal;
}





//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////




DWORD KDumper::_eR8_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE*  pDstBYTE  =(BYTE*)pUnpacked;
    memset( pDstBYTE, 0, 4 );
    memcpy( (pDstBYTE + 0), (pSrcBYTE + 0), 1 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, ETYPELESS8 );
    OutVal  = CompCnt * 4;
    return OutVal;
}



DWORD KDumper::_eR8_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE Input = *pSrcBYTE;
    UINT packedInput = (UINT)Input;
    pDstUINT[ 0 ] =  packedInput  & 0x000000ff;
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eR8_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    INT*          pDstSINT  = (INT*)pUnpacked;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE Input = *pSrcBYTE;
    UINT packedInput = (UINT)Input;
    pDstSINT[ 0 ]    = (INT) (packedInput << 24) >> 24;
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, ESINT );
    OutVal = CompCnt * sizeof( INT );
    return OutVal;
}



DWORD KDumper::_eR8_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE Input = *pSrcBYTE;
    UINT packedInput = (UINT)Input;
    INT signExtendedBits[ 1 ];
    signExtendedBits[ 0 ] = (INT)(packedInput  << 24) >> 24;
    pDstFLOAT[ 0 ] = D3DX_INT_to_FLOAT( signExtendedBits[ 0 ], 127 );
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    const BYTE*   pSrcBYTE  = (BYTE*)pData;
    BYTE Input = *pSrcBYTE;
    UINT packedInput = (UINT)Input;
    pDstFLOAT[ 0 ] = (FLOAT)  (packedInput & 0x000000ff) / 255;
    CompCnt = 1;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eFLOAT5( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    pDstFLOAT[ 2 ] = *( pSrcFLOAT + 2 );
    pDstFLOAT[ 3 ] = *( pSrcFLOAT + 3 );
    pDstFLOAT[ 4 ] = *( pSrcFLOAT + 4 );
    CompCnt = 5;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eFLOAT6( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    pDstFLOAT[ 2 ] = *( pSrcFLOAT + 2 );
    pDstFLOAT[ 3 ] = *( pSrcFLOAT + 3 );
    pDstFLOAT[ 4 ] = *( pSrcFLOAT + 4 );
    pDstFLOAT[ 5 ] = *( pSrcFLOAT + 5 );
    CompCnt = 6;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eFLOAT7( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    pDstFLOAT[ 2 ] = *( pSrcFLOAT + 2 );
    pDstFLOAT[ 3 ] = *( pSrcFLOAT + 3 );
    pDstFLOAT[ 4 ] = *( pSrcFLOAT + 4 );
    pDstFLOAT[ 5 ] = *( pSrcFLOAT + 5 );
    pDstFLOAT[ 6 ] = *( pSrcFLOAT + 6 );
    CompCnt = 7;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eFLOAT8( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const FLOAT*  pSrcFLOAT = (FLOAT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    pDstFLOAT[ 0 ] = *( pSrcFLOAT + 0 );
    pDstFLOAT[ 1 ] = *( pSrcFLOAT + 1 );
    pDstFLOAT[ 2 ] = *( pSrcFLOAT + 2 );
    pDstFLOAT[ 3 ] = *( pSrcFLOAT + 3 );
    pDstFLOAT[ 4 ] = *( pSrcFLOAT + 4 );
    pDstFLOAT[ 5 ] = *( pSrcFLOAT + 5 );
    pDstFLOAT[ 6 ] = *( pSrcFLOAT + 6 );
    pDstFLOAT[ 7 ] = *( pSrcFLOAT + 7 );
    CompCnt = 8;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eUDEC3( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    UINT*  pDstUINT  = (UINT*)pUnpacked;
    UINT compressedValue = *( pSrcUINT + 0 );
    pDstUINT[ 0 ] = (   (compressedValue>>22 ) );
    pDstUINT[ 1 ] = ( ( (compressedValue>>12 ) & 0x3ff) );
    pDstUINT[ 2 ] = ( ( (compressedValue>>2  ) & 0x3ff) );
    CompCnt = 3;
    InitTypeMap( pTypeMap, CompCnt, EUINT );
    OutVal  = CompCnt * sizeof( UINT );
    return OutVal;
}



DWORD KDumper::_eDEC3N( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    UINT compressedValue = *( pSrcUINT + 0 );
    pDstFLOAT[ 0 ] = ( FLOAT )(   (compressedValue>>22)          - 512) / 511.0f;
    pDstFLOAT[ 1 ] = ( FLOAT )( ( (compressedValue>>12) & 0x3ff) - 512) / 511.0f;
    pDstFLOAT[ 2 ] = ( FLOAT )( ( (compressedValue>>2 ) & 0x3ff) - 512) / 511.0f;
    CompCnt = 3;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eR10G10B10A2_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    DWORD packedInput = *( pSrcUINT + 0 );
    pDstFLOAT[ 0 ] = (FLOAT)  (packedInput      & 0x000003ff)  / 1023;
    pDstFLOAT[ 1 ] = (FLOAT)(((packedInput>>10) & 0x000003ff)) / 1023;
    pDstFLOAT[ 2 ] = (FLOAT)(((packedInput>>20) & 0x000003ff)) / 1023;
    pDstFLOAT[ 3 ] = (FLOAT)(((packedInput>>30) & 0x00000003)) / 3;
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}



DWORD KDumper::_eB8G8R8A8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt )
{
    DWORD OutVal = 0;
    const UINT*   pSrcUINT  = (UINT*)pData;
    FLOAT* pDstFLOAT = (FLOAT*)pUnpacked;
    DWORD packedInput = *( pSrcUINT + 0 );
    pDstFLOAT[ 2 ] = (FLOAT)  (packedInput      & 0x000000ff)  / 255;
    pDstFLOAT[ 1 ] = (FLOAT)(((packedInput>> 8) & 0x000000ff)) / 255;
    pDstFLOAT[ 0 ] = (FLOAT)(((packedInput>>16) & 0x000000ff)) / 255;
    pDstFLOAT[ 3 ] = (FLOAT)  (packedInput>>24)                / 255;
    CompCnt = 4;
    InitTypeMap( pTypeMap, CompCnt, EFLOAT );
    OutVal  = CompCnt * sizeof( FLOAT );
    return OutVal;
}


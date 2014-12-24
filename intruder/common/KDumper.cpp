
#include "PreComp.h"
#include "Output.h"
#include "KDumper.h"


FLOAT KDumper::D3DX_INT_to_FLOAT(INT _V, FLOAT _Scale)
{
    FLOAT Scaled = (FLOAT)_V / _Scale;
    // The integer is a two's-complement signed
    // number so the negative range is slightly
    // larger than the positive range, meaning
    // the scaled value can be slight less than -1.
    // Clamp to keep the float range [-1, 1].
    return max(Scaled, -1.0f);
}




DWORD KDumper::halfToFloatI(USHORT y){
    register int s = (y >> 15) & 0x00000001;
    register int e = (y >> 10) & 0x0000001f;
    register int m =  y        & 0x000003ff;

    if (e == 0)
    {
        if (m == 0) // Plus or minus zero
            return s << 31;

        else // Denormalized number -- renormalize it
        {
            while (!(m & 0x00000400))
            {
                m <<= 1;
                e -=  1;
            }

            e += 1;
            m &= ~0x00000400;
        }
    }
    else if (e == 31)
    {
        if (m == 0) // Inf
            return (s << 31) | 0x7f800000;
        else // NaN
            return (s << 31) | 0x7f800000 | (m << 13);
    }

    e = e + (127 - 15);
    m = m << 13;

    return (s << 31) | (e << 23) | m;
}


float KDumper::halfToFloat(USHORT y){

    union { float f; DWORD i; } v;
    v.i = halfToFloatI(y);
    return v.f;
}


void KDumper::DumpVertSemantic( 
    
    EInputType SrcType,

    BYTE* pSrc, 
    DWORD SrcOffs, 
    DWORD SrcVertSize, 

    BYTE* pDst, 
    DWORD DstOffs,
    DWORD DstVertSize,

    DWORD VertexCnt
    )
{
    
    PFN_DECODER decoder = getDecoder( SrcType );
    
    for( DWORD i = 0; i < VertexCnt; i++ )
    {
        BYTE UnpackedData[ MAX_UNPACKED_LEN ];
        KDumper::EOutputType TypeMap[ MAX_TYPEMAP_SIZE ];
        DWORD CompCnt = 0;
        DWORD UnpSize = decoder( pSrc + SrcOffs, UnpackedData, TypeMap, CompCnt );

        //Copy unpacked data to destination buffer
        memcpy( pDst + DstOffs, UnpackedData, UnpSize );

        pSrc += SrcVertSize;
        pDst += DstVertSize;
    }
}




HRESULT KDumper::SaveMeshToRIPFile2(
    const std::wstring& File,
    const KRipHeader& RipHeader,
    const KOutputVertexDeclaration& VertDecl,
    const KMeshTextures2& MeshTextures,
    const KMeshShaders2& MeshShaders,
    const void* pIndexData,
    const void* pVertData
    )
{
    DWORD VertDataLen  = RipHeader.VertexSize * RipHeader.dwVertexesCnt ;
    DWORD IndexDataLen = sizeof( KFace ) * RipHeader.dwFacesCnt;// 3 * 4 * FaceCount  idx0, idx1, idx2

    FILE* fFile = NULL;
    errno_t err = _wfopen_s( &fFile, File.c_str(), L"wb" );
    if( err )
        return 1;//Error

    fwrite( &RipHeader, sizeof( RipHeader ), 1, fFile );//Header
    

    //////////////////////////////////////////////////////////////////////////
    //Save Vertex declaration
    for( size_t i = 0; i < VertDecl.Decl.size(); i++ ){
        KOutputVertexElement Elem = VertDecl.Decl[i];

        //Semantic save
        fwrite( Elem.UsageSemantic, 1 + strlen( Elem.UsageSemantic ), 1, fFile );

        //Semantic index
        fwrite( &Elem.SemanticIndex, sizeof( Elem.SemanticIndex ), 1, fFile );

        //Element offset
        fwrite( &Elem.Offset, sizeof( Elem.Offset ), 1, fFile );

        //Element size
        fwrite( &Elem.Size, sizeof( Elem.Size ), 1, fFile );

        //Typemap elements count
        fwrite( &Elem.TypeMapElements, sizeof( Elem.TypeMapElements ), 1, fFile );

        for( DWORD j = 0; j < Elem.TypeMapElements; j++ ){
            fwrite( &Elem.TypeMap[ j ], sizeof( Elem.TypeMapElements ), 1, fFile );
        }

    }

    //////////////////////////////////////////////////////////////////////////
    //Save textures
    for( DWORD i = 0; i < RipHeader.TextureFilesCnt; i++ ){
        std::string File = MeshTextures.Textures[ i ];
        fwrite( File.c_str(), File.size() + 1, 1, fFile );
    }

    //////////////////////////////////////////////////////////////////////////
    //Save shaders
    for( DWORD i = 0; i < RipHeader.ShaderFilesCnt; i++ ){
        std::string File = MeshShaders.Shaders[ i ];
        fwrite( File.c_str(), File.size() + 1, 1, fFile );
    }

    //////////////////////////////////////////////////////////////////////////
    //Index data
    fwrite( pIndexData, IndexDataLen, 1 , fFile );//Indexes

    //////////////////////////////////////////////////////////////////////////
    //Vertex data
    fwrite( pVertData, VertDataLen, 1, fFile );//Vertexes

    fclose( fFile );
    return S_OK;
}



DWORD KDumper::FacesCntFromIndexCnt( UINT IndexCount, EPrimitiveType PrimType )
{
    if( PrimType == KDumper::eTriangleList ){
        return IndexCount / 3;// Three indexes per primitive
    }
    else if( PrimType == KDumper::eTriangleStrip ){
        return IndexCount - 2;
    }
    return 0;
}




void KDumper::AddBaseVertexLocation( 
    KFACES* pFaceData,
    INT BaseIdx
    )
{
    DWORD PrimCnt = pFaceData->PrimitivesCnt;
    KFace* pFaces = pFaceData->pFaces;

    for( DWORD i = 0; i < PrimCnt; i++ ){
        pFaces[ i ].i0 += BaseIdx;
        pFaces[ i ].i1 += BaseIdx;
        pFaces[ i ].i2 += BaseIdx;
    }

}



/*
Quick idea:
DEC3N
uint32 compressedValue = ...
float x = float((compressedValue>>22) - 512)/511.0f;
float y = float(((compressedValue>>12) & 0x3ff) - 512)/511.0f;
float z = float(((compressedValue>>2) & 0x3ff) - 512)/511.0f;

UDEC3N
uint32 compressedValue = ...
float x = float((compressedValue>>22) )/1023.0f;
float y = float(((compressedValue>>12) & 0x3ff) )/1023.0f;
float z = float(((compressedValue>>2) & 0x3ff) )/1023.0f;

*/


KDumper::PFN_DECODER KDumper::getDecoder( EInputType id )
{
    static PFN_DECODER funcArray[ eLast ] =
    {
        _eUnknownInputType,
        _eR32G32B32A32_TYPELESS,
        _eR32G32B32A32_FLOAT,
        _eR32G32B32A32_SINT,
        _eR32G32B32A32_UINT,
        _eR32G32B32_TYPELESS,
        _eR32G32B32_FLOAT,
        _eR32G32B32_SINT,
        _eR32G32B32_UINT,
        _eR16G16B16A16_TYPELESS,
        _eR16G16B16A16_FLOAT,
        _eR16G16B16A16_SINT,
        _eR16G16B16A16_UINT,
        _eR16G16B16A16_SNORM,
        _eR16G16B16A16_UNORM,
        _eR32G32_TYPELESS,
        _eR32G32_FLOAT,
        _eR32G32_SINT,
        _eR32G32_UINT,
        _eR8G8B8A8_TYPELESS,
        _eR8G8B8A8_SINT,
        _eR8G8B8A8_UINT,
        _eR8G8B8A8_SNORM,
        _eR8G8B8A8_UNORM,
        _eR16G16_TYPELESS,
        _eR16G16_FLOAT,
        _eR16G16_SINT,
        _eR16G16_UINT,
        _eR16G16_SNORM,
        _eR16G16_UNORM,
        _eR32_TYPELESS,
        _eR32_FLOAT,
        _eR32_SINT,
        _eR32_UINT,
        _eR8G8_TYPELESS,
        _eR8G8_UNORM,
        _eR8G8_UINT,
        _eR8G8_SNORM,
        _eR8G8_SINT,
        _eR16_TYPELESS,
        _eR16_FLOAT,
        _eR16_UNORM,
        _eR16_UINT,
        _eR16_SNORM,
        _eR16_SINT,
        _eR8_TYPELESS,
        _eR8_UINT,
        _eR8_SINT,
        _eR8_SNORM,
        _eR8_UNORM,
        _eFLOAT5,
        _eFLOAT6,
        _eFLOAT7,
        _eFLOAT8,
        _eUDEC3,
        _eDEC3N,
        _eR10G10B10A2_UNORM,
        _eB8G8R8A8_UNORM
    };


    return funcArray[ id ];
}


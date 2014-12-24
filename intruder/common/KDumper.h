#pragma once


/*!
Helper class. Contain common functions for work with indexes
vertexes, data conversion, index generation etc
*/


#define MAX_UNPACKED_LEN 64


struct KVERTICES{

    DWORD VertexCount;
    DWORD VertexSize;
    BYTE* pVertices;

    KVERTICES( DWORD VertexCount_, DWORD VertexSize_ ):
    VertexCount( VertexCount_ ),
    VertexSize( VertexSize_ )
    {
        pVertices = new BYTE[ VertexCount * VertexSize ];
    }

    ~KVERTICES(){
        SAFE_DELETE_ARRAY( pVertices );
    }

};


struct KFACES{
    DWORD PrimitivesCnt;
    DWORD MinIdx;
    DWORD MaxIdx;
    KFace* pFaces;

    KFACES( DWORD PrimCnt ):
    PrimitivesCnt( PrimCnt ),
    pFaces( NULL ),
    MinIdx( 0 ),
    MaxIdx( 0 )
    {
        pFaces = new ( std::nothrow ) KFace[ PrimCnt ];
    }

    ~KFACES(){
        SAFE_DELETE_ARRAY( pFaces );
    }

    DWORD GetVertexCount(){
        return 1 + MaxIdx - MinIdx;
    }

};



class KDumper{
public:

    enum EPrimitiveType
    {
        ePointList,
        eLineList,
        eLineStrip,
        eTriangleList,
        eTriangleStrip,
        eTriangleFan,
        eUnknownPrimitiveType,
        eEPrimitiveTypeForce = 0xFFFFFFFFUL
    };

    static bool IsPrimitiveTypeSupported( EPrimitiveType t );


    //******************************************
    // WARNING
    // NOT modify enum. Add to end!!!!
    //
    // Modify also:
    // Add handler!!! in KDumper3.cpp
    // KDumper::GetDecoder()
    // KDumper::EInputType2Str()
    // KDumper::GetInputTypeSize()
    //******************************************
    enum EInputType
    {
        eUnknownInputType = 0,

        eR32G32B32A32_TYPELESS,
        eR32G32B32A32_FLOAT,    //
        eR32G32B32A32_SINT,
        eR32G32B32A32_UINT,

        eR32G32B32_TYPELESS,
        eR32G32B32_FLOAT,       //
        eR32G32B32_SINT,
        eR32G32B32_UINT,

        eR16G16B16A16_TYPELESS,
        eR16G16B16A16_FLOAT,    // Float 16 bit 4 comp
        eR16G16B16A16_SINT,     // Signed int 16 bit  4 comp
        eR16G16B16A16_UINT,     // Unsigned int 16 bit  4 comp
        eR16G16B16A16_SNORM,    // Signed normalized int 16 bit 4 comp
        eR16G16B16A16_UNORM,    // Unsigned normalized int 16 bit 4 comp
        
        eR32G32_TYPELESS,
        eR32G32_FLOAT,          // 
        eR32G32_SINT,
        eR32G32_UINT,
        
        eR8G8B8A8_TYPELESS,
        eR8G8B8A8_SINT,         // Signed int 8bit 4 comp
        eR8G8B8A8_UINT,         // Unsigned int 8bit 4 comp
        eR8G8B8A8_SNORM,        // Signed normalized 8 bit 4 comp
        eR8G8B8A8_UNORM,        // Unsigned normalized 8 bit 4 comp

        eR16G16_TYPELESS,       //
        eR16G16_FLOAT,          // Float 16 bit 2 comp
        eR16G16_SINT,           // Signed int 16 bit  2 comp
        eR16G16_UINT,           // Unsigned int 16 bit  2 comp
        eR16G16_SNORM,          // Signed normalized int 16 bit 2 comp
        eR16G16_UNORM,          // Unsigned normalized int 16 bit 2 comp

        eR32_TYPELESS,
        eR32_FLOAT,             // 32 bit float 1 comp
        eR32_SINT,
        eR32_UINT,        

        eR8G8_TYPELESS,
        eR8G8_UNORM,
        eR8G8_UINT,
        eR8G8_SNORM,
        eR8G8_SINT,

        eR16_TYPELESS,
        eR16_FLOAT,            // Float 16 bit 1 comp
        eR16_UNORM,
        eR16_UINT,
        eR16_SNORM,
        eR16_SINT,

        eR8_TYPELESS,
        eR8_UINT,
        eR8_SINT,
        eR8_SNORM,
        eR8_UNORM,

        eFLOAT5,//D3D8 legacy
        eFLOAT6,
        eFLOAT7,
        eFLOAT8,

        eUDEC3, //D3D9 legacy types
        eDEC3N,

        eR10G10B10A2_UNORM,
        eB8G8R8A8_UNORM,
        eLast,
        eINPUT_TYPE_FORCE_DWORD = 0xFFFFFFFFUL
    };


    enum EOutputType
    {
        EFLOAT      = 0,
        EUINT       = 1,
        ESINT       = 2,
        ETYPELESS8  = 3,
        ETYPELESS16 = 4,
        ETYPELESS32 = 5,
        ETYPENOTSET = 6,
        EOUTPUT_TYPE_FORCE_DWORD = 0xFFFFFFFFUL
    };

    static DWORD GetInputTypeSize( EInputType t );

    //Function pointer
    typedef  DWORD (*PFN_DECODER)( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt);

    static PFN_DECODER getDecoder( EInputType );


    //Input vertex. Common for all rippers
    struct KInputVertexElement
    {
        KInputVertexElement():
        Stream( 0 ),
        Offset( 0 ),
        Size( 0 ),
        Type( KDumper::eUnknownInputType ),
        SemanticIndex( 0 )
        {
            ZeroMemory( UsageSemantic, SEMANTIC_LEN );
        }

        char  UsageSemantic[ SEMANTIC_LEN ];//"POSITION", "NORMAL","TEXCOORD"...
        DWORD SemanticIndex;
        DWORD Stream;
        DWORD Offset;//Element offset from vertex start in bytes
        DWORD Size;  //Element size in bytes
        KDumper::EInputType Type;
    };


    struct KInputVertexDeclaration
    {
        std::vector < KInputVertexElement > Decl;

        DWORD GetStreamVertexSize( DWORD Stream )const
        {
            DWORD Size = 0;
            for( size_t i = 0; i < Decl.size(); i++ )
            {
                if( Decl[i].Stream == Stream )
                {
                    Size += Decl[i].Size;
                }
            }
            return Size;
        }
    };

    static void DumpInputVertexDeclaration2Log( const KInputVertexDeclaration& );
    static const wchar_t* EInputType2Str( EInputType t );
    static const wchar_t* EOutputType2Str( EOutputType t );

    //////////////////////////////////////////////////////////////////////////
    //Output
    struct KOutputVertexElement
    {
        char  UsageSemantic[ SEMANTIC_LEN ];//"POSITION", "NORMAL", "TEXCOORD"
        DWORD SemanticIndex;
        DWORD Offset;//Element offset from vertex start in bytes
        DWORD Size;  //Element size in bytes

        DWORD TypeMapElements;//Element type map size
        EOutputType TypeMap[ MAX_TYPEMAP_SIZE ];


        KOutputVertexElement():
        Offset( 0 ),
        Size( 0 ),
        SemanticIndex( 0 ),
        TypeMapElements( 0 )
        {
            memset( UsageSemantic, 0, SEMANTIC_LEN );

            for( DWORD i = 0; i < MAX_TYPEMAP_SIZE; i++ )
            {
                TypeMap[ i ] = ETYPENOTSET;
            }

        }
    };

    struct KOutputVertexDeclaration
    {
        std::vector < KOutputVertexElement > Decl;

        DWORD GetVertexSize()
        {
            DWORD OutSize = 0;
            for( size_t i = 0; i < Decl.size(); i++ )
            {
                OutSize += Decl[ i ].Size;
            }
            return OutSize;
        }
    };

    static HRESULT CreateKOutputVertexDeclaration( 
        const KInputVertexDeclaration& InputDecl, 
        KOutputVertexDeclaration& OutputDecl 
        );

    static void DumpOutputVertexDeclaration2Log( const KOutputVertexDeclaration& VertDecl );





    virtual ~KDumper(){}
    KDumper(){}

    static float halfToFloat(USHORT y);
    static DWORD halfToFloatI(USHORT y);

    static void DumpVertSemantic(
        EInputType SrcType,

        BYTE* pSrc, 
        DWORD SrcOffs, 
        DWORD SrcVertSize, 

        BYTE* pDst, 
        DWORD DstOffs,
        DWORD DstVertSize,

        DWORD VertexCnt
        );


    static HRESULT SaveMeshToRIPFile2(
        const std::wstring& File,
        const KRipHeader& RipHeader,
        const KOutputVertexDeclaration& VertDecl,
        const KMeshTextures2& MeshTextures,
        const KMeshShaders2& MeshShaders,
        const void* pIndexData,
        const void* pVertData
        );

    static const wchar_t* PrimTopology2Str( EPrimitiveType t );

    static DWORD FacesCntFromIndexCnt( UINT IndexCount, EPrimitiveType PrimType );


    static void GetMax( DWORD v, DWORD& MaxVal ){
        MaxVal = ( v > MaxVal ) ? v : MaxVal;
    }

    static void GetMin( DWORD v, DWORD& MinVal ){
        MinVal = ( v < MinVal ) ? v : MinVal;
    }

    template< class T >
    static DWORD GetMaxIndex2( EPrimitiveType Type, T* pIdx, DWORD dwPrimCount );

    template< class T >
    static DWORD GetMinIndex2( EPrimitiveType Type, T* pIdx, DWORD dwPrimCount );


    template < class T >
    static void DumpIndexes2(
        KFACES* pDst,
        T* pSrc, 
        EPrimitiveType Type
        );

    static void AddBaseVertexLocation( KFACES* pFaceData, INT BaseIdx );

    static void PrepareHeader( 
        KRipHeader&, 
        const KInputVertexDeclaration& InpDecl,
        const KFACES&, 
        const KVERTICES&, 
        const KMeshTextures2&, 
        const KMeshShaders2& 
        );


private:
    static FLOAT D3DX_INT_to_FLOAT(INT _V, FLOAT _Scale);

    static /*__forceinline */ void InitTypeMap( EOutputType* p, DWORD Cnt, EOutputType Type ){
        for( DWORD i = 0; i < Cnt; i++ ){
            p[ i ] = Type;
        }
    }


    static DWORD _eUnknownInputType( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32A32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32A32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32A32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32A32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32B32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16B16A16_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16B16A16_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16B16A16_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16B16A16_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16B16A16_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16B16A16_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32G32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8B8A8_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8B8A8_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8B8A8_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8B8A8_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8B8A8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16G16_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR32_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8G8_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16_FLOAT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR16_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8_TYPELESS( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8_UINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8_SINT( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8_SNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eFLOAT5( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eFLOAT6( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eFLOAT7( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eFLOAT8( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eUDEC3( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eDEC3N( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eR10G10B10A2_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );
    static DWORD _eB8G8R8A8_UNORM( const void* pData, void* pUnpacked, EOutputType* pTypeMap, DWORD& CompCnt );

};






template< class T >
DWORD KDumper::GetMaxIndex2( EPrimitiveType Type, T* pIdx, DWORD dwPrimCount )
{
    T* pSrc=pIdx;
    DWORD Max=0;

    if( Type == eTriangleList ){
        for( DWORD i = 0; i < dwPrimCount; i++ ){
            GetMax( ( T )( *pSrc ), Max );
            pSrc++;
            GetMax( ( T )( *pSrc ), Max );
            pSrc++;
            GetMax( ( T )( *pSrc ), Max );
            pSrc++;
        }
    }
    else if( Type == eTriangleStrip ){
        DWORD k=0;
        for(DWORD i = 0; i < dwPrimCount; i++){
            GetMax( ( T )( *pSrc ), Max);
            if((k & 0x1)!=0){//WAS ==
                GetMax( ( T )( *( pSrc+1 ) ), Max );
                GetMax( ( T )( *( pSrc+2 ) ), Max );
            }
            else{
                GetMax( ( T )( *( pSrc+2 ) ), Max );
                GetMax( ( T )( *( pSrc+1 ) ), Max );
            }
            pSrc++;
            k++;
        }
    }
    return Max;
}




template< class T >
DWORD KDumper::GetMinIndex2( EPrimitiveType Type, T* pIdx, DWORD dwPrimCount )
{
    T* pSrc = pIdx;
    DWORD Min = 0xFFFFFFFF;

    if( Type == eTriangleList ){
        for( DWORD i = 0; i < dwPrimCount; i++ ){
            GetMin( ( T )( *pSrc ), Min );
            pSrc++;
            GetMin( ( T )( *pSrc ), Min );
            pSrc++;
            GetMin( ( T )( *pSrc ), Min );
            pSrc++;
        }
    }
    else if( Type == eTriangleStrip ){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            GetMin( ( T )( *pSrc ), Min );
            if((k & 0x1)!=0){//WAS ==
                GetMin( ( T )( *( pSrc+1 ) ), Min );
                GetMin( ( T )( *( pSrc+2 ) ), Min );
            }
            else{
                GetMin( ( T )( *( pSrc+2 ) ), Min );
                GetMin( ( T )( *( pSrc+1 ) ), Min );
            }
            pSrc++;
            k++;
        }
    }
    return Min;
}



template< class T >
void KDumper::DumpIndexes2( 
    KFACES* pFACES, 
    T* pSrc, 
    EPrimitiveType Type
    )
{
    DWORD dwPrimCount = pFACES->PrimitivesCnt;
    KFace* pDst = pFACES->pFaces;

    
    pFACES->MaxIdx = GetMaxIndex2 < T > ( Type, pSrc, dwPrimCount );
    pFACES->MinIdx = GetMinIndex2 < T > ( Type, pSrc, dwPrimCount );


    if( Type == eTriangleList ){
        for( DWORD i = 0; i < dwPrimCount; i++ ){
            pDst->i0 = ( DWORD )( *pSrc );
            pSrc++;

            pDst->i1 = ( DWORD )( *pSrc );
            pSrc++;

            pDst->i2 = ( DWORD )( *pSrc );
            pSrc++;

            pDst++;
        }
    }
    else if( Type == eTriangleStrip ){
        DWORD k=0;
        for( DWORD i = 0; i < dwPrimCount; i++ ){
            pDst->i0 = ( DWORD )( *pSrc );
            if( ( k & 0x1 ) != 0 ){//WAS ==
                pDst->i1 = ( DWORD )( *( pSrc+1 ) );
                pDst->i2 = ( DWORD )( *( pSrc+2 ) );
            }
            else{
                pDst->i1=( DWORD )( *( pSrc+2 ) );
                pDst->i2=( DWORD )( *( pSrc+1 ) );
            }
            k++;
            pSrc++;
            pDst++;
        }
    }
}


#pragma once

#include <vector>

//Output ".rip" file structures

//----File Format----
//KRipHeader struct
//KVertexElement array with RipHeader.VertexElements count
//KMeshTextures2 data (if present)
//KMeshShaders2 data (if present)
//Index data   RipHeader.dwFaces * sizeof( KFace )
//Vertex data  RipHeader.dwVertexCount * VertexSize


#define RIP_SIGNATURE    0xDEADC0DE
#define RIP_VERSION      4

#define SEMANTIC_LEN     64
#define MAX_TYPEMAP_SIZE 8



#pragma pack(push,1)


struct KFace{
    DWORD i0;
    DWORD i1;
    DWORD i2;
};



struct KMeshTextures2{
    std::vector < std::string > Textures;
};


struct KMeshShaders2{
    std::vector < std::string > Shaders;
};



//Main "RIP" header
struct KRipHeader{
    DWORD Signature;
    DWORD Version;
    DWORD dwFacesCnt;//Triangles count
    DWORD dwVertexesCnt;//Vertexes count
    DWORD VertexSize;//Size in bytes of output vertex
    DWORD TextureFilesCnt;
    DWORD ShaderFilesCnt;
    DWORD VertexAttributesCnt;

    KRipHeader():
    Signature( RIP_SIGNATURE ),
    Version( RIP_VERSION ),
    dwFacesCnt( 0 ),
    dwVertexesCnt( 0 ),
    VertexSize( 0 ),
    TextureFilesCnt( 0 ),
    ShaderFilesCnt( 0 ),
    VertexAttributesCnt( 0 )
    {

    }
};

#pragma pack(pop)


#include "PreComp.h"
#include "Output.h"
#include "KDumper.h"



bool KDumper::IsPrimitiveTypeSupported( EPrimitiveType t ){
    if( (t == eTriangleList) || (t == eTriangleStrip) )
        return TRUE;

    return FALSE;
}


const wchar_t* KDumper::EInputType2Str( EInputType t ){

    switch( t ){
    case eUnknownInputType:
        return L"eUnknownInputType";

    case eR32G32B32A32_TYPELESS:
        return L"eR32G32B32A32_TYPELESS";

    case eR32G32B32A32_FLOAT:
        return L"eR32G32B32A32_FLOAT";

    case eR32G32B32A32_SINT:
        return L"eR32G32B32A32_SINT";

    case eR32G32B32A32_UINT:
        return L"eR32G32B32A32_UINT";

    case eR32G32B32_TYPELESS:
        return L"eR32G32B32_TYPELESS";

    case eR32G32B32_FLOAT:
        return L"eR32G32B32_FLOAT";

    case eR32G32B32_SINT:
        return L"eR32G32B32_SINT";

    case eR32G32B32_UINT:
        return L"eR32G32B32_UINT";

    case eR16G16B16A16_TYPELESS:
        return L"eR16G16B16A16_TYPELESS";

    case eR16G16B16A16_FLOAT:
        return L"eR16G16B16A16_FLOAT";

    case eR16G16B16A16_SINT:
        return L"eR16G16B16A16_SINT";

    case eR16G16B16A16_UINT:
        return L"eR16G16B16A16_UINT";

    case eR16G16B16A16_SNORM:
        return L"eR16G16B16A16_SNORM";

    case eR16G16B16A16_UNORM:
        return L"eR16G16B16A16_UNORM";

    case eR32G32_TYPELESS:
        return L"eR32G32_TYPELESS";

    case eR32G32_FLOAT:
        return L"eR32G32_FLOAT";

    case eR32G32_SINT:
        return L"eR32G32_SINT";

    case eR32G32_UINT:
        return L"eR32G32_UINT";

    case eR8G8B8A8_TYPELESS:
        return L"eR8G8B8A8_TYPELESS";

    case eR8G8B8A8_SINT:
        return L"eR8G8B8A8_SINT";

    case eR8G8B8A8_UINT:
        return L"eR8G8B8A8_UINT";

    case eR8G8B8A8_SNORM:
        return L"eR8G8B8A8_SNORM";

    case eR8G8B8A8_UNORM:
        return L"eR8G8B8A8_UNORM";

    case eR16G16_TYPELESS:
        return L"eR16G16_TYPELESS";

    case eR16G16_FLOAT:
        return L"eR16G16_FLOAT";

    case eR16G16_SINT:
        return L"eR16G16_SINT";

    case eR16G16_UINT:
        return L"eR16G16_UINT";

    case eR16G16_SNORM:
        return L"eR16G16_SNORM";

    case eR16G16_UNORM:
        return L"eR16G16_UNORM";

    case eR32_TYPELESS:
        return L"eR32_TYPELESS";

    case eR32_FLOAT:
        return L"eR32_FLOAT";

    case eR32_SINT:
        return L"eR32_SINT";

    case eR32_UINT:
        return L"eR32_UINT";

    case eR8G8_TYPELESS:
        return L"eR8G8_TYPELESS";

    case eR8G8_UNORM:
        return L"eR8G8_UNORM";

    case eR8G8_UINT:
        return L"eR8G8_UINT";

    case eR8G8_SNORM:
        return L"eR8G8_SNORM";

    case eR8G8_SINT:
        return L"eR8G8_SINT";

    case eR16_TYPELESS:
        return L"eR16_TYPELESS";

    case eR16_FLOAT:
        return L"eR16_FLOAT";

    case eR16_UNORM:
        return L"eR16_UNORM";

    case eR16_UINT:
        return L"eR16_UINT";

    case eR16_SNORM:
        return L"eR16_SNORM";

    case eR16_SINT:
        return L"eR16_SINT";

    case eR8_TYPELESS:
        return L"eR8_TYPELESS";

    case eR8_UINT:
        return L"eR8_UINT";

    case eR8_SINT:
        return L"eR8_SINT";

    case eR8_SNORM:
        return L"eR8_SNORM";

    case eR8_UNORM:
        return L"eR8_UNORM";

    case eFLOAT5:
        return L"eFLOAT5";

    case eFLOAT6:
        return L"eFLOAT6";

    case eFLOAT7:
        return L"eFLOAT7";

    case eFLOAT8:
        return L"eFLOAT8";

    case eUDEC3:
        return L"eUDEC3";

    case eDEC3N:
        return L"eDEC3N";

    case eR10G10B10A2_UNORM:
        return L"eR10G10B10A2_UNORM";

    case eB8G8R8A8_UNORM:
        return L"eB8G8R8A8_UNORM";
    }
    return L"Unknown";
}


//Return type size in bytes
DWORD KDumper::GetInputTypeSize( EInputType t ){

    switch( t ){

    case eUnknownInputType:
        return 0;


    case eR32G32B32A32_TYPELESS:
    case eR32G32B32A32_FLOAT:
    case eR32G32B32A32_SINT:
    case eR32G32B32A32_UINT:
        return 16;


    case eR32G32B32_TYPELESS:
    case eR32G32B32_FLOAT:
    case eR32G32B32_SINT:
    case eR32G32B32_UINT:
        return 12;


    case eR16G16B16A16_TYPELESS:
    case eR16G16B16A16_FLOAT:
    case eR16G16B16A16_SINT:
    case eR16G16B16A16_UINT:
    case eR16G16B16A16_SNORM:
    case eR16G16B16A16_UNORM:

    case eR32G32_TYPELESS:
    case eR32G32_FLOAT:
    case eR32G32_SINT:
    case eR32G32_UINT:
        return 8;


    case eR8G8B8A8_TYPELESS:
    case eR8G8B8A8_SINT:
    case eR8G8B8A8_UINT:
    case eR8G8B8A8_SNORM:
    case eR8G8B8A8_UNORM:

    case eR16G16_TYPELESS:
    case eR16G16_FLOAT:
    case eR16G16_SINT:
    case eR16G16_UINT:
    case eR16G16_SNORM:
    case eR16G16_UNORM:

    case eR32_TYPELESS:
    case eR32_FLOAT:
    case eR32_SINT:
    case eR32_UINT:

    case eUDEC3:
    case eDEC3N:
    case eR10G10B10A2_UNORM:
    case eB8G8R8A8_UNORM:
        return 4;


    case eR8G8_TYPELESS:
    case eR8G8_UNORM:
    case eR8G8_UINT:
    case eR8G8_SNORM:
    case eR8G8_SINT:

    case eR16_TYPELESS:
    case eR16_FLOAT:
    case eR16_UNORM:
    case eR16_UINT:
    case eR16_SNORM:
    case eR16_SINT:
        return 2;

    case eR8_TYPELESS:
    case eR8_UINT:
    case eR8_SINT:
    case eR8_SNORM:
    case eR8_UNORM:
        return 1;

    case eFLOAT5:
        return 5 * 4;

    case eFLOAT6:
        return 6 * 4;

    case eFLOAT7:
        return 7 * 4;

    case eFLOAT8:
        return 8 * 4;
    }
    return 0;
}



void KDumper::DumpInputVertexDeclaration2Log( const KInputVertexDeclaration& InpDecl ){
    
    g_pLog->Write( L"---Input Vertex Declaration Dump---\n" );
    for( size_t i = 0; i < InpDecl.Decl.size(); i++ ){
        g_pLog->Write( L"Stream  : %d\n",  InpDecl.Decl[ i ].Stream );
        g_pLog->Write( L"Semantic: %s\n", ::StringToWString( InpDecl.Decl[i].UsageSemantic ).c_str() );
        g_pLog->Write( L"SemIndex: %d\n",  InpDecl.Decl[ i ].SemanticIndex );
        g_pLog->Write( L"Offset  : %d\n",  InpDecl.Decl[ i ].Offset );
        g_pLog->Write( L"Size    : %d\n",  InpDecl.Decl[ i ].Size );
        g_pLog->Write( L"Type    : %s\n",  EInputType2Str( InpDecl.Decl[ i ].Type ) );
        g_pLog->Write( L"\n\n");

    }
    g_pLog->Write( L"-------------------------------\n" );

}



HRESULT KDumper::CreateKOutputVertexDeclaration( 
    const KInputVertexDeclaration& InputDecl, 
    KOutputVertexDeclaration& OutputDecl 
    )
{

    HRESULT hr;
    DWORD Offset = 0;
//    DWORD TotalElements = 0;
//    DWORD OutVertSize = 0;

    for( size_t i = 0; i < InputDecl.Decl.size(); i++ )
    {

        KDumper::KOutputVertexElement OutputElem;

        BYTE InputData [ MAX_UNPACKED_LEN ] = { 0 };
        BYTE UnpackedData[ MAX_UNPACKED_LEN ] = { 0 };
        KDumper::EOutputType TypeMap[ MAX_TYPEMAP_SIZE ];
        DWORD CompCnt = 0;

        KDumper::EInputType InputType = InputDecl.Decl[ i ].Type;

        if( InputType == KDumper::eUnknownInputType ){
            hr = E_INPUT_TYPE_ERR;
            break;
        }

        PFN_DECODER decoder = getDecoder( InputType );
        DWORD UnpSize = decoder( InputData, UnpackedData, TypeMap, CompCnt );
        OutputElem.Size   = UnpSize;
        OutputElem.Offset = Offset;
//        OutVertSize   += UnpSize;

        OutputElem.TypeMapElements = CompCnt;
        for( DWORD j = 0; j < CompCnt; j++ )
        {
            OutputElem.TypeMap[ j ] = TypeMap[ j ];
        }

        Offset        += UnpSize;
//        TotalElements += CompCnt;

        ::StrCopy( OutputElem.UsageSemantic, SEMANTIC_LEN, InputDecl.Decl[ i ].UsageSemantic );

        OutputElem.SemanticIndex = InputDecl.Decl[ i ].SemanticIndex;

        OutputDecl.Decl.push_back( OutputElem );
        hr = S_OK;
    }

    return hr;
}



const wchar_t* KDumper::EOutputType2Str( EOutputType t ){
    switch( t ){
    case EFLOAT:
        return L"FLOAT";
    case EUINT:
        return L"UINT";
    case ESINT:
        return L"SINT";
    case ETYPELESS8:
        return L"TYPELESS8";
    case ETYPELESS16:
        return L"TYPELESS16";
    case ETYPELESS32:
        return L"TYPELESS32";
    }
    return L"Unknown";
}




void KDumper::DumpOutputVertexDeclaration2Log(
    const KOutputVertexDeclaration& VertDecl
    )
{
    g_pLog->Write( L"---Output vertex format dump---\n" );
    for( size_t i = 0; i < VertDecl.Decl.size(); i++ ){
        g_pLog->Write( L"Semantic: %s\n", ::StringToWString( VertDecl.Decl[i].UsageSemantic ).c_str() );
        g_pLog->Write( L"SemIndex: %d\n",   VertDecl.Decl[ i ].SemanticIndex );
        g_pLog->Write( L"Offset  : %d\n",   VertDecl.Decl[ i ].Offset );
        g_pLog->Write( L"Size    : %d\nTypes Dump: ", VertDecl.Decl[ i ].Size );

        for( DWORD j = 0; j < VertDecl.Decl[ i ].TypeMapElements; j++ ){
            g_pLog->Write( L"%s ", EOutputType2Str( VertDecl.Decl[i].TypeMap[ j ] ) );
        }
        g_pLog->Write( L"\n\n");
    }
    g_pLog->Write( L"-------------------------------\n" );
}




const wchar_t* KDumper::PrimTopology2Str( EPrimitiveType t ){

    switch( t ){
    case KDumper::eTriangleList:
        return L"eTriangleList";

    case KDumper::eTriangleStrip:
        return L"eTriangleStrip";
    }

    return L"Unknown";
}



void KDumper::PrepareHeader( 
    KRipHeader& RipHeader, 
    const KInputVertexDeclaration& InpDecl,
    const KFACES& Faces, 
    const KVERTICES& Vertices, 
    const KMeshTextures2& Textures, 
    const KMeshShaders2& Shaders
    )
{
    RipHeader.dwFacesCnt = Faces.PrimitivesCnt;
    RipHeader.dwVertexesCnt = Vertices.VertexCount;
    RipHeader.ShaderFilesCnt = Shaders.Shaders.size();
    RipHeader.TextureFilesCnt = Textures.Textures.size();
    RipHeader.VertexSize = Vertices.VertexSize;
    RipHeader.VertexAttributesCnt = InpDecl.Decl.size();
}


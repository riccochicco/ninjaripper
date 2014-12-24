
#include "PreComp.h"
#include "KRipper11.h"




HRESULT KRipper11::DumpVertexBuffer(
    ID3D11DeviceContext* pDevCont,
    const KVERTICES* pVERTICES,
    const KFACES* pFACES,
    const KDumper::KInputVertexDeclaration&  InputVertDecl,
    const KDumper::KOutputVertexDeclaration& OutputVertDecl,
    INT BaseVertexIndex
    )
{
    HRESULT hr;


    //Vertex semantic loop
    for( size_t i = 0; i < InputVertDecl.Decl.size(); i++ ){
        
        KDumper::KInputVertexElement InputElem = InputVertDecl.Decl[ i ];

        ID3D11Buffer* pVertexBuffer = NULL;
        UINT VBStride = 0;
        UINT VBOffs = 0;
        ID3D11Buffer* pDstVBuffer = NULL;

        pDevCont->IAGetVertexBuffers( InputElem.Stream, 1, &pVertexBuffer, &VBStride, &VBOffs );

        //Dump Vertex Buffer info
        g_pLog->Write( L"VertexBuffer: 0x%p Stride %d  Offset: %d\n", pVertexBuffer, VBStride, VBOffs );

        if( !pVertexBuffer ){// VB == NULL  Try next or break loop?
            g_pLog->Write( L"Error: VertexBuffer == NULL. Try next slot\n" );
            hr = E_NULL_BUFF;
            continue;
        }


        hr = CopyBuffer( pDevCont, pVertexBuffer, &pDstVBuffer );
        if( FAILED( hr ) ){
            g_pLog->Write( L"Vertex buffer copy error: 0x%08X\n", hr );
            SAFE_RELEASE( pVertexBuffer );
            break;
        }

        D3D11_MAPPED_SUBRESOURCE MapData;
        ZeroMemory( &MapData, sizeof( MapData ) );
        hr = pDevCont->Map( pDstVBuffer, 0, D3D11_MAP_READ, 0, &MapData );
        if( FAILED( hr ) ){
            SAFE_RELEASE( pVertexBuffer );
            SAFE_RELEASE( pDstVBuffer );
            g_pLog->Write( L"ID3D11DeviceContext::Map() Error: 0x%08X\n", hr );
            break;
        }


        KDumper::KOutputVertexElement OutputElem =  OutputVertDecl.Decl [ i ];
    
        BYTE* pVertData = (BYTE*)MapData.pData + VBOffs;
        
        //DWORD InpVertSize = InputVertDecl.GetStreamVertexSize( InputElem.Stream );
        //( pFACES->MinIdx + BaseVertexIndex ) * InpVertSize
        KDumper::DumpVertSemantic(
            InputElem.Type,

            pVertData +  ( pFACES->MinIdx + BaseVertexIndex ) * VBStride,//***WAS InpVertSize. Move to vertex with min index
            InputElem.Offset,
            VBStride,

            pVERTICES->pVertices,
            OutputElem.Offset,
            pVERTICES->VertexSize,

            pVERTICES->VertexCount
        );

        pDevCont->Unmap( pDstVBuffer, 0 );
        
        SAFE_RELEASE( pDstVBuffer );
        SAFE_RELEASE( pVertexBuffer );
        
        hr = S_OK;
    }


    return hr;
}


KDumper::EPrimitiveType KRipper11::GetPrimTopology( ID3D11DeviceContext* pDevCont )
{
    D3D11_PRIMITIVE_TOPOLOGY PrimTopology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    pDevCont->IAGetPrimitiveTopology( &PrimTopology );
    KDumper::EPrimitiveType PrimType = D3D11_PRIMITIVE_TOPOLOGY_to_EPrimitiveType( PrimTopology );
    return PrimType;
}


HRESULT KRipper11::GetInputLayout( 
    ID3D11DeviceContext* pDevCont,
    KD3D11VertexDeclaration& D3D11VertDecl
    )
{
    HRESULT hr;
    do{
        ID3D11InputLayout* pInputLayout = NULL;

        pDevCont->IAGetInputLayout( &pInputLayout );
        KInputLayoutMap::iterator p = InputLayoutMap.find( pInputLayout );
        SAFE_RELEASE( pInputLayout );

        if( p == InputLayoutMap.end() ){
            g_pLog->Write( L"Error InputLayout not found\n" );
            hr = E_INPUT_LAYOUT_NOT_FOUND;
            break;
        }
        D3D11VertDecl = p->second;
        hr = S_OK;
    }
    while( FALSE );

    return hr;
}


HRESULT KRipper11::DumpIndexBuffer(
    ID3D11DeviceContext* pDevCont, 
    KFACES* pFACES,
    UINT StartIndexLocation,
    INT  BaseVertexLocation,
    KDumper::EPrimitiveType PrimType
    )
{
    
    HRESULT hr = E_UNK_ERR;

    do{
        ID3D11Buffer* pIndexBuffer = NULL;
        ID3D11Buffer* pDstIBuffer  = NULL;
        DXGI_FORMAT IBFormat = DXGI_FORMAT_UNKNOWN;
        UINT IBOffset = 0;

        pDevCont->IAGetIndexBuffer( &pIndexBuffer, &IBFormat, &IBOffset );

        g_pLog->Write( L"IndexBuffer: 0x%p Format: %s Offset: 0x%08X\n", pIndexBuffer, DXGI_FORMAT_2_Str( IBFormat ), IBOffset );

        if( !pIndexBuffer ){
            g_pLog->Write( L"Error IndexBuffer == NULL\n" );
            break;
        }

        hr = CopyBuffer( pDevCont, pIndexBuffer, &pDstIBuffer );
        if( FAILED( hr ) ){
            SAFE_RELEASE( pIndexBuffer );
            g_pLog->Write( L"Index buffer copy error: 0x%08X\n", hr );
            break;
        }

        D3D11_MAPPED_SUBRESOURCE MapData;
        ZeroMemory( &MapData, sizeof( MapData ) );
        hr = pDevCont->Map( pDstIBuffer, 0, D3D11_MAP_READ, 0, &MapData );
        if( FAILED( hr ) ){
            SAFE_RELEASE( pIndexBuffer );
            SAFE_RELEASE( pDstIBuffer );
            g_pLog->Write( L"ID3D11DeviceContext::Map() Error: 0x%08X\n", hr );
            break;
        }


        BYTE* pIndexData = (BYTE*)MapData.pData + IBOffset;
        
        if( IBFormat == DXGI_FORMAT_R16_UINT ){//Dump 16 bit indexes
            KDumper::DumpIndexes2 < WORD >( pFACES, (WORD*)pIndexData + StartIndexLocation, PrimType );
        }
        else if( IBFormat == DXGI_FORMAT_R32_UINT ){//Dump 32 bit indexes
            KDumper::DumpIndexes2 < DWORD >( pFACES, (DWORD*)pIndexData + StartIndexLocation, PrimType );
        }
        else{
            hr = E_UNK_INDEX_FORMAT_ERR;
            g_pLog->Write( L"Unknown index buffer format error\n" );
            pDevCont->Unmap( pDstIBuffer, 0 );
            SAFE_RELEASE( pIndexBuffer );
            SAFE_RELEASE( pDstIBuffer );
            break;
        }

        pDevCont->Unmap( pDstIBuffer, 0 );
        SAFE_RELEASE( pDstIBuffer );
        SAFE_RELEASE( pIndexBuffer );
        
        KDumper::AddBaseVertexLocation( pFACES, -( (INT)pFACES->MinIdx ) /* + BaseVertexLocation */ );

        hr = S_OK;
    }
    while( FALSE );

    return hr;
}




void KRipper11::RipDI( 
    ID3D11DeviceContext* pDevCont,
    UINT IndexCount,
    UINT StartIndexLocation,
    INT  BaseVertexLocation
)
{
    do{
        HRESULT hr;
        KRipHeader  RipHeader;
        KDumper::KOutputVertexDeclaration  OutputVertDecl;
        KDumper::KInputVertexDeclaration   InputVertDecl;
        KMeshTextures2 MeshTextures;
        KMeshShaders2  MeshShaders;


        //////////////////////////////////////////////////////////////////////////
        //Primitive topology
        //////////////////////////////////////////////////////////////////////////
        KDumper::EPrimitiveType PrimType = GetPrimTopology( pDevCont );
        if( !KDumper::IsPrimitiveTypeSupported( PrimType ) ){
            g_pLog->Write( L"Input primitive topology not supported\n" );
            break;
        }
        g_pLog->Write( L"Input primitive topology: %s\n", KDumper::PrimTopology2Str( PrimType ) );


        //Calculate primitives count
        DWORD PrimitivesCount = KDumper::FacesCntFromIndexCnt( IndexCount, PrimType );
        g_pLog->Write( L"Primitives count: %d\n", RipHeader.dwFacesCnt );
        KFACES Faces( PrimitivesCount );


        //////////////////////////////////////////////////////////////////////////
        // Input/Output vertex declaration
        //////////////////////////////////////////////////////////////////////////
        hr = GetVertexDeclarations( pDevCont, InputVertDecl, OutputVertDecl );
        if( FAILED( hr ) ){
            g_pLog->Write( L"Input vertex declaration error: 0x%08X\n", hr );
            break;
        }
        KDumper::DumpInputVertexDeclaration2Log( InputVertDecl );
        KDumper::DumpOutputVertexDeclaration2Log( OutputVertDecl );




        //////////////////////////////////////////////////////////////////////////
        //Dump Index buffer
        //////////////////////////////////////////////////////////////////////////
        hr = DumpIndexBuffer( 
            pDevCont, 
            &Faces, 
            StartIndexLocation, 
            BaseVertexLocation, PrimType
            );
        if( FAILED( hr ) ){
            g_pLog->Write( L"Index buffer dump failed: 0x%08X\n", hr );
            break;
        }


        //////////////////////////////////////////////////////////////////////////
        // Vertices
        //////////////////////////////////////////////////////////////////////////
        DWORD VertCnt = Faces.GetVertexCount();
        DWORD VertSize= OutputVertDecl.GetVertexSize();

        g_pLog->Write( L"Min/Max Index: %d %d\nVertSize=%d\n", Faces.MinIdx, Faces.MaxIdx, VertSize );

        KVERTICES Vertices( VertCnt, VertSize );


        hr = DumpVertexBuffer( 
            pDevCont, 
            &Vertices,
            &Faces,
            InputVertDecl,
            OutputVertDecl,
            BaseVertexLocation
            );

        if( FAILED( hr ) ){
            g_pLog->Write( L"Vertex buffer dump error: 0x%08X\n", hr );
            break;
        }

        
        SaveMeshTextures( pDevCont, MeshTextures );
        //SaveMeshShaders( pDevCont, MeshShaders );


        KDumper::PrepareHeader(
            RipHeader, 
            InputVertDecl,
            Faces,
            Vertices, 
            MeshTextures, 
            MeshShaders 
            );

        //Save RIP file
        std::wstring RipFilePath = g_pIntruder->GetFrameMeshSavePath();

        hr = KDumper::SaveMeshToRIPFile2(
            RipFilePath, 
            RipHeader, 
            OutputVertDecl,
            MeshTextures, 
            MeshShaders, 
            Faces.pFaces, 
            Vertices.pVertices
            );

        if( SUCCEEDED( hr ) ){
            g_pLog->Write( L"Mesh saved: %s\n\n\n", RipFilePath.c_str() );
        }
        else{
            g_pLog->Write( L"Mesh save error: %s\n\n\n", RipFilePath.c_str() );
        }

        g_pIntruder->IncFrameMeshIdx();
    }
    while( FALSE );
}



void KRipper11::_ID3D11DeviceContext_DrawIndexed(
    PFN_ID3D11DeviceContext_DrawIndexed e,
    ID3D11DeviceContext* pDevCont,
    UINT IndexCount,
    UINT StartIndexLocation,
    INT  BaseVertexLocation
    )
{    

    unhDrawIndexed = e;//Save last used

    //g_pLog->Write( L"ID3D11DeviceContext_DrawIndexed( 0x%p, %d, %d, %d )\n", pDevCont, IndexCount, StartIndexLocation, BaseVertexLocation );

    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinIndeces = g_pIntruder->GetSettings()->dwMinIndicies;
    
    ::EnterCriticalSection( &cs );

    if ( RipEnabled && ( IndexCount >= MinIndeces ) )
    {
        g_pLog->Write( L"ID3D11DeviceContext_DrawIndexed( 0x%p, %d, %d, %d )\n", pDevCont, IndexCount, StartIndexLocation, BaseVertexLocation );
    
        __try
        {
            RipDI( pDevCont, IndexCount, StartIndexLocation, BaseVertexLocation );
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            g_pLog->Write( L"Error ID3D11DeviceContext_DrawIndexed() exception\n\n\n" );
        }

    }
    
    ::LeaveCriticalSection( &cs );

    return e( pDevCont, IndexCount, StartIndexLocation, BaseVertexLocation );
}


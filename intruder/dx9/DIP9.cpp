
#include "PreComp.h"
#include "KRipper9.h"



HRESULT KRipper9::DumpVertexBuffer(
    IDirect3DDevice9 *pDev, 
    const KVERTICES* pVERTICES,
    const KFACES* pFACES,
    const KDumper::KInputVertexDeclaration&  InputVertDecl,
    const KDumper::KOutputVertexDeclaration& OutputVertDecl,
    INT BaseVertexIndex 
    )
{
    HRESULT hr;

    for( size_t i = 0; i < InputVertDecl.Decl.size(); i++ )
    {
        
        KDumper::KInputVertexElement  InputElem  = InputVertDecl.Decl[ i ];
        KDumper::KOutputVertexElement OutputElem = OutputVertDecl.Decl[ i ];
        
        D3DVERTEXBUFFER_DESC VertexBufferDesc;
        TDXRef < IDirect3DVertexBuffer9 > pVertexBufferRef;
        VOID* pbVertData = NULL;
        ZeroMemory( &VertexBufferDesc, sizeof( VertexBufferDesc ) );
        
        UINT OffsetInBytes = 0, Stride = 0;

        hr = pDev->GetStreamSource( 
            InputElem.Stream, 
            &pVertexBufferRef, 
            &OffsetInBytes, 
            &Stride 
            );
            
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DDevice9::GetStreamSource() Error: 0x%08X Stream: 0x%08X\n", hr, InputElem.Stream );
            break;
        }

        if( !pVertexBufferRef.get() )
        {
            g_pLog->Write( L"Error: pVertexBuffer==NULL\n" );
            hr = E_NULL_BUFF;
            return hr;
        }


        hr = pVertexBufferRef->GetDesc( &VertexBufferDesc );//May be need for use
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DVertexBuffer9::GetDesc() Error: 0x%08X\n", hr );
            break;
        }

        //Dump stream info
        std::string  TmpStr  = InputElem.UsageSemantic;
        std::wstring TmpWStr = ::StringToWString( TmpStr );

        g_pLog->Write( L"---Stream Info For: %s---\n", TmpWStr.c_str() );
        g_pLog->Write( L"Stream Number     : %d\n", InputElem.Stream );
        g_pLog->Write( L"Stream OffsInBytes: %d\n", OffsetInBytes );
        g_pLog->Write( L"Stream Stride     : %d\n", Stride );
        g_pLog->Write( L"\n" );

        hr = pVertexBufferRef->Lock( 0, 0, &pbVertData, D3DLOCK_READONLY );
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DVertexBuffer9::Lock() Error: 0x%08X\n", hr );
            break;
        }

        //Get vertex size from STRIDE ?????
        //DWORD InpVertSize = InputVertDecl.GetStreamVertexSize( InputElem.Stream );

        KDumper::DumpVertSemantic(

            InputElem.Type,

            //was InpVertSize, now Stride
            (BYTE*)pbVertData + ( pFACES->MinIdx + BaseVertexIndex ) * Stride + OffsetInBytes,
            InputElem.Offset,
            Stride,              //Stride or InpVertSize ???  Calculate from input decl ???

            pVERTICES->pVertices,
            OutputElem.Offset,
            pVERTICES->VertexSize,

            pVERTICES->VertexCount
            );



        hr = pVertexBufferRef->Unlock();
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DVertexBuffer9::Unlock() Error: 0x%08X\n", hr );
            break;
        }

    }
    return hr;
}



DWORD KRipper9::IsEndDecl( D3DVERTEXELEMENT9* p ){
    if( 
        ( p->Stream == 0xFF ) &&
        ( p->Offset == 0 ) &&
        ( p->Type == D3DDECLTYPE_UNUSED ) &&
        ( p->Method == 0 ) &&
        ( p->Usage == 0 ) &&
        ( p->UsageIndex == 0 )
    )
    {
        return 1;
    }


    return 0;
}


HRESULT KRipper9::DumpIndexBuffer(
    IDirect3DDevice9 *pDev, 
    KFACES* pFACES,
    KDumper::EPrimitiveType PrimType,
    UINT StartIndex
    )
{
    HRESULT hr;

    do
    {
        D3DINDEXBUFFER_DESC IndexBufferDesc;
        TDXRef < IDirect3DIndexBuffer9 > pIndexBufferRef;
        VOID* pbIndexData = NULL;

        ZeroMemory( &IndexBufferDesc , sizeof( IndexBufferDesc ) );

        hr = pDev->GetIndices( &pIndexBufferRef );
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DDevice9::GetIndices() Error: 0x%08X\n", hr );
            break;
        }

        if( !pIndexBufferRef.get() )
        {
            g_pLog->Write( L"Error: Index buffer==NULL\n", hr );
            hr = E_NULL_BUFF;
            break;
        }


        hr = pIndexBufferRef->GetDesc( &IndexBufferDesc );
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DIndexBuffer9::GetDesc() Error: 0x%08X\n", hr );
            break;
        }

        hr = pIndexBufferRef->Lock( 0, 0, &pbIndexData, D3DLOCK_READONLY );
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DIndexBuffer9::Lock() Error: 0x%08X\n", hr );
            break;
        }


        if( IndexBufferDesc.Format == D3DFMT_INDEX16 )
        {
            //Dump 16 bit indexes
            KDumper::DumpIndexes2 < WORD >( pFACES, (WORD*)pbIndexData + StartIndex, PrimType );
        }
        else if( IndexBufferDesc.Format == D3DFMT_INDEX32 )
        {
            //Dump 32 bit indexes
            KDumper::DumpIndexes2 < DWORD >( pFACES, (DWORD*)pbIndexData + StartIndex, PrimType );                            
        }
        else
        {
            hr = E_UNK_INDEX_FORMAT_ERR;
            g_pLog->Write( L"Unknown index buffer format error\n" );
            hr = pIndexBufferRef->Unlock();
            if( FAILED( hr ) )
            {
                g_pLog->Write( L"IDirect3DIndexBuffer9::Unlock() Error: 0x%08X\n", hr );
            }
            break;
        }

        //Unlock index buffer
        hr = pIndexBufferRef->Unlock();
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DIndexBuffer9::Unlock() Error: 0x%08X\n", hr );
            break;
        }
        
        KDumper::AddBaseVertexLocation( pFACES, -( (INT)pFACES->MinIdx ) );

        hr = S_OK;
    }
    while( FALSE );

    return hr;
}


void KRipper9::RipDIP(
    IDirect3DDevice9 *pDev, 
    D3DPRIMITIVETYPE Type, 
    INT BaseVertexIndex, 
    UINT MinIndex, 
    UINT NumVertices, 
    UINT StartIndex, 
    UINT PrimitiveCount
    )
{
    do
    {
        HRESULT hr;
        KRipHeader RipHeader;
        KFACES Faces( (DWORD)PrimitiveCount );
        KDumper::KInputVertexDeclaration  InputVertDecl;
        KDumper::KOutputVertexDeclaration OutputVertDecl;
        KMeshTextures2 MeshTextures;
        KMeshShaders2  MeshShaders;


        //////////////////////////////////////////////////////////////////////////
        // Primitive topology
        //////////////////////////////////////////////////////////////////////////
        KDumper::EPrimitiveType PrimType = D3DPRIMITIVETYPE_to_EPrimitiveType( Type );
        if( !KDumper::IsPrimitiveTypeSupported( PrimType ) )
        {
            g_pLog->Write( L"Input primitive topology not supported\n" );
            break;
        }
        g_pLog->Write( L"Input primitive topology: %s\n", KDumper::PrimTopology2Str( PrimType ) );


        //////////////////////////////////////////////////////////////////////////
        // Input/Output vertex declaration
        //////////////////////////////////////////////////////////////////////////
        hr = GetVertexDeclarations( pDev, InputVertDecl, OutputVertDecl );
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"Input vertex declaration error: 0x%08X\n", hr );
            break;
        }
        KDumper::DumpInputVertexDeclaration2Log( InputVertDecl );
        KDumper::DumpOutputVertexDeclaration2Log( OutputVertDecl );

        //////////////////////////////////////////////////////////////////////////
        // Index Buffer
        //////////////////////////////////////////////////////////////////////////
        hr = DumpIndexBuffer( 
            pDev, 
            &Faces, 
            PrimType, 
            StartIndex
            );
        if( FAILED( hr ) )
        {
            g_pLog->Write( L"Index buffer dump error: 0x%08X\n", hr );
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
            pDev, 
            &Vertices,
            &Faces,
            InputVertDecl,
            OutputVertDecl,
            BaseVertexIndex
            );
        if( FAILED ( hr ) )
        {
            g_pLog->Write( L"Vertex buffer dump error: 0x%08X\n", hr );
            break;
        }


        SaveMeshTextures( pDev, MeshTextures );
        //SaveMeshShaders()

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

        if( SUCCEEDED( hr ) )
        {
            g_pLog->Write( L"Mesh saved: %s\n\n\n", RipFilePath.c_str() );
        }
        else
        {
            g_pLog->Write( L"Mesh save error: %s\n\n\n", RipFilePath.c_str() );
        }

        g_pIntruder->IncFrameMeshIdx();

    }
    while( FALSE );

}



HRESULT KRipper9::_IDirect3DDevice9_DrawIndexedPrimitive(
    PFN_IDirect3DDevice9_DrawIndexedPrimitive e,
    IDirect3DDevice9 *pDev, 
    D3DPRIMITIVETYPE Type, 
    INT BaseVertexIndex, 
    UINT MinIndex, 
    UINT NumVertices, 
    UINT StartIndex, 
    UINT PrimitiveCount
    )
{
    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinPrim    = g_pIntruder->GetSettings()->dwMinPrimitives;

    ::EnterCriticalSection( &cs );

    if( RipEnabled && ( PrimitiveCount >= MinPrim ) )
    {
        g_pLog->Write( L"IDirect3DDevice9_DrawIndexedPrimitive( 0x%p, %d, %d, %d, %d, %d, %d )\n", pDev, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount );
    
        __try
        {
            RipDIP(pDev,Type,BaseVertexIndex,MinIndex,NumVertices,StartIndex,PrimitiveCount);
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            g_pLog->Write( L"Error: IDirect3DDevice9_DrawIndexedPrimitive() exception\n\n\n" );
        }
    }
    ::LeaveCriticalSection( &cs );

    return e(pDev, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}

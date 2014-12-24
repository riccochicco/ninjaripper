
#include "PreComp.h"
#include "KRipper8.h"



HRESULT KRipper8::DumpVertexBuffer(
    IDirect3DDevice8* pDev, 
    const KVERTICES* pVERTICES,
    const KFACES* pFACES,
    const KDumper::KInputVertexDeclaration& InputVertDecl,
    const KDumper::KOutputVertexDeclaration& OutputVertDecl,
    INT BaseVertexIndex 
    )
{
    HRESULT hr;

    //////////////////////////////////////////////////////////////////////////
    ///Vertex elements loop
    //////////////////////////////////////////////////////////////////////////
    for ( size_t i = 0; i < InputVertDecl.Decl.size(); i++ )
    {
        UINT Stride = 0;
        KDumper::KInputVertexElement  InputElem  = InputVertDecl.Decl[ i ];
        KDumper::KOutputVertexElement OutputElem = OutputVertDecl.Decl[ i ];

        TDXRef < IDirect3DVertexBuffer8 > pVertexBufferRef;
        hr = pDev->GetStreamSource( InputElem.Stream, &pVertexBufferRef, &Stride );

        if ( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DDevice8::GetStreamSource() Error: 0x%08X\n", hr );
            break;
        }

        if ( !pVertexBufferRef.get() )
        {
            g_pLog->Write( L"pVertexBuffer==NULL\n" );
            hr = E_NULL_BUFF;
            break;
        }

        D3DVERTEXBUFFER_DESC VertexBufferDesc;
        ZeroMemory( &VertexBufferDesc, sizeof( VertexBufferDesc ) );
        hr = pVertexBufferRef->GetDesc( &VertexBufferDesc );
        if (FAILED( hr ))
        {
            g_pLog->Write( L"IDirect3DVertexBuffer8::GetDesc() Error: 0x%08X\n", hr );
            break;
        }

        std::string  TmpStr  = InputElem.UsageSemantic;
        std::wstring TmpWStr = ::StringToWString( TmpStr );
        g_pLog->Write( L"---Stream Info For: %s---\n", TmpWStr.c_str() );
        g_pLog->Write( L"pVertexBuffer=0x%p\n", pVertexBufferRef.get() );
        g_pLog->Write( L"Stream Number     : %d\n", InputElem.Stream );
        g_pLog->Write( L"Stream Stride     : %d\n", Stride );
        g_pLog->Write( L"\n" );


        BYTE* pbVertData = NULL;//in d3d8 must BYTE* instead of VOID* in d3d9
        hr = pVertexBufferRef->Lock( 0, 0, &pbVertData, D3DLOCK_READONLY );
        if (FAILED( hr ))
        {
            g_pLog->Write( L"IDirect3DVertexBuffer8::Lock() Error: 0x%08X\n", hr );
            break;
        }

        //DWORD InpVertSize = InputVertDecl.GetStreamVertexSize( InputElem.Stream );

        KDumper::DumpVertSemantic(
            InputElem.Type,

            //  *************************************************  WAS InpVertSize
            (BYTE*)pbVertData + ( pFACES->MinIdx + BaseVertexIndex ) * Stride,
            InputElem.Offset,
            Stride,
        
            pVERTICES->pVertices,
            OutputElem.Offset,
            pVERTICES->VertexSize,
            
            pVERTICES->VertexCount
            );

        hr = pVertexBufferRef->Unlock();
        if (FAILED( hr ))
        {
            g_pLog->Write( L"IDirect3DVertexBuffer8::Unlock() Error: 0x%08X\n", hr );
            break;
        }
    }
    return hr;
}



HRESULT KRipper8::DumpIndexBuffer(
    IDirect3DDevice8* pDev, 
    KFACES* pFACES,
    KDumper::EPrimitiveType PrimType,
    UINT* pBaseVertexIndex,  
    UINT StartIndex
    )
{
    HRESULT hr;

    do 
    {
        D3DINDEXBUFFER_DESC IndexBufferDesc;
        
        //IDirect3DIndexBuffer8* pIndexBuffer = NULL;
        TDXRef < IDirect3DIndexBuffer8 > pIndexBufferRef;


        BYTE* pbIndexData = NULL;//in d3d8 must BYTE* instead of VOID* in d3d9

        ZeroMemory( &IndexBufferDesc , sizeof( IndexBufferDesc ) );
    
        hr = pDev->GetIndices( &pIndexBufferRef, pBaseVertexIndex );
        if ( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DDevice8::GetIndices() Error: 0x%08X\n", hr );
            break;
        }


        if ( !pIndexBufferRef.get() )
        {
            hr = E_NULL_BUFF;
            g_pLog->Write( L"pIndexBuffer==NULL Error: 0x%08X\n", hr );
            break;
        }


        hr = pIndexBufferRef->GetDesc( &IndexBufferDesc );
        if ( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DIndexBuffer8::GetDesc() Error: 0x%08X\n", hr );
            break;
        }


        hr = pIndexBufferRef->Lock( 0, 0, &pbIndexData, D3DLOCK_READONLY );
        if ( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DIndexBuffer8::Lock() Error: 0x%08X\n", hr );
            break;
        }
        
        if ( IndexBufferDesc.Format == D3DFMT_INDEX16 ){//Dump 16 bit indexes
            KDumper::DumpIndexes2 < WORD >( pFACES, (WORD*)((WORD*)pbIndexData + StartIndex), PrimType );
        }
        else{//Dump 32 bit indexes
            KDumper::DumpIndexes2 < DWORD >( pFACES, (DWORD*)((DWORD*)pbIndexData + StartIndex), PrimType );                            
        }
        

        hr = pIndexBufferRef->Unlock();
        if ( FAILED( hr ) )
        {
            g_pLog->Write( L"IDirect3DIndexBuffer8::Unlock() Error: 0x%08X\n", hr );
            break;
        }

        KDumper::AddBaseVertexLocation( pFACES, -( (INT)pFACES->MinIdx ) );
        
        hr = S_OK;
    }
    while( FALSE );

    return hr;
}


void  KRipper8::RipDIP(
    IDirect3DDevice8* pDev,  
    D3DPRIMITIVETYPE Type,
    UINT MinIndex,
    UINT NumVertices,
    UINT StartIndex, 
    UINT PrimitiveCount )
{
    do{
        HRESULT hr;
        KDumper::KInputVertexDeclaration  InputVertDecl;
        KDumper::KOutputVertexDeclaration OutputVertDecl;

        KFACES Faces( PrimitiveCount );
        UINT   BaseVertexIndex = 0;

        KRipHeader              RipHeader;    
        KMeshTextures2          MeshTextures;
        KMeshShaders2           MeshShaders;


        //////////////////////////////////////////////////////////////////////////
        // Primitive topology
        //////////////////////////////////////////////////////////////////////////
        KDumper::EPrimitiveType PrimType = D3DPRIMITIVETYPE_to_EPrimitiveType( Type );
        if( !KDumper::IsPrimitiveTypeSupported( PrimType ) ){
            g_pLog->Write( L"Input primitive topology not supported\n" );
            break;
        }
        g_pLog->Write( L"Input primitive topology: %s\n", KDumper::PrimTopology2Str( PrimType ) );


        //////////////////////////////////////////////////////////////////////////
        // Input/Output vertex declaration
        //////////////////////////////////////////////////////////////////////////
        hr = GetVertexDeclarations( pDev, InputVertDecl, OutputVertDecl );
        if( FAILED( hr ) ){
            g_pLog->Write( L"Input vertex declaration error: 0x%08X\n", hr );
            break;
        }
        KDumper::DumpInputVertexDeclaration2Log( InputVertDecl );
        KDumper::DumpOutputVertexDeclaration2Log( OutputVertDecl );


        //////////////////////////////////////////////////////////////////////////
        //INDEXES. *MUST* present in DIP method!
        //////////////////////////////////////////////////////////////////////////
        hr = DumpIndexBuffer(
            pDev, 
            &Faces, 
            PrimType, 
            &BaseVertexIndex,
            StartIndex
            );
        if( FAILED( hr ) ){
            g_pLog->Write( L"DumpIndexBuffer() Error: 0x%08X\n", hr );
            break;
        }




        //////////////////////////////////////////////////////////////////////////
        // VERTECIES
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
        if( FAILED( hr ) ){
            g_pLog->Write( L"KRipper8::DumpVertexBuffer() error: 0x%08X", hr );
            break;
        }
        

        SaveMeshTextures( pDev, MeshTextures );
        //SaveMeshShaders(....)


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



HRESULT  KRipper8::_IDirect3DDevice8_DrawIndexedPrimitive(
    PFN_IDirect3DDevice8_DrawIndexedPrimitive e,
    IDirect3DDevice8* pDev,  
    D3DPRIMITIVETYPE PrimitiveType,
    UINT MinIndex,
    UINT NumVertices,
    UINT StartIndex, 
    UINT PrimitiveCount )
{
    g_pIntruder->KeyHandler( this );

    DWORD RipEnabled = g_pIntruder->IsMeshRipEnabled();
    DWORD MinPrim    = g_pIntruder->GetSettings()->dwMinPrimitives;

    ::EnterCriticalSection( &cs );
    if ( RipEnabled && ( PrimitiveCount >= MinPrim ) )
    {
        g_pLog->Write( L"IDirect3DDevice8_DrawIndexedPrimitive( 0x%p, %d, %d, %d, %d, %d )\n", pDev, PrimitiveType, MinIndex, NumVertices, StartIndex, PrimitiveCount );

        __try
        {
            RipDIP( pDev, PrimitiveType, MinIndex, NumVertices, StartIndex, PrimitiveCount );
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            g_pLog->Write( L"Error: IDirect3DDevice8_DrawIndexedPrimitive() exception\n\n\n" );
        }
        
    }
    ::LeaveCriticalSection( &cs );
    
    return e( pDev, PrimitiveType, MinIndex, NumVertices, StartIndex, PrimitiveCount );
}

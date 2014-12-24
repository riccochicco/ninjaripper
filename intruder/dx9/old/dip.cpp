
#include "PreComp.h"
#include "dip.h"
#include "vertform.h"
#include "outtypes.h"
#include "predisp.h"



HRESULT __stdcall mine_IDirect3DDevice9_DrawIndexedPrimitive(IDirect3DDevice9 *pDev, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount){
/*
    TRIPFILE2                rip2head={0};
    TVERTEX_FORMAT            vf={0};
    IDirect3DIndexBuffer9*    pIndexBuffer=0;
    D3DINDEXBUFFER_DESC        IndexBufferDesc;
    VOID*                    pbIndexData=0;
    VOID*                    pbVertData=0;
    TFACE*                    pFaces=0;
    IDirect3DVertexBuffer9*    pVertexBuffer=0;
    UINT                    OffsetInBytes=0, Stride=0;
    D3DVERTEXBUFFER_DESC    VertexBufferDesc;
    TVERTEX*                pVertecies=0;
    HRESULT                    foo=0;

    ZeroMemory(&IndexBufferDesc , sizeof(D3DINDEXBUFFER_DESC));
    ZeroMemory(&VertexBufferDesc, sizeof(D3DVERTEXBUFFER_DESC));

    PFN_IDirect3DDevice9_DrawIndexedPrimitive e=(PFN_IDirect3DDevice9_DrawIndexedPrimitive)phook_IDirect3DDevice9_DrawIndexedPrimitive->exec;

    if( ( fRip != 0 ) && ( PrimitiveCount >= Options.dwMinPrimitives ) ){
        g_log.Write(TEXT("DrawIndexedPrimitive(0x%08X, %d, %d, %d, %d, %d, %d)\n"), pDev, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
        for(;;){
            if((Type!=D3DPT_TRIANGLELIST)&&(Type!=D3DPT_TRIANGLESTRIP)){
                g_log.Write(TEXT("Unsupported Primitive Type: %d\n"), Type);
                break;
            }
            if(GetVertexAttributes(pDev, &vf)) break;

            foo = pDev->GetIndices(&pIndexBuffer);
            if(FAILED(foo) || !pIndexBuffer){
                g_log.Write(TEXT("GetIndices Error: 0x%08X\n"), foo);
                break;
            }

            foo = pIndexBuffer->GetDesc(&IndexBufferDesc);
            if( FAILED(foo) ){
                g_log.Write(TEXT("IndexBuffer::GetDesc Error: 0x%08X\n"), foo);
                break;
            }

            //log_indexbuffer_desc(&IndexBufferDesc);

            foo = pIndexBuffer->Lock(0, 0, &pbIndexData, D3DLOCK_READONLY);
            if( FAILED(foo) ){
                g_log.Write(TEXT("IndexBuffer::Lock Error: 0x%08X\n"), foo);
                break;
            }

            rip2head.dwFaces=PrimitiveCount;
            
            pFaces=(TFACE*)malloc(rip2head.dwFaces*sizeof(TFACE));//???????????
            
            if(pFaces==0){
                pIndexBuffer->Unlock();
                g_log.Write(TEXT("malloc Error\n"));
                break;
            }

            if(IndexBufferDesc.Format==D3DFMT_INDEX16){//Dump 16 bit indexes
                rip2head.dwVertices=1+GetMaxIndex(Type, (WORD*)((WORD*)pbIndexData+StartIndex), PrimitiveCount);
                DumpIndexes(pFaces, (WORD*)((WORD*)pbIndexData+StartIndex), Type, PrimitiveCount);
            }
            else{//Dump 32 bit indexes
                rip2head.dwVertices=1+GetMaxIndex(Type, (DWORD*)((DWORD*)pbIndexData+StartIndex), PrimitiveCount);
                DumpIndexes(pFaces, (DWORD*)((DWORD*)pbIndexData+StartIndex), Type, PrimitiveCount);                            
            }

            foo = pIndexBuffer->Unlock();
            if( FAILED(foo) ){
                g_log.Write(TEXT("IndexBuffer::Unlock Error: 0x%08X\n"), foo);
                break;
            }
            //Release Index Buffer
            if(pIndexBuffer!=0) pIndexBuffer->Release();

            //---------------------------------------------------
            //Vertecies
            //Position
            foo = pDev->GetStreamSource(vf.Position_Stream, &pVertexBuffer, &OffsetInBytes, &Stride);
            if( FAILED(foo) || !pVertexBuffer){
                g_log.Write(TEXT("Position GetStreamSource Error: 0x%08X Stream: 0x%08X, Offset: 0x%08X, Stride: 0x%08X\n"), 
                    foo,
                    vf.Position_Stream,
                    OffsetInBytes,
                    Stride);
                break;
            }

            foo = pVertexBuffer->GetDesc(&VertexBufferDesc);
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("Position GetDesc Error: 0x%08X\n"), foo);
                break;
            }

            g_log.Write(TEXT("Position Stream Number     : %d\n"), vf.Position_Stream);
            g_log.Write(TEXT("Position Stream OffsInBytes: %d\n"), OffsetInBytes);
            g_log.Write(TEXT("Position Stream Stride     : %d\n"), Stride);

            pVertecies=(TVERTEX*)malloc(rip2head.dwVertices*sizeof(TVERTEX));
            if(pVertecies==0){
                pVertexBuffer->Release();
                g_log.Write(TEXT("malloc Error\n"));
                break;
            }
            
            foo = pVertexBuffer->Lock(0, 0, &pbVertData, D3DLOCK_READONLY);
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("Vertex Buffer Lock Error: 0x%08X\n"), foo);
                break;
            }

            DumpVertecies(POSITION, ((BYTE*)pbVertData+BaseVertexIndex*vf.VertSize+OffsetInBytes), pVertecies, rip2head.dwVertices, vf.Position_Type, vf.Position_Offset, Stride);

            foo = pVertexBuffer->Unlock();
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("VertexBuffer::Unlock Error: 0x%08X\n"), foo);
                break;
            }
            if(pVertexBuffer!=0) pVertexBuffer->Release();


        //-------------------------------------------------
        //Normals
        //-------------------------------------------------
        if(vf.NormalFailed==0){

            pVertexBuffer=0;
            foo = pDev->GetStreamSource(vf.Normal_Stream, &pVertexBuffer, &OffsetInBytes, &Stride);
            if(FAILED( foo ) || !pVertexBuffer){
                g_log.Write(TEXT("Normals GetStreamSource Error: 0x%08X\n"), foo);
                break;
            }

            foo = pVertexBuffer->GetDesc(&VertexBufferDesc);
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("Normals GetDesc Error: 0x%08X\n"), foo);
                break;
            }

            g_log.Write(TEXT("Normals  Stream Number     : %d\n"), vf.Normal_Stream);
            g_log.Write(TEXT("Normals  Stream OffsInBytes: %d\n"), OffsetInBytes);
            g_log.Write(TEXT("Normals  Stream Stride     : %d\n"), Stride);
            
            foo = pVertexBuffer->Lock(0, 0, &pbVertData, D3DLOCK_READONLY);
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("Vertex Buffer Lock Error: 0x%08X\n"), foo);
                break;
            }

            DumpVertecies(NORMALS, ((BYTE*)pbVertData+BaseVertexIndex*vf.VertSize+OffsetInBytes), pVertecies, rip2head.dwVertices, vf.Normal_Type, vf.Normal_Offset, Stride);

            foo = pVertexBuffer->Unlock();
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("VertexBuffer::Unlock Error: 0x%08X\n"), foo);
                break;
            }
            if(pVertexBuffer!=0) pVertexBuffer->Release();
            
        }

        //-------------------------------------------------
        //Texture Coordinates
        //-------------------------------------------------
        if(vf.TexCoordFailed==0){

            pVertexBuffer=0;
            foo = pDev->GetStreamSource(vf.TexCoord_Stream, &pVertexBuffer, &OffsetInBytes, &Stride);
            if(FAILED( foo ) || !pVertexBuffer){
                g_log.Write(TEXT("TexCoord GetStreamSource Error: 0x%08X\n"), foo);
                break;
            }

            foo = pVertexBuffer->GetDesc(&VertexBufferDesc);
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("TexCoord GetDesc Error: 0x%08X\n"), foo);
                break;
            }

            g_log.Write(TEXT("TexCoord Stream Number     : %d\n"), vf.TexCoord_Stream);
            g_log.Write(TEXT("TexCoord Stream OffsInBytes: %d\n"), OffsetInBytes);
            g_log.Write(TEXT("TexCoord Stream Stride     : %d\n"), Stride);
            
            foo = pVertexBuffer->Lock(0, 0, &pbVertData, D3DLOCK_READONLY);
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("Vertex Buffer Lock Error: 0x%08X\n"), foo);
                break;
            }

            DumpVertecies(TEXCOORD, ((BYTE*)pbVertData+BaseVertexIndex*vf.VertSize+OffsetInBytes), pVertecies, rip2head.dwVertices, vf.TexCoord_Type, vf.TexCoord_Offset, Stride);

            foo = pVertexBuffer->Unlock();
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("VertexBuffer::Unlock Error: 0x%08X\n"), foo);
                break;
            }
            if(pVertexBuffer!=0) pVertexBuffer->Release();

        }

            DumpMesh(pDev, &rip2head, pVertecies, pFaces);

            break;
        }
        g_log.Write( TEXT( "\n\n" ) );
    }

    return e(pDev, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
    */
return 0;
}

static void log_indexbuffer_desc(D3DINDEXBUFFER_DESC *desc){
    /*
    g_log.Write(TEXT("---IndexBuffer Desc---\n"));
    g_log.Write(TEXT("Format : %d\n"), desc->Format);
    g_log.Write(TEXT("Type   : %d\n"), desc->Type);
    g_log.Write(TEXT("Usage  : %d\n"), desc->Usage);
    g_log.Write(TEXT("Pool   : %d\n"), desc->Pool);
    g_log.Write(TEXT("Size   : %d\n"), desc->Size);
    g_log.Write(TEXT("----------------------\n"));
    */
}

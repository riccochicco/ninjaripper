
#include "PreComp.h"
#include "dp.h"
#include "vertform.h"
#include "outtypes.h"
#include "predisp.h"


HRESULT __stdcall mine_IDirect3DDevice9_DrawPrimitive(IDirect3DDevice9 *pDev, D3DPRIMITIVETYPE Type, UINT StartVertex, UINT PrimitiveCount){
/*
    TRIPFILE2                rip2head={0};
    TVERTEX_FORMAT            vf={0};
    TFACE*                    pFaces=0;
    VOID*                    pbVertData=0;
    IDirect3DVertexBuffer9*    pVertexBuffer=0;
    UINT                    OffsetInBytes=0, Stride=0;
    D3DVERTEXBUFFER_DESC    VertexBufferDesc;
    TVERTEX*                pVertecies=0;
    HRESULT                    foo=0;

    ZeroMemory(&VertexBufferDesc, sizeof(D3DVERTEXBUFFER_DESC));

    PFN_IDirect3DDevice9_DrawPrimitive e=(PFN_IDirect3DDevice9_DrawPrimitive)phook_IDirect3DDevice9_DrawPrimitive->exec;

    if( ( fRip != 0 ) && ( PrimitiveCount >= Options.dwMinPrimitives ) ){
        g_log.Write(TEXT("DrawPrimitive(0x%08X, %d, %d, %d)\n"), pDev, Type, StartVertex, PrimitiveCount);
        for(;;){
            if((Type!=D3DPT_TRIANGLELIST)&&(Type!=D3DPT_TRIANGLESTRIP)){
                g_log.Write(TEXT("Unsupported Primitive Type: %d\n"), Type);
                break;
            }
            if(GetVertexAttributes(pDev, &vf)) break;

            rip2head.dwFaces=PrimitiveCount;

            pFaces=(TFACE*)malloc(rip2head.dwFaces*sizeof(TFACE));
            if(pFaces==0){
                g_log.Write(TEXT("malloc Error\n"));
                break;
            }

            //Generate Indexes
            GenerateIndexes(pFaces, Type, rip2head.dwFaces);


            //Vertecies
            //Position
            rip2head.dwVertices=GetVerteciesCount(Type, rip2head.dwFaces);

            foo = pDev->GetStreamSource(vf.Position_Stream, &pVertexBuffer, &OffsetInBytes, &Stride);
            if(FAILED(foo) || !pVertexBuffer){
                g_log.Write(TEXT("Position GetStreamSource Error: 0x%08X\n"), foo);
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

            DumpVertecies(POSITION, ((BYTE*)pbVertData+StartVertex*Stride+OffsetInBytes), pVertecies, rip2head.dwVertices, vf.Position_Type, vf.Position_Offset, Stride);

            foo = pVertexBuffer->Unlock();
            if( FAILED(foo) ){
                pVertexBuffer->Release();
                g_log.Write(TEXT("Vertex Buffer Unlock Error: 0x%08X\n"), foo);
                break;
            }
            if(pVertexBuffer!=0) pVertexBuffer->Release();

            //-------------------------------------------------
            //Normals
        if(vf.NormalFailed==0){

            pVertexBuffer=0;
            foo = pDev->GetStreamSource(vf.Normal_Stream, &pVertexBuffer, &OffsetInBytes, &Stride);
            if( FAILED(foo) || !pVertexBuffer){
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

            DumpVertecies(NORMALS, ((BYTE*)pbVertData+StartVertex*Stride+OffsetInBytes), pVertecies, rip2head.dwVertices, vf.Normal_Type, vf.Normal_Offset, Stride);

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
        if(vf.TexCoordFailed==0){

            pVertexBuffer=0;
            foo = pDev->GetStreamSource(vf.TexCoord_Stream, &pVertexBuffer, &OffsetInBytes, &Stride);
            if( FAILED(foo) || !pVertexBuffer){
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

            DumpVertecies(TEXCOORD, ((BYTE*)pbVertData+StartVertex*Stride+OffsetInBytes), pVertecies, rip2head.dwVertices, vf.TexCoord_Type, vf.TexCoord_Offset, Stride);

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
    }

    return e(pDev, Type, StartVertex, PrimitiveCount);
    */
return 0;
}

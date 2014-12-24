
#include "PreComp.h"
#include "dipup.h"
#include "vertform.h"
#include "outtypes.h"
#include "predisp.h"


HRESULT __stdcall mine_IDirect3DDevice9_DrawIndexedPrimitiveUP(IDirect3DDevice9 *pDev, D3DPRIMITIVETYPE Type, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void * pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride){
/*
    TRIPFILE2                rip2head={0};
    TVERTEX_FORMAT            vf={0};
    TFACE*                    pFaces=0;
    TVERTEX*                pVertecies=0;


    PFN_IDirect3DDevice9_DrawIndexedPrimitiveUP e=(PFN_IDirect3DDevice9_DrawIndexedPrimitiveUP)phook_IDirect3DDevice9_DrawIndexedPrimitiveUP->exec;

    if( ( fRip != 0 ) && ( PrimitiveCount >= Options.dwMinPrimitives ) ){
        g_log.Write(TEXT("DrawIndexedPrimitiveUP(0x%08X, %d, %d, %d, %d, 0x%08X, %d, 0x%08X, %d)\n"), pDev, Type, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
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

            if(IndexDataFormat==D3DFMT_INDEX16){//Dump 16 bit indexes
                rip2head.dwVertices=1+GetMaxIndex(Type, (WORD*)((WORD*)pIndexData), PrimitiveCount);
                DumpIndexes(pFaces, (WORD*)((WORD*)pIndexData), Type, PrimitiveCount);
            }
            else{//Dump 32 bit indexes
                rip2head.dwVertices=1+GetMaxIndex(Type, (DWORD*)((DWORD*)pIndexData), PrimitiveCount);
                DumpIndexes(pFaces, (DWORD*)((DWORD*)pIndexData), Type, PrimitiveCount);                            
            }

            pVertecies=(TVERTEX*)malloc(rip2head.dwVertices*sizeof(TVERTEX));
            if(pVertecies==0){
                g_log.Write(TEXT("malloc Error\n"));
                break;
            }

            //Vertecies
            //Position
            DumpVertecies(POSITION, ((BYTE*)pVertexStreamZeroData), pVertecies, rip2head.dwVertices, vf.Position_Type, vf.Position_Offset, VertexStreamZeroStride);
            //-------------------------------------------------
            //Normals
            if(vf.NormalFailed==0){
            DumpVertecies(NORMALS, ((BYTE*)pVertexStreamZeroData), pVertecies, rip2head.dwVertices, vf.Normal_Type, vf.Normal_Offset, VertexStreamZeroStride);
            }

            //Texture Coordinates
            if(vf.TexCoordFailed==0){
            DumpVertecies(TEXCOORD, ((BYTE*)pVertexStreamZeroData), pVertecies, rip2head.dwVertices, vf.TexCoord_Type, vf.TexCoord_Offset, VertexStreamZeroStride);
            }

            DumpMesh(pDev, &rip2head, pVertecies, pFaces);

            break;
        }
    }

    return e(pDev, Type, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);

    */
return 0;    
}

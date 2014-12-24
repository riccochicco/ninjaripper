
#include "PreComp.h"
#include "dpup.h"
#include "vertform.h"
#include "outtypes.h"
#include "predisp.h"


HRESULT __stdcall mine_IDirect3DDevice9_DrawPrimitiveUP(IDirect3DDevice9 *pDev, D3DPRIMITIVETYPE Type, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride){
/*
    TRIPFILE2                rip2head={0};
    TVERTEX_FORMAT            vf={0};
    TFACE*                    pFaces=0;
    TVERTEX*                pVertecies=0;

    PFN_IDirect3DDevice9_DrawPrimitiveUP e=(PFN_IDirect3DDevice9_DrawPrimitiveUP)phook_IDirect3DDevice9_DrawPrimitiveUP->exec;

    if( ( fRip != 0 ) && ( PrimitiveCount >= Options.dwMinPrimitives ) ){
        g_log.Write(TEXT("DrawPrimitiveUP(0x%08X, %d, %d, 0x%08X, %d)\n"), pDev, Type, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
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

    HRESULT    res=e(pDev, Type, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
    return res;
    */
    return 0;
}

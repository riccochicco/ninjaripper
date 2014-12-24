
#include "PreComp.h"
#include "vertform.h"
#include "outtypes.h"
#include "shaders.h"
#include "predisp.h"


wchar_t * szD3DDECLTYPE[]={
    TEXT("FLOAT1"),        //0
    TEXT("FLOAT2"),        //1
    TEXT("FLOAT3"),        //2
    TEXT("FLOAT4"),        //3
    TEXT("D3DCOLOR"),    //4
    TEXT("UBYTE4"),        //5
    TEXT("SHORT2"),        //6
    TEXT("SHORT4"),        //7
    TEXT("UBYTE4N"),    //8
    TEXT("SHORT2N"),    //9
    TEXT("SHORT4N"),    //10
    TEXT("USHORT2N"),    //11
    TEXT("USHORT4N"),    //12
    TEXT("UDEC3"),        //13
    TEXT("DEC3N"),        //14
    TEXT("FLOAT16_2"),    //15
    TEXT("FLOAT16_4"),    //16
    TEXT("UNUSED")        //17
};

wchar_t * szD3DDECLUSAGE[]={
    TEXT("POSITION"),        //0
    TEXT("BLENDWEIGHT"),    //1
    TEXT("BLENDINDICES"),    //2
    TEXT("NORMAL"),            //3
    TEXT("PSIZE"),            //4
    TEXT("TEXCOORD"),        //5
    TEXT("TANGENT"),        //6
    TEXT("BINORMAL"),        //7
    TEXT("TESSFACTOR"),        //8
    TEXT("POSITIONT"),        //9
    TEXT("COLOR"),            //10
    TEXT("FOG"),            //11
    TEXT("DEPTH"),            //12
    TEXT("SAMPLE")            //13
};

wchar_t * szD3DDECLMETHOD[]={
    TEXT("DEFAULT"),        //0
    TEXT("PARTIALU"),        //1
    TEXT("PARTIALV"),        //2
    TEXT("CROSSUV"),        //3
    TEXT("UV"),                //4
    TEXT("LOOKUP"),            //5
    TEXT("LOOKUPPRESAMPLED")//6
};

DWORD TypeSizes[]={
    4,                        //TEXT("FLOAT1"),        //0
    8,                        //TEXT("FLOAT2"),        //1
    12,                        //TEXT("FLOAT3"),        //2
    16,                        //TEXT("FLOAT4"),        //3
    4,                        //TEXT("D3DCOLOR"),        //4
    4,                        //TEXT("UBYTE4"),        //5
    4,                        //TEXT("SHORT2"),        //6
    8,                        //TEXT("SHORT4"),        //7
    4,                        //TEXT("UBYTE4N"),        //8
    4,                        //TEXT("SHORT2N"),        //9
    8,                        //TEXT("SHORT4N"),        //10
    4,                        //TEXT("USHORT2N"),        //11
    8,                        //TEXT("USHORT4N"),        //12
    4,                        //TEXT("UDEC3"),        //13
    4,                        //TEXT("DEC3N"),        //14
    4,                        //TEXT("FLOAT16_2"),    //15
    8,                        //TEXT("FLOAT16_4"),    //16
    0,                        //TEXT("UNUSED")        //17
};


DWORD IsEndDecl( D3DVERTEXELEMENT9* p ){
    if( 
        ( p->Stream == 0xFF ) &&
        ( p->Offset == 0 ) &&
        ( p->Type == D3DDECLTYPE_UNUSED ) &&
        ( p->Method == 0 ) &&
        ( p->Usage == 0 ) &&
        ( p->UsageIndex == 0 )
    )
    return 1;

    return 0;
}

DWORD GetVertexAttributes(IDirect3DDevice9 *pDev, TVERTEX_FORMAT *vf){
/*
    HRESULT res;
    DWORD    Status=-1;
    IDirect3DVertexDeclaration9* pVertDecl=0;
    D3DVERTEXELEMENT9 decl[256];
    UINT numElements;

    //Vertex Declaration
    res = pDev->GetVertexDeclaration(&pVertDecl);
    if(res!=D3D_OK){
        g_log.Write(TEXT("GetVertexDeclaration Error: 0x%08X\n"), res);
    }
    else{
        if(pVertDecl!=0){
//            g_log.Write(TEXT("VertexDeclaration=0x%08X\n"), pVertDecl);
            pVertDecl->GetDeclaration(decl, &numElements);
            
            g_log.Write(TEXT("---VertexDeclaration Dump---\n"));    
            g_log.Write(TEXT("Elements=%d\n"), numElements);
            for(UINT i=0; i<numElements; i++){
                g_log.Write(TEXT("Stream=%d\n"),    decl[i].Stream);
                g_log.Write(TEXT("Offset=%d\n"),    decl[i].Offset);
                g_log.Write(TEXT("Type  =%s\n"),    szD3DDECLTYPE[decl[i].Type]);
                g_log.Write(TEXT("Method=%d\n"),    decl[i].Method);
                g_log.Write(TEXT("Usage =%s\n"),    szD3DDECLUSAGE[decl[i].Usage]);
                g_log.Write(TEXT("UsIndx=%d\n\n"),    decl[i].UsageIndex);
            }

            //Vertex Format
            //Size
            vf->VertSize=0;
            for(UINT i=0; i<numElements; i++){
                vf->VertSize+=TypeSizes[decl[i].Type];
            }

            //Position
            DWORD fPositionExist=0, fNormalsExist=0, fTexCoordExist=0;

            for(UINT i=0; i<numElements; i++){
                if( !IsEndDecl( &decl[i] )  && decl[i].Usage==D3DDECLUSAGE_POSITION ){
                    fPositionExist++;
                    vf->Position_Stream    =(DWORD)decl[i].Stream;
                    vf->Position_Offset    =(DWORD)decl[i].Offset;
                    vf->Position_Type    =(DWORD)decl[i].Type;
                    break;
                }
            }
            //Normals D3DDECL_END
            for(UINT i=0; i<numElements; i++){
                if( !IsEndDecl( &decl[i] ) && decl[i].Usage==D3DDECLUSAGE_NORMAL ){
                    fNormalsExist++;
                    vf->Normal_Stream    =(DWORD)decl[i].Stream;
                    vf->Normal_Offset    =(DWORD)decl[i].Offset;
                    vf->Normal_Type        =(DWORD)decl[i].Type;
                    break;
                }
            }
            //Texture coordinates
            for(UINT i=0; i<numElements; i++){
                if( !IsEndDecl( &decl[i] ) && decl[i].Usage==D3DDECLUSAGE_TEXCOORD ){
                    fTexCoordExist++;
                    vf->TexCoord_Stream    =(DWORD)decl[i].Stream;
                    vf->TexCoord_Offset    =(DWORD)decl[i].Offset;
                    vf->TexCoord_Type    =(DWORD)decl[i].Type;
                    break;
                }
            }

            if(fPositionExist==0){
                g_log.Write(TEXT("Can't recognize all requred vertex data\n"));
            }
            else{
                g_log.Write(TEXT("---Recognized Vertex---\n"));
                g_log.Write(TEXT("Calc. Vert Size: %d\n"), vf->VertSize);

                g_log.Write(TEXT("Position Stream: %d\n"), vf->Position_Stream);
                g_log.Write(TEXT("Position Offset: %d\n"), vf->Position_Offset);
                g_log.Write(TEXT("Position Type  : %s\n"), szD3DDECLTYPE[vf->Position_Type]);
                
                if(fNormalsExist!=0){
                    g_log.Write(TEXT("Normal   Stream: %d\n"), vf->Normal_Stream);
                    g_log.Write(TEXT("Normal   Offset: %d\n"), vf->Normal_Offset);
                    g_log.Write(TEXT("Normal   Type  : %s\n"), szD3DDECLTYPE[vf->Normal_Type]);
                }
                else{
                    g_log.Write(TEXT("Normal   NOT FOUND!!!\n"));
                    vf->NormalFailed=1;
                }

                if(fTexCoordExist!=0){
                    g_log.Write(TEXT("TexCoord Stream: %d\n"), vf->TexCoord_Stream);
                    g_log.Write(TEXT("TexCoord Offset: %d\n"), vf->TexCoord_Offset);
                    g_log.Write(TEXT("TexCoord Type  : %s\n"), szD3DDECLTYPE[vf->TexCoord_Type]);
                }
                else{
                    g_log.Write(TEXT("TexCoord NOT FOUND!!!\n"));
                    vf->TexCoordFailed=1;
                }

                g_log.Write(TEXT("-----------------------\n"));
                Status=0;
            }
        }
        else{
            g_log.Write(TEXT("Vertex Declaration Not Set\n"));
        }
    }
    return Status;
    */
return 0;
}

inline void GetMax(DWORD v, DWORD *pMax){
    *pMax=(v>*pMax)?v:*pMax;
}

DWORD GetMaxIndex(D3DPRIMITIVETYPE Type, WORD *pIdx, DWORD dwPrimCount){
    WORD    *pSrc=pIdx;
    DWORD    Max=0;

    if(Type==D3DPT_TRIANGLELIST){
        for(DWORD i=0; i<dwPrimCount; i++){
            GetMax((DWORD)*pSrc, &Max);
            pSrc++;
            GetMax((DWORD)*pSrc, &Max);
            pSrc++;
            GetMax((DWORD)*pSrc, &Max);
            pSrc++;
        }
    }
    else if(Type==D3DPT_TRIANGLESTRIP){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            GetMax((DWORD)*pSrc, &Max);
            if((k & 0x1)!=0){//WAS ==
                GetMax((DWORD)*(pSrc+1), &Max);
                GetMax((DWORD)*(pSrc+2), &Max);
            }
            else{
                GetMax((DWORD)*(pSrc+2), &Max);
                GetMax((DWORD)*(pSrc+1), &Max);
            }
            pSrc++;
            k++;
        }
    }
    return Max;
}

DWORD GetMaxIndex(D3DPRIMITIVETYPE Type, DWORD *pSrc, DWORD dwPrimCount){
    DWORD    Max=0;

    if(Type==D3DPT_TRIANGLELIST){
        for(DWORD i=0; i<dwPrimCount; i++){
            GetMax(*pSrc, &Max);
            pSrc++;
            GetMax(*pSrc, &Max);
            pSrc++;
            GetMax(*pSrc, &Max);
            pSrc++;
        }
    }
    else if(Type==D3DPT_TRIANGLESTRIP){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            GetMax(*pSrc, &Max);
            if((k & 0x1)!=0){//WAS ==
                GetMax(*(pSrc+1), &Max);
                GetMax(*(pSrc+2), &Max);
            }
            else{
                GetMax(*(pSrc+2), &Max);
                GetMax(*(pSrc+1), &Max);
            }
            pSrc++;
            k++;
        }
    }
    return Max;
}

void DumpIndexes(TFACE *pDst, WORD *pSrc, D3DPRIMITIVETYPE Type, DWORD dwPrimCount){

    if(Type==D3DPT_TRIANGLELIST){
        for(DWORD i=0; i<dwPrimCount; i++){
            pDst->i0=(DWORD)*pSrc;
            pSrc++;
            
            pDst->i1=(DWORD)*pSrc;
            pSrc++;

            pDst->i2=(DWORD)*pSrc;
            pSrc++;

            pDst++;
        }
    }
    else if(Type==D3DPT_TRIANGLESTRIP){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            pDst->i0=(DWORD)*pSrc;
            if((k & 0x1)!=0){//WAS ==
                pDst->i1=(DWORD)*(pSrc+1);
                pDst->i2=(DWORD)*(pSrc+2);
            }
            else{
                pDst->i1=(DWORD)*(pSrc+2);
                pDst->i2=(DWORD)*(pSrc+1);
            }
            k++;
            pSrc++;
            pDst++;
        }
    }
}

void DumpIndexes(TFACE *pDst, DWORD *pSrc, D3DPRIMITIVETYPE Type, DWORD dwPrimCount){

    if(Type==D3DPT_TRIANGLELIST){
        for(DWORD i=0; i<dwPrimCount; i++){
            pDst->i0=*pSrc;
            pSrc++;
            
            pDst->i1=*pSrc;
            pSrc++;

            pDst->i2=*pSrc;
            pSrc++;

            pDst++;
        }
    }
    else if(Type==D3DPT_TRIANGLESTRIP){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            pDst->i0=*pSrc;
            if((k & 0x1)!=0){//WAS ==
                pDst->i1=*(pSrc+1);
                pDst->i2=*(pSrc+2);
            }
            else{
                pDst->i1=*(pSrc+2);
                pDst->i2=*(pSrc+1);
            }
            k++;
            pSrc++;
            pDst++;
        }
    }
}

void DecodeVertex(VOID *pData, DWORD dwVertType, float *f0, float *f1, float *f2, float *f3){
    if       (dwVertType==D3DDECLTYPE_FLOAT1){
        *f0=*((float*)pData+0);
    }
    else if(dwVertType==D3DDECLTYPE_FLOAT2){
        *f0=*((float*)pData+0);
        *f1=*((float*)pData+1);
    }
    else if(dwVertType==D3DDECLTYPE_FLOAT3){
        *f0=*((float*)pData+0);
        *f1=*((float*)pData+1);
        *f2=*((float*)pData+2);
    }
    else if(dwVertType==D3DDECLTYPE_FLOAT4){
        *f0=*((float*)pData+0);
        *f1=*((float*)pData+1);
        *f2=*((float*)pData+2);
        *f3=*((float*)pData+3);
    }
    else if(dwVertType==D3DDECLTYPE_D3DCOLOR){//??????
        *f0=(float)*((BYTE*)pData+0);
        *f1=(float)*((BYTE*)pData+1);
        *f2=(float)*((BYTE*)pData+2);
        *f3=(float)*((BYTE*)pData+3);
    }
    else if(dwVertType==D3DDECLTYPE_UBYTE4){
        *f0=(float)*((BYTE*)pData+0);
        *f1=(float)*((BYTE*)pData+1);
        *f2=(float)*((BYTE*)pData+2);
        *f3=(float)*((BYTE*)pData+3);
    }
    else if(dwVertType==D3DDECLTYPE_SHORT2){
        *f0=(float)*((SHORT*)pData+0);
        *f1=(float)*((SHORT*)pData+1);
    }
    else if(dwVertType==D3DDECLTYPE_SHORT4){
        *f0=(float)*((SHORT*)pData+0);
        *f1=(float)*((SHORT*)pData+1);
        *f2=(float)*((SHORT*)pData+2);
        *f3=(float)*((SHORT*)pData+3);
    }
    else if(dwVertType==D3DDECLTYPE_UBYTE4N){
        *f0=(float)*((BYTE*)pData+0)/255.0f;
        *f1=(float)*((BYTE*)pData+1)/255.0f;
        *f2=(float)*((BYTE*)pData+2)/255.0f;
        *f3=(float)*((BYTE*)pData+3)/255.0f;
    }
    else if(dwVertType==D3DDECLTYPE_SHORT2N){
        *f0=(float)*((SHORT*)pData+0)/32767.0f;
        *f1=(float)*((SHORT*)pData+1)/32767.0f;
    }
    else if(dwVertType==D3DDECLTYPE_SHORT4N){
        *f0=(float)*((SHORT*)pData+0)/32767.0f;
        *f1=(float)*((SHORT*)pData+1)/32767.0f;
        *f2=(float)*((SHORT*)pData+2)/32767.0f;
        *f3=(float)*((SHORT*)pData+3)/32767.0f;
    }
    else if(dwVertType==D3DDECLTYPE_USHORT2N){
        *f0=(float)*((USHORT*)pData+0)/65535.0f;
        *f1=(float)*((USHORT*)pData+1)/65535.0f;
    }
    else if(dwVertType==D3DDECLTYPE_USHORT4N){
        *f0=(float)*((USHORT*)pData+0)/65535.0f;
        *f1=(float)*((USHORT*)pData+1)/65535.0f;
        *f2=(float)*((USHORT*)pData+2)/65535.0f;
        *f3=(float)*((USHORT*)pData+3)/65535.0f;
    }
    else if(dwVertType==D3DDECLTYPE_UDEC3){
        //     10 0x3FF
        //  10    0xFFC00
        //10      0x3FF00000
    
        DWORD t=*((DWORD*)pData+0);

        *f0=(float)((DWORD)(t&0x3FF));
        *f1=(float)((DWORD)(t&0xFFC00)>>10);
        *f2=(float)((DWORD)(t&0x3FF00000)>>20);
    }
    else if(dwVertType==D3DDECLTYPE_DEC3N){    
        DWORD t=*((DWORD*)pData+0);

        *f0=(float)(((DWORD)(t&0x3FF))            /511.0f);
        *f1=(float)(((DWORD)(t&0xFFC00)>>10)    /511.0f);
        *f2=(float)(((DWORD)(t&0x3FF00000)>>20)    /511.0f);
    }
    else if(dwVertType==D3DDECLTYPE_FLOAT16_2){
        *f0=halfToFloat(*((USHORT*)pData+0));
        *f1=halfToFloat(*((USHORT*)pData+1));
    }
    else if(dwVertType==D3DDECLTYPE_FLOAT16_4){
        *f0=halfToFloat(*((USHORT*)pData+0));
        *f1=halfToFloat(*((USHORT*)pData+1));
        *f2=halfToFloat(*((USHORT*)pData+2));
        *f3=halfToFloat(*((USHORT*)pData+3));
    }
}

/*
    pSrc- input data. VertexData(VertexDeclarations)
    pDst- output. TVERTEX array
*/
void DumpVertecies(DWORD OutType, BYTE *pSrc, TVERTEX *pDst, DWORD dwVertCount, DWORD dwVertType, DWORD dwVertOffset, DWORD dwVertSize){
    float flt_0, flt_1, flt_2, flt_3;

    for(DWORD i=0; i<dwVertCount; i++){
        
        flt_0 = flt_1 = flt_2 = flt_3 = 0.0f;

        DecodeVertex(pSrc+dwVertOffset, dwVertType, &flt_0, &flt_1, &flt_2, &flt_3);

        if(OutType==POSITION){
            pDst->v0=flt_0;
            pDst->v1=flt_1;
            pDst->v2=flt_2;
            pDst->v3=flt_3;
        }
        else if(OutType==NORMALS){
            pDst->n0=flt_0;
            pDst->n1=flt_1;
            pDst->n2=flt_2;
            pDst->n3=flt_3;
        }
        else if(OutType==TEXCOORD){
            pDst->tu=flt_0;
            pDst->tv=flt_1;
        }

        pSrc+=dwVertSize;    //next vertex decl
        pDst++;                //next TVERTEX
    }
}


DWORD halfToFloatI(USHORT y){
             register int s = (y >> 15) & 0x00000001;
             register int e = (y >> 10) & 0x0000001f;
             register int m =  y        & 0x000003ff;
         
             if (e == 0)
             {
                 if (m == 0) // Plus or minus zero
                     return s << 31;

                 else // Denormalized number -- renormalize it
                 {
                     while (!(m & 0x00000400))
                     {
                         m <<= 1;
                         e -=  1;
                     }
         
                     e += 1;
                     m &= ~0x00000400;
                 }
             }
             else if (e == 31)
             {
                 if (m == 0) // Inf
                     return (s << 31) | 0x7f800000;
                 else // NaN
                     return (s << 31) | 0x7f800000 | (m << 13);
             }
        
             e = e + (127 - 15);
             m = m << 13;
         
             return (s << 31) | (e << 23) | m;
}

void GenerateIndexes(TFACE *pDst, D3DPRIMITIVETYPE Type, DWORD dwPrimCount){

    if(Type==D3DPT_TRIANGLELIST){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            pDst->i0=k+0;
            pDst->i1=k+1;
            pDst->i2=k+2;
            k+=3;
            pDst++;
        }
    }
    else if(Type==D3DPT_TRIANGLESTRIP){
        DWORD k=0;
        for(DWORD i=0; i<dwPrimCount; i++){
            if((k & 0x1)==0){
                pDst->i0=k+0;
                pDst->i1=k+1;
                pDst->i2=k+2;

            }
            else{
                pDst->i0=k+0;
                pDst->i1=k+2;
                pDst->i2=k+1;
            }
            k++;
            pDst++;
        }
    }
}

DWORD GetVerteciesCount(D3DPRIMITIVETYPE Type, DWORD dwPrimCount){
    DWORD dwVertecies=0;
    if(Type==D3DPT_TRIANGLELIST){
        dwVertecies=3*dwPrimCount;
    }
    else if(Type==D3DPT_TRIANGLESTRIP){
        dwVertecies=2+dwPrimCount;
    }
    return dwVertecies;
}


float halfToFloat(USHORT y){

    union { float f; DWORD i; } v;
    v.i = halfToFloatI(y);
    return v.f;
}


void DumpMesh(IDirect3DDevice9 *pDev, TRIPFILE2 *pRip2head, TVERTEX *pVertecies, TFACE *pFaces){
/*
    wchar_t    szOutFileName[MAX_PATH];
    FILE*    fOutFile=0;

    _stprintf(szOutFileName, TEXT("%s%s%s%s%02d\\%s%04d%s"), szTargetDir, szRipDir, szFramesDir , szFrame, dwFrames, szMesh, dwMeshsInFrame, szMeshExt);
    pRip2head->sign='TSUR';
    pRip2head->cSize=sizeof(TRIPFILE2);
    SaveMeshTextures(pDev, &pRip2head->textures);

    if( Options.fSaveShaders ){
        SaveShaders(pDev, &pRip2head->shaders);
    }

    g_log.Write(TEXT("----------------------\n"));
    g_log.Write(TEXT("Vertecies in mesh: %d\n"), pRip2head->dwVertices);
    g_log.Write(TEXT("Faces     in mesh: %d\n"), pRip2head->dwFaces);
    g_log.Write(TEXT("----------------------\n"));

    fOutFile=_tfopen(szOutFileName, TEXT("wb"));
    if(fOutFile!=0){
        //Header Output
        fwrite(pRip2head, sizeof(TRIPFILE2), 1, fOutFile);
        fwrite(pVertecies, pRip2head->dwVertices*sizeof(TVERTEX), 1, fOutFile);
        fwrite(pFaces     , pRip2head->dwFaces*sizeof(TFACE), 1, fOutFile);
        fclose(fOutFile);

        g_log.Write(TEXT("Mesh saved: %s\n\n"), szOutFileName);
        dwMeshsInFrame++;
        dwMeshsSaved++;
    }
    else{
        g_log.Write(TEXT("Can't open file: %s\n"), szOutFileName);
    }

    if(pFaces!=0)        free(pFaces);
    if(pVertecies!=0)    free(pVertecies);
*/
}

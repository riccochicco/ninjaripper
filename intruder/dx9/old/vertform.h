#pragma once

#include "types.h"
#include "outtypes.h"

struct TVERTEX_FORMAT{
    DWORD    VertSize;

    DWORD    Position_Stream;
    DWORD    Position_Offset;
    DWORD    Position_Type;
    
    DWORD    NormalFailed;
    DWORD    Normal_Stream;
    DWORD    Normal_Offset;
    DWORD    Normal_Type;

    DWORD    TexCoordFailed;
    DWORD    TexCoord_Stream;
    DWORD    TexCoord_Offset;
    DWORD    TexCoord_Type;
};

enum VERTOUTTYPE{
    POSITION    =0,
    NORMALS        =1,
    TEXCOORD    =2
};

DWORD    GetVertexAttributes(IDirect3DDevice9 *, TVERTEX_FORMAT *);
void    GetMax(DWORD, DWORD *, DWORD *);
DWORD    GetMaxIndex(D3DPRIMITIVETYPE, WORD  *, DWORD);
DWORD    GetMaxIndex(D3DPRIMITIVETYPE, DWORD *, DWORD);
void    DumpIndexes(TFACE *, WORD  *, D3DPRIMITIVETYPE, DWORD);
void    DumpIndexes(TFACE *, DWORD *, D3DPRIMITIVETYPE, DWORD);
void    DumpVertecies(DWORD, BYTE *, TVERTEX *, DWORD, DWORD, DWORD, DWORD);
DWORD    halfToFloatI(USHORT);
void    GenerateIndexes(TFACE *, D3DPRIMITIVETYPE , DWORD);
DWORD    GetVerteciesCount(D3DPRIMITIVETYPE, DWORD);
float    halfToFloat(USHORT);
void    DumpMesh(IDirect3DDevice9 *, TRIPFILE2 *, TVERTEX *, TFACE *);

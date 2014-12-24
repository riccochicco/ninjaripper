
#pragma once

#include "types.h"
#include "outtypes.h"

struct TVSRIP{
    IDirect3DVertexShader9    *pVSH;
    char                    vsh_name[16];
};

struct TPSRIP{
    IDirect3DPixelShader9    *pPSH;
    char                    psh_name[16];
};


void SaveShaders(IDirect3DDevice9 *, TSHADERS *);
HRESULT __stdcall mine_IDirect3DDevice9_SetPixelShader (IDirect3DDevice9 *, IDirect3DPixelShader9  *pShader);
HRESULT __stdcall mine_IDirect3DDevice9_SetVertexShader(IDirect3DDevice9 *, IDirect3DVertexShader9 *pShader);

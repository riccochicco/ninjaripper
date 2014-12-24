
#pragma once
#include "types.h"
#include "outtypes.h"

HRESULT __stdcall mine_IDirect3DDevice9_SetTexture(IDirect3DDevice9 *, DWORD, IDirect3DBaseTexture9 *);

void    SaveMeshTextures(IDirect3DDevice9 *, TMESHTEXTURES *);
char *    IsTextureExist(IDirect3DBaseTexture9 *, char *);

struct    TMESHTEXRIP{
    IDirect3DBaseTexture9    *pTex;
    char                    texname[16];
};
void LogTextureSaveError( IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture);

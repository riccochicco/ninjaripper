#pragma once

#include "types.h"
#include "outtypes.h"

DWORD CanSaveTexture( IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture );

DWORD SaveTexture(LPCTSTR szFileName, IDirect3DDevice9 *pDev, IDirect3DBaseTexture9 *pTexture);

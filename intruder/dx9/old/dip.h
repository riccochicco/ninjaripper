#pragma once

#include "types.h"

HRESULT __stdcall mine_IDirect3DDevice9_DrawIndexedPrimitive(IDirect3DDevice9 *, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);

void log_indexbuffer_desc(D3DINDEXBUFFER_DESC *);


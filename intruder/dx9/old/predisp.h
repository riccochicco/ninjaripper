#pragma once

#include "types.h"
#include "intruder.h"

class KHook;


IDirect3D9* __stdcall mine_Direct3DCreate9(UINT);
HRESULT     __stdcall mine_IDirect3D9_CreateDevice(IDirect3D9 *, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS *, IDirect3DDevice9 **);
HRESULT     __stdcall mine_IDirect3DDevice9_Present(IDirect3DDevice9 *, CONST RECT *, CONST RECT *, HWND, CONST RGNDATA *);
HRESULT     __stdcall mine_IDirect3DDevice9_GetSwapChain(IDirect3DDevice9 *pDev, UINT iSwapChain, IDirect3DSwapChain9 ** ppSwapChain);
HRESULT     __stdcall mine_IDirect3DSwapChain9_Present(IDirect3DDevice9 *pDev, 
                                                   CONST RECT * pSourceRect,
                                                   CONST RECT * pDestRect,
                                                   HWND hDestWindowOverride,
                                                   CONST RGNDATA * pDirtyRegion,
                                                   DWORD dwFlags
                                                   );
HRESULT    __stdcall mine_IDirect3DDevice9_CreateVertexBuffer(IDirect3DDevice9 *, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle);
HRESULT    __stdcall mine_IDirect3DDevice9_CreateIndexBuffer(IDirect3DDevice9 *, UINT Length, DWORD Usage, DWORD Format, D3DPOOL Pool,IDirect3DIndexBuffer9  **ppIndexBuffer, HANDLE *pSharedHandle);


//D3D9 Ripper Global Vars
extern KHook* phook_Direct3DCreate9;
extern KHook* phook_IDirect3D9_CreateDevice;
extern KHook* phook_IDirect3DDevice9_SetTexture;
extern KHook* phook_IDirect3DDevice9_DrawIndexedPrimitive;
extern KHook* phook_IDirect3DDevice9_DrawPrimitive;
extern KHook* phook_IDirect3DDevice9_DrawIndexedPrimitiveUP;
extern KHook* phook_IDirect3DDevice9_DrawPrimitiveUP;
extern KHook* phook_IDirect3DDevice9_Present;
extern KHook* phook_IDirect3DDevice9_SetPixelShader;
extern KHook* phook_IDirect3DDevice9_SetVertexShader;
extern KHook* phook_IDirect3DSwapChain9_Persent;
extern KHook* phook_IDirect3DDevice9_GetSwapChain;
extern KHook* phook_IDirect3DDevice9_CreateVertexBuffer;
extern KHook* phook_IDirect3DDevice9_CreateIndexBuffer;

//extern PFN_D3D9_D3DXSaveTextureToFile D3D9_D3DXSaveTextureToFile;
//extern PFN_D3D9_D3DXDisassembleShader D3D9_D3DXDisassembleShader;


#pragma once

#include "../DXSDK/DXSDK9/include/d3d9.h"
#include "../DXSDK/DXSDK9/include/d3dx9tex.h"
#include "../DXSDK/DXSDK9/include/d3dx9shader.h"
#include "../DXSDK/DXSDK9/include/d3dx9mesh.h"
#include "../DXSDK/DXSDK9/include/d3dx9core.h"
#include "../DXSDK/DXSDK9/include/d3d9types.h"


//Types

typedef    HRESULT (__stdcall *PFN_D3DXSaveTextureToFileW)(LPCTSTR, D3DXIMAGE_FILEFORMAT, LPDIRECT3DBASETEXTURE9, CONST PALETTEENTRY *);
typedef    HRESULT (__stdcall *PFN_D3DXDisassembleShader)(CONST DWORD *, BOOL, LPCSTR, LPD3DXBUFFER *);

typedef IDirect3D9* (__stdcall *PFN_Direct3DCreate9)(UINT);
typedef    HRESULT  (__stdcall *PFN_IDirect3D9_CreateDevice)(IDirect3D9 *, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS *, IDirect3DDevice9 **);
//typedef    UINT    ( __stdcall *PFN_IDirect3D9_Release )( IDirect3D9* );
//typedef    UINT    ( __stdcall *PFN_IDirect3DDevice9_Release )( IDirect3DDevice9* );


typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetTexture)            ( IDirect3DDevice9 *, DWORD, IDirect3DBaseTexture9 *);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_DrawIndexedPrimitive)  ( IDirect3DDevice9 *, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_DrawPrimitive)         ( IDirect3DDevice9 *, D3DPRIMITIVETYPE, UINT, UINT);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_DrawIndexedPrimitiveUP)( IDirect3DDevice9 *, D3DPRIMITIVETYPE, UINT, UINT, UINT, CONST void *, D3DFORMAT, CONST void*, UINT);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_DrawPrimitiveUP)       ( IDirect3DDevice9 *, D3DPRIMITIVETYPE, UINT, CONST void *, UINT);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_Present)               ( IDirect3DDevice9 *, CONST RECT *, CONST RECT *, HWND, CONST RGNDATA *);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetPixelShader)        ( IDirect3DDevice9 *, IDirect3DPixelShader9 *);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetVertexShader)       ( IDirect3DDevice9 *, IDirect3DVertexShader9 *);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_GetSwapChain)          ( IDirect3DDevice9 *, UINT iSwapChain, IDirect3DSwapChain9 **);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_CreateVertexBuffer)    ( IDirect3DDevice9 *, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle);
typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_CreateIndexBuffer)     ( IDirect3DDevice9 *, UINT Length, DWORD Usage, DWORD Format, D3DPOOL Pool,IDirect3DIndexBuffer9  **ppIndexBuffer, HANDLE *pSharedHandle);

//typedef HRESULT (__stdcall *PFN_IDirect3DSwapChain9_Release)            ( IDirect3DSwapChain9 * );
typedef HRESULT (__stdcall *PFN_IDirect3DSwapChain9_Present)            ( IDirect3DSwapChain9 *, CONST RECT *,CONST RECT *,HWND,CONST RGNDATA *,DWORD);

//typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetFVF)                ( IDirect3DDevice9 *, DWORD );
//typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetVertexDeclaration)  ( IDirect3DDevice9 *, IDirect3DVertexDeclaration9* );


typedef    HRESULT (__stdcall *PFN_D3DXCompileShader)(
    LPCSTR pSrcData,
    UINT srcDataLen,
    const D3DXMACRO *pDefines,
    LPD3DXINCLUDE pInclude,
    LPCSTR pFunctionName,
    LPCSTR pProfile,
    DWORD Flags,
    LPD3DXBUFFER *ppShader,
    LPD3DXBUFFER *ppErrorMsgs,
    LPD3DXCONSTANTTABLE *ppConstantTable
);


typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetRenderState)( 
    IDirect3DDevice9*, 
    D3DRENDERSTATETYPE State, 
    DWORD Value 
    );


typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetSamplerState)(
    IDirect3DDevice9*,
    DWORD Sampler,
    D3DSAMPLERSTATETYPE Type,
    DWORD Value
    );


typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetTextureStageState)(
    IDirect3DDevice9*,
    DWORD Stage,
    D3DTEXTURESTAGESTATETYPE Type,
    DWORD Value
    );


typedef HRESULT (__stdcall *PFN_IDirect3DDevice9_SetDepthStencilSurface)(
    IDirect3DDevice9*,
    IDirect3DSurface9*
    );


typedef void (__stdcall *PFN_IDirect3DDevice9_SetGammaRamp)(
    IDirect3DDevice9*,
    UINT  iSwapChain,
    DWORD Flags,
    const D3DGAMMARAMP *pRamp
    );

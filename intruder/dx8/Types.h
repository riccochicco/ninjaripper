#pragma once
#include "../DXSDK/DXSDK8/include/d3d8.h"
#include "../DXSDK/DXSDK8/include/d3d8types.h"
#include "../DXSDK/DXSDK8/include/d3dx8tex.h"


typedef IDirect3D8* ( __stdcall *PFN_Direct3DCreate8 )( UINT );


typedef    HRESULT ( __stdcall *PFN_IDirect3D8_CreateDevice )
        ( IDirect3D8*, 
        UINT Adapter,
        D3DDEVTYPE DeviceType,
        HWND hFocusWindow,
        DWORD BehaviorFlags,
        D3DPRESENT_PARAMETERS* pPresentationParameters,
        IDirect3DDevice8** ppReturnedDeviceInterface
        );


typedef HRESULT ( __stdcall* PFN_D3DXSaveTextureToFileW )
    ( 
    LPCTSTR, 
    DWORD, 
    LPDIRECT3DBASETEXTURE8, 
    void* 
    );


typedef UINT    ( __stdcall* PFN_D3DXGetFVFVertexSize )( DWORD );

typedef HRESULT ( __stdcall* PFN_D3DXDeclaratorFromFVF)( DWORD FVF, DWORD* Declaration );



typedef    UINT    ( __stdcall *PFN_IDirect3D8_Release )( IDirect3D8* );

typedef    UINT    ( __stdcall *PFN_IDirect3DDevice8_Release )( IDirect3DDevice8* );

typedef    HRESULT ( __stdcall *PFN_IDirect3DDevice8_SetTexture )
    ( 
    IDirect3DDevice8*, 
    DWORD Stage, 
    IDirect3DBaseTexture8* pTexture 
    );


typedef    HRESULT ( __stdcall *PFN_IDirect3DDevice8_DrawPrimitive)
    ( 
    IDirect3DDevice8*, 
    D3DPRIMITIVETYPE PrimitiveType, 
    UINT StartVertex, 
    UINT PrimitiveCount 
    );


typedef    HRESULT ( __stdcall *PFN_IDirect3DDevice8_DrawIndexedPrimitive)
    ( 
    IDirect3DDevice8*,  
    D3DPRIMITIVETYPE,
    UINT minIndex,
    UINT NumVertices,
    UINT startIndex, 
    UINT primCount 
    );


typedef    HRESULT ( __stdcall *PFN_IDirect3DDevice8_DrawPrimitiveUP )
    ( 
    IDirect3DDevice8*, 
    D3DPRIMITIVETYPE PrimitiveType,
    UINT PrimitiveCount,
    CONST void* pVertexStreamZeroData, 
    UINT VertexStreamZeroStride
    );


typedef    HRESULT ( __stdcall *PFN_IDirect3DDevice8_DrawIndexedPrimitiveUP)
    ( 
    IDirect3DDevice8*, 
    D3DPRIMITIVETYPE PrimitiveType,
    UINT MinVertexIndex,
    UINT NumVertexIndices,
    UINT PrimitiveCount,
    CONST void* pIndexData,
    D3DFORMAT IndexDataFormat,
    CONST void* pVertexStreamZeroData,
    UINT VertexStreamZeroStride
    );


typedef HRESULT ( __stdcall *PFN_IDirect3DDevice8_Present)
    ( 
    IDirect3DDevice8 *,
    CONST RECT *,
    CONST RECT *,
    HWND,
    CONST RGNDATA *
    );


typedef HRESULT ( __stdcall *PFN_IDirect3DDevice8_CreateVertexBuffer)
    ( 
    IDirect3DDevice8 *,
    UINT Length,
    DWORD Usage,
    DWORD FVF,
    D3DPOOL Pool,
    IDirect3DVertexBuffer8** ppVertexBuffer
    );


typedef HRESULT ( __stdcall *PFN_IDirect3DDevice8_CreateIndexBuffer)
    (
    IDirect3DDevice8 *,
    UINT Length,
    DWORD Usage,
    D3DFORMAT Format,
    D3DPOOL Pool,
    IDirect3DIndexBuffer8** ppIndexBuffer
    );



typedef HRESULT (__stdcall *PFN_IDirect3DDevice8_CreateVertexShader)(
    IDirect3DDevice8 *,
    CONST DWORD* pDeclaration,
    CONST DWORD* pFunction,
    DWORD* pHandle,
    DWORD Usage
    );


typedef HRESULT (__stdcall* PFN_IDirect3DDevice8_CreatePixelShader)(
    IDirect3DDevice8 *,
    CONST DWORD* pFunction,
    DWORD* pHandle
    );



typedef HRESULT ( __stdcall* PFN_IDirect3DDevice8_DeleteVertexShader)(
    IDirect3DDevice8*,
    DWORD Handle
    );


typedef HRESULT ( __stdcall* PFN_IDirect3DDevice8_DeletePixelShader)(
    IDirect3DDevice8*,
    DWORD Handle
    );


typedef HRESULT ( __stdcall* PFN_IDirect3DDevice8_SetVertexShader)(
    IDirect3DDevice8*,
    DWORD Handle
    );

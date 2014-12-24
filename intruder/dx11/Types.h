#pragma once
#include "../DXSDK/DXSDK11/include/d3d11.h"
#include "../DXSDK/DXSDK11/include/d3dx11tex.h"
#include "../DXSDK/DXSDK11/include/d3dx11.h"
#include "../DXSDK/DXSDK11/include/d3dcompiler.h"
#include "../DXSDK/DXSDK11/include/xnamath.h"
#include "../DXSDK/DXSDK11/include/dxgi.h"



typedef HRESULT ( __stdcall* PFN_ID3D11Device_CreateInputLayout )(
    ID3D11Device* pDev,
    const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
    UINT NumElements,
    const void *pShaderBytecodeWithInputSignature,
    SIZE_T BytecodeLength,
    ID3D11InputLayout **ppInputLayout
    );



typedef HRESULT (__stdcall* PFN_IDXGIFactory_CreateSwapChain )(
    IDXGIFactory* pFactory,
    IUnknown *pDevice,
    DXGI_SWAP_CHAIN_DESC *pDesc,
    IDXGISwapChain **ppSwapChain
);


typedef HRESULT  (__stdcall* PFN_CreateDXGIFactory )(
    void* riid,
    void** ppFactory
);


typedef HRESULT  (__stdcall* PFN_CreateDXGIFactory1 )(
    void* riid,
    void **ppFactory
);


typedef HRESULT (__stdcall* PFN_D3D11CreateDeviceAndSwapChain)(
    IDXGIAdapter*, 
    D3D_DRIVER_TYPE, 
    HMODULE, 
    UINT, 
    CONST D3D_FEATURE_LEVEL*, 
    UINT FeatureLevels, 
    UINT,
    CONST DXGI_SWAP_CHAIN_DESC*, 
    IDXGISwapChain**,
    ID3D11Device**, 
    D3D_FEATURE_LEVEL*,
    ID3D11DeviceContext** 
    );


typedef HRESULT (__stdcall* PFN_D3D11CreateDevice)(
    IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device **ppDevice,
    D3D_FEATURE_LEVEL *pFeatureLevel,
    ID3D11DeviceContext **ppImmediateContext
    );


typedef HRESULT ( __stdcall *PFN_D3DX11SaveTextureToFileW )(
        ID3D11DeviceContext       *pContext,
        ID3D11Resource            *pSrcTexture,
        D3DX11_IMAGE_FILE_FORMAT   DestFormat,
        const wchar_t*             pDestFile);




typedef HRESULT ( __stdcall *PFN_D3DX11CompileFromMemory)(
    LPCSTR pSrcData, 
    SIZE_T SrcDataLen, 
    LPCSTR pFileName, 
    CONST D3D10_SHADER_MACRO* pDefines, 
    LPD3D10INCLUDE pInclude, 
    LPCSTR pFunctionName, 
    LPCSTR pProfile, 
    UINT Flags1, 
    UINT Flags2, 
    ID3DX11ThreadPump* pPump, 
    ID3D10Blob** ppShader, 
    ID3D10Blob** ppErrorMsgs, 
    HRESULT* pHResult
    );




typedef void ( __stdcall *PFN_ID3D11DeviceContext_PSSetShaderResources )(
        ID3D11DeviceContext*,
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews );

typedef void ( __stdcall *PFN_ID3D11DeviceContext_VSSetShaderResources )(
    ID3D11DeviceContext*,
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView *const *ppShaderResourceViews );


typedef void ( __stdcall *PFN_ID3D11DeviceContext_GSSetShaderResources )(
    ID3D11DeviceContext*,
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView *const *ppShaderResourceViews );


typedef void ( __stdcall *PFN_ID3D11DeviceContext_Draw )(
        ID3D11DeviceContext*,
        UINT VertexCount,
        UINT StartVertexLocation);


typedef void ( __stdcall *PFN_ID3D11DeviceContext_DrawAuto )(
        ID3D11DeviceContext*);


typedef void ( __stdcall *PFN_ID3D11DeviceContext_DrawIndexed )(
        ID3D11DeviceContext*,
        UINT IndexCount,
        UINT StartIndexLocation,
        INT BaseVertexLocation
        );



typedef void ( __stdcall *PFN_ID3D11DeviceContext_DrawIndexedInstanced )(
        ID3D11DeviceContext*,
        UINT IndexCountPerInstance,
        UINT InstanceCount,
        UINT StartIndexLocation,
        INT BaseVertexLocation,
        UINT StartInstanceLocation
        );


typedef void ( __stdcall *PFN_ID3D11DeviceContext_DrawIndexedInstancedIndirect )(
        ID3D11DeviceContext*,
        ID3D11Buffer *pBufferForArgs,
        UINT AlignedByteOffsetForArgs
        );


typedef void ( __stdcall *PFN_ID3D11DeviceContext_DrawInstanced )(
        ID3D11DeviceContext*,
        UINT VertexCountPerInstance,
        UINT InstanceCount,
        UINT StartVertexLocation,
        UINT StartInstanceLocation
        );


typedef void ( __stdcall *PFN_ID3D11DeviceContext_DrawInstancedIndirect )(
        ID3D11DeviceContext*,
        ID3D11Buffer *pBufferForArgs,
        UINT AlignedByteOffsetForArgs
        );


typedef HRESULT ( __stdcall *PFN_IDXGISwapChain_Present )(
    IDXGISwapChain*,
    UINT,
    UINT
    );

/*
typedef HRESULT ( __stdcall* PFN_ID3D11Device_CreateBuffer )(
    ID3D11Device*,
    const D3D11_BUFFER_DESC*,
    const D3D11_SUBRESOURCE_DATA *,
    ID3D11Buffer**
    );
*/

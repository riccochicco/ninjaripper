#pragma once

#include "../DXSDK/DXSDK11/include/d3d11.h"
#include "../DXSDK/DXSDK11/include/d3dx11tex.h"
#include "../DXSDK/DXSDK11/include/d3dx11.h"
#include "../DXSDK/DXSDK11/include/d3dcompiler.h"
#include "../DXSDK/DXSDK11/include/xnamath.h"
#include "../DXSDK/DXSDK11/include/dxgi.h"


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



typedef HRESULT (__stdcall* PFN_D3D11CoreRegisterLayers)( PVOID, PVOID );
typedef HRESULT (__stdcall* PFN_D3D11CoreGetLayeredDeviceSize)( PVOID, PVOID );
typedef HRESULT (__stdcall* PFN_D3D11CoreCreateLayeredDevice)( PVOID, PVOID,PVOID, PVOID, PVOID );

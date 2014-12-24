
#include "stdafx.h"
#include <windows.h>
#include "d3d11wrap.h"
#include "intruder.h"



static HINSTANCE LoadD3D11(){
	HINSTANCE hD3D11 = NULL;

	TCHAR	szBuffer[MAX_PATH];
	GetSystemDirectory(szBuffer, MAX_PATH);
	lstrcat(szBuffer, TEXT("\\d3d11.dll"));
	hD3D11 = GetModuleHandle( szBuffer );
	if( !hD3D11 ){
		hD3D11 = LoadLibrary( szBuffer );
		if( hD3D11 == 0 ) FatalErrorMsg( TEXT("Can't load d3d11.dll") );
	}
	return hD3D11;
}


//D3D11
extern "C" HRESULT __stdcall D3D11CreateDeviceAndSwapChain_(
	IDXGIAdapter* pAdap, 
	D3D_DRIVER_TYPE dt, 
	HMODULE hm, 
	UINT  param1, 
	CONST D3D_FEATURE_LEVEL* pFeat, 
	UINT FeatureLevels, 
	UINT param2,
	CONST DXGI_SWAP_CHAIN_DESC* pparam3, 
	IDXGISwapChain** ppSwap,
	ID3D11Device** ppDev, 
	D3D_FEATURE_LEVEL* pFeat2,
	ID3D11DeviceContext** ppDevCont
	)
{
	HINSTANCE hD3D11 = LoadD3D11();
	
	PFN_D3D11CreateDeviceAndSwapChain true_D3D11CreateDeviceAndSwapChain = NULL;
	true_D3D11CreateDeviceAndSwapChain
		= ( PFN_D3D11CreateDeviceAndSwapChain )GetProcAddress( hD3D11, "D3D11CreateDeviceAndSwapChain" );
	
	if( !true_D3D11CreateDeviceAndSwapChain ){
		FatalErrorMsg( TEXT("Can't get address of D3D11CreateDeviceAndSwapChain") );
	}
		
	return true_D3D11CreateDeviceAndSwapChain(
		pAdap, dt,hm, param1,pFeat, FeatureLevels, param2, pparam3, ppSwap, ppDev, pFeat2, ppDevCont
		);

}




extern "C" HRESULT __stdcall D3D11CreateDevice_(
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
	)
{

	HINSTANCE hD3D11 = LoadD3D11();

	PFN_D3D11CreateDevice true_D3D11CreateDevice = NULL;
	true_D3D11CreateDevice
		= ( PFN_D3D11CreateDevice )GetProcAddress( hD3D11, "D3D11CreateDevice" );

	if( !true_D3D11CreateDevice ){
		FatalErrorMsg( TEXT("Can't get address of D3D11CreateDevice") );
	}

	return true_D3D11CreateDevice(
		pAdapter, 
		DriverType, 
		Software, 
		Flags, 
		pFeatureLevels, 
		FeatureLevels,
		SDKVersion,
		ppDevice,
		pFeatureLevel, 
		ppImmediateContext
		);

}


extern "C" HRESULT __stdcall D3D11CoreRegisterLayers_( PVOID p1, PVOID p2 ){

	HINSTANCE hD3D11 = LoadD3D11();

	PFN_D3D11CoreRegisterLayers true_D3D11CoreRegisterLayers = NULL;
	true_D3D11CoreRegisterLayers
		= ( PFN_D3D11CoreRegisterLayers )GetProcAddress( hD3D11, "D3D11CoreRegisterLayers" );

	if( !true_D3D11CoreRegisterLayers ){
		FatalErrorMsg( TEXT("Can't get address of D3D11CoreRegisterLayers") );
	}

	return true_D3D11CoreRegisterLayers( p1, p2 );
}




extern "C" HRESULT __stdcall D3D11CoreGetLayeredDeviceSize_( PVOID p1, PVOID p2 ){

	HINSTANCE hD3D11 = LoadD3D11();

	PFN_D3D11CoreGetLayeredDeviceSize true_Func = NULL;
	true_Func
		= ( PFN_D3D11CoreGetLayeredDeviceSize )GetProcAddress( hD3D11, "D3D11CoreGetLayeredDeviceSize" );

	if( !true_Func ){
		FatalErrorMsg( TEXT("Can't get address of D3D11CoreGetLayeredDeviceSize") );
	}

	return true_Func( p1, p2 );
}


extern "C" HRESULT __stdcall D3D11CoreCreateLayeredDevice_( PVOID p1, PVOID p2, PVOID p3, PVOID p4, PVOID p5 ){

	HINSTANCE hD3D11 = LoadD3D11();

	PFN_D3D11CoreCreateLayeredDevice true_Func = NULL;
	true_Func
		= ( PFN_D3D11CoreCreateLayeredDevice )GetProcAddress( hD3D11, "D3D11CoreCreateLayeredDevice" );

	if( !true_Func ){
		FatalErrorMsg( TEXT("Can't get address of D3D11CoreCreateLayeredDevice") );
	}

	return true_Func( p1, p2, p3, p4, p5 );
}


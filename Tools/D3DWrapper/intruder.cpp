// intruder.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>

#include "intruder.h"
#include "registry.h"


#pragma comment(lib, "shlwapi.lib")


//Global Variables
static HINSTANCE hIntruder=0, hDDraw=0, hDInput=0, hD3D8=0, hD3D9=0;


void LoadDDRAW(){
	TCHAR	szBuffer[MAX_PATH];
	GetSystemDirectory(szBuffer, MAX_PATH);
	lstrcat(szBuffer, TEXT("\\ddraw.dll"));
	hDDraw = GetModuleHandle(szBuffer);
	if(hDDraw==0){
		hDDraw=LoadLibrary(szBuffer);
		if(hDDraw==0) FatalErrorMsg(TEXT("Can't load ddraw.dll"));
	}
}

void LoadD3D9(){
	TCHAR	szBuffer[MAX_PATH];
	GetSystemDirectory(szBuffer, MAX_PATH);
	lstrcat(szBuffer, TEXT("\\d3d9.dll"));
	hD3D9 = GetModuleHandle(szBuffer);
	if(hD3D9==0){
		hD3D9=LoadLibrary(szBuffer);
		if(hD3D9==0) FatalErrorMsg(TEXT("Can't load d3d9.dll"));
	}
}


void LoadD3D8(){
	TCHAR	szBuffer[MAX_PATH];
	GetSystemDirectory(szBuffer, MAX_PATH);
	lstrcat(szBuffer, TEXT("\\d3d8.dll"));
	hD3D8 = GetModuleHandle(szBuffer);
	if( !hD3D8 ){
		hD3D8 = LoadLibrary(szBuffer);
		if(! hD3D8 ) FatalErrorMsg(TEXT("Can't load d3d8.dll"));
	}
}



void FatalErrorMsg(LPCTSTR msg){
	MessageBox(0, msg, TEXT("intruder"), MB_ICONERROR|MB_TOPMOST);
	ExitProcess(-1);
}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	hIntruder=(HINSTANCE)hModule;

	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls((HMODULE)hModule);
			install();
			break;
		case DLL_PROCESS_DETACH:
			uninst();
			break;
	}
	return TRUE;
}

void install(){
	//TCHAR szIntruderDir[MAX_PATH];
	//Intruder dll Directory
	//GetModuleFileName(hIntruder, szIntruderDir, MAX_PATH);
	//for(DWORD i=(DWORD)lstrlen(szIntruderDir); i>0; i--){if(szIntruderDir[i-1]==TEXT('\\')){szIntruderDir[i]=0; break;}}
	
	wchar_t szSubKey[ 250 ];
	swprintf_s( szSubKey, 250, L"%s", L"SOFTWARE\\black_ninja\\NinjaRipper" );
	
	std::wstring IntruderDir;

	RegGetStringValue( HKEY_CURRENT_USER, szSubKey, L"IntruderDir", IntruderDir );
	//wcscat_s(szIntruderDir, MAX_PATH, L"intruder.dll");
	IntruderDir += L"intruder.dll";
	HMODULE hMod = LoadLibrary( IntruderDir.c_str() );
	if( !hMod ){
		FatalErrorMsg( L"intruder.dll load error" );
	}
}

void uninst(){

}





//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//FIX: write normal pointers to function


//////////////////////////////////////////////////////////////////////////
//EXPORTS FOR WRAPPER MODE
//////////////////////////////////////////////////////////////////////////






//DDRAW
extern "C" DWORD __stdcall DirectDrawCreate_(DWORD lpGUID, DWORD lplpDD, DWORD pUnkOuter){
	LoadDDRAW();
	PFN1 true_DirectDrawCreate=(PFN1)GetProcAddress(hDDraw, "DirectDrawCreate");
	if(true_DirectDrawCreate==0) FatalErrorMsg(TEXT("Can't get address of DirectDrawCreate"));

	return true_DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
}

//DX7
extern "C" DWORD __stdcall DirectDrawCreateEx_(DWORD lpGUID, DWORD lplpDD, DWORD iid, DWORD pUnkOuter){
	LoadDDRAW();
	PFN2 true_DirectDrawCreateEx=(PFN2)GetProcAddress(hDDraw, "DirectDrawCreateEx");
	if(true_DirectDrawCreateEx==0) FatalErrorMsg(TEXT("Can't get address of DirectDrawCreateEx"));
	return true_DirectDrawCreateEx(lpGUID, lplpDD, iid, pUnkOuter);
}


extern "C" DWORD __stdcall DirectDrawEnumerateW_(DWORD lpCallback, DWORD lpContext ){
	LoadDDRAW();
	PFN000_1 adrDirectDrawEnumerateW=(PFN000_1)GetProcAddress(hDDraw, "DirectDrawEnumerateW");
	if(!adrDirectDrawEnumerateW) FatalErrorMsg(TEXT("Can't get address of DirectDrawEnumerateW"));
	return adrDirectDrawEnumerateW(lpCallback, lpContext);
}

extern "C" DWORD __stdcall DirectDrawEnumerateA_(DWORD lpCallback, DWORD lpContext){
	LoadDDRAW();
	PFN000_2 adrDirectDrawEnumerateA=(PFN000_2)GetProcAddress(hDDraw, "DirectDrawEnumerateA");
	if(!adrDirectDrawEnumerateA) FatalErrorMsg(TEXT("Can't get address of DirectDrawEnumerateA"));
	return adrDirectDrawEnumerateA(lpCallback, lpContext);
}

extern "C" DWORD __stdcall DirectDrawEnumerateExW_(DWORD lpCallback, DWORD lpContext, DWORD dwFlags){
	LoadDDRAW();
	PFN000_3 adrDirectDrawEnumerateExW=(PFN000_3)GetProcAddress(hDDraw, "DirectDrawEnumerateExW");
	if(!adrDirectDrawEnumerateExW) FatalErrorMsg(TEXT("Can't get address of DirectDrawEnumerateExW"));
	return adrDirectDrawEnumerateExW(lpCallback, lpContext, dwFlags);
}

extern "C" DWORD __stdcall DirectDrawEnumerateExA_(DWORD lpCallback, DWORD lpContext, DWORD dwFlags){
	LoadDDRAW();
	PFN000_4 adrDirectDrawEnumerateExA=(PFN000_4)GetProcAddress(hDDraw, "DirectDrawEnumerateExA");
	if(!adrDirectDrawEnumerateExA) FatalErrorMsg(TEXT("Can't get address of DirectDrawEnumerateExA"));
	return adrDirectDrawEnumerateExA(lpCallback, lpContext, dwFlags);
}
/////////////////////////////////////////////////////////////



//DX 9
extern "C" DWORD __stdcall Direct3DCreate9_(UINT SDKVersion){
	LoadD3D9();
	PFN5 true_Direct3DCreate9=(PFN5)GetProcAddress(hD3D9, "Direct3DCreate9");
	if(true_Direct3DCreate9==0) FatalErrorMsg(TEXT("Can't get address of Direct3DCreate9"));
	return true_Direct3DCreate9(SDKVersion);
}

extern "C" DWORD __stdcall D3DPERF_BeginEvent_(DWORD col, LPCWSTR wszName){
	LoadD3D9();
	PFN001	adrD3DPERF_BeginEvent=(PFN001)GetProcAddress(hD3D9, "D3DPERF_BeginEvent");
	if(adrD3DPERF_BeginEvent==0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_BeginEvent"));
	return adrD3DPERF_BeginEvent(col, wszName);
}


extern "C" DWORD __stdcall D3DPERF_EndEvent_(){
	LoadD3D9();
	PFN002	adrD3DPERF_EndEvent=(PFN002)GetProcAddress(hD3D9, "D3DPERF_EndEvent");
	if(adrD3DPERF_EndEvent==0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_EndEvent"));
	return adrD3DPERF_EndEvent();
}


extern "C" DWORD __stdcall D3DPERF_SetMarker_(DWORD col, LPCWSTR wszName){
	LoadD3D9();
	PFN003	adrD3DPERF_SetMarker=(PFN003)GetProcAddress(hD3D9, "D3DPERF_SetMarker");
	if(adrD3DPERF_SetMarker==0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_SetMarker"));
	return adrD3DPERF_SetMarker(col, wszName);
}

extern "C" DWORD __stdcall D3DPERF_SetRegion_(DWORD col, LPCWSTR wszName){
	LoadD3D9();
	PFN004	adrD3DPERF_SetRegion=(PFN004)GetProcAddress(hD3D9, "D3DPERF_SetRegion");
	if(adrD3DPERF_SetRegion==0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_SetRegion"));
	return adrD3DPERF_SetRegion(col, wszName);
}


extern "C" DWORD __stdcall D3DPERF_QueryRepeatFrame_(){
	LoadD3D9();
	PFN005	adrD3DPERF_QueryRepeatFrame=(PFN005)GetProcAddress(hD3D9, "D3DPERF_QueryRepeatFrame");
	if(adrD3DPERF_QueryRepeatFrame=0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_QueryRepeatFrame"));
	return adrD3DPERF_QueryRepeatFrame();
}


extern "C" DWORD __stdcall D3DPERF_SetOptions_(DWORD dwOptions){
	LoadD3D9();
	PFN006	adrD3DPERF_SetOptions=(PFN006)GetProcAddress(hD3D9, "D3DPERF_SetOptions");
	if(adrD3DPERF_SetOptions=0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_SetOptions"));
	return adrD3DPERF_SetOptions(dwOptions);
}


extern "C" DWORD __stdcall D3DPERF_GetStatus_(){
	LoadD3D9();
	PFN007	adrD3DPERF_GetStatus=(PFN007)GetProcAddress(hD3D9, "D3DPERF_GetStatus");
	if(adrD3DPERF_GetStatus=0) FatalErrorMsg(TEXT("Can't get address of D3DPERF_GetStatus"));
	return adrD3DPERF_GetStatus();
}



//DX 8
extern "C" DWORD __stdcall Direct3DCreate8_(UINT SDKVersion){
	LoadD3D8();
	PFN5 true_Direct3DCreate8;
	true_Direct3DCreate8=(PFN5)GetProcAddress(hD3D8, "Direct3DCreate8");
	if(true_Direct3DCreate8==0) FatalErrorMsg(TEXT("Can't get address of Direct3DCreate8"));
	return true_Direct3DCreate8(SDKVersion);
}






//////////////////////////////////////////////////////////////////////////
//DDRAW undocumented exports
extern "C" DWORD __stdcall ReleaseDDThreadLock_(){
	LoadDDRAW();
	PFN0 true_f=(PFN0)GetProcAddress(hDDraw, "ReleaseDDThreadLock");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of ReleaseDDThreadLock"));
	return true_f();
}

extern "C" DWORD __stdcall D3DParseUnknownCommand_(DWORD a0, DWORD a1){
	LoadDDRAW();
	PFN000_1 true_f=(PFN000_1)GetProcAddress(hDDraw, "D3DParseUnknownCommand");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of D3DParseUnknownCommand"));
	return true_f(a0, a1);
}


extern "C" DWORD __stdcall AcquireDDThreadLock_(){
	LoadDDRAW();
	PFN0 true_f=(PFN0)GetProcAddress(hDDraw, "AcquireDDThreadLock");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of AcquireDDThreadLock"));
	return true_f();
}

extern "C" DWORD __stdcall CheckFullscreen_(){
	LoadDDRAW();
	PFN0 true_f=(PFN0)GetProcAddress(hDDraw, "CheckFullscreen");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of CheckFullscreen"));
	return true_f();
}


extern "C" DWORD __stdcall CompleteCreateSysmemSurface_(DWORD a0){
	LoadDDRAW();
	PFN7 true_f=(PFN7)GetProcAddress(hDDraw, "CompleteCreateSysmemSurface");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of CompleteCreateSysmemSurface"));
	return true_f(a0);
}



extern "C" DWORD __stdcall DDGetAttachedSurfaceLcl_(DWORD a0, DWORD a1, DWORD a2){
	LoadDDRAW();
	PFN1 true_f=(PFN1)GetProcAddress(hDDraw, "DDGetAttachedSurfaceLcl");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of DDGetAttachedSurfaceLcl"));
	return true_f(a0,a1,a2);
}


extern "C" DWORD __stdcall DDInternalLock_(){
	LoadDDRAW();
	PFN0 true_f=(PFN0)GetProcAddress(hDDraw, "DDInternalLock");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of DDInternalLock"));
	return true_f();
}



extern "C" DWORD __stdcall DDInternalUnlock_(DWORD a0){
	LoadDDRAW();
	PFN7 true_f=(PFN7)GetProcAddress(hDDraw, "DDInternalUnlock");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of DDInternalUnlock"));
	return true_f(a0);
}


extern "C" DWORD __stdcall DSoundHelp_(DWORD a0, DWORD a1, DWORD a2){
	LoadDDRAW();
	PFN1 true_f=(PFN1)GetProcAddress(hDDraw, "DSoundHelp");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of DSoundHelp"));
	return true_f(a0,a1,a2);
}

extern "C" DWORD __stdcall GetDDSurfaceLocal_(DWORD a0, DWORD a1, DWORD a2){
	LoadDDRAW();
	PFN1 true_f=(PFN1)GetProcAddress(hDDraw, "GetDDSurfaceLocal");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of GetDDSurfaceLocal"));
	return true_f(a0,a1,a2);
}


extern "C" DWORD __stdcall GetOLEThunkData_(DWORD a0){
	LoadDDRAW();
	PFN7 true_f=(PFN7)GetProcAddress(hDDraw, "GetOLEThunkData");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of GetOLEThunkData"));
	return true_f(a0);
}


extern "C" DWORD __stdcall GetSurfaceFromDC_(DWORD a0, DWORD a1, DWORD a2){
	LoadDDRAW();
	PFN1 true_f=(PFN1)GetProcAddress(hDDraw, "GetSurfaceFromDC");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of GetSurfaceFromDC"));
	return true_f(a0,a1,a2);
}


extern "C" DWORD __stdcall RegisterSpecialCase_(DWORD a0, DWORD a1, DWORD a2, DWORD a3){
	LoadDDRAW();
	PFN2 true_f=(PFN2)GetProcAddress(hDDraw, "RegisterSpecialCase");
	if(true_f==0) FatalErrorMsg(TEXT("Can't get address of RegisterSpecialCase"));
	return true_f(a0, a1, a2, a3);
}



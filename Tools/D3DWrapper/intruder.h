#pragma once


//Function Prototypes
void	install();
void	uninst();
void	FatalErrorMsg(LPCTSTR);
void	ReadSettings();

DWORD	__stdcall mine_DirectDrawCreate(DWORD, DWORD, DWORD);
DWORD	__stdcall mine_DirectDrawCreateEx(DWORD, DWORD, DWORD, DWORD);
DWORD	__stdcall mine_DirectInputCreateA(DWORD, DWORD, DWORD,  DWORD);
DWORD	__stdcall mine_Direct3DCreate8(UINT);
DWORD	__stdcall mine_Direct3DCreate9(UINT);

typedef DWORD	(__stdcall *PFN1)(DWORD, DWORD, DWORD);
typedef DWORD	(__stdcall *PFN2)(DWORD, DWORD, DWORD, DWORD);
typedef DWORD	(__stdcall *PFN3)(DWORD, DWORD, DWORD, DWORD);
typedef DWORD	(__stdcall *PFN4)(UINT);
typedef DWORD	(__stdcall *PFN5)(UINT);

typedef DWORD	(__stdcall *PFN0)();
typedef DWORD	(__stdcall *PFN7)(DWORD);

//ddraw.dll export types
//DirectDrawEnumerateW
typedef DWORD	(__stdcall *PFN000_1)(DWORD, DWORD);

//DirectDrawEnumerateA
typedef DWORD	(__stdcall *PFN000_2)(DWORD, DWORD);

//DirectDrawEnumerateExW
typedef DWORD	(__stdcall *PFN000_3)(DWORD, DWORD, DWORD);

//DirectDrawEnumerateExA
typedef DWORD	(__stdcall *PFN000_4)(DWORD, DWORD, DWORD);

typedef DWORD			(__stdcall *PFN001)(DWORD, LPCWSTR);
typedef DWORD			(__stdcall *PFN002)();
typedef DWORD			(__stdcall *PFN003)(DWORD, LPCWSTR);
typedef DWORD			(__stdcall *PFN004)(DWORD, LPCWSTR);
typedef DWORD			(__stdcall *PFN005)();
typedef DWORD			(__stdcall *PFN006)(DWORD);
typedef DWORD			(__stdcall *PFN007)();


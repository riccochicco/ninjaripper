#pragma once



//Function Prototypes
void FatalErrorMsg(LPCTSTR msg);


#pragma pack(push,1)
struct KUNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
};
#pragma pack(pop)



typedef    DWORD (__stdcall *PFN_LdrLoadDll)( WORD* a1, DWORD* pError, KUNICODE_STRING* pUnicode, DWORD* pResInst );
LPVOID Pre_LdrLoadDll( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook );
DWORD  _LdrLoadDll( PFN_LdrLoadDll e, WORD* a1, DWORD* pError, KUNICODE_STRING* pUnicode, DWORD* pResInst );


typedef    DWORD (__stdcall *PFN_LdrUnloadDll)( HINSTANCE );
LPVOID Pre_LdrUnloadDll( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook );
DWORD  _LdrUnloadDll( PFN_LdrUnloadDll e, HINSTANCE );



typedef BOOL ( __stdcall *PFN_CreateProcessA )(
    const char* lpApplicationName,
    char* lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    const char* lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );
LPVOID Pre_CreateProcessA( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook );
DWORD  _CreateProcessA( PFN_CreateProcessA e, 
    const char* lpApplicationName,
    char* lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    const char* lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );



typedef BOOL ( __stdcall *PFN_CreateProcessW )(
    const wchar_t* lpApplicationName,
    wchar_t* lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    const wchar_t* lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );
LPVOID Pre_CreateProcessW( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook );
DWORD  _CreateProcessW( PFN_CreateProcessW e, 
    const wchar_t* lpApplicationName,
    wchar_t* lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    const wchar_t* lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );


typedef BOOL (__stdcall *PFN_EnumProcessModules)
    (HANDLE hProcess,HMODULE* lphModule,DWORD cb,LPDWORD lpcbNeeded);

typedef DWORD (__stdcall *PFN_GetModuleFileNameExW)
    (HANDLE hProcess,HMODULE hModule,wchar_t* lpFilename,DWORD nSize);

void PrintModules();

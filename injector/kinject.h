#pragma once

#include <windows.h>

void EnableDebugPriv(void);

class KInject{

public:
//    BOOL WINAPI InjectLibW(DWORD, PCWSTR);
//    BOOL WINAPI InjectLibA(DWORD, PCSTR);

    void Inject2(HANDLE hProcess, HANDLE hThread, const char* szDLL );
    void InjectDll(HANDLE hProcess, HANDLE hThread, ULONG_PTR param);

    int CreateAndInject2Process(LPCTSTR szExe, LPCTSTR szArgs, const char* szDLL, LPCTSTR);
    int CreateAndInject2Process(LPCTSTR szExe, LPCTSTR szArgs, const char* szDLL);
//    BOOL Inject2Process(DWORD, LPCTSTR);
    int CreateProcess(
        LPCTSTR szExe, 
        LPCTSTR szArgs,
        LPCTSTR szDir
        );
};

#ifdef UNICODE
#define InjectLib  InjectLibW
#else
#define InjectLib  InjectLibA
#endif // !UNICODE

DWORD APCInject(HANDLE hProcess, HANDLE hThread, PCHAR sDllName);

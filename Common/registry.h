#pragma once
#include <string>


BOOL RegGetDwordValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    DWORD& OutVal
    );


BOOL RegSetDwordValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    DWORD Val
    );


BOOL RegSetStringValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    const std::wstring& OutStr
    );

BOOL RegGetStringValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    std::wstring& OutStr
    );


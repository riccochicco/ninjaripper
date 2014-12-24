

#include <Windows.h>
#include "registry.h"


BOOL RegGetDwordValue
( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    DWORD& OutVal
)
{
    DWORD Type = 0;
    DWORD size = 4;
    HKEY  hKey = NULL;
    DWORD data = 0;
    BOOL Ret = FALSE;

    if( RegOpenKeyEx( hOpenKey, szSubKey, 0, KEY_QUERY_VALUE, &hKey ) == ERROR_SUCCESS )
    {
        LONG foo = RegQueryValueEx( hKey, szValue, 0, &Type, (BYTE*)&data, &size );
        if(  foo == ERROR_SUCCESS ){
            OutVal = data;
            Ret = TRUE;
        }
        RegCloseKey(hKey);
    }

    return Ret;
}


BOOL RegSetDwordValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    DWORD Val
    )
{
    HKEY  hKey = NULL;
    if( RegCreateKey( hOpenKey, szSubKey, &hKey ) == ERROR_SUCCESS ){
        if( RegSetValueEx(hKey, szValue, 0, REG_DWORD, (const BYTE*)&Val, 4 ) != ERROR_SUCCESS){
            return FALSE;
        }
        RegCloseKey( hKey );
        return TRUE;
    }
    return FALSE;
}



BOOL RegGetStringValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    std::wstring& OutStr
    )
{
    HKEY  hKey=0;
    DWORD Type=0;

    BOOL RetVal = FALSE;
    wchar_t* pOutStr = new wchar_t[2];
    DWORD  size = 2*sizeof(wchar_t);

    if(RegOpenKeyEx( hOpenKey, szSubKey, 0, KEY_QUERY_VALUE, &hKey )==ERROR_SUCCESS){
        if( RegQueryValueEx(hKey, szValue, 0, &Type, (BYTE*)pOutStr, &size)==ERROR_SUCCESS){
            OutStr = pOutStr;
            RetVal = TRUE;
        }
        else{
            delete[] pOutStr;
            pOutStr = new wchar_t[ size + 1 ];
            if( RegQueryValueEx(hKey, szValue, 0, &Type, (BYTE*)pOutStr, &size)==ERROR_SUCCESS){
                OutStr = pOutStr;
                RetVal = TRUE;
            }
            delete[] pOutStr;
        }
        RegCloseKey(hKey);
    }

    return RetVal;
}



BOOL RegSetStringValue
    ( 
    HKEY hOpenKey, 
    const TCHAR* szSubKey, 
    const TCHAR* szValue,
    const std::wstring& OutStr
    )
{
    HKEY hKey=0;
    DWORD Type=0;
    DWORD size=0;
    BOOL RetVal = FALSE;

    if(RegCreateKey(HKEY_CURRENT_USER, szSubKey, &hKey)==ERROR_SUCCESS){
        if(RegSetValueEx(hKey, szValue, 0, REG_SZ, (const BYTE*)OutStr.c_str(), 2 * ( 1 + wcslen( OutStr.c_str() ) ) ) !=ERROR_SUCCESS)
        {
            RetVal = TRUE;
        }
        RegCloseKey(hKey);    
    }
    return RetVal;
}


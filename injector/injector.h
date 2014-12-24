#pragma once

#include <windows.h>
#include <string>
#include "registry.h"

void Init( HWND hDlg );
void SelOutFolder( HWND hDlg );
LRESULT CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void GetSelectedKeys( HWND hDlg );



#define WRAP_NOWRAP  0
#define WRAP_D3D9  1
#define WRAP_D3D8  2
#define WRAP_D3D11 3


struct KSettings{
    std::wstring PrevEXE;
    std::wstring PrevArg;
    std::wstring PrevDir;
    std::wstring OutDir;
    std::wstring IntruderDir;

    DWORD RipKey;
    DWORD TextureRipKey;
    ;
    TCHAR szSubKey[ 250 ];
    DWORD DontOverwriteOutDir;

    KSettings():
        RipKey( 0 ),
        TextureRipKey( 0 ),
        DontOverwriteOutDir( 0 )
    {
        wchar_t szBuf[ MAX_PATH ];
        swprintf_s( szSubKey, 250, L"%s", TEXT( "SOFTWARE\\black_ninja\\NinjaRipper" ) );

        GetModuleFileName(0, szBuf, MAX_PATH);
        for(DWORD i=(DWORD)lstrlen(szBuf); i>0; i--){if(szBuf[i-1]==TEXT('\\')){szBuf[i]=0; break;}}
        IntruderDir = szBuf;
    }

    void Load(){
        BOOL foo;

        RegGetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("PrevEXE"), PrevEXE );
        RegGetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("PrevArg"), PrevArg );
        RegGetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("PrevDir"), PrevDir );
        RegGetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("OutDir"), OutDir );

        RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, TEXT("DontOverwriteOutDir"), DontOverwriteOutDir );


        foo = RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, TEXT("RipKey"), RipKey );
        if( !foo )
            RipKey = 121;

        foo = RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, TEXT("TextureRipKey"), TextureRipKey );
        if( !foo )
            TextureRipKey = 120;

    }

    void Save(){
        RegSetDwordValue( HKEY_CURRENT_USER, szSubKey, TEXT("DontOverwriteOutDir"), DontOverwriteOutDir );

        RegSetDwordValue( HKEY_CURRENT_USER, szSubKey, TEXT("RipKey"), RipKey );
        RegSetDwordValue( HKEY_CURRENT_USER, szSubKey, TEXT("TextureRipKey"),  TextureRipKey );

        RegSetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("PrevEXE"), PrevEXE );
        RegSetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("PrevArg"), PrevArg );
        RegSetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("PrevDir"), PrevDir );
        RegSetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("OutDir"),  OutDir );
        RegSetStringValue( HKEY_CURRENT_USER, szSubKey, TEXT("IntruderDir"),  IntruderDir );
    }

};

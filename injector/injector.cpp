
#include "stdafx.h"
#include "injector.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "kinject.h"
#include <stdio.h>
#include <Shlobj.h>
#include "Hyperlinks.h"


#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "advapi32.lib" )


//Global vars
KSettings g_Settings;

static const wchar_t aa[] = L"Ninja Ripper 1.1.2";



bool checkWrapperDll(HWND hDlg, const std::wstring& exeDir)
{
    WIN32_FIND_DATA fd;
    HANDLE h;

    std::wstring checkDir;


    checkDir = exeDir + L"d3d8.dll";
    h = ::FindFirstFile(checkDir.c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE)
    {
        ::MessageBox(hDlg, L"Wrapper d3d8.dll detected in exe dir. \
Delete it manually", NULL, MB_TOPMOST|MB_OK|MB_ICONERROR);
        return true;
    }
    else
    {
        ::FindClose(h);
    }


    checkDir = exeDir + L"d3d9.dll";
    h = ::FindFirstFile(checkDir.c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE)
    {
        ::MessageBox(hDlg, L"Wrapper d3d9.dll detected in exe dir. \
Delete it manually", NULL, MB_TOPMOST|MB_OK|MB_ICONERROR);
        return true;
    }
    else
    {
        ::FindClose(h);
    }


    checkDir = exeDir + L"d3d11.dll";
    h = ::FindFirstFile(checkDir.c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE)
    {
        ::MessageBox(hDlg, L"Wrapper d3d11.dll detected in exe dir. \
Delete it manually", NULL, MB_TOPMOST|MB_OK|MB_ICONERROR);
        return true;
    }
    else
    {
        ::FindClose(h);
    }
    return false;
}


void UpdateDontOverwriteFlag( HWND hDlg ){
    if( IsDlgButtonChecked( hDlg, IDC_CHECK_DONT_OVERWRITE ) == BST_CHECKED ){
        g_Settings.DontOverwriteOutDir = 1;
    }
    else{
        g_Settings.DontOverwriteOutDir = 0;
    }
}



HWND CreateToolTip(int toolID, HWND hDlg, PTSTR pszText)
{
    if (!toolID || !hDlg || !pszText)
    {
        return FALSE;
    }
    // Get the window of the tool.
    HWND hwndTool = GetDlgItem(hDlg, toolID);

    // Create the tooltip. g_hInst is the global instance handle.
    HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
        WS_POPUP |TTS_ALWAYSTIP | TTS_BALLOON,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        hDlg, NULL, 
        GetModuleHandle( NULL ), NULL);

    if (!hwndTool || !hwndTip)
    {
        return (HWND)NULL;
    }                              

    // Associate the tooltip with the tool.
    TOOLINFO toolInfo = { 0 };
    //toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.cbSize = 40;//VS2010 bugfix
    toolInfo.hwnd = hDlg;
    toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    toolInfo.uId = (UINT_PTR)hwndTool;
    toolInfo.lpszText = pszText;
    SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

    return hwndTip;
}



//Set output directory to GUI and settings
void SetDir(HWND hDlg, TCHAR* szExe){

    TCHAR buf2[MAX_PATH];
    lstrcpy(buf2, szExe);
    for(DWORD i=(DWORD)lstrlen(buf2); i>0; i--){if(buf2[i-1]==TEXT('\\')){buf2[i]=0; break;}}
    SetDlgItemText(hDlg, IDC_DIR, buf2);


    UpdateDontOverwriteFlag( hDlg );
    if( g_Settings.DontOverwriteOutDir )
        return;

    SetDlgItemText(hDlg, IDC_OUTDIR, buf2);
    g_Settings.OutDir = buf2;

}


void GetSelectedKeys( HWND hDlg ){
    g_Settings.RipKey = 0x70+ ( (ULONG)SendMessage( GetDlgItem( hDlg, IDC_RIP_KEY ) , CB_GETCURSEL , 0 , 0 ) );
    g_Settings.TextureRipKey = 0x70+ ( (ULONG)SendMessage( GetDlgItem( hDlg, IDC_TEXTURE_RIP_KEY ) , CB_GETCURSEL , 0 , 0 ) );
//    g_Settings.ShaderRipKey = 0x70+ ( (ULONG)SendMessage( GetDlgItem( hDlg, IDC_SHADER_RIP_KEY ) , CB_GETCURSEL , 0 , 0 ) );

}


BOOL CopyWrapDll( 
    const std::wstring& DestDir,
    const std::wstring& SrcDir,
    const std::wstring& DllName 
    )
{
    std::wstring DstFile = DestDir + DllName;
    std::wstring SrcFile = SrcDir + L"d3dwrap.dll";
    BOOL foo = CopyFile( SrcFile.c_str(), DstFile.c_str(), FALSE );

    return foo;
}



LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    OPENFILENAME ofn;
    char    szDLL[MAX_PATH];
    TCHAR    szArgs[MAX_PATH];
    TCHAR    szDir[MAX_PATH];
    static    TCHAR    szExe[MAX_PATH];

    switch (message)
    {
    case WM_INITDIALOG:
        Init( hDlg );
        break;
    case WM_COMMAND:
        if(LOWORD(wParam) == IDCANCEL){
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        else if(LOWORD(wParam)==IDC_OPEN_OUT_FOLDER){//"Browse" button
            ShellExecute(0, 0, g_Settings.OutDir.c_str(), 0, 0, SW_SHOWMAXIMIZED);        
        }
        else if(LOWORD(wParam)==ID_SEL_OUTDIR){//Select out directory button
            SelOutFolder( hDlg );
        }
        else if( LOWORD(wParam) == IDC_ABOUT1 ){
            DialogBox((HINSTANCE)GetModuleHandle(0), (LPCTSTR)IDD_DIALOG2, hDlg, (DLGPROC)AboutDlgProc );
        }
        else if(LOWORD(wParam)==ID_SEL_EXE){
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize=sizeof(ofn);
            ofn.hwndOwner = hDlg;
            ofn.hInstance=(HINSTANCE)GetModuleHandle(0);
            ofn.lpstrFilter=TEXT("EXE Files\0*.exe\0All Files\0*.*\0\0");
            ofn.nMaxFile=MAX_PATH;
            ofn.lpstrFile = szExe;
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {
                SetDlgItemText(hDlg, IDC_EXENAME, szExe);
                SetDir( hDlg, szExe );
            }
        }
        else if (LOWORD(wParam)==IDC_RUN){//Save settings in registry and start exe
            GetDlgItemText(hDlg, IDC_EXENAME, szExe, MAX_PATH);
            if (szExe[0] != 0)
            {
                
                GetModuleFileNameA(0, szDLL, MAX_PATH);
                for(SIZE_T i=strlen(szDLL); i>0; i--){if(szDLL[i-1]=='\\'){szDLL[i]=0; break;}}
                strcat_s(szDLL, MAX_PATH, "intruder.dll");


                KInject inj;
                GetDlgItemText(hDlg, IDC_ARGS, szArgs, MAX_PATH);
                GetDlgItemText(hDlg, IDC_DIR, szDir, MAX_PATH);

                GetSelectedKeys( hDlg );
                g_Settings.PrevEXE = szExe;
                g_Settings.PrevArg = szArgs;
                g_Settings.PrevDir = szDir;

                UpdateDontOverwriteFlag( hDlg );

                g_Settings.Save();

                DWORD WrapMode = ( (ULONG)SendMessage( GetDlgItem( hDlg, IDC_DXWRAP ) , CB_GETCURSEL , 0 , 0 ) );
                
                //Prepare dst buffer
                wchar_t szDstDir[ MAX_PATH ] = { 0 };
                wcscpy_s( szDstDir, MAX_PATH, szExe );
                for(DWORD i=(DWORD)lstrlen(szDstDir); i>0; i--){if(szDstDir[i-1]==TEXT('\\')){szDstDir[i]=0; break;}}


                if ( WrapMode == WRAP_NOWRAP )
                {
                    //No wrapper
                    // Check wrapper dll in exe dir
                    bool wrapperDllExist = checkWrapperDll(hDlg, szDstDir);
                    
                    if (
                        wrapperDllExist ||
                        (inj.CreateAndInject2Process(szExe, szArgs, szDLL, szDir) != 0)
                        )
                    {
                        MessageBox(hDlg, TEXT("Inject Failed"), 0, MB_ICONERROR | MB_TOPMOST);
                    }
                }
                else if( WrapMode == WRAP_D3D9 ){//D3D9 wrapper
                    if( CopyWrapDll( szDstDir, g_Settings.IntruderDir, L"d3d9.dll" ) ){
                        inj.CreateProcess(szExe, szArgs, szDir);
                    }
                    else{//Copy error
                    }
                }
                else if( WrapMode == WRAP_D3D8 ){//D3D8 wrapper
                    if( CopyWrapDll( szDstDir, g_Settings.IntruderDir, L"d3d8.dll" ) ){
                        inj.CreateProcess(szExe, szArgs, szDir);
                    }
                    else{//Copy error
                    }
                }
                else if( WrapMode == WRAP_D3D11 ){//D3D11 wrapper
                    if( CopyWrapDll( szDstDir, g_Settings.IntruderDir, L"d3d11.dll" ) ){
                        inj.CreateProcess(szExe, szArgs, szDir);
                    }
                    else{//Copy error
                    }
                }


            }
            else{
                MessageBox(hDlg, TEXT("Select EXE"), 0, MB_ICONERROR|MB_TOPMOST);
            }
        }
        break;
    case WM_DROPFILES:
        DragQueryFile((HDROP)wParam, 0, szExe, MAX_PATH-1);
        SetDlgItemText(hDlg, IDC_EXENAME, szExe);
        SetDir(hDlg, szExe);
        break;
    }
    return FALSE;
}

void cmd_line_inj( LPWSTR sz_targ, LPWSTR sz_args ){

    char szDLL[MAX_PATH];//Intruder.dll full path
    GetModuleFileNameA(0, szDLL, MAX_PATH);
    for(SIZE_T i=strlen(szDLL); i>0; i--){if(szDLL[i-1]=='\\'){szDLL[i]=0; break;}}
    strcat_s(szDLL, MAX_PATH, "intruder.dll");

    KInject inj;
    if(inj.CreateAndInject2Process(sz_targ, sz_args, szDLL)==-1){
        MessageBox(0, TEXT("Inject Error"), 0, MB_ICONERROR|MB_OK);
    }
}

/*
Usage:
injector.exe            - User Interface
injector.exe exe        - Start Process With Inject
injector.exe exe args    - Start Process With Args And Inject
*/
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    int args;
    LPWSTR* argv=CommandLineToArgvW(GetCommandLineW(), &args);
    g_Settings.Load();

    if(args==1){

        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_WIN95_CLASSES|ICC_COOL_CLASSES|ICC_BAR_CLASSES|ICC_USEREX_CLASSES;
        InitCommonControlsEx( &icex );

        DialogBox((HINSTANCE)GetModuleHandle(0), (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)MainDlgProc);
    }
    else if(args==2){    //target
        cmd_line_inj(argv[1], 0);
    }
    else if(args==3){    //target, args
        cmd_line_inj(argv[1], argv[2]);
    }
    else{
        MessageBox(0, TEXT("Invalid command line"), 0, MB_ICONERROR|MB_OK);
    }
    return 0;
}


void InitKeys( HWND hDlg, DWORD Item, DWORD Sel ){

    for( DWORD i = 1; i <= 12; i++ ){
        wchar_t Buf[ 100 ] = { 0 };
        swprintf_s( Buf, 100, L"F%d", i );
        SendMessage(GetDlgItem(hDlg, Item), CB_ADDSTRING, 0, (LPARAM)Buf );
    }
    SendMessage(GetDlgItem(hDlg, Item), CB_SETCURSEL, Sel , 0);
}

void InitWrapperCompbo( HWND hDlg, DWORD Item ){
    SendMessage(GetDlgItem(hDlg, Item), CB_ADDSTRING, 0, (LPARAM)L"Intruder (Recommended)" );
    SendMessage(GetDlgItem(hDlg, Item), CB_ADDSTRING, 0, (LPARAM)L"D3D9 Wrapper" );
    SendMessage(GetDlgItem(hDlg, Item), CB_ADDSTRING, 0, (LPARAM)L"D3D8 Wrapper" );
    SendMessage(GetDlgItem(hDlg, Item), CB_ADDSTRING, 0, (LPARAM)L"D3D11 Wrapper" );
    SendMessage(GetDlgItem(hDlg, Item), CB_SETCURSEL, 0 , 0);
}


void Init( HWND hDlg )
{
    SetWindowText(hDlg, aa);

    CreateToolTip(IDC_ARGS, hDlg, TEXT("Command line arguments"));
    CreateToolTip(IDC_DIR,  hDlg, TEXT("Work directory"));
    CreateToolTip(ID_SEL_EXE,  hDlg, TEXT("Select target file"));
    CreateToolTip(IDC_RIP_KEY,  hDlg, TEXT("Meshs rip key select"));
    CreateToolTip(IDC_TEXTURE_RIP_KEY,  hDlg, TEXT("Forced to save textures rip key select") );

    CreateToolTip(ID_SEL_OUTDIR,  hDlg, TEXT("Select output directory") );
    CreateToolTip(IDC_OPEN_OUT_FOLDER,  hDlg, TEXT("Browse output directory") );
    CreateToolTip(IDC_DXWRAP,  hDlg, TEXT("Inject mode") );
    CreateToolTip(IDC_RUN,  hDlg, TEXT("Run target") );

    SetDlgItemText(hDlg, IDC_EXENAME, g_Settings.PrevEXE.c_str() );
    SetDlgItemText(hDlg, IDC_ARGS,    g_Settings.PrevArg.c_str() );
    SetDlgItemText(hDlg, IDC_DIR,     g_Settings.PrevDir.c_str() );
    SetDlgItemText( hDlg, IDC_OUTDIR, g_Settings.OutDir.c_str() );

    if( g_Settings.DontOverwriteOutDir )
        SendDlgItemMessage(hDlg, IDC_CHECK_DONT_OVERWRITE, BM_CLICK ,0 ,0);


    InitKeys( hDlg, IDC_RIP_KEY,         g_Settings.RipKey - 0x70 );
    InitKeys( hDlg, IDC_TEXTURE_RIP_KEY, g_Settings.TextureRipKey - 0x70 );
    InitWrapperCompbo( hDlg, IDC_DXWRAP );
    HICON hIco = LoadIcon(GetModuleHandle(0), (LPCWSTR)IDI_ICON1);
    PostMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIco );

}


void SelOutFolder( HWND hDlg ){

    wchar_t szFile[ 1024 ];
    BROWSEINFO bi = { 0 };
    bi.hwndOwner = hDlg;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    LPITEMIDLIST pitemlist = SHBrowseForFolder( &bi );
    if( pitemlist ){
        SHGetPathFromIDList( pitemlist, szFile );
        g_Settings.OutDir = szFile;
        SetDlgItemText( hDlg, IDC_OUTDIR, g_Settings.OutDir.c_str() );
    }

}


HFONT	hFont;

LRESULT CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){

    switch (message)
    {
        case WM_INITDIALOG:
        {
            HANDLE hImage = ::LoadImage( GetModuleHandle(0),(LPCWSTR)IDB_BITMAP1, IMAGE_BITMAP, 0,0,LR_DEFAULTCOLOR);
            SendMessage( GetDlgItem( hDlg, IDC_BUTTON1 ),
                BM_SETIMAGE,
                IMAGE_BITMAP,
                (LPARAM)hImage );

            HICON hIco = LoadIcon( GetModuleHandle(0), (LPCWSTR)IDI_ICON1 );
            PostMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIco );

            LOGFONT lf={0};
            BITMAPINFO bi={0};
            ZeroMemory(&lf, sizeof(LOGFONT));
            lf.lfHeight=20;
            lf.lfWeight = FW_BOLD;
            lstrcpy((LPTSTR)&lf.lfFaceName, L"Arial" );
            hFont = CreateFontIndirect( &lf );        
            
            char wmrcryp[13] = { 0x25,0x46,0x40,0x42,0x43,0x4E,0x41,0x43,0x44,0x46,0x45,0x45,0x40 };
            char wmr[14] = {0};
            for( size_t i = 0; i < 13; i++ ){wmr[i] = wmrcryp[i] ^ 0x77;}
            SetDlgItemTextA( hDlg, IDC_EDIT1, wmr );


            char wmzcryp[13] = { 0x2D,0x4E,0x4F,0x44,0x44,0x41,0x4E,0x42,0x41,0x46,0x46,0x46,0x4F };
            char wmz[14] = {0};
            for( size_t i = 0; i < 13; i++ ){wmz[i] = wmzcryp[i] ^ 0x77;}
            SetDlgItemTextA( hDlg, IDC_EDIT2, wmz );

            ConvertStaticToHyperlink( hDlg, IDC_HOMEPAGE );
            ConvertStaticToHyperlink( hDlg, IDC_AUTHORMAIL );
            CreateToolTip(IDC_BUTTON1,  hDlg, L"Make a donation via PayPal ( Browser launch )" );
            CreateToolTip(IDC_EDIT1,  hDlg, L"Make a donation via WebMoney" );
            CreateToolTip(IDC_EDIT2,  hDlg, L"Make a donation via WebMoney" );
            break;
        }

    case WM_PAINT:
    {
        PAINTSTRUCT Ps;
        HDC hDC=BeginPaint(hDlg, &Ps);
        SetBkMode(hDC, TRANSPARENT);
        SetTextColor(hDC, RGB(0, 0, 0));
        SelectObject(hDC, hFont);

        TextOut(hDC, 105, 35, aa, lstrlen(aa));
        EndPaint(hDlg, &Ps);
        break;
    }


    case WM_COMMAND:
        if(LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        else if( LOWORD(wParam) == IDOK )
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        else if( LOWORD(wParam) == IDC_BUTTON1 )
        {
            char paypalcryp[82] = { 0x1F,0x03,0x03,0x07,0x04,0x4D,0x58,0x58,0x00,0x00,0x00,0x59,0x07,0x16,0x0E,0x07,0x16,0x1B,0x59,0x14,0x18,0x1A,0x58,0x14,0x10,0x1E,0x5A,0x15,0x1E,0x19,0x58,0x00,0x12,0x15,0x04,0x14,0x05,0x48,0x14,0x1A,0x13,0x4A,0x28,0x04,0x5A,0x0F,0x14,0x1B,0x1E,0x14,0x1C,0x51,0x1F,0x18,0x04,0x03,0x12,0x13,0x28,0x15,0x02,0x03,0x03,0x18,0x19,0x28,0x1E,0x13,0x4A,0x25,0x27,0x39,0x31,0x24,0x30,0x3C,0x24,0x22,0x3C,0x3B,0x3A,0x45 };
            char paypal[83] = {0};
            for( size_t i = 0; i < 82; i++ ){paypal[i] = paypalcryp[i] ^ 0x77;}
            HINSTANCE err = ::ShellExecuteA( NULL, "open", paypal, NULL, NULL, SW_SHOW );
            if( err < (HINSTANCE)32 )
            {
                ::MessageBox( hDlg, L"Browser launch failed. PayPal account to donate: fasihov@mail.ru", NULL, MB_TOPMOST|MB_ICONERROR );
            }
        
        }
        else if (LOWORD(wParam) == IDC_HOMEPAGE)
        {
//            ::MessageBox( hDlg, L"nlnlnl", NULL, MB_TOPMOST|MB_ICONINFORMATION);
            HINSTANCE err = ::ShellExecuteA( NULL, "open", "http://cgig.ru/ninjaripper/", NULL, NULL, SW_SHOW );
            if( err < (HINSTANCE)32 )
            {
                ::MessageBox( hDlg, L"Browser launch failed", NULL, MB_TOPMOST|MB_ICONERROR );
            }
        }
        else if (LOWORD(wParam) == IDC_AUTHORMAIL)
        {
            HINSTANCE err = ::ShellExecuteA( NULL, "open", "mailto:black_ninja2000@mail.ru", NULL, NULL, SW_SHOW );
            if( err < (HINSTANCE)32 )
            {
                ::MessageBox( hDlg, L"Mail client launch failed", NULL, MB_TOPMOST|MB_ICONERROR );
            }
        }
    }

    return FALSE;
}



#include "PreComp.h"
#include "KIntruder.h"
#include "klog.h"
#include "intruder.h"//KUNICODE_STRING
#include "registry.h"


static const wchar_t  szRipperDir[]    = L"_Ripper";
static const wchar_t  szTexturesDir[]  = L"Textures\\";
static const wchar_t  szTex[]          = L"Tex_";
static const wchar_t  szBMP[]          = L".bmp";
static const wchar_t  szFramesDir[]    = L"Frames\\";
static const wchar_t  szFrameDir[]     = L"Frame";
static const wchar_t  szMesh[]         = L"Mesh_";
static const wchar_t  szMeshExt[]      = L".rip";
static const wchar_t  szShader[]       = L"Shader_";
static const wchar_t  szVS[]           = L".vs";
static const wchar_t  szPS[]           = L".ps";
static const wchar_t  szDDS[]          = L".dds";

//ASCII strings
static const char   szTex_A[]          = "Tex_";
static const char   szBMP_A[]          = ".bmp";
static const char   szDDS_A[]          = ".dds";
static const char   szShader_A[]       = "Shader_";
static const char   szVS_A[]           = ".vs";
static const char   szPS_A[]           = ".ps";



KIntruder::KIntruder( HINSTANCE hIntruderDLL_):
hIntruderDLL( hIntruderDLL_ ),
fTexturesKeyPressed( 0 ),
TexturesDirCreated( 0 ),
TextureIdx( 0 ),
fRipEnabled( 0 ),
fMeshRipKeyPressed( 0 ),
FramesDirCreated( 0 ),
RipperDirCreated( 0 ),
FrameIdx( 0 ),
FrameMeshIdx( 0 ),
FrameTextureIdx( 0 ),
FrameVertexShaderIdx( 0 ),
FramePixelShaderIdx( 0 )
{

}


BOOL KIntruder::Init(){
    wchar_t szBuf[ MAX_PATH ] = { 0 };

    //Get ripper directory
    ::GetModuleFileName( hIntruderDLL, szBuf, MAX_PATH);
    for(DWORD i=(DWORD)lstrlen(szBuf); i>0; i--){if( szBuf[i-1]==L'\\' ){szBuf[i]=0; break;}}

    IntruderDir = szBuf;


    //Target EXE Directory
    ::GetModuleFileName(0, szBuf, MAX_PATH);
    for(DWORD i=(DWORD)lstrlen(szBuf); i>0; i--){if(szBuf[i-1]==TEXT('\\')){szBuf[i]=0; break;}}
    TargetDir = szBuf;

    ReadSettings();

    TimerFreq.QuadPart = 0;
    ::QueryPerformanceFrequency( &TimerFreq );
    return TRUE;
}



void KIntruder::Uninit(){

}


void KIntruder::ReadSettings(){

    wchar_t szSubKey[ 250 ];
    swprintf_s( szSubKey, 250, L"%s", L"SOFTWARE\\black_ninja\\NinjaRipper" );

    RegGetStringValue( HKEY_CURRENT_USER, szSubKey, L"OutDir", OutDir );

    Settings.dwMinPrimitives  = 0;
    Settings.dwMinIndicies    = 0;
    Settings.dwMinVertexCount = 0;
    
    Settings.minFrameIntervalUs = 0; // if 0 - not use
    RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, L"RipKey",        Settings.MeshsRipKey );
    RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, L"TextureRipKey", Settings.TexturesRipKey );

    RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, L"MinPrimitives", (DWORD&)Settings.dwMinPrimitives );
    RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, L"MinIndicies", (DWORD&)Settings.dwMinIndicies );
    RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, L"MinVertexCount", (DWORD&)Settings.dwMinVertexCount );


    BOOL foo = RegGetDwordValue( HKEY_CURRENT_USER, szSubKey, L"MinPresentInterval", Settings.minFrameIntervalUs );
    if (!foo)
    {
        Settings.minFrameIntervalUs = 10000;//10ms
    }
}



void KIntruder::KeyHandler( IRipper* pRipper ){
    SHORT KeyState;

    //Textures rip key
    KeyState = ::GetAsyncKeyState( Settings.TexturesRipKey );
    if( KeyState != 0 ){//Pressed
        fTexturesKeyPressed ^= 1;

        if( fTexturesKeyPressed ){
            pRipper->TextureRipStart();
        }
        else{
            pRipper->TextureRipEnd();
        }

        ::Sleep( 2000 );
    }

    //Get actual state
    fMeshRipKeyPressed = ::GetAsyncKeyState( Settings.MeshsRipKey );
/*
    if( KeyState != 0 ){
        fMeshRipKeyPressed ^= 1;
        ::Sleep( 2000 );
    }
*/
}



std::wstring KIntruder::GetOutputDir()
{

    if( !RipperDirCreated ){
        wchar_t timedDir[200];
        SYSTEMTIME st;
        ::GetLocalTime( &st );
        //frame_25.09.2012_11.30.00
        swprintf_s( timedDir, 200, L"%02d.%02d.%d_%02d.%02d.%02d", 
            st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond );


        RipperDir = OutDir;
        size_t x = RipperDir.size();

        //If last sym not slash -> add slash
        if( (RipperDir.c_str()[x-1] != L'\\') && (RipperDir.c_str()[x-1] != L'/') ){
            RipperDir += L"\\";
        }
        
        RipperDir += szRipperDir;//Add "_Ripper"
        RipperDir += L"\\";//Add slash
        ::CreateDirectory( RipperDir.c_str(), 0 );

        // _Ripper/18.10.2012_18.36.11/
        RipperDir += timedDir;
        RipperDir += L"\\";//Add slash
        ::CreateDirectory( RipperDir.c_str(), 0 );

        RipperDirCreated = 1;
    }
    return RipperDir;
}


//Forced
std::wstring KIntruder::GetTextureSavePath( ETextureExt eExt ){
    if( !TexturesDirCreated ){
        TexturesDir = GetOutputDir();
        TexturesDir += szTexturesDir;
        ::CreateDirectory( TexturesDir.c_str(), 0 );
        TexturesDirCreated = 1;
    }
    
    wchar_t szOutPath[MAX_PATH] = {0};
    if( eExt == EBMP ){
        _stprintf_s( szOutPath, MAX_PATH, L"%s%s%04d%s", TexturesDir.c_str() ,szTex ,TextureIdx, szBMP );
    }
    else if( eExt == EDDS ){
        _stprintf_s( szOutPath, MAX_PATH, L"%s%s%04d%s", TexturesDir.c_str() ,szTex ,TextureIdx, szDDS );
    }
    return szOutPath;
}


//Return forced to save texture path without extension
std::wstring KIntruder::GetTextureSavePath(){
    if( !TexturesDirCreated ){
        TexturesDir = GetOutputDir();
        TexturesDir += szTexturesDir;
        ::CreateDirectory( TexturesDir.c_str(), 0 );
        TexturesDirCreated = 1;
    }

    wchar_t szOutPath[MAX_PATH] = {0};
    _stprintf_s( szOutPath, MAX_PATH, L"%s%s%04d", TexturesDir.c_str() ,szTex ,TextureIdx );
    return szOutPath;
}


//Return: "_Ripper/Frames/FrameNN/"
std::wstring KIntruder::GetFrameDir(){
    if( !FramesDirCreated ){
        FramesDir = GetOutputDir();
        FramesDir += szFramesDir;
        ::CreateDirectory( FramesDir.c_str(), 0 );
        FramesDirCreated = 1;
    }

    //Add "frameN" and create dir
    wchar_t szFrame[ 100 ] = {0};
    _stprintf_s( szFrame, 100, L"%s%04d\\", szFrameDir, FrameIdx );

    std::wstring Out = FramesDir + szFrame;
    
    if( LastCreatedDir != Out ){
        ::CreateDirectory( Out.c_str(), 0 );
        LastCreatedDir = Out;
    }

    return Out;
}



void KIntruder::FrameHandler( IRipper* pRipper ){
    
    KeyHandler( pRipper );


    DWORD MeshKeyPressed = IsMeshsRipKeyPressed();

    if( !fRipEnabled && MeshKeyPressed )
    {
        g_pLog->Write( L"Frame Start...#%02d\n", FrameIdx );

        GetFrameDir();//Create current frame dir
        
        fRipEnabled = 1;//Rip on

        FrameMeshIdx = 0;
        FrameTextureIdx = 0;
        FrameVertexShaderIdx = 0;
        FramePixelShaderIdx = 0;

        pRipper->FrameStart();

        ::Sleep( 1000 );

        ::QueryPerformanceCounter( &frameStartTime );
    }
    else if( fRipEnabled )
    {
        LARGE_INTEGER timerVal;
        ::QueryPerformanceCounter( &timerVal );

        LARGE_INTEGER usDelta;// Convert to microseconds
        usDelta.QuadPart = ( timerVal.QuadPart - frameStartTime.QuadPart ) * 1000000 / TimerFreq.QuadPart;


        // If min_frame_len not set or current frame len > min_frame_len
        if( 
            0 == Settings.minFrameIntervalUs
            || 
            usDelta.QuadPart > Settings.minFrameIntervalUs
            )
        {
            g_pLog->Write( L"Frame len: %dus\n", usDelta.LowPart );
            g_pLog->Write( L"Frame End...\n\n\n" );
            fRipEnabled = 0;// Rip off
            pRipper->FrameEnd();
            FrameIdx++;
        }
    }
}





//Return: "_Ripper/Frames/FrameNN/TexYYYY_J.bmp"
std::wstring KIntruder::GetFrameTextureSavePath( 
    std::string& OutFileName, 
    DWORD Ext, 
    DWORD Level 
    )
{
    std::wstring Out = GetFrameDir();

    wchar_t szTexBuf [ 100 ] = { 0 };
    char    szTexABuf[ 100 ] = { 0 };

    if( Ext == EBMP ){
        _stprintf_s( szTexBuf, 100, L"%s%04d_%01d%s", szTex, FrameTextureIdx, Level, szBMP );
        sprintf_s( szTexABuf, 100,  "%s%04d_%01d%s",  szTex_A, FrameTextureIdx, Level, szBMP_A );
    }
    else if( Ext == EDDS ){
        _stprintf_s( szTexBuf, 100, L"%s%04d_%01d%s", szTex, FrameTextureIdx, Level, szDDS );
        sprintf_s( szTexABuf, 100,  "%s%04d_%01d%s",  szTex_A, FrameTextureIdx, Level, szDDS_A );
    }

    Out += szTexBuf;
    OutFileName = szTexABuf;
    return Out;
}


std::wstring KIntruder::GetFrameMeshSavePath(){
    std::wstring Out = GetFrameDir();

    wchar_t szMeshBuf[ 100 ] = { 0 };
    
    _stprintf_s( szMeshBuf, 100, L"%s%04d%s", szMesh, FrameMeshIdx, szMeshExt );
    Out += szMeshBuf;
    return Out;
}

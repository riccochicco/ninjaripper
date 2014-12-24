
#include "PreComp.h"
#include "KRipper8.h"



const wchar_t* KRipper8::D3DFORMAT_2Str( D3DFORMAT f ){
    switch( f ){
    case D3DFMT_UNKNOWN:
        return L"D3DFMT_UNKNOWN";

    case D3DFMT_R8G8B8:
        return L"D3DFMT_R8G8B8";

    case D3DFMT_A8R8G8B8:
        return L"D3DFMT_A8R8G8B8";

    case D3DFMT_X8R8G8B8:
        return L"D3DFMT_X8R8G8B8";

    case D3DFMT_R5G6B5:
        return L"D3DFMT_R5G6B5";

    case D3DFMT_X1R5G5B5:
        return L"D3DFMT_X1R5G5B5";

    case D3DFMT_A1R5G5B5:
        return L"D3DFMT_A1R5G5B5";

    case D3DFMT_A4R4G4B4:
        return L"D3DFMT_A4R4G4B4";

    case D3DFMT_R3G3B2:
        return L"D3DFMT_R3G3B2";

    case D3DFMT_A8:
        return L"D3DFMT_A8";

    case D3DFMT_A8R3G3B2:
        return L"D3DFMT_A8R3G3B2";

    case D3DFMT_X4R4G4B4:
        return L"D3DFMT_X4R4G4B4";

    case D3DFMT_A2B10G10R10:
        return L"D3DFMT_A2B10G10R10";

    case D3DFMT_A8P8:
        return L"D3DFMT_A8P8";

    case D3DFMT_P8:
        return L"D3DFMT_P8";

    case D3DFMT_L8:
        return L"D3DFMT_L8";

    case D3DFMT_A8L8:
        return L"D3DFMT_A8L8";

    case D3DFMT_A4L4:
        return L"D3DFMT_A4L4";

    case D3DFMT_V8U8:
        return L"D3DFMT_V8U8";

    case D3DFMT_L6V5U5:
        return L"D3DFMT_L6V5U5";

    case D3DFMT_X8L8V8U8:
        return L"D3DFMT_X8L8V8U8";

    case D3DFMT_Q8W8V8U8:
        return L"D3DFMT_Q8W8V8U8";

    case D3DFMT_V16U16:
        return L"D3DFMT_V16U16";

    case D3DFMT_A2W10V10U10:
        return L"D3DFMT_A2W10V10U10";

    case D3DFMT_UYVY:
        return L"D3DFMT_UYVY";

    case D3DFMT_YUY2:
        return L"D3DFMT_YUY2";

    case D3DFMT_DXT1:
        return L"D3DFMT_DXT1";

    case D3DFMT_DXT2:
        return L"D3DFMT_DXT2";

    case D3DFMT_DXT3:
        return L"D3DFMT_DXT3";

    case D3DFMT_DXT4:
        return L"D3DFMT_DXT4";

    case D3DFMT_DXT5:
        return L"D3DFMT_DXT5";

    case D3DFMT_D16_LOCKABLE:
        return L"D3DFMT_D16_LOCKABLE";

    case D3DFMT_D32:
        return L"D3DFMT_D32";

    case D3DFMT_D15S1:
        return L"D3DFMT_D15S1";

    case D3DFMT_D24S8:
        return L"D3DFMT_D24S8";

    case D3DFMT_D24X8:
        return L"D3DFMT_D24X8";

    case D3DFMT_D24X4S4:
        return L"D3DFMT_D24X4S4";

    case D3DFMT_D16:
        return L"D3DFMT_D16";

    case D3DFMT_VERTEXDATA:
        return L"D3DFMT_VERTEXDATA";

    case D3DFMT_INDEX16:
        return L"D3DFMT_INDEX16";

    case D3DFMT_INDEX32:
        return L"D3DFMT_INDEX32";

    case D3DFMT_FORCE_DWORD:
        return L"D3DFMT_FORCE_DWORD";
    }

    return L"Unknown";
}



const wchar_t* KRipper8::D3DRESOURCETYPE_2Str( D3DRESOURCETYPE t ){
    switch( t ){
    case D3DRTYPE_SURFACE:
        return L"D3DRTYPE_SURFACE";

    case D3DRTYPE_VOLUME:
        return L"D3DRTYPE_VOLUME";

    case D3DRTYPE_TEXTURE:
        return L"D3DRTYPE_TEXTURE";

    case D3DRTYPE_VOLUMETEXTURE:
        return L"D3DRTYPE_VOLUMETEXTURE";

    case D3DRTYPE_CUBETEXTURE:
        return L"D3DRTYPE_CUBETEXTURE";

    case D3DRTYPE_VERTEXBUFFER:
        return L"D3DRTYPE_VERTEXBUFFER";

    case D3DRTYPE_INDEXBUFFER:
        return L"D3DRTYPE_INDEXBUFFER";
    }
    return L"Unknown";
}


const wchar_t* KRipper8::D3DMULTISAMPLE_2Str( D3DMULTISAMPLE_TYPE x ){
    switch( x ){

    case D3DMULTISAMPLE_NONE:
        return L"D3DMULTISAMPLE_NONE";

    case D3DMULTISAMPLE_2_SAMPLES:
        return L"D3DMULTISAMPLE_2_SAMPLES";

    case D3DMULTISAMPLE_3_SAMPLES:
        return L"D3DMULTISAMPLE_3_SAMPLES";

    case D3DMULTISAMPLE_4_SAMPLES:
        return L"D3DMULTISAMPLE_4_SAMPLES";

    case D3DMULTISAMPLE_5_SAMPLES:
        return L"D3DMULTISAMPLE_5_SAMPLES";

    case D3DMULTISAMPLE_6_SAMPLES:
        return L"D3DMULTISAMPLE_6_SAMPLES";

    case D3DMULTISAMPLE_7_SAMPLES:
        return L"D3DMULTISAMPLE_7_SAMPLES";

    case D3DMULTISAMPLE_8_SAMPLES:
        return L"D3DMULTISAMPLE_8_SAMPLES";

    case D3DMULTISAMPLE_9_SAMPLES:
        return L"D3DMULTISAMPLE_9_SAMPLES";

    case D3DMULTISAMPLE_10_SAMPLES:
        return L"D3DMULTISAMPLE_10_SAMPLES";

    case D3DMULTISAMPLE_11_SAMPLES:
        return L"D3DMULTISAMPLE_11_SAMPLES";

    case D3DMULTISAMPLE_12_SAMPLES:
        return L"D3DMULTISAMPLE_12_SAMPLES";

    case D3DMULTISAMPLE_13_SAMPLES:
        return L"D3DMULTISAMPLE_13_SAMPLES";

    case D3DMULTISAMPLE_14_SAMPLES:
        return L"D3DMULTISAMPLE_14_SAMPLES";

    case D3DMULTISAMPLE_15_SAMPLES:
        return L"D3DMULTISAMPLE_15_SAMPLES";

    case D3DMULTISAMPLE_16_SAMPLES:
        return L"D3DMULTISAMPLE_16_SAMPLES";

    }
    return L"Unknown";
}


const wchar_t* KRipper8::D3DPOOL_2Str( D3DPOOL t ){

    switch( t ){

    case D3DPOOL_DEFAULT:
        return L"D3DPOOL_DEFAULT";

    case D3DPOOL_MANAGED:
        return L"D3DPOOL_MANAGED";

    case D3DPOOL_SYSTEMMEM:
        return L"D3DPOOL_SYSTEMMEM";

    case D3DPOOL_SCRATCH:
        return L"D3DPOOL_SCRATCH";

    }
    return L"Unknown";
}




void KRipper8::Dump_TextureDesc2Log( IDirect3DBaseTexture8* pTexture ){

    if( !pTexture )
        return;

    D3DRESOURCETYPE Type = pTexture->GetType();

    g_pLog->Write( L"-----Texture desc-----\n" );
    g_pLog->Write( L"Level count: %u\n", pTexture->GetLevelCount() );
    g_pLog->Write( L"Type: %s\n", D3DRESOURCETYPE_2Str( pTexture->GetType() ) );
    g_pLog->Write( L"----------------------\n" );
    HRESULT hr;
    if( Type == D3DRTYPE_TEXTURE )
    {
        LPDIRECT3DTEXTURE8 pTex = static_cast <LPDIRECT3DTEXTURE8>( pTexture );
        D3DSURFACE_DESC desc;
        ZeroMemory( &desc, sizeof( desc ) );
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) )
        {
            g_pLog->Write( L"Format: %s\n", D3DFORMAT_2Str( desc.Format ) );
            g_pLog->Write( L"Type  : %s\n", D3DRESOURCETYPE_2Str( desc.Type ) );
            g_pLog->Write( L"Usage : %s\n", D3DUSAGE_2Str( desc.Usage ) );
            g_pLog->Write( L"Pool  : %s\n", D3DPOOL_2Str( desc.Pool ) );
            g_pLog->Write( L"Size  : %u\n", desc.Size );
            g_pLog->Write( L"MultiSampleType: %s\n", D3DMULTISAMPLE_2Str( desc.MultiSampleType ) );
            g_pLog->Write( L"Width : %d\n", desc.Width );
            g_pLog->Write( L"Height: %d\n", desc.Height );
        }
        else
        {
            g_pLog->Write( L"IDirect3DTexture8::GetLevelDesc() error: 0x%08X\n", hr );
        }
    }
    else if( Type == D3DRTYPE_VOLUMETEXTURE )
    {//VOLUME
        LPDIRECT3DVOLUMETEXTURE8 pTex = static_cast <LPDIRECT3DVOLUMETEXTURE8>( pTexture );
        D3DVOLUME_DESC desc;
        ZeroMemory( &desc, sizeof( desc ) );
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) ){
            g_pLog->Write( L"Format: %s\n", D3DFORMAT_2Str( desc.Format ) );
            g_pLog->Write( L"Type  : %s\n", D3DRESOURCETYPE_2Str( desc.Type ) );
            g_pLog->Write( L"Usage : %s\n", D3DUSAGE_2Str( desc.Usage ) );
            g_pLog->Write( L"Pool  : %s\n", D3DPOOL_2Str( desc.Pool ) );
            g_pLog->Write( L"Size  : %u\n", desc.Size );
            g_pLog->Write( L"Width : %d\n", desc.Width );
            g_pLog->Write( L"Height: %d\n", desc.Height );
            g_pLog->Write( L"Depth : %d\n", desc.Depth );
        }
        else{
            g_pLog->Write( L"IDirect3DVolumeTexture8::GetLevelDesc() error: 0x%08X\n", hr );
        }
    }
    else if( Type == D3DRTYPE_CUBETEXTURE )
    {//CUBE
        LPDIRECT3DCUBETEXTURE8 pTex = static_cast <LPDIRECT3DCUBETEXTURE8>( pTexture );
        D3DSURFACE_DESC desc;
        ZeroMemory( &desc, sizeof( desc ) );
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) )
        {
            g_pLog->Write( L"Format: %s\n", D3DFORMAT_2Str( desc.Format ) );
            g_pLog->Write( L"Type  : %s\n", D3DRESOURCETYPE_2Str( desc.Type ) );
            g_pLog->Write( L"Usage : %s\n", D3DUSAGE_2Str( desc.Usage ) );
            g_pLog->Write( L"Pool  : %s\n", D3DPOOL_2Str( desc.Pool ) );
            g_pLog->Write( L"Size  : %u\n", desc.Size );
            g_pLog->Write( L"MultiSampleType: %s\n", D3DMULTISAMPLE_2Str( desc.MultiSampleType ) );
            g_pLog->Write( L"Width : %d\n", desc.Width );
            g_pLog->Write( L"Height: %d\n", desc.Height );
        }
        else
        {
            g_pLog->Write( L"IDirect3DCubeTexture8::GetLevelDesc() error: 0x%08X\n", hr );
        }    
    }


    g_pLog->Write( L"----------------------\n" );
}



const wchar_t* KRipper8::D3DUSAGE_2Str( DWORD t ){
    switch( t ){

    case D3DUSAGE_DEPTHSTENCIL:
        return L"D3DUSAGE_DEPTHSTENCIL";

    case D3DUSAGE_DONOTCLIP:
        return L"D3DUSAGE_DONOTCLIP";

    case D3DUSAGE_DYNAMIC:
        return L"D3DUSAGE_DYNAMIC";

    case D3DUSAGE_NPATCHES:
        return L"D3DUSAGE_NPATCHES";

    case D3DUSAGE_POINTS:
        return L"D3DUSAGE_POINTS";

    case D3DUSAGE_RTPATCHES:
        return L"D3DUSAGE_RTPATCHES";

    case D3DUSAGE_RENDERTARGET:
        return L"D3DUSAGE_RENDERTARGET";

    case D3DUSAGE_SOFTWAREPROCESSING:
        return L"D3DUSAGE_SOFTWAREPROCESSING";

    case D3DUSAGE_WRITEONLY:
        return L"D3DUSAGE_WRITEONLY";

    }
    return L"Unknown";
}


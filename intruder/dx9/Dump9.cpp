#include "PreComp.h"
#include "KRipper9.h"


const wchar_t* KRipper9::D3DDECLMETHOD_2Str( D3DDECLMETHOD t ){
    switch( t ){
    case D3DDECLMETHOD_DEFAULT:
        return L"D3DDECLMETHOD_DEFAULT";

    case D3DDECLMETHOD_PARTIALU:
        return L"D3DDECLMETHOD_PARTIALU";

    case D3DDECLMETHOD_PARTIALV:
        return L"D3DDECLMETHOD_PARTIALV";

    case D3DDECLMETHOD_CROSSUV:
        return L"D3DDECLMETHOD_CROSSUV";

    case D3DDECLMETHOD_UV:
        return L"D3DDECLMETHOD_UV";

    case D3DDECLMETHOD_LOOKUP:
        return L"D3DDECLMETHOD_LOOKUP";

    case D3DDECLMETHOD_LOOKUPPRESAMPLED:
        return L"D3DDECLMETHOD_LOOKUPPRESAMPLED";
    }
    return L"Unknown";
}



const wchar_t* KRipper9::D3DDECLUSAGE_2Str( D3DDECLUSAGE t ){
    switch( t ){
    case D3DDECLUSAGE_POSITION:
        return L"D3DDECLUSAGE_POSITION";

    case D3DDECLUSAGE_BLENDWEIGHT:
        return L"D3DDECLUSAGE_BLENDWEIGHT";

    case D3DDECLUSAGE_BLENDINDICES:
        return L"D3DDECLUSAGE_BLENDINDICES";

    case D3DDECLUSAGE_NORMAL:
        return L"D3DDECLUSAGE_NORMAL";

    case D3DDECLUSAGE_PSIZE:
        return L"D3DDECLUSAGE_PSIZE";

    case D3DDECLUSAGE_TEXCOORD:
        return L"D3DDECLUSAGE_TEXCOORD";

    case D3DDECLUSAGE_TANGENT:
        return L"D3DDECLUSAGE_TANGENT";

    case D3DDECLUSAGE_BINORMAL:
        return L"D3DDECLUSAGE_BINORMAL";

    case D3DDECLUSAGE_TESSFACTOR:
        return L"D3DDECLUSAGE_TESSFACTOR";

    case D3DDECLUSAGE_POSITIONT:
        return L"D3DDECLUSAGE_POSITIONT";

    case D3DDECLUSAGE_COLOR:
        return L"D3DDECLUSAGE_COLOR";

    case D3DDECLUSAGE_FOG:
        return L"D3DDECLUSAGE_FOG";

    case D3DDECLUSAGE_DEPTH:
        return L"D3DDECLUSAGE_DEPTH";

    case D3DDECLUSAGE_SAMPLE:
        return L"D3DDECLUSAGE_SAMPLE";

    }
    return L"Unknown";
}


const wchar_t* KRipper9::D3DDECLTYPE_2Str( D3DDECLTYPE t ){

    switch( t ){

    case D3DDECLTYPE_FLOAT1:
        return L"D3DDECLTYPE_FLOAT1";

    case D3DDECLTYPE_FLOAT2:
        return L"D3DDECLTYPE_FLOAT2";

    case D3DDECLTYPE_FLOAT3:
        return L"D3DDECLTYPE_FLOAT3";

    case D3DDECLTYPE_FLOAT4:
        return L"D3DDECLTYPE_FLOAT4";

    case D3DDECLTYPE_D3DCOLOR:
        return L"D3DDECLTYPE_D3DCOLOR";

    case D3DDECLTYPE_UBYTE4:
        return L"D3DDECLTYPE_UBYTE4";

    case D3DDECLTYPE_SHORT2:
        return L"D3DDECLTYPE_SHORT2";

    case D3DDECLTYPE_SHORT4:
        return L"D3DDECLTYPE_SHORT4";

    case D3DDECLTYPE_UBYTE4N:
        return L"D3DDECLTYPE_UBYTE4N";

    case D3DDECLTYPE_SHORT2N:
        return L"D3DDECLTYPE_SHORT2N";

    case D3DDECLTYPE_SHORT4N:
        return L"D3DDECLTYPE_SHORT4N";

    case D3DDECLTYPE_USHORT2N:
        return L"D3DDECLTYPE_USHORT2N";

    case D3DDECLTYPE_USHORT4N:
        return L"D3DDECLTYPE_USHORT4N";

    case D3DDECLTYPE_UDEC3:
        return L"D3DDECLTYPE_UDEC3";

    case D3DDECLTYPE_DEC3N:
        return L"D3DDECLTYPE_DEC3N";

    case D3DDECLTYPE_FLOAT16_2:
        return L"D3DDECLTYPE_FLOAT16_2";

    case D3DDECLTYPE_FLOAT16_4:
        return L"D3DDECLTYPE_FLOAT16_4";

    case D3DDECLTYPE_UNUSED:
        return L"D3DDECLTYPE_UNUSED";
    
    }
    return L"Unknown";
}



void KRipper9::Dump_D3DVERTEXELEMENT9_2Log( const D3DVERTEXELEMENT9& Elem ){

    g_pLog->Write( L"Stream=%u\n", Elem.Stream);
    g_pLog->Write( L"Offset=%u\n", Elem.Offset);
    g_pLog->Write( L"Type  =%s\n", D3DDECLTYPE_2Str( (D3DDECLTYPE)Elem.Type ) );
    g_pLog->Write( L"Method=%s\n", D3DDECLMETHOD_2Str( (D3DDECLMETHOD)Elem.Method ) );
    g_pLog->Write( L"Usage =%s\n", D3DDECLUSAGE_2Str( (D3DDECLUSAGE)Elem.Usage ) );
    g_pLog->Write( L"UsIndx=%u\n\n", Elem.UsageIndex );
}


const wchar_t* KRipper9::D3DRESOURCETYPE_2Str( D3DRESOURCETYPE t ){
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



const wchar_t* KRipper9::D3DFORMAT_2Str( D3DFORMAT f ){
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

    case D3DFMT_A8B8G8R8:
        return L"D3DFMT_A8B8G8R8";

    case D3DFMT_X8B8G8R8:
        return L"D3DFMT_X8B8G8R8";

    case D3DFMT_G16R16:
        return L"D3DFMT_G16R16";

    case D3DFMT_A2R10G10B10:
        return L"D3DFMT_A2R10G10B10";

    case D3DFMT_A16B16G16R16:
        return L"D3DFMT_A16B16G16R16";

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

    case D3DFMT_R8G8_B8G8:
        return L"D3DFMT_R8G8_B8G8";

    case D3DFMT_YUY2:
        return L"D3DFMT_YUY2";

    case D3DFMT_G8R8_G8B8:
        return L"D3DFMT_G8R8_G8B8";

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

    case D3DFMT_D32F_LOCKABLE:
        return L"D3DFMT_D32F_LOCKABLE";

    case D3DFMT_D24FS8:
        return L"D3DFMT_D24FS8";

//    case D3DFMT_D32_LOCKABLE:
//        return L"D3DFMT_D32_LOCKABLE";

//    case D3DFMT_S8_LOCKABLE:
//        return L"D3DFMT_S8_LOCKABLE";

    case D3DFMT_L16:
        return L"D3DFMT_L16";

    case D3DFMT_VERTEXDATA:
        return L"D3DFMT_VERTEXDATA";

    case D3DFMT_INDEX16:
        return L"D3DFMT_INDEX16";

    case D3DFMT_INDEX32:
        return L"D3DFMT_INDEX32";

    case D3DFMT_Q16W16V16U16:
        return L"D3DFMT_Q16W16V16U16";

    case D3DFMT_MULTI2_ARGB8:
        return L"D3DFMT_MULTI2_ARGB8";

    case D3DFMT_R16F:
        return L"D3DFMT_R16F";

    case D3DFMT_G16R16F:
        return L"D3DFMT_G16R16F";

    case D3DFMT_A16B16G16R16F:
        return L"D3DFMT_A16B16G16R16F";

    case D3DFMT_R32F:
        return L"D3DFMT_R32F";

    case D3DFMT_G32R32F:
        return L"D3DFMT_G32R32F";

    case D3DFMT_A32B32G32R32F:
        return L"D3DFMT_A32B32G32R32F";

    case D3DFMT_CxV8U8:
        return L"D3DFMT_CxV8U8";

//    case D3DFMT_A1:
//        return L"D3DFMT_A1";

//    case D3DFMT_A2B10G10R10_XR_BIAS:
//        return L"D3DFMT_A2B10G10R10_XR_BIAS";

//    case D3DFMT_BINARYBUFFER:
//        return L"D3DFMT_BINARYBUFFER";

    case D3DFMT_FORCE_DWORD:
        return L"D3DFMT_FORCE_DWORD";
    }

    return L"Unknown";
}


const wchar_t* KRipper9::D3DUSAGE_2Str( DWORD t ){
    switch( t ){

    case D3DUSAGE_AUTOGENMIPMAP:
        return L"D3DUSAGE_AUTOGENMIPMAP";

    case D3DUSAGE_DEPTHSTENCIL:
        return L"D3DUSAGE_DEPTHSTENCIL";

    case D3DUSAGE_DMAP:
        return L"D3DUSAGE_DMAP";

    case D3DUSAGE_DONOTCLIP:
        return L"D3DUSAGE_DONOTCLIP";

    case D3DUSAGE_DYNAMIC:
        return L"D3DUSAGE_DYNAMIC";

//    case D3DUSAGE_NONSECURE:
//        return L"D3DUSAGE_NONSECURE";

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

//    case D3DUSAGE_TEXTAPI:
//        return L"D3DUSAGE_TEXTAPI";

    case D3DUSAGE_WRITEONLY:
        return L"D3DUSAGE_WRITEONLY";

    }
    return L"Unknown";
}


const wchar_t* KRipper9::D3DPOOL_2Str( D3DPOOL t ){

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


const wchar_t* KRipper9::D3DMULTISAMPLE_2Str( D3DMULTISAMPLE_TYPE x ){
    switch( x ){

    case D3DMULTISAMPLE_NONE:
        return L"D3DMULTISAMPLE_NONE";

    case D3DMULTISAMPLE_NONMASKABLE:
        return L"D3DMULTISAMPLE_NONMASKABLE";

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


void KRipper9::Dump_TextureDesc2Log( IDirect3DBaseTexture9 *pTexture ){

    if( !pTexture )
        return;

    D3DRESOURCETYPE Type = pTexture->GetType();

    g_pLog->Write( L"-----Texture desc-----\n" );
    g_pLog->Write( L"Level count: %u\n", pTexture->GetLevelCount() );
    g_pLog->Write( L"Type: %s\n", D3DRESOURCETYPE_2Str( pTexture->GetType() ) );
    g_pLog->Write( L"----------------------\n" );
    HRESULT hr;
    if( Type == D3DRTYPE_TEXTURE ){
        LPDIRECT3DTEXTURE9 pTex = static_cast <LPDIRECT3DTEXTURE9>( pTexture );
        D3DSURFACE_DESC desc;
        ZeroMemory( &desc, sizeof( desc ) );
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) ){
            g_pLog->Write( L"Format: %s\n", D3DFORMAT_2Str( desc.Format ) );
            g_pLog->Write( L"Type  : %s\n", D3DRESOURCETYPE_2Str( desc.Type ) );
            g_pLog->Write( L"Usage : %s\n", D3DUSAGE_2Str( desc.Usage ) );
            g_pLog->Write( L"Pool  : %s\n", D3DPOOL_2Str( desc.Pool ) );
            g_pLog->Write( L"MultiSampleType: %s\n", D3DMULTISAMPLE_2Str( desc.MultiSampleType ) );
            g_pLog->Write( L"MultiSampleQuality: %d\n", desc.MultiSampleQuality );
            g_pLog->Write( L"Width : %d\n", desc.Width );
            g_pLog->Write( L"Height: %d\n", desc.Height );
        }
        else{
            g_pLog->Write( L"IDirect3DTexture9::GetLevelDesc() error: 0x%08X\n", hr );
        }
    }
    else if( Type == D3DRTYPE_VOLUMETEXTURE ){//VOLUME
        LPDIRECT3DVOLUMETEXTURE9 pTex = static_cast <LPDIRECT3DVOLUMETEXTURE9>( pTexture );
        D3DVOLUME_DESC desc;
        ZeroMemory( &desc, sizeof( desc ) );
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) ){
            g_pLog->Write( L"Format: %s\n", D3DFORMAT_2Str( desc.Format ) );
            g_pLog->Write( L"Type  : %s\n", D3DRESOURCETYPE_2Str( desc.Type ) );
            g_pLog->Write( L"Usage : %s\n", D3DUSAGE_2Str( desc.Usage ) );
            g_pLog->Write( L"Pool  : %s\n", D3DPOOL_2Str( desc.Pool ) );
            g_pLog->Write( L"Width : %d\n", desc.Width );
            g_pLog->Write( L"Height: %d\n", desc.Height );
            g_pLog->Write( L"Depth : %d\n", desc.Depth );
        }
        else{
            g_pLog->Write( L"IDirect3DVolumeTexture9::GetLevelDesc() error: 0x%08X\n", hr );
        }
    }
    else if( Type == D3DRTYPE_CUBETEXTURE ){//CUBE
        LPDIRECT3DCUBETEXTURE9 pTex = static_cast <LPDIRECT3DCUBETEXTURE9>( pTexture );
        D3DSURFACE_DESC desc;
        ZeroMemory( &desc, sizeof( desc ) );
        hr = pTex->GetLevelDesc( 0, &desc );
        if( SUCCEEDED( hr ) ){
            g_pLog->Write( L"Format: %s\n", D3DFORMAT_2Str( desc.Format ) );
            g_pLog->Write( L"Type  : %s\n", D3DRESOURCETYPE_2Str( desc.Type ) );
            g_pLog->Write( L"Usage : %s\n", D3DUSAGE_2Str( desc.Usage ) );
            g_pLog->Write( L"Pool  : %s\n", D3DPOOL_2Str( desc.Pool ) );
            g_pLog->Write( L"MultiSampleType: %s\n", D3DMULTISAMPLE_2Str( desc.MultiSampleType ) );
            g_pLog->Write( L"MultiSampleQuality: %d\n", desc.MultiSampleQuality );
            g_pLog->Write( L"Width : %d\n", desc.Width );
            g_pLog->Write( L"Height: %d\n", desc.Height );
        }
        else{
            g_pLog->Write( L"IDirect3DCubeTexture9::GetLevelDesc() error: 0x%08X\n", hr );
        }    
    }


    g_pLog->Write( L"----------------------\n" );
}



const wchar_t* KRipper9::D3DRENDERSTATETYPE_2Str( D3DRENDERSTATETYPE t )
{
    switch ( t )
    {
    case D3DRS_ZENABLE:
        return L"D3DRS_ZENABLE";

    case D3DRS_FILLMODE:
        return L"D3DRS_FILLMODE";

    case D3DRS_SHADEMODE:
        return L"D3DRS_SHADEMODE";

    case D3DRS_ZWRITEENABLE:
        return L"D3DRS_ZWRITEENABLE";

    case D3DRS_ALPHATESTENABLE:
        return L"D3DRS_ALPHATESTENABLE";

    case D3DRS_LASTPIXEL:
        return L"D3DRS_LASTPIXEL";

    case D3DRS_SRCBLEND:
        return L"D3DRS_SRCBLEND";

    case D3DRS_DESTBLEND:
        return L"D3DRS_DESTBLEND";

    case D3DRS_CULLMODE:
        return L"D3DRS_CULLMODE";

    case D3DRS_ZFUNC:
        return L"D3DRS_ZFUNC";

    case D3DRS_ALPHAREF:
        return L"D3DRS_ALPHAREF";

    case D3DRS_ALPHAFUNC:
        return L"D3DRS_ALPHAFUNC";

    case D3DRS_DITHERENABLE:
        return L"D3DRS_DITHERENABLE";

    case D3DRS_ALPHABLENDENABLE:
        return L"D3DRS_ALPHABLENDENABLE";

    case D3DRS_FOGENABLE:
        return L"D3DRS_FOGENABLE";

    case D3DRS_SPECULARENABLE:
        return L"D3DRS_SPECULARENABLE";

    case D3DRS_FOGCOLOR:
        return L"D3DRS_FOGCOLOR";

    case D3DRS_FOGTABLEMODE:
        return L"D3DRS_FOGTABLEMODE";

    case D3DRS_FOGSTART:
        return L"D3DRS_FOGSTART";

    case D3DRS_FOGEND:
        return L"D3DRS_FOGEND";

    case D3DRS_FOGDENSITY:
        return L"D3DRS_FOGDENSITY";

    case D3DRS_RANGEFOGENABLE:
        return L"D3DRS_RANGEFOGENABLE";

    case D3DRS_STENCILENABLE:
        return L"D3DRS_STENCILENABLE";

    case D3DRS_STENCILFAIL:
        return L"D3DRS_STENCILFAIL";

    case D3DRS_STENCILZFAIL:
        return L"D3DRS_STENCILZFAIL";

    case D3DRS_STENCILPASS:
        return L"D3DRS_STENCILPASS";

    case D3DRS_STENCILFUNC:
        return L"D3DRS_STENCILFUNC";

    case D3DRS_STENCILREF:
        return L"D3DRS_STENCILREF";

    case D3DRS_STENCILMASK:
        return L"D3DRS_STENCILMASK";

    case D3DRS_STENCILWRITEMASK:
        return L"D3DRS_STENCILWRITEMASK";

    case D3DRS_TEXTUREFACTOR:
        return L"D3DRS_TEXTUREFACTOR";

    case D3DRS_WRAP0:
        return L"D3DRS_WRAP0";

    case D3DRS_WRAP1:
        return L"D3DRS_WRAP1";

    case D3DRS_WRAP2:
        return L"D3DRS_WRAP2";

    case D3DRS_WRAP3:
        return L"D3DRS_WRAP3";

    case D3DRS_WRAP4:
        return L"D3DRS_WRAP4";

    case D3DRS_WRAP5:
        return L"D3DRS_WRAP5";

    case D3DRS_WRAP6:
        return L"D3DRS_WRAP6";

    case D3DRS_WRAP7:
        return L"D3DRS_WRAP7";

    case D3DRS_CLIPPING:
        return L"D3DRS_CLIPPING";

    case D3DRS_LIGHTING:
        return L"D3DRS_LIGHTING";

    case D3DRS_AMBIENT:
        return L"D3DRS_AMBIENT";

    case D3DRS_FOGVERTEXMODE:
        return L"D3DRS_FOGVERTEXMODE";

    case D3DRS_COLORVERTEX:
        return L"D3DRS_COLORVERTEX";

    case D3DRS_LOCALVIEWER:
        return L"D3DRS_LOCALVIEWER";

    case D3DRS_NORMALIZENORMALS:
        return L"D3DRS_NORMALIZENORMALS";

    case D3DRS_DIFFUSEMATERIALSOURCE:
        return L"D3DRS_DIFFUSEMATERIALSOURCE";

    case D3DRS_SPECULARMATERIALSOURCE:
        return L"D3DRS_SPECULARMATERIALSOURCE";

    case D3DRS_AMBIENTMATERIALSOURCE:
        return L"D3DRS_AMBIENTMATERIALSOURCE";

    case D3DRS_EMISSIVEMATERIALSOURCE:
        return L"D3DRS_EMISSIVEMATERIALSOURCE";

    case D3DRS_VERTEXBLEND:
        return L"D3DRS_VERTEXBLEND";

    case D3DRS_CLIPPLANEENABLE:
        return L"D3DRS_CLIPPLANEENABLE";

    case D3DRS_POINTSIZE:
        return L"D3DRS_POINTSIZE";

    case D3DRS_POINTSIZE_MIN:
        return L"D3DRS_POINTSIZE_MIN";

    case D3DRS_POINTSPRITEENABLE:
        return L"D3DRS_POINTSPRITEENABLE";

    case D3DRS_POINTSCALEENABLE:
        return L"D3DRS_POINTSCALEENABLE";

    case D3DRS_POINTSCALE_A:
        return L"D3DRS_POINTSCALE_A";

    case D3DRS_POINTSCALE_B:
        return L"D3DRS_POINTSCALE_B";

    case D3DRS_POINTSCALE_C:
        return L"D3DRS_POINTSCALE_C";

    case D3DRS_MULTISAMPLEANTIALIAS:
        return L"D3DRS_MULTISAMPLEANTIALIAS";

    case D3DRS_MULTISAMPLEMASK:
        return L"D3DRS_MULTISAMPLEMASK";

    case D3DRS_PATCHEDGESTYLE:
        return L"D3DRS_PATCHEDGESTYLE";

    case D3DRS_DEBUGMONITORTOKEN:
        return L"D3DRS_DEBUGMONITORTOKEN";

    case D3DRS_POINTSIZE_MAX:
        return L"D3DRS_POINTSIZE_MAX";

    case D3DRS_INDEXEDVERTEXBLENDENABLE:
        return L"D3DRS_INDEXEDVERTEXBLENDENABLE";

    case D3DRS_COLORWRITEENABLE:
        return L"D3DRS_COLORWRITEENABLE";

    case D3DRS_TWEENFACTOR:
        return L"D3DRS_TWEENFACTOR";

    case D3DRS_BLENDOP:
        return L"D3DRS_BLENDOP";

    case D3DRS_POSITIONDEGREE:
        return L"D3DRS_POSITIONDEGREE";

    case D3DRS_NORMALDEGREE:
        return L"D3DRS_NORMALDEGREE";

    case D3DRS_SCISSORTESTENABLE:
        return L"D3DRS_SCISSORTESTENABLE";

    case D3DRS_SLOPESCALEDEPTHBIAS:
        return L"D3DRS_SLOPESCALEDEPTHBIAS";

    case D3DRS_ANTIALIASEDLINEENABLE:
        return L"D3DRS_ANTIALIASEDLINEENABLE";

    case D3DRS_MINTESSELLATIONLEVEL:
        return L"D3DRS_MINTESSELLATIONLEVEL";

    case D3DRS_MAXTESSELLATIONLEVEL:
        return L"D3DRS_MAXTESSELLATIONLEVEL";

    case D3DRS_ADAPTIVETESS_X:
        return L"D3DRS_ADAPTIVETESS_X";

    case D3DRS_ADAPTIVETESS_Y:
        return L"D3DRS_ADAPTIVETESS_Y";

    case D3DRS_ADAPTIVETESS_Z:
        return L"D3DRS_ADAPTIVETESS_Z";

    case D3DRS_ADAPTIVETESS_W:
        return L"D3DRS_ADAPTIVETESS_W";

    case D3DRS_ENABLEADAPTIVETESSELLATION:
        return L"D3DRS_ENABLEADAPTIVETESSELLATION";

    case D3DRS_TWOSIDEDSTENCILMODE:
        return L"D3DRS_TWOSIDEDSTENCILMODE";

    case D3DRS_CCW_STENCILFAIL:
        return L"D3DRS_CCW_STENCILFAIL";

    case D3DRS_CCW_STENCILZFAIL:
        return L"D3DRS_CCW_STENCILZFAIL";

    case D3DRS_CCW_STENCILPASS:
        return L"D3DRS_CCW_STENCILPASS";

    case D3DRS_CCW_STENCILFUNC:
        return L"D3DRS_CCW_STENCILFUNC";

    case D3DRS_COLORWRITEENABLE1:
        return L"D3DRS_COLORWRITEENABLE1";

    case D3DRS_COLORWRITEENABLE2:
        return L"D3DRS_COLORWRITEENABLE2";

    case D3DRS_COLORWRITEENABLE3:
        return L"D3DRS_COLORWRITEENABLE3";

    case D3DRS_BLENDFACTOR:
        return L"D3DRS_BLENDFACTOR";

    case D3DRS_SRGBWRITEENABLE:
        return L"D3DRS_SRGBWRITEENABLE";

    case D3DRS_DEPTHBIAS:
        return L"D3DRS_DEPTHBIAS";

    case D3DRS_WRAP8:
        return L"D3DRS_WRAP8";

    case D3DRS_WRAP9:
        return L"D3DRS_WRAP9";

    case D3DRS_WRAP10:
        return L"D3DRS_WRAP10";

    case D3DRS_WRAP11:
        return L"D3DRS_WRAP11";

    case D3DRS_WRAP12:
        return L"D3DRS_WRAP12";

    case D3DRS_WRAP13:
        return L"D3DRS_WRAP13";

    case D3DRS_WRAP14:
        return L"D3DRS_WRAP14";

    case D3DRS_WRAP15:
        return L"D3DRS_WRAP15";

    case D3DRS_SEPARATEALPHABLENDENABLE:
        return L"D3DRS_SEPARATEALPHABLENDENABLE";

    case D3DRS_SRCBLENDALPHA:
        return L"D3DRS_SRCBLENDALPHA";

    case D3DRS_DESTBLENDALPHA:
        return L"D3DRS_DESTBLENDALPHA";

    case D3DRS_BLENDOPALPHA:
        return L"D3DRS_BLENDOPALPHA";

    }
    return L"Unknown";
}



const wchar_t* KRipper9::D3DSAMPLERSTATETYPE_2Str( D3DSAMPLERSTATETYPE t )
{
    switch( t )
    {
    case D3DSAMP_ADDRESSU:
        return L"D3DSAMP_ADDRESSU";

    case D3DSAMP_ADDRESSV:
        return L"D3DSAMP_ADDRESSV";

    case D3DSAMP_ADDRESSW:
        return L"D3DSAMP_ADDRESSW";

    case D3DSAMP_BORDERCOLOR:
        return L"D3DSAMP_BORDERCOLOR";

    case D3DSAMP_MAGFILTER:
        return L"D3DSAMP_MAGFILTER";

    case D3DSAMP_MINFILTER:
        return L"D3DSAMP_MINFILTER";

    case D3DSAMP_MIPFILTER:
        return L"D3DSAMP_MIPFILTER";

    case D3DSAMP_MIPMAPLODBIAS:
        return L"D3DSAMP_MIPMAPLODBIAS";

    case D3DSAMP_MAXMIPLEVEL:
        return L"D3DSAMP_MAXMIPLEVEL";

    case D3DSAMP_MAXANISOTROPY:
        return L"D3DSAMP_MAXANISOTROPY";

    case D3DSAMP_SRGBTEXTURE:
        return L"D3DSAMP_SRGBTEXTURE";

    case D3DSAMP_ELEMENTINDEX:
        return L"D3DSAMP_ELEMENTINDEX";

    case D3DSAMP_DMAPOFFSET:
        return L"D3DSAMP_DMAPOFFSET";

    }
    return L"Unknown";
}


const wchar_t* KRipper9::D3DTEXTURESTAGESTATETYPE_2Str( D3DTEXTURESTAGESTATETYPE t )
{
    switch( t )
    {
    case D3DTSS_COLOROP:
        return L"D3DTSS_COLOROP";

    case D3DTSS_COLORARG1:
        return L"D3DTSS_COLORARG1";

    case D3DTSS_COLORARG2:
        return L"D3DTSS_COLORARG2";

    case D3DTSS_ALPHAOP:
        return L"D3DTSS_ALPHAOP";

    case D3DTSS_ALPHAARG1:
        return L"D3DTSS_ALPHAARG1";

    case D3DTSS_ALPHAARG2:
        return L"D3DTSS_ALPHAARG2";

    case D3DTSS_BUMPENVMAT00:
        return L"D3DTSS_BUMPENVMAT00";

    case D3DTSS_BUMPENVMAT01:
        return L"D3DTSS_BUMPENVMAT01";

    case D3DTSS_BUMPENVMAT10:
        return L"D3DTSS_BUMPENVMAT10";

    case D3DTSS_BUMPENVMAT11:
        return L"D3DTSS_BUMPENVMAT11";

    case D3DTSS_TEXCOORDINDEX:
        return L"D3DTSS_TEXCOORDINDEX";

    case D3DTSS_BUMPENVLSCALE:
        return L"D3DTSS_BUMPENVLSCALE";

    case D3DTSS_BUMPENVLOFFSET:
        return L"D3DTSS_BUMPENVLOFFSET";

    case D3DTSS_TEXTURETRANSFORMFLAGS:
        return L"D3DTSS_TEXTURETRANSFORMFLAGS";

    case D3DTSS_COLORARG0:
        return L"D3DTSS_COLORARG0";

    case D3DTSS_ALPHAARG0:
        return L"D3DTSS_ALPHAARG0";

    case D3DTSS_RESULTARG:
        return L"D3DTSS_RESULTARG";

    case D3DTSS_CONSTANT:
        return L"D3DTSS_CONSTANT";

    }
    return L"Unknown";
}



#include "PreComp.h"
#include "KRipper11.h"



void KRipper11::DumpShaderResourceView( ID3D11ShaderResourceView* pShaderResView )
{
    if( !pShaderResView )
    {
        g_pLog->Write( L"pTexture==NULL\n" );
        return;
    }


    D3D11_SHADER_RESOURCE_VIEW_DESC  Descr;
    pShaderResView->GetDesc( &Descr );

    g_pLog->Write( L"---Resource format dump---\n" );
    g_pLog->Write( L"Format: %s\n", DXGI_FORMAT_2_Str( Descr.Format ) );
    g_pLog->Write( L"View Dimension: %s\n",  D3D11_SRV_DIMENSION_2_Str( Descr.ViewDimension ) );
    g_pLog->Write( L"--------------------------\n" );

    
    TDXRef < ID3D11Resource > shaderResourceRef;
    pShaderResView->GetResource( &shaderResourceRef );


    switch ( Descr.ViewDimension )
    {
    case D3D11_SRV_DIMENSION_TEXTURE1D:
    case D3D11_SRV_DIMENSION_TEXTURE1DARRAY:
    {
        ID3D11Texture1D* pTexture1D = static_cast <ID3D11Texture1D*> ( shaderResourceRef.get() );
        D3D11_TEXTURE1D_DESC desc;
        pTexture1D->GetDesc( &desc );
        g_pLog->Write( L"Width    : %u\n", desc.Width );
        g_pLog->Write( L"MipLevels: %u\n", desc.MipLevels );
        g_pLog->Write( L"ArraySize: %u\n", desc.ArraySize );
        g_pLog->Write( L"Format   : %s\n", DXGI_FORMAT_2_Str( desc.Format ) );
        g_pLog->Write( L"Usage    : %s\n", D3D11_USAGE_2_Str( desc.Usage ) );
        g_pLog->Write( L"BindFlags: 0x%08X\n", desc.BindFlags );
        g_pLog->Write( L"CPUAccessFlags:0x%08X\n", desc.CPUAccessFlags );
        g_pLog->Write( L"MiscFlags:0x%08X\n", desc.MiscFlags );
        break;
    }

    case D3D11_SRV_DIMENSION_TEXTURE2D:
    case D3D11_SRV_DIMENSION_TEXTURE2DARRAY:
    case D3D11_SRV_DIMENSION_TEXTURE2DMS:
    {
        ID3D11Texture2D* pTexture2D = static_cast <ID3D11Texture2D*> ( shaderResourceRef.get() );
        D3D11_TEXTURE2D_DESC desc;
        pTexture2D->GetDesc( &desc );
        g_pLog->Write( L"Width    : %u\n", desc.Width );
        g_pLog->Write( L"Height   : %u\n", desc.Height );
        g_pLog->Write( L"MipLevels: %u\n", desc.MipLevels );
        g_pLog->Write( L"ArraySize: %u\n", desc.ArraySize );
        g_pLog->Write( L"Format   : %s\n", DXGI_FORMAT_2_Str( desc.Format ) );
        g_pLog->Write( L"DXGI_SAMPLE_DESC.Count: %u\n", desc.SampleDesc.Count );
        g_pLog->Write( L"DXGI_SAMPLE_DESC.Quality: %u\n", desc.SampleDesc.Quality );
        g_pLog->Write( L"Usage    : %s\n", D3D11_USAGE_2_Str( desc.Usage ) );
        g_pLog->Write( L"BindFlags: 0x%08X\n", desc.BindFlags );
        g_pLog->Write( L"CPUAccessFlags :0x%08X\n", desc.CPUAccessFlags );
        g_pLog->Write( L"MiscFlags:0x%08X\n", desc.MiscFlags );
        break;
    }


    case D3D11_SRV_DIMENSION_TEXTURE3D:
    {
        ID3D11Texture3D* pTexture3D = static_cast <ID3D11Texture3D*> ( shaderResourceRef.get() );
        D3D11_TEXTURE3D_DESC desc;
        pTexture3D->GetDesc( &desc );
        g_pLog->Write( L"Width    : %u\n", desc.Width );
        g_pLog->Write( L"Height   : %u\n", desc.Height );
        g_pLog->Write( L"Depth    : %u\n", desc.Depth );
        g_pLog->Write( L"MipLevels: %u\n", desc.MipLevels );
        g_pLog->Write( L"Format   : %s\n", DXGI_FORMAT_2_Str( desc.Format ) );
        g_pLog->Write( L"Usage    : %s\n", D3D11_USAGE_2_Str( desc.Usage ) );
        g_pLog->Write( L"BindFlags: 0x%08X\n", desc.BindFlags );
        g_pLog->Write( L"CPUAccessFlags :0x%08X\n", desc.CPUAccessFlags );
        g_pLog->Write( L"MiscFlags:0x%08X\n", desc.MiscFlags );
        break;
    }

    case D3D11_SRV_DIMENSION_TEXTURECUBE:
    case D3D11_SRV_DIMENSION_TEXTURECUBEARRAY:
    {
        break;
    }


    }// switch
    g_pLog->Write( L"--------------------------\n" );
}


const wchar_t* KRipper11::D3D11_USAGE_2_Str( D3D11_USAGE t )
{
    switch (t)
    {
    case D3D11_USAGE_DEFAULT:
        return L"D3D11_USAGE_DEFAULT";

    case D3D11_USAGE_IMMUTABLE:
        return L"D3D11_USAGE_IMMUTABLE";

    case D3D11_USAGE_DYNAMIC:
        return L"D3D11_USAGE_DYNAMIC";

    case D3D11_USAGE_STAGING:
        return L"D3D11_USAGE_STAGING";
    }
    return L"Unknown";
}


const wchar_t* KRipper11::D3D_FEATURE_LEVEL_2_Str( D3D_FEATURE_LEVEL fl ){

    switch( fl ){

    case D3D_FEATURE_LEVEL_9_1:
        return L"D3D_FEATURE_LEVEL_9_1";

    case D3D_FEATURE_LEVEL_9_2:
        return L"D3D_FEATURE_LEVEL_9_2";

    case D3D_FEATURE_LEVEL_9_3:
        return L"D3D_FEATURE_LEVEL_9_3";

    case D3D_FEATURE_LEVEL_10_0:
        return L"D3D_FEATURE_LEVEL_10_0";

    case D3D_FEATURE_LEVEL_10_1:
        return L"D3D_FEATURE_LEVEL_10_1";

    case D3D_FEATURE_LEVEL_11_0:
        return L"D3D_FEATURE_LEVEL_11_0";
    }
    return L"Unknown";
}

const wchar_t* KRipper11::D3D_DRIVER_TYPE_2_Str( D3D_DRIVER_TYPE dt ){
    switch( dt ){
    
    case D3D_DRIVER_TYPE_UNKNOWN:
        return L"D3D_DRIVER_TYPE_UNKNOWN";

    case D3D_DRIVER_TYPE_HARDWARE:
        return L"D3D_DRIVER_TYPE_HARDWARE";

    case D3D_DRIVER_TYPE_REFERENCE:
        return L"D3D_DRIVER_TYPE_REFERENCE";

    case D3D_DRIVER_TYPE_NULL:
        return L"D3D_DRIVER_TYPE_NULL";

    case D3D_DRIVER_TYPE_SOFTWARE:
        return L"D3D_DRIVER_TYPE_SOFTWARE";

    case D3D_DRIVER_TYPE_WARP:
        return L"D3D_DRIVER_TYPE_WARP";
    }
    return L"Unknown";
}

const wchar_t* KRipper11::D3D11_SRV_DIMENSION_2_Str( D3D11_SRV_DIMENSION Foo )
{
    switch( Foo ){
    case D3D11_SRV_DIMENSION_UNKNOWN:
        return L"D3D11_SRV_DIMENSION_UNKNOWN";

    case D3D11_SRV_DIMENSION_BUFFER:
        return L"D3D11_SRV_DIMENSION_BUFFER";

    case D3D11_SRV_DIMENSION_TEXTURE1D:
        return L"D3D11_SRV_DIMENSION_TEXTURE1D";

    case D3D11_SRV_DIMENSION_TEXTURE1DARRAY:
        return L"D3D11_SRV_DIMENSION_TEXTURE1DARRAY";

    case D3D11_SRV_DIMENSION_TEXTURE2D:
        return L"D3D11_SRV_DIMENSION_TEXTURE2D";

    case D3D11_SRV_DIMENSION_TEXTURE2DARRAY:
        return L"D3D11_SRV_DIMENSION_TEXTURE2DARRAY";

    case D3D11_SRV_DIMENSION_TEXTURE2DMS:
        return L"D3D11_SRV_DIMENSION_TEXTURE2DMS";

    case D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY:
        return L"D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY";

    case D3D11_SRV_DIMENSION_TEXTURE3D:
        return L"D3D11_SRV_DIMENSION_TEXTURE3D";

    case D3D11_SRV_DIMENSION_TEXTURECUBE:
        return L"D3D11_SRV_DIMENSION_TEXTURECUBE";

    case D3D11_SRV_DIMENSION_TEXTURECUBEARRAY:
        return L"D3D11_SRV_DIMENSION_TEXTURECUBEARRAY";

    case D3D11_SRV_DIMENSION_BUFFEREX:
        return L"D3D11_SRV_DIMENSION_BUFFEREX";
    }
    return L"Unknown";
}



const wchar_t* KRipper11::DXGI_FORMAT_2_Str( DXGI_FORMAT Format )
{
    switch( Format ){
    case DXGI_FORMAT_UNKNOWN:
        return L"DXGI_FORMAT_UNKNOWN";

    case DXGI_FORMAT_R32G32B32A32_TYPELESS:
        return L"DXGI_FORMAT_R32G32B32A32_TYPELESS";

    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return L"DXGI_FORMAT_R32G32B32A32_FLOAT";

    case DXGI_FORMAT_R32G32B32A32_UINT:
        return L"DXGI_FORMAT_R32G32B32A32_UINT";

    case DXGI_FORMAT_R32G32B32A32_SINT:
        return L"DXGI_FORMAT_R32G32B32A32_SINT";

    case DXGI_FORMAT_R32G32B32_TYPELESS:
        return L"DXGI_FORMAT_R32G32B32_TYPELESS";

    case DXGI_FORMAT_R32G32B32_FLOAT:
        return L"DXGI_FORMAT_R32G32B32_FLOAT";

    case DXGI_FORMAT_R32G32B32_UINT:
        return L"DXGI_FORMAT_R32G32B32_UINT";

    case DXGI_FORMAT_R32G32B32_SINT:
        return L"DXGI_FORMAT_R32G32B32_SINT";

    case DXGI_FORMAT_R16G16B16A16_TYPELESS:
        return L"DXGI_FORMAT_R16G16B16A16_TYPELESS";

    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return L"DXGI_FORMAT_R16G16B16A16_FLOAT";

    case DXGI_FORMAT_R16G16B16A16_UNORM:
        return L"DXGI_FORMAT_R16G16B16A16_UNORM";

    case DXGI_FORMAT_R16G16B16A16_UINT:
        return L"DXGI_FORMAT_R16G16B16A16_UINT";

    case DXGI_FORMAT_R16G16B16A16_SNORM:
        return L"DXGI_FORMAT_R16G16B16A16_SNORM";

    case DXGI_FORMAT_R16G16B16A16_SINT:
        return L"DXGI_FORMAT_R16G16B16A16_SINT";

    case DXGI_FORMAT_R32G32_TYPELESS:
        return L"DXGI_FORMAT_R32G32_TYPELESS";

    case DXGI_FORMAT_R32G32_FLOAT:
        return L"DXGI_FORMAT_R32G32_FLOAT";

    case DXGI_FORMAT_R32G32_UINT:
        return L"DXGI_FORMAT_R32G32_UINT";

    case DXGI_FORMAT_R32G32_SINT:
        return L"DXGI_FORMAT_R32G32_SINT";

    case DXGI_FORMAT_R32G8X24_TYPELESS:
        return L"DXGI_FORMAT_R32G8X24_TYPELESS";

    case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        return L"DXGI_FORMAT_D32_FLOAT_S8X24_UINT";

    case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        return L"DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS";

    case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        return L"DXGI_FORMAT_X32_TYPELESS_G8X24_UINT";

    case DXGI_FORMAT_R10G10B10A2_TYPELESS:
        return L"DXGI_FORMAT_R10G10B10A2_TYPELESS";

    case DXGI_FORMAT_R10G10B10A2_UNORM:
        return L"DXGI_FORMAT_R10G10B10A2_UNORM";

    case DXGI_FORMAT_R10G10B10A2_UINT:
        return L"DXGI_FORMAT_R10G10B10A2_UINT";

    case DXGI_FORMAT_R11G11B10_FLOAT:
        return L"DXGI_FORMAT_R11G11B10_FLOAT";

    case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        return L"DXGI_FORMAT_R8G8B8A8_TYPELESS";

    case DXGI_FORMAT_R8G8B8A8_UNORM:
        return L"DXGI_FORMAT_R8G8B8A8_UNORM";

    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        return L"DXGI_FORMAT_R8G8B8A8_UNORM_SRGB";

    case DXGI_FORMAT_R8G8B8A8_UINT:
        return L"DXGI_FORMAT_R8G8B8A8_UINT";

    case DXGI_FORMAT_R8G8B8A8_SNORM:
        return L"DXGI_FORMAT_R8G8B8A8_SNORM";

    case DXGI_FORMAT_R8G8B8A8_SINT:
        return L"DXGI_FORMAT_R8G8B8A8_SINT";

    case DXGI_FORMAT_R16G16_TYPELESS:
        return L"DXGI_FORMAT_R16G16_TYPELESS";

    case DXGI_FORMAT_R16G16_FLOAT:
        return L"DXGI_FORMAT_R16G16_FLOAT";

    case DXGI_FORMAT_R16G16_UNORM:
        return L"DXGI_FORMAT_R16G16_UNORM";

    case DXGI_FORMAT_R16G16_UINT:
        return L"DXGI_FORMAT_R16G16_UINT";

    case DXGI_FORMAT_R16G16_SNORM:
        return L"DXGI_FORMAT_R16G16_SNORM";

    case DXGI_FORMAT_R16G16_SINT:
        return L"DXGI_FORMAT_R16G16_SINT";

    case DXGI_FORMAT_R32_TYPELESS:
        return L"DXGI_FORMAT_R32_TYPELESS";

    case DXGI_FORMAT_D32_FLOAT:
        return L"DXGI_FORMAT_D32_FLOAT";

    case DXGI_FORMAT_R32_FLOAT:
        return L"DXGI_FORMAT_R32_FLOAT";

    case DXGI_FORMAT_R32_UINT:
        return L"DXGI_FORMAT_R32_UINT";

    case DXGI_FORMAT_R32_SINT:
        return L"DXGI_FORMAT_R32_SINT";

    case DXGI_FORMAT_R24G8_TYPELESS:
        return L"DXGI_FORMAT_R24G8_TYPELESS";

    case DXGI_FORMAT_D24_UNORM_S8_UINT:
        return L"DXGI_FORMAT_D24_UNORM_S8_UINT";

    case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        return L"DXGI_FORMAT_R24_UNORM_X8_TYPELESS";

    case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        return L"DXGI_FORMAT_X24_TYPELESS_G8_UINT";

    case DXGI_FORMAT_R8G8_TYPELESS:
        return L"DXGI_FORMAT_R8G8_TYPELESS";

    case DXGI_FORMAT_R8G8_UNORM:
        return L"DXGI_FORMAT_R8G8_UNORM";

    case DXGI_FORMAT_R8G8_UINT:
        return L"DXGI_FORMAT_R8G8_UINT";

    case DXGI_FORMAT_R8G8_SNORM:
        return L"DXGI_FORMAT_R8G8_SNORM";

    case DXGI_FORMAT_R8G8_SINT:
        return L"DXGI_FORMAT_R8G8_SINT";

    case DXGI_FORMAT_R16_TYPELESS:
        return L"DXGI_FORMAT_R16_TYPELESS";

    case DXGI_FORMAT_R16_FLOAT:
        return L"DXGI_FORMAT_R16_FLOAT";

    case DXGI_FORMAT_D16_UNORM:
        return L"DXGI_FORMAT_D16_UNORM";

    case DXGI_FORMAT_R16_UNORM:
        return L"DXGI_FORMAT_R16_UNORM";

    case DXGI_FORMAT_R16_UINT:
        return L"DXGI_FORMAT_R16_UINT";

    case DXGI_FORMAT_R16_SNORM:
        return L"DXGI_FORMAT_R16_SNORM";

    case DXGI_FORMAT_R16_SINT:
        return L"DXGI_FORMAT_R16_SINT";

    case DXGI_FORMAT_R8_TYPELESS:
        return L"DXGI_FORMAT_R8_TYPELESS";

    case DXGI_FORMAT_R8_UNORM:
        return L"DXGI_FORMAT_R8_UNORM";

    case DXGI_FORMAT_R8_UINT:
        return L"DXGI_FORMAT_R8_UINT";

    case DXGI_FORMAT_R8_SNORM:
        return L"DXGI_FORMAT_R8_SNORM";

    case DXGI_FORMAT_R8_SINT:
        return L"DXGI_FORMAT_R8_SINT";

    case DXGI_FORMAT_A8_UNORM:
        return L"DXGI_FORMAT_A8_UNORM";

    case DXGI_FORMAT_R1_UNORM:
        return L"DXGI_FORMAT_R1_UNORM";

    case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        return L"DXGI_FORMAT_R9G9B9E5_SHAREDEXP";

    case DXGI_FORMAT_R8G8_B8G8_UNORM:
        return L"DXGI_FORMAT_R8G8_B8G8_UNORM";

    case DXGI_FORMAT_G8R8_G8B8_UNORM:
        return L"DXGI_FORMAT_G8R8_G8B8_UNORM";

    case DXGI_FORMAT_BC1_TYPELESS:
        return L"DXGI_FORMAT_BC1_TYPELESS";

    case DXGI_FORMAT_BC1_UNORM:
        return L"DXGI_FORMAT_BC1_UNORM";

    case DXGI_FORMAT_BC1_UNORM_SRGB:
        return L"DXGI_FORMAT_BC1_UNORM_SRGB";

    case DXGI_FORMAT_BC2_TYPELESS:
        return L"DXGI_FORMAT_BC2_TYPELESS";

    case DXGI_FORMAT_BC2_UNORM:
        return L"DXGI_FORMAT_BC2_UNORM";

    case DXGI_FORMAT_BC2_UNORM_SRGB:
        return L"DXGI_FORMAT_BC2_UNORM_SRGB";

    case DXGI_FORMAT_BC3_TYPELESS:
        return L"DXGI_FORMAT_BC3_TYPELESS";

    case DXGI_FORMAT_BC3_UNORM:
        return L"DXGI_FORMAT_BC3_UNORM";

    case DXGI_FORMAT_BC3_UNORM_SRGB:
        return L"DXGI_FORMAT_BC3_UNORM_SRGB";

    case DXGI_FORMAT_BC4_TYPELESS:
        return L"DXGI_FORMAT_BC4_TYPELESS";

    case DXGI_FORMAT_BC4_UNORM:
        return L"DXGI_FORMAT_BC4_UNORM";

    case DXGI_FORMAT_BC4_SNORM:
        return L"DXGI_FORMAT_BC4_SNORM";

    case DXGI_FORMAT_BC5_TYPELESS:
        return L"DXGI_FORMAT_BC5_TYPELESS";

    case DXGI_FORMAT_BC5_UNORM:
        return L"DXGI_FORMAT_BC5_UNORM";

    case DXGI_FORMAT_BC5_SNORM:
        return L"DXGI_FORMAT_BC5_SNORM";

    case DXGI_FORMAT_B5G6R5_UNORM:
        return L"DXGI_FORMAT_B5G6R5_UNORM";

    case DXGI_FORMAT_B5G5R5A1_UNORM:
        return L"DXGI_FORMAT_B5G5R5A1_UNORM";

    case DXGI_FORMAT_B8G8R8A8_UNORM:
        return L"DXGI_FORMAT_B8G8R8A8_UNORM";

    case DXGI_FORMAT_B8G8R8X8_UNORM:
        return L"DXGI_FORMAT_B8G8R8X8_UNORM";

    case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        return L"DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM";

    case DXGI_FORMAT_B8G8R8A8_TYPELESS:
        return L"DXGI_FORMAT_B8G8R8A8_TYPELESS";

    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        return L"DXGI_FORMAT_B8G8R8A8_UNORM_SRGB";

    case DXGI_FORMAT_B8G8R8X8_TYPELESS:
        return L"DXGI_FORMAT_B8G8R8X8_TYPELESS";

    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        return L"DXGI_FORMAT_B8G8R8X8_UNORM_SRGB";

    case DXGI_FORMAT_BC6H_TYPELESS:
        return L"DXGI_FORMAT_BC6H_TYPELESS";

    case DXGI_FORMAT_BC6H_UF16:
        return L"DXGI_FORMAT_BC6H_UF16";

    case DXGI_FORMAT_BC6H_SF16:
        return L"DXGI_FORMAT_BC6H_SF16";

    case DXGI_FORMAT_BC7_TYPELESS:
        return L"DXGI_FORMAT_BC7_TYPELESS";

    case DXGI_FORMAT_BC7_UNORM:
        return L"DXGI_FORMAT_BC7_UNORM";

    case DXGI_FORMAT_BC7_UNORM_SRGB:
        return L"DXGI_FORMAT_BC7_UNORM_SRGB";

    case DXGI_FORMAT_FORCE_UINT:
        return L"DXGI_FORMAT_FORCE_UINT";
    }
    return L"Unknown";
}



const wchar_t* KRipper11::D3D11_PRIMITIVE_TOPOLOGY_to_Str( D3D11_PRIMITIVE_TOPOLOGY t )
{
    switch( t ){
    case D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED:
        return L"D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED";

    case D3D11_PRIMITIVE_TOPOLOGY_POINTLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_POINTLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_LINELIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_LINELIST";

    case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
        return L"D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP";

    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST";

    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
        return L"D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP";

    case D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
        return L"D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ";

    case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
        return L"D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ";

    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
        return L"D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ";

    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
        return L"D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ";

    case D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST";

    case D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST:
        return L"D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST";

    }
    return L"Unknown";
}



void KRipper11::Dump_KD3D11InputElement2Log( const KD3D11InputElement& Elem )
{
    std::string STR = Elem.SemanticName;
    g_pLog->Write( L"Element: %s\n", StringToWString( STR ).c_str() );

    g_pLog->Write( L"Index: %d\n", Elem.SemanticIndex );
    g_pLog->Write( L"Format : %s\n", DXGI_FORMAT_2_Str( Elem.Format ) );
    g_pLog->Write( L"InputSlot: %d\n", Elem.InputSlot );
    g_pLog->Write( L"AlignOffs: %d\n", Elem.AlignedByteOffset );
    g_pLog->Write( L"InputSlotClass: %d\n", Elem.InputSlotClass );
    g_pLog->Write( L"InstanceDataStepRate: %d\n\n", Elem.InstanceDataStepRate );

}

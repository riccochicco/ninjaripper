

#include "PreComp.h"
#include "KRipper11.h"


static const char* szShaderCode = "\
Texture2D txDiffuse : register( t0 );\
SamplerState samLinear : register( s0 );\
\
struct VS_INPUT\
{\
    float3 Pos : POSITION;\
    float2 Tex : TEXCOORD0;\
};\
\
struct PS_INPUT\
{\
    float4 Pos : SV_POSITION;\
    float2 Tex : TEXCOORD0;\
};\
\
\
PS_INPUT VS( VS_INPUT input )\
{\
    PS_INPUT output = (PS_INPUT)0;\
    output.Pos.xyz = input.Pos.xyz;\
    output.Pos.w = 1.0f;\
    output.Tex = input.Tex;\
    return output;\
}\
\
\
float4 PS( PS_INPUT input) : SV_Target\
{\
    return txDiffuse.Sample( samLinear, input.Tex );\
}\
";



struct KVert11
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};


HRESULT KRipper11::CompileShaderFromMemory( 
    LPCSTR pData, 
    SIZE_T Len, 
    LPCSTR szEntryPoint, 
    LPCSTR szShaderModel, 
    ID3DBlob** ppBlobOut 
)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    TDXRef < ID3DBlob > pErrorBlobRef;

    hr = D3DX11CompileFromMemory_( pData, Len, NULL, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlobRef, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlobRef.get() != NULL )
        {
            OutputDebugStringA( (char*)pErrorBlobRef->GetBufferPointer() );
        }
        return hr;
    }
    return S_OK;
}


//Current vertex buffers
//    std::vector < ID3D11Buffer* > PrevVB;
//    std::vector < UINT >          PrevVBStrides;
//    std::vector < UINT >          PrevVBOffsets;



HRESULT KRipper11::SaveTexture2FileMain( 
    const wchar_t* szFile, 
    ID3D11DeviceContext* pImmediateContext, 
    ID3D11ShaderResourceView* pShaderResView 
)
{
    HRESULT hr;

    TDXRef <ID3D11Device>       pDevRef;
    TDXRef <ID3D11VertexShader> pVertexShaderRef;
    TDXRef <ID3D11PixelShader>  pPixelShaderRef;
    TDXRef <ID3D11InputLayout>  pVertexLayoutRef;
    TDXRef <ID3D11Buffer>       pVertexBufferRef;
    TDXRef <ID3D11Buffer>       pIndexBufferRef;    
    
    //***No need release***
    ID3D11Texture2D* pSrcTexture   = NULL;

    TDXRef <ID3D11Resource>     pSrcResourceRef;
    TDXRef <ID3D11SamplerState> pSamplerLinearRef;
    TDXRef <ID3D11Texture2D>    pDepthStencilRef;
    TDXRef <ID3D11DepthStencilView> pDepthStencilViewRef;
    TDXRef <ID3D11Texture2D> pColorTexRef;
    TDXRef <ID3D11RenderTargetView> pRenderTargetViewRef;
    TDXRef <ID3D11InputLayout> pPrevInputLayoutRef;
    TDXRef <ID3D11Buffer> pPrevBertexBufferRef;

    UINT PrevVBStride = 0;
    UINT PrevVBOffs   = 0;
    TDXRef <ID3D11Buffer> pPrevIndexBufferRef;

    DXGI_FORMAT PrevIBFormat = DXGI_FORMAT_UNKNOWN;
    UINT IBOffset = 0;
    D3D11_PRIMITIVE_TOPOLOGY PrevPrimTopology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    TDXRef <ID3D11RenderTargetView> pPrevRendTargetRef;
    TDXRef <ID3D11DepthStencilView> pPrevDepthStencilRef;

    UINT PrevViewPortsCnt =  D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    std::vector < D3D11_VIEWPORT > PrevViewPorts;
    PrevViewPorts.resize( PrevViewPortsCnt );

    TDXRef <ID3D11BlendState>      blendStateRef;
    TDXRef <ID3D11BlendState>      prevBlendStateRef;

    TDXRef <ID3D11RasterizerState> pPrevRasterizerStateRef;
    TDXRef <ID3D11RasterizerState> pRasterStateRef;
    
    //Current vertex shader
    TDXRef <ID3D11VertexShader> pPrevVSRef;
    
    UINT VSNumClassInstances = 256;
    TDXRefVec <ID3D11ClassInstance> PrevVSClassInstRefVec(VSNumClassInstances);

    //Current pixel shader
    TDXRef <ID3D11PixelShader> pPrevPSRef;

    UINT PSNumClassInstances = 256;
    TDXRefVec <ID3D11ClassInstance> PrevPSClassInstRefVec(PSNumClassInstances);

    TDXRef <ID3D11ShaderResourceView> pPrevSRVRef;


    TDXRef <ID3D11DepthStencilState> depthStencilStateRef;
    TDXRef <ID3D11DepthStencilState> prevDepthStencilStateRef;
    UINT stencilReference = 0;


    D3D11_TEXTURE2D_DESC TexDescr;
    D3D11_SHADER_RESOURCE_VIEW_DESC  Descr;
    ZeroMemory( &TexDescr, sizeof( TexDescr ) );
    ZeroMemory( &Descr, sizeof( Descr ) );

    FLOAT prevBlendFactor[4]={0.0f, 0.0f, 0.0f, 0.0f};
    UINT sampleMask = 0;


    pShaderResView->GetDesc( &Descr );
    if( Descr.ViewDimension != D3D11_SRV_DIMENSION_TEXTURE2D )
    {
        //FIXME: delete log
        g_pLog->Write( L"Error D3D11_SRV_DIMENSION : %d\n", Descr.ViewDimension );
        return 0x88887777;//Source texture format incorrect
    }


    if( 
        !unhDrawIndexed ||
        !unhPSSetShaderResources
    )
    {
        //FIXME: use enum
        return 0x88886666;//Unhooked pointers not initialized
    }

    // Assume that resource is a texture2D
    do
    {
        pImmediateContext->GetDevice( &pDevRef );

        //Get ID3D11Resource* from ID3D11ShaderResourceView*
        pShaderResView->GetResource( &pSrcResourceRef );
        
        //Cast ID3D11Resource* to ID3D11Texture2D*
        pSrcTexture = static_cast < ID3D11Texture2D* >( pSrcResourceRef.get() );
        // Check pointer for NULL
        pSrcTexture->GetDesc( &TexDescr );


        //Vertex shader create
        TDXRef <ID3DBlob> pVSBlobRef;
        hr = CompileShaderFromMemory( szShaderCode, lstrlenA( szShaderCode ), "VS", "vs_4_0", &pVSBlobRef );
        if( FAILED( hr ) )
        {
            MessageBox( NULL, L"The Texture save FX file cannot be compiled.", L"Error", MB_OK );
            break;
        }

        hr = pDevRef->CreateVertexShader( pVSBlobRef->GetBufferPointer(), pVSBlobRef->GetBufferSize(), NULL, &pVertexShaderRef );
        if( FAILED( hr ) )
        {
            break;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = ARRAYSIZE( layout );

        // Create the input layout
        hr = pDevRef->CreateInputLayout( layout, numElements, pVSBlobRef->GetBufferPointer(), pVSBlobRef->GetBufferSize(), &pVertexLayoutRef );
        if( FAILED( hr ) )
        {
            break;
        }

        // Compile the pixel shader
        TDXRef <ID3DBlob> pPSBlobRef;
        hr = CompileShaderFromMemory(szShaderCode, lstrlenA( szShaderCode ), "PS", "ps_4_0", &pPSBlobRef );
        if( FAILED( hr ) ){
            MessageBox( NULL, L"The Save Tex FX file cannot be compiled.", L"Error", MB_OK );
            break;
        }

        // Create the pixel shader
        hr = pDevRef->CreatePixelShader( pPSBlobRef->GetBufferPointer(), pPSBlobRef->GetBufferSize(), NULL, &pPixelShaderRef );
        if( FAILED( hr ) )
        {
            break;
        }

        KVert11 vertices[] =
        {
            { XMFLOAT3( -1.0f, -1.0f, 0.0f ), XMFLOAT2( 0.0f, 1.0f ) },
            { XMFLOAT3( 1.0f, -1.0f, 0.0f ),  XMFLOAT2( 1.0f, 1.0f ) },
            { XMFLOAT3( 1.0f,  1.0f, 0.0f ),  XMFLOAT2( 1.0f, 0.0f ) },
            { XMFLOAT3( -1.0f,  1.0f, 0.0f ), XMFLOAT2( 0.0f, 0.0f ) }
        };


        D3D11_BUFFER_DESC bd;
        ZeroMemory( &bd, sizeof(bd) );
        bd.Usage     = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof( KVert11 ) * 4;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory( &InitData, sizeof(InitData) );
        InitData.pSysMem = vertices;
        hr = pDevRef->CreateBuffer( &bd, &InitData, &pVertexBufferRef );
        if (FAILED( hr ))
        {
            break;
        }
        

        WORD indices[] = 
        {
             0, 1, 3,
             3, 1, 2//Back
        };

        bd.Usage     = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof( WORD ) * 6;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        InitData.pSysMem = indices;
        hr = pDevRef->CreateBuffer( &bd, &InitData, &pIndexBufferRef );
        if (FAILED( hr ))
        {
            break;
        }


        // Create the sample state
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory( &sampDesc, sizeof(sampDesc) );
        sampDesc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
        hr = pDevRef->CreateSamplerState( &sampDesc, &pSamplerLinearRef );
        if (FAILED( hr ))
        {
            break;
        }


        //Render target color texture
        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory( &descDepth, sizeof(descDepth) );
        descDepth.Width  = TexDescr.Width;
        descDepth.Height = TexDescr.Height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_RENDER_TARGET |  D3D11_BIND_SHADER_RESOURCE;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        hr = pDevRef->CreateTexture2D( &descDepth, NULL, &pColorTexRef );
        if (FAILED( hr ))
        {
            break;
        }

        D3D11_RENDER_TARGET_VIEW_DESC RTDesc;
        ZeroMemory( &RTDesc, sizeof( RTDesc ) );
        RTDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//DXGI_FORMAT_R8G8B8A8_UNORM
        RTDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        RTDesc.Texture2D.MipSlice = 0;
        if (FAILED( pDevRef->CreateRenderTargetView( pColorTexRef.get(), &RTDesc, &pRenderTargetViewRef )))
        {
            MessageBox(NULL,L"Can't Create g_pColorRTView",L"Error",MB_OK|MB_ICONERROR);
            break;
        }

        // Create depth stencil texture
        ZeroMemory( &descDepth, sizeof(descDepth) );
        descDepth.Width  = TexDescr.Width;
        descDepth.Height = TexDescr.Height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        hr = pDevRef->CreateTexture2D( &descDepth, NULL, &pDepthStencilRef );
        if (FAILED(hr))
        {
            break;
        }

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory( &descDSV, sizeof(descDSV) );
        descDSV.Format = descDepth.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = pDevRef->CreateDepthStencilView( pDepthStencilRef.get(), &descDSV, &pDepthStencilViewRef );
        if (FAILED(hr))
        {
            break;
        }

        D3D11_RASTERIZER_DESC rasterDesc;
        ZeroMemory( &rasterDesc, sizeof( rasterDesc ) );
        rasterDesc.AntialiasedLineEnable = false;
        rasterDesc.CullMode = D3D11_CULL_FRONT;
        rasterDesc.DepthBias = 0;
        rasterDesc.DepthBiasClamp = 0.0f;
        rasterDesc.DepthClipEnable = false;
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.MultisampleEnable = false;
        rasterDesc.ScissorEnable = false;
        rasterDesc.SlopeScaledDepthBias = 0.0f;
        // Create the rasterizer state from the description we just filled out.
        hr = pDevRef->CreateRasterizerState(&rasterDesc, &pRasterStateRef);
        if (FAILED(hr))
        {
            break;
        }



        D3D11_BLEND_DESC blendStateDescription;
        ZeroMemory(&blendStateDescription, sizeof(blendStateDescription));
        // Create an alpha enabled blend state description.
        blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

        blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
        //blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;

        blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        
        hr = pDevRef->CreateBlendState(&blendStateDescription, &blendStateRef);
        if (FAILED(hr))
        {
            break;
        }


        // Create new depth stencil state
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
        hr = pDevRef->CreateDepthStencilState(&depthStencilDesc, &depthStencilStateRef);
        if (FAILED(hr))
        {
            break;
        }


        //////////////////////////////////////////////////////////////////////////
        //Get current state
        //////////////////////////////////////////////////////////////////////////
        pImmediateContext->IAGetInputLayout( &pPrevInputLayoutRef );
        pImmediateContext->VSGetShader( &pPrevVSRef, &PrevVSClassInstRefVec, &VSNumClassInstances );
        pImmediateContext->PSGetShader( &pPrevPSRef, &PrevPSClassInstRefVec, &PSNumClassInstances );
        pImmediateContext->PSGetShaderResources( 0, 1, &pPrevSRVRef );
        pImmediateContext->IAGetVertexBuffers( 0, 1, &pPrevBertexBufferRef, &PrevVBStride, &PrevVBOffs );
        pImmediateContext->IAGetIndexBuffer( &pPrevIndexBufferRef, &PrevIBFormat, &IBOffset );
        pImmediateContext->IAGetPrimitiveTopology( &PrevPrimTopology );
        pImmediateContext->OMGetRenderTargets( 1, &pPrevRendTargetRef, &pPrevDepthStencilRef );

        pImmediateContext->RSGetViewports( &PrevViewPortsCnt, &PrevViewPorts[0] );
        pImmediateContext->RSGetState( &pPrevRasterizerStateRef );

        pImmediateContext->OMGetBlendState(&prevBlendStateRef, prevBlendFactor, &sampleMask);

        pImmediateContext->OMGetDepthStencilState(&prevDepthStencilStateRef, &stencilReference);

        //////////////////////////////////////////////////////////////////////////
        //Set new state
        //////////////////////////////////////////////////////////////////////////

        // Turn off alpha blending
        float blendFactor[4];
        // Setup the blend factor.
        blendFactor[0] = 0.0f;
        blendFactor[1] = 0.0f;
        blendFactor[2] = 0.0f;
        blendFactor[3] = 0.0f;
        // Turn off the alpha blending.
        pImmediateContext->OMSetBlendState(blendStateRef.get(), blendFactor, 0xffffffff);

        pImmediateContext->OMSetDepthStencilState(depthStencilStateRef.get(), 0 );

        pImmediateContext->OMSetRenderTargets( 1, &pRenderTargetViewRef, pDepthStencilViewRef.get() );
        float ClearColor[4] = {1.0f, 0.0f, 1.0f, 1.0f }; // red, green, blue, alpha
        pImmediateContext->ClearRenderTargetView( pRenderTargetViewRef.get(), ClearColor );
        pImmediateContext->ClearDepthStencilView( pDepthStencilViewRef.get(), D3D11_CLEAR_DEPTH, 1.0f, 0 );
        pImmediateContext->RSSetState(pRasterStateRef.get());

        D3D11_VIEWPORT vp;
        vp.Width    = (FLOAT)TexDescr.Width;
        vp.Height   = (FLOAT)TexDescr.Height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        pImmediateContext->RSSetViewports( 1, &vp );

        pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        pImmediateContext->IASetIndexBuffer( pIndexBufferRef.get(), DXGI_FORMAT_R16_UINT, 0 );
        UINT stride = sizeof( KVert11 );
        UINT offset = 0;
        pImmediateContext->IASetVertexBuffers( 0, 1, &pVertexBufferRef, &stride, &offset );
        pImmediateContext->IASetInputLayout( pVertexLayoutRef.get() );
        pImmediateContext->VSSetShader( pVertexShaderRef.get(), NULL, 0 );
        pImmediateContext->PSSetShader( pPixelShaderRef.get(), NULL, 0 );
        unhPSSetShaderResources( pImmediateContext, 0, 1, &pShaderResView );
        pImmediateContext->PSSetSamplers( 0, 1, &pSamplerLinearRef );
        unhDrawIndexed( pImmediateContext, 6, 0, 0 );

        //Save texture to file
        hr = D3DX11SaveTextureToFileW_( pImmediateContext, pColorTexRef.get(), D3DX11_IFF_DDS, szFile );
        if (FAILED(hr))
        {
            g_pLog->Write(L"D3DX11SaveTextureToFileW() failed: %08X\n", hr );
        }
        hr = S_OK;
    }
    while( FALSE );


    //Restore prev state

    pImmediateContext->OMSetBlendState(prevBlendStateRef.get(), prevBlendFactor, sampleMask);

    pImmediateContext->OMSetDepthStencilState(prevDepthStencilStateRef.get(), stencilReference );

    pImmediateContext->IASetInputLayout( pPrevInputLayoutRef.get() );
    pImmediateContext->IASetVertexBuffers( 0, 1, &pPrevBertexBufferRef, &PrevVBStride, &PrevVBOffs );
    pImmediateContext->IASetIndexBuffer( pPrevIndexBufferRef.get(), PrevIBFormat, IBOffset );
    pImmediateContext->IASetPrimitiveTopology( PrevPrimTopology );
    pImmediateContext->OMSetRenderTargets( 1, &pPrevRendTargetRef, pPrevDepthStencilRef.get() );
    pImmediateContext->RSSetViewports( PrevViewPortsCnt, &PrevViewPorts[0] );
    pImmediateContext->RSSetState( pPrevRasterizerStateRef.get() );
    pImmediateContext->VSSetShader( pPrevVSRef.get(), &PrevVSClassInstRefVec, VSNumClassInstances );
    pImmediateContext->PSSetShader( pPrevPSRef.get(), &PrevPSClassInstRefVec, PSNumClassInstances );
    unhPSSetShaderResources( pImmediateContext,  0, 1, &pPrevSRVRef );

    return hr;
}





HRESULT KRipper11::SaveTexture2File( 
    const wchar_t* szFile, 
    ID3D11DeviceContext* pDevCont, 
    ID3D11ShaderResourceView* pSRV
    )
{
    DumpShaderResourceView( pSRV );
/*        
    ID3D11Resource* pTexture = NULL;
    pSRV->GetResource( &pTexture );
    hr = D3DX11SaveTextureToFileW_( pDevCont, pTexture, D3DX11_IFF_DDS, szFile );
    SAFE_RELEASE( pTexture );
*/        
    HRESULT  hr = SaveTexture2FileMain( szFile, pDevCont, pSRV );
    return hr;
}

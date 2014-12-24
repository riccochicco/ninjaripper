#pragma once


//-----------------------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

HRESULT SaveTexture( 
    const wchar_t* szFile, 
    ID3D11DeviceContext* pDevCont, 
    ID3D11ShaderResourceView* pRes 
    );

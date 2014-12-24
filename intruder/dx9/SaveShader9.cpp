
#include "PreComp.h"
#include "KRipper9.h"


HRESULT KRipper9::SavePixelShader2File(
    const wchar_t* szFile, 
    IDirect3DDevice9* pDev, 
    IDirect3DPixelShader9* pPS 
)
{

    UINT    DataSize=0;
    void    *pData = NULL;
    ID3DXBuffer *DXBuffer = NULL;
    FILE*    fOutFile = NULL;
    HRESULT foo;

    do{
        foo = pPS->GetFunction( 0, &DataSize );
        if( FAILED(foo) ){
            g_pLog->Write( L"IDirect3DPixelShader9()::GetFunction Error: 0x%08X\n", foo );
            break;
        }

        pData = new BYTE[ DataSize ];
        if( !pData ){
            g_pLog->Write( L"Save pixel shader. Malloc Error\n" );
            break;
        }

        foo = pPS->GetFunction( pData, &DataSize );
        if( FAILED( foo ) ){
            g_pLog->Write( L"IDirect3DPixelShader9::GetFunction Error: 0x%08X\n", foo );
            break;
        }

        foo = D3DXDisassembleShader_( (DWORD*)pData, FALSE, 0, &DXBuffer );
        if( FAILED( foo ) ){
            g_pLog->Write( L"D3DXDisassembleShader Error: 0x%08X\n", foo );
            break;
        }
        delete[] pData;

        errno_t Err = _wfopen_s( &fOutFile, szFile, L"w" );
        if( Err ){
            g_pLog->Write( L"Can't Open File: %s", szFile );
            break;
        }
        fprintf( fOutFile, "%s", DXBuffer->GetBufferPointer() );
        fclose( fOutFile );
        DXBuffer->Release();

        foo = S_OK;
    }
    while( FALSE );

    return foo;
}


HRESULT KRipper9::SaveVertexShader2File( 
    const wchar_t* szFile, 
    IDirect3DDevice9* pDev, 
    IDirect3DVertexShader9* pVsh 
    )
{
    UINT    DataSize=0;
    void    *pData = NULL;
    ID3DXBuffer *DXBuffer = NULL;
    FILE*    fOutFile = NULL;
    HRESULT foo;

    do{
        foo = pVsh->GetFunction( 0, &DataSize );
        if( FAILED(foo) ){
            g_pLog->Write( L"IDirect3DVertexShader9()::GetFunction Error: 0x%08X\n", foo );
            break;
        }
        
        pData = new BYTE[ DataSize ];
        if( !pData ){
            g_pLog->Write( L"Save vertex shader. Malloc Error\n" );
            break;
        }

        foo = pVsh->GetFunction( pData, &DataSize );
        if( FAILED( foo ) ){
            g_pLog->Write( L"IDirect3DVertexShader9::GetFunction Error: 0x%08X\n", foo );
            break;
        }

        foo = D3DXDisassembleShader_( (DWORD*)pData, FALSE, 0, &DXBuffer );
        if( FAILED( foo ) ){
            g_pLog->Write( L"D3DXDisassembleShader Error: 0x%08X\n", foo );
            break;
        }
        delete[] pData;

        errno_t Err = _wfopen_s( &fOutFile, szFile, L"w" );
        if( Err ){
            g_pLog->Write( L"Can't Open File: %s", szFile );
            break;
        }
        fprintf( fOutFile, "%s", DXBuffer->GetBufferPointer() );
        fclose( fOutFile );
        DXBuffer->Release();

        foo = S_OK;
    }
    while( FALSE );

    return foo;

}




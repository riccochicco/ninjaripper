
#include "PreComp.h"


void* GetMethodAddr( void* Table, DWORD idx ){
    size_t** ppVtbl = (size_t**)Table;
    size_t*  pVtbl = (size_t*)*ppVtbl;
    return (void*)pVtbl[ idx ];
}


std::wstring StringToWString( const std::string &s )
{
    std::wstring wsTmp(s.begin(), s.end());
    return wsTmp;
}


void StrCopy( char* pDst, DWORD BufSize, const char* pSrc ){
    
    ZeroMemory( pDst, BufSize );

    size_t Len = strlen( pSrc );
    if( Len > BufSize ){
        Len = BufSize - 1;
    }
    memcpy( pDst, pSrc, Len );
}


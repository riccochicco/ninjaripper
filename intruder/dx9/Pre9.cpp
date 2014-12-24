
#include "PreComp.h"
#include "KRipper9.h"


KRipper9* Create_KRipper9(  HINSTANCE hD3D9 ){
    return KRipper9::Create( hD3D9 );
}


void Delete_KRipper9( KRipper9* & p ){
    KRipper9::Delete( p );
}

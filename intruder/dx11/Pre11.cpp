
#include "PreComp.h"
#include "KRipper11.h"


KRipper11* Create_KRipper11( HINSTANCE hD3D11 ){
    return KRipper11::Create( hD3D11 );
}


void Delete_KRipper11( KRipper11* & p ){
    KRipper11::Delete( p );
}

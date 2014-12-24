
#include "PreComp.h"
#include "KRipper8.h"


KRipper8* Create_KRipper8(  HINSTANCE hD3D8 ){
    return KRipper8::Create( hD3D8 );
}


void Delete_KRipper8( KRipper8* & p ){
    KRipper8::Delete( p );
}

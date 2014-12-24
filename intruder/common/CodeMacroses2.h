#pragma once


//Pre-Function code macros es with prototypes

#define PREGEN_0( FuncName ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked()\
    );\
    return stub_0; \
}\
HRESULT _##FuncName (PFN_##FuncName);



#define PREGEN_1( FuncName, Param0 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ] \
    );\
    return stub_1; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0);



#define PREGEN_2( FuncName, Param0, Param1 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ] \
    );\
    return stub_2; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1);



#define PREGEN_3( FuncName, Param0, Param1, Param2 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ] \
    );\
    return stub_3; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2);




#define PREGEN_4( FuncName, Param0, Param1, Param2, Param3 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ] \
    );\
    return stub_4; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3);



#define PREGEN_5( FuncName, Param0, Param1, Param2, Param3, Param4 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ] \
    );\
    return stub_5; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4);



#define PREGEN_6( FuncName, Param0, Param1, Param2, Param3, Param4, Param5 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ] \
    );\
    return stub_6; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5);



#define PREGEN_7( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ] \
    );\
    return stub_7; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6);



#define PREGEN_8( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ] \
    );\
    return stub_8; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7);




#define PREGEN_9( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ] \
    );\
    return stub_9; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8);




#define PREGEN_10( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ] \
    );\
    return stub_10; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9);




#define PREGEN_11( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ] \
    );\
    return stub_11; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10);



#define PREGEN_12( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ], \
    (##Param11)pEntry->parameters[ 11 ] \
    );\
    return stub_12; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10,##Param11);



#define PREGEN_13( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ], \
    (##Param11)pEntry->parameters[ 11 ] \
    (##Param12)pEntry->parameters[ 12 ] \
    );\
    return stub_13; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10,##Param11,##Param12);



#define PREGEN_14( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ], \
    (##Param11)pEntry->parameters[ 11 ], \
    (##Param12)pEntry->parameters[ 12 ], \
    (##Param13)pEntry->parameters[ 13 ] \
    );\
    return stub_14; \
}\
HRESULT _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10,##Param11,##Param12,##Param13);




//////////////////////////////////////////////////////////////////////////
//VOID return Pre-Function code macroses and prototypes
//////////////////////////////////////////////////////////////////////////

#define VVPREGEN_0( FuncName ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked()\
    );\
    return stub_0; \
}\
VOID _##FuncName (PFN_##FuncName);



#define VPREGEN_1( FuncName, Param0 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ]\
    );\
    return stub_1; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0);



#define VPREGEN_2( FuncName, Param0, Param1 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ] \
    );\
    return stub_2; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1);




#define VPREGEN_3( FuncName, Param0, Param1, Param2 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ] \
    );\
    return stub_3; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2);




#define VPREGEN_4( FuncName, Param0, Param1, Param2, Param3 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ] \
    );\
    return stub_4; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3);




#define VPREGEN_5( FuncName, Param0, Param1, Param2, Param3, Param4 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ] \
    );\
    return stub_5; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4);




#define VPREGEN_6( FuncName, Param0, Param1, Param2, Param3, Param4, Param5 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ] \
    );\
    return stub_6; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5);




#define VPREGEN_7( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ] \
    );\
    return stub_7; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6);




#define VPREGEN_8( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ] \
    );\
    return stub_8; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7);



#define VPREGEN_9( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ] \
    );\
    return stub_9; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8);



#define VPREGEN_10( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ] \
    );\
    return stub_10; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9);



#define VPREGEN_11( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ] \
    );\
    return stub_11; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10);



#define VPREGEN_12( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ], \
    (##Param11)pEntry->parameters[ 11 ] \
    );\
    return stub_12; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10,##Param11);



#define VPREGEN_13( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ], \
    (##Param11)pEntry->parameters[ 11 ] \
    (##Param12)pEntry->parameters[ 12 ] \
    );\
    return stub_13; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10,##Param11,##Param12);



#define VPREGEN_14( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ], \
    (##Param3)pEntry->parameters[ 3 ], \
    (##Param4)pEntry->parameters[ 4 ], \
    (##Param5)pEntry->parameters[ 5 ], \
    (##Param6)pEntry->parameters[ 6 ], \
    (##Param7)pEntry->parameters[ 7 ], \
    (##Param8)pEntry->parameters[ 8 ], \
    (##Param9)pEntry->parameters[ 9 ], \
    (##Param10)pEntry->parameters[ 10 ], \
    (##Param11)pEntry->parameters[ 11 ], \
    (##Param12)pEntry->parameters[ 12 ], \
    (##Param13)pEntry->parameters[ 13 ] \
    );\
    return stub_14; \
}\
VOID _##FuncName (PFN_##FuncName,##Param0,##Param1,##Param2,##Param3,##Param4,##Param5,##Param6,##Param7,##Param8,##Param9,##Param10,##Param11,##Param12,##Param13);


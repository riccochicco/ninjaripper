#pragma once



//Pre-Function code macroses

#define PRE_0( FuncName ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked()\
    );\
    return stub_0; \
}


#define PRE_1( FuncName, Param0 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ] \
    );\
    return stub_1; \
}


#define PRE_2( FuncName, Param0, Param1 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ] \
    );\
    return stub_2; \
}



#define PRE_3( FuncName, Param0, Param1, Param2 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    pEntry->eax = (REGTYPE)this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ] \
    );\
    return stub_3; \
}



#define PRE_4( FuncName, Param0, Param1, Param2, Param3 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_5( FuncName, Param0, Param1, Param2, Param3, Param4 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_6( FuncName, Param0, Param1, Param2, Param3, Param4, Param5 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_7( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_8( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_9( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_10( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_11( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}


#define PRE_12( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define PRE_13( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}


#define PRE_14( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}




///////////////////////////////////////////////////////////////////////////////





//VOID return Pre-Function code macroses


#define VVPRE_0( FuncName ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked()\
    );\
    return stub_0; \
}


#define VPRE_1( FuncName, Param0 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ]\
    );\
    return stub_1; \
}


#define VPRE_2( FuncName, Param0, Param1 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ] \
    );\
    return stub_2; \
}



#define VPRE_3( FuncName, Param0, Param1, Param2 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
{\
    this_->_##FuncName\
    (\
    (PFN_##FuncName)pHook->GetUnhooked(),\
    (##Param0)pEntry->parameters[ 0 ], \
    (##Param1)pEntry->parameters[ 1 ], \
    (##Param2)pEntry->parameters[ 2 ] \
    );\
    return stub_3; \
}



#define VPRE_4( FuncName, Param0, Param1, Param2, Param3 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_5( FuncName, Param0, Param1, Param2, Param3, Param4 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_6( FuncName, Param0, Param1, Param2, Param3, Param4, Param5 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_7( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_8( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_9( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_10( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_11( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}


#define VPRE_12( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}



#define VPRE_13( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}


#define VPRE_14( FuncName, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) static LPVOID Pre_##FuncName( SPROXYENTRYSTRUCT* pEntry, KHOOK* pHook )\
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
}

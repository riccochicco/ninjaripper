#pragma once


class KHookMgr;

class KHook
{

private:
    size_t RefCnt;

    LPCVOID    addr;//Target function address
    LPCVOID    stub;//Handler
    DWORD    code_len;    //Code Len before JMP targ+5
    BYTE    exec_buf[32];//JMP buffer
    LPCVOID    exec;//Unhooked function start

    //Access only through KHookMgr
    KHook( LPCVOID, LPCVOID );
    virtual ~KHook();

    friend class KHookMgr;

public:
    void SetHook();
    void Unhook();

    LPCVOID GetTargAddr()const{
        return addr;
    }
    
    LPCVOID GetStubAddr()const{
        return stub;
    }
    
    LPCVOID GetUnhookedFunc()const{
        return exec;
    }

    void CheckHookConflict( LPCVOID, LPCTSTR );


};

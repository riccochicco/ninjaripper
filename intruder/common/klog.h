#pragma once
#include <stdio.h>    //for FILE*


class KLog{
    FILE    *f;
    void Logger( const wchar_t* fmt, va_list argptr );
    CRITICAL_SECTION cs;

public:
    KLog();
    ~KLog();

    int     Open( const wchar_t* szFile );
    void    Close();

    void    Write(const wchar_t*, ...);
    void    WriteTime();
};


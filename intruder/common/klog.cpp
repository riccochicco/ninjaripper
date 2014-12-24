
#include "PreComp.h"
#include "klog.h"


KLog::KLog():
f( NULL )
{
    ::InitializeCriticalSection(&cs);
}

KLog::~KLog()
{
    ::DeleteCriticalSection(&cs);
}


int KLog::Open( const wchar_t* szFileName ){
    errno_t foo = _wfopen_s( &f, szFileName, L"wb" );
    if( foo ){
        return -1;
    }

    fwrite( "\xFF\xFE", 2, 1, f );//write Unicode Little Endian marker to file
    return 0;
}


void KLog::Close(){
    fclose(f);
}


void KLog::WriteTime(){
    wchar_t *day[]={TEXT("Sun"), TEXT("Mon"), TEXT("Tue"), TEXT("Wed"), TEXT("Thu"), TEXT("Fri"), TEXT("Sat")};
    wchar_t *month[]={TEXT("Jan"), TEXT("Feb"), TEXT("Mar"), TEXT("Apr"), TEXT("May"), TEXT("Jun"), TEXT("Jul"), TEXT("Aug"), TEXT("Sep"), TEXT("Oct"), TEXT("Nov"), TEXT("Dec")};

    SYSTEMTIME t;
    GetLocalTime(&t);
    Write(    TEXT("%s %s %d %d:%02d:%02d %d"), 
            day[t.wDayOfWeek],
            month[t.wMonth-1],
            t.wDay,
            t.wHour,
            t.wMinute, 
            t.wSecond,
            t.wYear
            );
}



void KLog::Write( const wchar_t* fmt, ...)
{
    ::EnterCriticalSection(&cs);

    va_list ap;
    va_start( ap, fmt );
    Logger( fmt, ap );
    va_end( ap );

    ::LeaveCriticalSection(&cs);
}


void KLog::Logger( const wchar_t* fmt, va_list argptr ){
    wchar_t buffer[1024] = {0};
    wchar_t Buf2[2048] = {0};
        
    vswprintf( buffer, 1024, fmt, argptr );

    size_t DstIdx = 0;
    for( size_t i = 0; i < wcslen( buffer ); i++ ){
        if( buffer[ i ] != '\n' ){
            Buf2[ DstIdx ] = buffer[ i ];
        }
        else{
            Buf2 [ DstIdx ] = '\r';
            DstIdx++;
            Buf2 [DstIdx ] = '\n';
        }
        DstIdx++;
    }



    fwrite( Buf2, 2, wcslen( Buf2 ), f );
    //    fwrite( cr, 2, wcslen(cr), f );  //write CR
    fflush( f );
}



#pragma once

#ifndef RELEASEFINAL
#define SET_CONS_CONTEXT( i_context )  if ( gConsole ) gConsole->SetContext( i_context );
void ConsolePrintF( int i_flags, const char* fmt ... );
void ConsolePrintF( const char* fmt ... );
void ConsolePrintFErr( const char* fmt ... );
void ConsolePrintFWarn( const char* fmt ... );
#else
#define SET_CONS_CONTEXT( i_context )  
#define ConsolePrintF(flags, format, ...) do { (void)sizeof(flags); (void)sizeof(format); } while(0)
#define ConsolePrintFErr(format, ...) do { (void)sizeof(format); } while(0)
#define ConsolePrintFWarn(format, ...) do { (void)sizeof(format); } while(0)
#endif

#include "SexyApp.h"

class CommandConsole;

enum EConsoleLogType
{
    CONS_LOG_NONE      = 0,
    CONS_LOG_DISPLAY   = 1 << 0,
    CONS_LOG_WARN      = 1 << 1,
    CONS_LOG_ERR       = 1 << 2
};

class ConsoleApp : public Sexy::SexyApp
{
public:
	CommandConsole* m_console;

public:
	ConsoleApp();
	virtual ~ConsoleApp();

    void ConsolePrintf( const char* fmt ... );
    void ConsolePrintf( int i_flags, const char* fmt ... );

private:
    typedef Sexy::SexyApp SuperClass;

	// SexyAppBase
	//////////////////////////////////////////////////////////////////////
    bool DebugKeyDown(int i_key);
};

extern ConsoleApp* gConsoleApp;
extern CommandConsole* gConsole;



#pragma once

#include "Precompile.h"

//TODO: 
//#define CONS_DEF( cmd, desc, ... )  AddConsoleAction( i_cmd, i_params, cmd, desc, ##__VA_ARGS__ )								// where ##__VA_ARGS__ are the arguments (optional args would have a '+' suffix or something)
//#define CONS_DEF_KEY( key, context, cmd, desc )				AddConsoleAction( i_cmd, i_params, context, cmd, desc, 0 )		// map keyboard input
//#define CONS_DEF_ARG_KEY( key, context, cmd, desc, count )	AddConsoleAction( i_cmd, i_params, context, cmd, desc, count )

// Not sure why we're bothering with the delegate stuff if we're defining an explicit listener class. We should probably just update the console to just use that instead.

#define CONS_DEF( context, cmd, desc )				AddConsoleAction( i_cmd, i_params, context, cmd, desc, 0, false )
#define CONS_DEF_BTN( context, cmd, desc )			AddConsoleAction( i_cmd, i_params, context, cmd, desc, 0, true )
#define CONS_DEF_ARG( context, cmd, desc, count )	AddConsoleAction( i_cmd, i_params, context, cmd, desc, count, false )

typedef std::vector<SexyString> CCStringVector;


bool ConsoleEnsureArgs( const CCStringVector& i_params, int i_count );

class ConsoleListener
{
public:
    ConsoleListener() :m_consoleDefineMode( false ), m_consoleEchoOn( true ) {}


    void DefineConsoleCommands();

    virtual void HandleConsoleCommand(const SexyString& i_cmd, const CCStringVector& i_params) = 0;

	bool GetConsoleEchoOn() const						{ return m_consoleEchoOn; }
	void SetConsoleEchoOn(bool val)						{ m_consoleEchoOn = val; }

protected:
    bool AddConsoleAction( const SexyString& i_passedCmd, const CCStringVector& i_passedParams, int i_context, const SexyString& i_cmd, const SexyString& i_desc, int i_argCount, bool i_addButton );
    bool AddConsoleAction( const SexyString& i_passedCmd, const CCStringVector& i_passedParams, int i_context, const SexyString& i_cmd, const SexyString& i_desc, bool i_addButton )
    { return AddConsoleAction( i_passedCmd, i_passedParams, i_context, i_cmd, i_desc, 0, i_addButton ); }


private:
    bool m_consoleDefineMode;
	bool m_consoleEchoOn;
};

/* SAMPLE USAGE:
void LawnApp::HandleConsoleCommand(const SexyString& i_cmd, const CCStringVector& i_params)
{
    if ( CONS_DEF( CONSOLE_APP, L"jump_list_levels",	        L"List jump_level aliases"))                                                                ConsolePrintF( ToString( gLawnApp->GetLevelAliases() ).c_str() );
    else if ( CONS_DEF_ARG( CONSOLE_APP, L"jump_level",		    L"Jump to level. Arg is #-#, c#, f#, or f#-#", 1 ) )                                        TryJumpStartLevel( i_params[ 0 ] );
    else if ( CONS_DEF_ARG( CONSOLE_APP, L"jump_start",		    L"Jump start level. Arg1=Level, Arg2=SimSeconds", 2 ) )                                     TryJumpStartLevel( i_params[ 0 ], sexyatof( i_params[ 1 ].c_str() ) );
    else if ( CONS_DEF_ARG( CONSOLE_APP, L"jump_start_fill",	L"Jump start and fill level. Arg1=Level, Arg2=SimSeconds, Arg3=FillToCol", 3 ) )    TryJumpStartLevel( i_params[ 0 ], sexyatof( i_params[ 1 ].c_str() ), sexyatoi( i_params[ 2 ].c_str() ) );
}
*/

#pragma once

#include "Precompile.h"

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/EditListener.h"
#include "SexyAppFramework/EditWidget.h"
#include "extern/FastDelegate.h"
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/KeyCodes.h"
#include "SexyAppFramework/CurvedVal.h"
#include <map>

//TODO: 
//#define CONS_DEF( cmd, desc, ... )  ConsoleAction( i_cmd, i_params, cmd, desc, ##__VA_ARGS__ )								// where ##__VA_ARGS__ are the arguments (optional args would have a '+' suffix or something)
//#define CONS_DEF_KEY( key, context, cmd, desc )				ConsoleAction( i_cmd, i_params, context, cmd, desc, 0 )		// map keyboard input

// support input
//#define CONS_DEF_ARG_KEY( key, context, cmd, desc, count )	ConsoleAction( i_cmd, i_params, context, cmd, desc, count )

// support multiple contexts

typedef std::vector<SexyString> CCStringVector;

namespace Sexy
{
	class Graphics;
	class MemoryImage;
	class DeviceImage;
	class SysFont;
	class Font;
}

typedef std::vector<SexyString> CCStringVector;

typedef fastdelegate::FastDelegate2<const SexyString&, const CCStringVector&> ConsoleCallback;
typedef std::map<SexyString, ConsoleCallback> CommandCallbackMap;
typedef std::map<SexyString, bool> StrBoolMap;
typedef std::map<SexyString, SexyString> CCStrStrMap;

struct ConsoleAction
{
    ConsoleCallback m_callback;
    SexyString m_description;
    bool m_hasBtn;
};

typedef std::map<SexyString, ConsoleAction> ConsoleActionMap;

struct ConsoleContext
{
    ConsoleActionMap    m_actions;
	int					m_contextNum;		
};

class CommandConsole : public Sexy::Widget, public Sexy::EditListener, public Sexy::ButtonListener
{
    public:
        enum ELineType
        {
            LINETYPE_NORMAL,
            LINETYPE_WARNING,
            LINETYPE_ERROR,
        };

	protected:
        const static int BTN_WIDGET_START_ID = 1000;

        class CommandConsoleEdit : public Sexy::EditWidget
        {
            typedef Sexy::EditWidget SuperClass;
        public:

            CommandConsole*	m_console;

        protected:

            virtual void    KeyDown(Sexy::KeyCode i_key);
            virtual void	ProcessKey(Sexy::KeyCode i_key, SexyChar i_char);

        public:

            CommandConsoleEdit(int i_id, Sexy::EditListener* i_editListener) : Sexy::EditWidget(i_id, i_editListener) {;}
            virtual ~CommandConsoleEdit() {;}

        };

        typedef Sexy::Widget SuperClass;

		friend class CommandConsoleEdit;

        struct DrawScreenText
        {
            uint m_textIdx;
            int m_updatesRemaining;
        };

		std::vector<ConsoleContext>		m_context;
		CCStringVector					m_history;
		CCStringVector					m_displayLines;
		std::vector<int>				m_displayLinesHeight;
    
        //PVZ2_CHINESE_BEGIN
        Font*                           m_font;
#ifdef WIDGETS_USE_PRIMETEXT
		PrimeTypeface*					m_primeFont;
#endif
        //PVZ2_CHINESE_END
		CommandConsoleEdit*				m_edit;
		Widget*							m_lastFocusWidget;
        Sexy::CurvedVal                 m_hideYPct;
        bool                            m_hidden;
        int								m_currentContext;
        int								m_startIndex;
		int								m_historyIndex;			
        int                             m_curCompletionIdx;
        bool                            m_displayingCompletion;
		bool							m_needDeleteFont;
        int                             m_completionHelpLength;
		int								m_updateCnt;
        int                             m_baseY;
        int                             m_drawScreenTextDur;
        int                             m_drawScreenTextFadeAt;
        std::vector<DrawScreenText>     m_drawScreenTexts;
        int                             m_windowHeight;
        bool                            m_autosetSize;

        std::vector<Sexy::ButtonWidget*>      m_btnWidgets;


	protected:
		
        void    RefreshSize( bool i_forced = false );
        void    RefreshButtons();
        void    RefreshButtonPositions();
        void    ClearButtons();
		void	AddHistory(const SexyString& str, bool mod_index);
        bool	EditKeyCodeDown(Sexy::KeyCode key);
		void	EditProcessKey(Sexy::KeyCode key);
		void	DoHelp();
		ConsoleContext* FindCurrentContext();
		int		GetDisplayLineHeight(int i, Sexy::Graphics* g);
        void    ResetCompletion();
        void    GetAllCompletionStrings( CCStringVector& i_completionStrings );

	public:

		CommandConsole(PrimeTypeface* font=NULL);
		virtual ~CommandConsole();

        void    AddLine(const SexyString& str, int num_nl = 0, bool i_doDrawText = false)             { addLineHelper( str, LINETYPE_NORMAL, num_nl, i_doDrawText ); }
        void    AddLineWarn(const SexyString& str, int num_nl = 0, bool i_doDrawText = true)          { addLineHelper( str, LINETYPE_WARNING, num_nl, i_doDrawText ); }
        void    AddLineErr(const SexyString& str, int num_nl = 0, bool i_doDrawText = true)           { addLineHelper( str, LINETYPE_ERROR, num_nl, i_doDrawText ); }

		void	AddCommand(int context, const SexyString& command, const SexyString& desc, bool i_addButton, ConsoleCallback callback_func);
		void	Hide(bool should_hide);
		void	SetContext(int context);
		void	EraseContext(int context);
	
        bool    GetHidden() const 		                        { return m_hidden; }
		void	Update();
    
        //PVZ2_CHINESE_BEGIN
        void    SetFont(Font* i_font);
#ifdef WIDGETS_USE_PRIMETEXT
		void	SetFont( PrimeTypeface* i_font );
#endif
        //PVZ2_CHINESE_END

        void    SetY( int i_y )                                { m_baseY = i_y; }

        void    DoNextCompletion( bool i_doReverseCompletion = false );
        void    UpdateCompletionHelp();
        void    ClearLastCompletionHelp();

        int     GetCurrentContext() const 		{ return m_currentContext; }
		
		void	ShowError(const SexyString& msg);
		void	Draw(Sexy::Graphics* g);
//PVZ2_CHINESE_BEGIN
        void    DrawWithFont(Sexy::Graphics* g);
#ifdef WIDGETS_USE_PRIMETEXT
        void    DrawWithPrimeFont(Sexy::Graphics* g);
#endif
//PVZ2_CHINESE_END
		void	EditWidgetText(int id, const SexyString& str);
		bool	AllowChar(int i_id, SexyChar i_char)			{return (i_char != '`') && (i_char != '\\'); 
                   // #pragma unused(i_id)
        }

		void	ClearFocusWidget()								{m_lastFocusWidget = NULL;}
		Widget* GetFocusWidget()								{return m_lastFocusWidget;}

    protected:
        void	addLineHelper(const SexyString& str, ELineType i_lineType = LINETYPE_NORMAL, int num_nl = 0, bool i_doDrawText = false);

    // ButtonListener
    //////////////////////////////////////////////////////////////////////
    public:
        virtual void			ButtonDepress(int i_id);

};

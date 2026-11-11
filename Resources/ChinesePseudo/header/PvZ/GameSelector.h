#ifndef __GAMESELECTOR_H__
#define __GAMESELECTOR_H__

#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/CheckboxListener.h"
#include "ConsoleListener.h"

#include "PvZ2IDs.h"
#include "GameNotify.h"


class LawnApp;
class TypingCheck;
class TodParticleSystem;
class ToolTipWidget;
class NewLawnButton;
class GameButton;
class StretchableGameButton;

namespace Sexy
{
	class ButtonWidget;
	class DialogButton;
}

enum SelectorAnimState
{
	SELECTOR_OPEN,
	SELECTOR_NEW_USER,
	SELECTOR_SHOW_SIGN,
	SELECTOR_IDLE,
    SELECTOR_PAMTEST,
    SELECTOR_TUTORIAL,
    SELECTOR_WAITINGTOSTART,
};


class GameSelector : public Sexy::Widget, public Sexy::ButtonListener
{
private:
	LawnApp* m_app;

	GameButton* m_optionsButton;
	GameButton* m_quitButton;
	GameButton* m_changeUserButton;
	GameButton* m_startGameButton;
	GameButton* m_moreGamesButton;
    
	class TitleLogoAnimation* m_logoAnimation;

	SelectorAnimState m_selectorState;

	bool m_loading;

#ifndef WANTS_CHEATS_DISABLED
	uint32 CalcAndDisplayDiscCost(Sexy::Graphics* i_g, const std::vector<std::string>& i_groupNames, const std::string& i_groupingName, const int i_xOffset, int &io_yOffset);
	bool m_showMemoryStuff;
#endif // WANTS_CHEATS_DISABLED

public:
	GameSelector(LawnApp* i_app);
	virtual ~GameSelector();
    
	virtual void Draw(Sexy::Graphics* g);

	virtual void Update();
	virtual void ButtonMouseEnter(int i_id);
	virtual void ButtonPress(int i_id, int i_clickCount);
	virtual void ButtonDepress(int i_id);
	virtual void TouchEnded(Sexy::Touch* i_touch);
    virtual void GotFocus();

	void TrackButton(class DialogButton *i_button, const SexyChar *i_trackName, float i_offsetX, float i_offsetY);

	void ClickedWorldMap();
	void ClickedMoreGames();

    void OnCreateUserDialogDone();

	void SetUIEnabled(bool i_enabled);
};

#endif //__GAMESELECTOR_H__

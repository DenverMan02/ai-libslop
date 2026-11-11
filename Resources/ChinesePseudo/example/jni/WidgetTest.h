#ifndef WIDGETTEST_H_
#define WIDGETTEST_H_

#include "Widget.h"
#include "LawnApp.h"

#include "SingletonExtern.h"

enum CheatButtonId
{
    CheatButtonTest,
    CheatButtonTestLevel
};

class WidgetTestCheatMenu : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    WidgetTestCheatMenu();

    void AddCheatButton(CheatButtonId i_id, const SexyString& i_buttonName);

	virtual void ButtonPress(int i_id) {}
	virtual void ButtonDepress(int i_id);
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) {}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) {}
private:
    std::vector<PVZ2UIButton *> m_cheatButtons;
};

class WidgetTest : public Sexy::Widget
{
public:
    WidgetTest();
    ~WidgetTest();

    virtual void Draw(Sexy::Graphics *g) override;
    virtual void Update() override;

    virtual void TouchEnded(const Sexy::Touch &touch) override;
private:
    bool m_init = false;
    bool m_menuOpen = false;
    WidgetTestCheatMenu *m_cheatMenuWidget;
    ScrollWidget *m_cheatScrollWidget;
};

#endif /* WIDGETTEST_H_ */

#include "WidgetTest.h"
#include "Board.h"
#include "UIHelper.h"
#include "PVZCheats.h"

//CachedUIResourcePtr<Image> cheat_ui_test("IMAGE_UI_CHEATMENU_ACTION");
CachedUIResourcePtr<Image> cheat_ui_test("IMAGE_UI_CARDS_STORE_GEM");
CachedUIResourcePtr<Image> cheat_ui_button("IMAGE_UI_GENERIC_PURPLEBUTTON");
CachedUIResourcePtr<Image> cheat_ui_button_pressed("IMAGE_UI_GENERIC_PURPLEBUTTON_DOWN");

WidgetTestCheatMenu::WidgetTestCheatMenu()
{
    Resize(gSexyApp->mWidth - 400, 0, 400, 2000);

    AddCheatButton(CheatButtonTest, L"Test");
    AddCheatButton(CheatButtonTestLevel, L"Load test level");

    //ButtonWidget *test = new ButtonWidget(0, this);
    //test->Resize(0, 0, 400, 40);
    //test->SetFont(FONT_EDITOR);
    //HACK to deal with empty string constructed in libSrc
    //new (&test->mLabel) std::wstring(L"Test");
    //AddWidget(test);
    //m_cheatButtons.push_back(test);
}

void WidgetTestCheatMenu::ButtonDepress(int i_id)
{
    if (i_id == CheatButtonTest) {
        if (gLawnApp->m_board)
            gLawnApp->m_board->RandFillToCol(gLawnApp->m_board->m_gridSizeX);

        if (gLawnApp->m_board) {
            //
        }

    } else if (i_id == CheatButtonTestLevel) {
        gGameStateMgr->StartLevel(g_strCheatwldName, "Sandbox5");
    }
}

void WidgetTestCheatMenu::AddCheatButton(CheatButtonId i_id, const SexyString& i_buttonName)
{
    PVZ2UIButton *button = new PVZ2UIButton(i_id, this, i_buttonName);
    button->Resize(0, 80 * m_cheatButtons.size(), 400, 80);
    button->SetFont(FONT_EDITOR);
    button->SetDialogStates(PVZ2UIImage(cheat_ui_button, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE),
        PVZ2UIImage(cheat_ui_button_pressed, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
    AddWidget(button);
    m_cheatButtons.push_back(button);
    Resize(gSexyApp->mWidth - 400, 0, 400, 80 * m_cheatButtons.size());
}

WidgetTest::WidgetTest()
{
    Resize(0, 0, 64, 64);
    mZOrder = 10000000;
    mClip = false;
    //mMouseVisible = false;
    gSexyApp->mWidgetManager->AddWidget(this);
}

WidgetTest::~WidgetTest()
{
    RemoveAllWidgets(true, true);
    //m_cheatButtons, m_cheatMenuWidget, m_cheatScrollWidget
}

void WidgetTest::Draw(Sexy::Graphics *g)
{
    Widget::Draw(g);
    if (!this->m_menuOpen)
        g->DrawRect(0, 0, 64, 64);
    else
        g->FillRect(0, 0, 64, 64);

    if (cheat_ui_test.IsValid())
        g->DrawImage(cheat_ui_test, 20, 20);

    //if (gLawnApp->m_board) {
    //    for (int i = 0; i < gLawnApp->m_board->m_gridSizeX; ++i) {
    //        for (int j = 0; j < gLawnApp->m_board->m_gridSizeY; ++j) {
    //            Plant *plant = gLawnApp->m_board->GetPlantAt(i, j);
    //            if (plant) {
    //                SexyStringStream wss;
    //                wss << "Health " << plant->GetMaxHealth() << "/" << plant->GetHealth();
    //                Sexy::Point pos(plant->GetPosition2D().x, plant->GetPosition2D().y);
    //                gLawnApp->m_board->TranslateBoardPositionToScreenPosition(pos);
    //                pos.mX += gLawnApp->m_board->mX;
    //                pos.mY += gLawnApp->m_board->mY;
    //                WriteWordInRect(g, wss.str(), Rect(pos.mX, pos.mY, 200, 200),
    //                    FONT_EDITOR, Sexy::Color::White, DS_ALIGN_CENTER, false);
    //            }
    //        }
    //    }
    //}
}

void WidgetTest::Update()
{
    Widget::Update();
}

void WidgetTest::TouchEnded(const Sexy::Touch &touch)
{
    Widget::TouchEnded(touch);
    if (!m_init && gLawnApp->IsInited()) {
        m_cheatMenuWidget = new WidgetTestCheatMenu();
        m_cheatScrollWidget = new ScrollWidget();
        m_cheatScrollWidget->Resize(gSexyApp->mWidth - 400, 0, 400, gSexyApp->mHeight);
        //m_cheatScrollWidget->EnableBackgroundFill(true);
        m_cheatScrollWidget->SetScrollMode(ScrollWidget::ScrollMode::SCROLL_VERTICAL);
        m_cheatScrollWidget->EnableBounce(true);
        m_cheatScrollWidget->EnableIndicators(cheat_ui_test);
        m_cheatScrollWidget->AddWidget(m_cheatMenuWidget);
        m_init = true;
    } 
    if (m_init) {
        this->m_menuOpen = !this->m_menuOpen;
        if (this->m_menuOpen) {
            AddWidget(m_cheatScrollWidget);
        } else {
            RemoveWidget(m_cheatScrollWidget);
        }
    }
}

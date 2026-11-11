//
//  WidgetButtonList.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WidgetButtonList__
#define __PlantsVersusZombies2__WidgetButtonList__

#include <functional>
#include <utility>
#include <vector>

#include "SexyString.h"
#include "Widget.h"

class PVZ2UIButton;
class PVZ2UIImage;
namespace Sexy {
class ButtonListener;
class Graphics;
class PrimeTypeface;
}  // namespace Sexy

struct Widget_Button_Stats
{
public:
    Widget_Button_Stats(int width, int widthMax, int height, int horizBorder, int vertBorder, int buttonID, Sexy::PrimeTypeface* font, SexyString label);

    int mWidth;
    int mHeight;
    int mHorizBorder;
    int mVertBorder;
    int mButtonID;
    int mMaxWidth;
    Sexy::PrimeTypeface* mFont;
    SexyString mLabel;
};

class Widget_ButtonList : public Sexy::Widget
{
public:
    Widget_ButtonList();

    void AddButton(PVZ2UIButton* button, Sexy::ButtonListener* i_listener);
	using OnPressedCallback = std::function<void()>;
    void AddButton(PVZ2UIButton* button, OnPressedCallback&& i_onPressed, Sexy::ButtonListener* i_listener);

    void ReplaceButton(int i_buttonIdToReplace, PVZ2UIButton* i_button, OnPressedCallback&& i_onPressed, Sexy::ButtonListener* i_listener);
    void SetButtonCallback(PVZ2UIButton* i_button, OnPressedCallback&& i_onPressed);

	bool HasButton(int i_buttonID);
    PVZ2UIButton* GetButton(int i_buttonID);

	void DrawButtonsManually(Sexy::Graphics* i_g);
	void ClearButtons();

    int GetNextFreeButtonID();
    void SetNextFreeButtonID(int i);

    void DoLayout(int startX, int startY, int maxWidth, int maxHeight, int extraEndGapLength = 0);

    void ButtonDepress(int i_buttonID);

private:

    PVZ2UIButton* AddButton_Internal(PVZ2UIButton* button);

    int m_nextFreeButtonId;
    bool m_layoutDirty;
    bool m_isDrawing;

	std::vector<std::pair<PVZ2UIButton*, OnPressedCallback>> m_buttons;

    bool NormalizeFonts();
    void PerformLayout(int startX, int startY, int maxWidth, int maxHeight, int extraEndGapLength);

public:
    static PVZ2UIButton* Build_WidgetList_Button(Widget_Button_Stats& stats, const PVZ2UIImage& normalImage, const PVZ2UIImage& downImage);
    static PVZ2UIButton* Build_WidgetList_Button_Base(Widget_Button_Stats& stats);
};

#endif /* defined(__PlantsVersusZombies2__WidgetButtonList__) */

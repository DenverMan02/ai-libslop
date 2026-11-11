#ifndef UI_UNCHARTED_ENTRY_H
#define UI_UNCHARTED_ENTRY_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"
#include "RepeatUIComponent.h"
#include "functional"
#include "PVZ2UnchartedModeNetworkMgr.h"



enum UIunchartedTabEnum {
	UIUnchartedTab_Invalid = -1,
	UIUnchartedTab_1,
	UIUnchartedTab_2,
	UIUnchartedTab_3,
	UIUnchartedTab_4,
	UIUnchartedTab_5,
	UIUnchartedTab_Max,
};

namespace Message
{
	void UIUnchartedSelectTab(int index);
}

class UIUnchartedTab : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate1<int> TabCallback;

    UIUnchartedTab(int tabIndex, std::string prefixWorld, bool isSelected);
    virtual ~UIUnchartedTab();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitView(int tabIndex, std::string prefixWorld, bool isSelected);
    void SetCallback(TabCallback callback){ m_callback = callback; }

protected:
    void SelectTab(int index);


protected:
    int m_tabIndex;// tab index
    TabCallback m_callback;// click callback
    Image* m_selectImage;// select image
    Image* m_unselectImage;// unselect image
    std::string m_prefixWorld;
};

class UIUnchartedEntry : public UISingletonDialog<UIUnchartedEntry>, public Sexy::ScrollWidgetListener
{
public:
    UIUnchartedEntry();
    virtual ~UIUnchartedEntry();
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIUnchartedEntry"; }
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void Init();
    void InitTab();
	void onClickTab(int i_tabIndex);
	void DoClickTab(int tabIndex = 0);

	void RefreshThemeBackground(int tabIndex);
	void RefreshRewardsList(int tabIndex);
    void RefreshOtherUI(int i_tabIndex);
    void RefreshByPrefixWorld(int i_tabIndex);

	void LoadData();
	void CreateRewardContainer();

	void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;


private:
    bool m_gotoHard;
	int m_currentTab;// the current tab is focus
	PVZ2UIScrollingWidget* m_pScrollContent;
	Widget* m_pRewardListScrollPanel;
	UnchartedModeMainEntryData m_data;
};


#endif

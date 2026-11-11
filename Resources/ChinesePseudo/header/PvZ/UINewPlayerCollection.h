#ifndef UINewPlayerCollection_H_
#define UINewPlayerCollection_H_

#include "UIActivityCollection.h"
#include "UIEasyButtonWidget.h"


enum NewPlayerCollectionTab : int
{
    NPCT_START = 0,
    NPCT_Sign,
    NPCT_NoviceSevenDays,
    NPCT_DiscountShop,
    NPCT_PennyClassroom,
    NPCT_SpecialGift,

    NPCT_END
};

////////////////////////////////////////////////////////////////////////////

class UINewPlayerCollection : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    UINewPlayerCollection();
    virtual ~UINewPlayerCollection();

    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void CreateView();

    static bool CheckActivityOpenAtLeastOne();

private:
    NewPlayerCollectionTab GetTabByActivity(int i_id);
    int GetActivityByTab(NewPlayerCollectionTab i_tab);

    void SelectTab(int i_tab);
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void CheckTabButton(NewPlayerCollectionTab i_tab);

	void NotifyCloseDialog();

    std::map<NewPlayerCollectionTab, ActivityCollectionTabBase*> m_tabMap;
private:
    bool m_hasInitView;
    std::map<NewPlayerCollectionTab, int> m_activityList;
public:
    int m_currentTab;
    ActivityCollectionData m_cacheData;
};


class WorldMap_NewPlayerButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_NewPlayerButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_NewPlayerButton();
    virtual ~WorldMap_NewPlayerButton();

    virtual void Draw(Graphics* i_g) override;
    
    bool CheckVisibility(bool i_init = false);
    void OnClick();

    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

#endif

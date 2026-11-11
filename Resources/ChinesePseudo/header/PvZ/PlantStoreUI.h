/*
 * PlantStoreUI.h
 *
 *  Created on: 2014-8-28
 *      Author: jianglc
 */

#ifndef PLANTSTOREUI_H_
#define PLANTSTOREUI_H_

#include "Precompile.h"
#include "PVZ2UIButton.h"

enum PlantStoreUIButtonId
{
    PLANT_STORE_BUTTON_ID_CLOSE = 0,
    PLANT_STORE_SHOWLEAFGACHA   = 100,
    PLANT_STORE_REFRESH         = 101,
    PLANT_STORE_SHOWDANGERROOM  = 102,
};

enum PlantStoreUITabPanel
{
	STAR_TAB = 1,
    PLANT_TAB   ,
    LEAF_TAB    ,
    STONE_TAB
};

namespace Message
{
    void RecreatePlantStoreUICurrentPanel();
    void RefreshStoneStore();
}

class PlantStoreContentBar : public Widget
{
public:
	PlantStoreContentBar(Rect &i_rect, PlantStoreUITabPanel type, int i_contentSize, const std::string& i_worldName, int i_num);
    ~PlantStoreContentBar();
    //std::vector<class DailySignRewardContent*> m_contents;
    virtual void Draw(Graphics *i_g);

private:
    void	InitView();
    int		GetTotalStarNum();
    Image* GetCurrentTitleImage();
    int m_contentSize;
    std::string m_worldName;
    int m_starNum;
    int m_maxStarNum;
    int m_emptyStartX;
    int m_emptyNum;
};

class PlantStoreScrollPanel : public Widget
{
public:
	PlantStoreScrollPanel(PlantStoreUITabPanel i_tab,Rect &i_rect, int i_contentSize);
    ~PlantStoreScrollPanel();
    //std::vector<class DailySignRewardContent*> m_contents;
    virtual void Draw(Graphics *i_g);

private:
    void	InitView();
    int m_contentSize;
    PlantStoreUITabPanel m_type;
};

class PlantStoreUI : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
	PlantStoreUI();
    ~PlantStoreUI();

    virtual void ButtonDepress(int i_id);
    virtual void Update();
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void ToPanel(int i_tab);
    void RefreshStoneTab();
private:
    void InitView();
    void createPanel(PlantStoreUITabPanel i_tab);
    void RecreateCurrentPanel();
    void onItemPurchasedFromStore(class MagentoProductProps* i_props);

    void OnCloseDialog();
    void OnTutorialFinished();

	PVZ2UIScrollingWidget* m_scrollingWidget;
    PVZ2UIButton*           m_closeButton;
    PVZ2UIButton*           m_refreshButton;
    PVZ2UIButton*           m_showGetCurrentButton;
    std::vector<class PVZ2UIButton*>	m_tabButtons;
    PlantStoreUITabPanel m_currentPanel;
};


#endif /* PLANTSTOREUI_H_ */

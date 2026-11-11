//
//  FestivalEntranceUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-9.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FestivalEntranceUI__
#define __PlantsVersusZombies2__FestivalEntranceUI__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"
#include "MagentoService.h"
#include "PVZ2UIPlantCard.h"
#include "SettingsDialog.h"
#include "FestivalManager.h"

///////////

namespace Message
{
    void RefreshCurrentPlantList();
}

class GameFestivalPanel : public Widget
{
    virtual ~GameFestivalPanel();
    
    virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
public:
    int  m_nHeadHeight;
};

///////////

class WishPanel : public Widget
{
    virtual ~WishPanel();
    
    virtual void	Draw(Sexy::Graphics* i_g);
    
public:
    int  m_nHeadHeight;
};

///////////

class WishScrollPanel : public Widget, Sexy::ButtonListener
{
public:
	WishScrollPanel(Rect &i_rect, FestivalGameMode i_mode);
    virtual ~WishScrollPanel();
    
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    
    std::vector<class WishContent*> m_contents;
    
private:
    
    void	InitView();
    void    InitCurrentPlantNameList();
    void    RefreshCurrentPlantsList();
    bool    AddPlantDataIntoPlantList(std::string PlantName);
    
    void	SelectWishInPanel(int i_id);
    
    int     m_nLastSelect;
    FestivalGameMode m_eGameMode;
    std::vector<std::string>  m_PlantNameList;
};

////////////////////////

class FestivalEntranceUI : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
    
	FestivalEntranceUI(FestivalGameMode i_mode);
	virtual ~FestivalEntranceUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    void onFinishBuyChallengeCount(const bool& i_Success);
    
private:
    
    void setupGameLevelScreen();
    bool setupWishScreen();
    
    void GoToPlay();
    
    void onDialogCancel();
    void onDialogOK();
    
    void SelectGameInEntrance(int i_id);
    
    void scrollRight();
	void scrollLeft();

	std::string GetModeType(FestivalGameMode i_mode);

    void onUseGemFinish(const bool& isSuccess);

    
private:
    
    //PVZ2UIScrollingWidget*          m_scrollingWidget;
    
    PVZ2UIButton *                  m_button_play;
    PVZ2UIButton *                  m_button_Refresh;
    
    Sexy::Rect                      m_rectDialog;
    Sexy::Rect                      m_rectGameMode;
    Sexy::Rect                      m_rectWish;
    
    SexyString						m_Title;
    
    FestivalGameMode                m_mode;
    
    std::vector<class FestivalGameWidget*> m_contents;
    //int                                    m_nLastSelect;
    
    std::vector<class SettingsDialogPane*> m_panes;
    
	TimeLineTrack<float> m_scrollTimeline;
	int m_depth;
};

////////////////////


class FestivalGameWidget : public Widget
{
public:
	FestivalGameWidget(FestivalGameLevel gameLevel,
                       int i_id,
                       ButtonListener* theButtonListener);
	virtual ~FestivalGameWidget();
    
    void SetSelected(bool i_selected);
    
    FestivalGameLevel GetGameLevel() const { return m_nGameLevel; }
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
        
private:
    
    PVZ2UIButton *    m_button;
    
    FestivalGameLevel m_nGameLevel;
    
    bool              m_bSelected;
    
    FestivalRewardMap m_RewardMap;
    
    int               m_Reward_x;
    int               m_Reward_Count;
    int               m_Reward_y;
};


////////////////////

class WishContent : public Widget
{
public:
	WishContent(MagentoProductPropsPtr i_props,
                int i_id,
                ButtonListener* theButtonListener);
	virtual ~WishContent();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
    void SetSelected(bool i_selected);
    
    MagentoProductPropsPtr GetProps() const
	{
		return m_props;
	}
    
private:
    
    PVZ2UIButton * m_button;
    
    PVZ2UIGameObjectCard* m_objCard;
    
    MagentoProductPropsPtr m_props;
    
    //SexyString  m_headerLabel;
    
    float       m_progress;
    SexyString  m_labelProgess;
    Rect        m_rectProgress;
    
    bool        m_bSelected;
};


////////////////////

#endif /* defined(__PlantsVersusZombies2__FestivalEntranceUI__) */

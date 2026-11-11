//
//  AdaptorRiftZombossLevelSetup.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/26/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorRiftZombossLevelSetup__
#define __PlantsVersusZombies2__AdaptorRiftZombossLevelSetup__

#include "HotUIAdaptor.h"
#include "UISingletonDialog.h"

class MapEventItem;
class AdaptorRiftDifficultyList;

enum RiftZombossLevelSetupButtons
{
    BUTTON_RIFT_ZOMBOSS_LEVEL_SETUP_CLOSE,
	BUTTON_RIFT_ZOMBOSS_LEVEL_SETUP_PLAY,
    BUTTON_RIFT_ZOMBOSS_LEVEL_SETUP_DIFFICULTY_1,
    BUTTON_RIFT_ZOMBOSS_LEVEL_SETUP_DIFFICULTY_2,
    BUTTON_RIFT_ZOMBOSS_LEVEL_SETUP_DIFFICULTY_3,
    BUTTON_RIFT_ZOMBOSS_LEVEL_SETUP_MODIFIER_INFO
};

class AdaptorRiftZombossLevelSetup : public HotUIAdaptor
{
public:

	RT_CLASS_DEFINE(AdaptorRiftZombossLevelSetup, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorRiftZombossLevelSetup();
    ~AdaptorRiftZombossLevelSetup();
    
    // HUMAN INPUT
	void ButtonDepress(int i_buttonID) override;
    bool OnBackButtonPressed() override;
    
    // NON-HUMAN INPUT
    void SetLevelName(const std::string& i_levelName) { m_levelNameToPlay = i_levelName; }
    void SetPlayLevelCallback(const Delegate1<const std::string&>& i_onPlayLevelCallback) { m_playLevelCallback = i_onPlayLevelCallback; }
    
    void Update() override;
    
protected:

	// UI View Link Handling
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

    void doAccept();
    void closeDialog();

    // zhousen
    void RefreshBonusContent(int difficulty);
    
private:

    void addRewardLists();
    void clearRewardLists();
    
    void startLevel();
    void selectDifficulty(int i_difficulty);
    void onDifficultySelected();
    
    std::string m_levelNameToPlay;
    Sexy::Delegate1<const std::string&> m_playLevelCallback;
    
    int m_difficultySelected;
	bool m_inTransition;
    Sexy::Widget* m_bonusWidget;
    
    AdaptorRiftDifficultyList* m_difficultyList;
    std::vector<class AdaptorMultiPurchaseItem*> m_itemWidgets;
};

class UIRiftZombossRewardSelect : public UISingletonDialog<UIRiftZombossRewardSelect>, public Sexy::EditListener
{
public:
	enum {
		RiftZombossRewardSelect_Close = 1000,
		RiftZombossRewardSelect_One,
		RiftZombossRewardSelect_Two,
	};

	UIRiftZombossRewardSelect();
	virtual ~UIRiftZombossRewardSelect();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIRiftZombossRewardSelect"; }
	virtual void ButtonDepress(int i_id) override;

	void SetFunctionOne(Delegate0 func) { m_functionOne = func;}
	void SetFunctionTwo(Delegate0 func) { m_functionTwo = func;}

protected:
	Delegate0 m_functionOne;
	Delegate0 m_functionTwo;
};

#endif

//
//  AdaptorRiftLevelSetup.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/25/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorRiftLevelSetup__
#define __PlantsVersusZombies2__AdaptorRiftLevelSetup__

#include "HotUIAdaptor.h"

class MapEventItem;
class AdaptorRiftDifficultyList;

enum RiftLevelSetupButtons
{
    BUTTON_RIFT_LEVEL_SETUP_CLOSE,
	BUTTON_RIFT_LEVEL_SETUP_PLAY,
    BUTTON_RIFT_LEVEL_SETUP_DIFFICULTY_1,
    BUTTON_RIFT_LEVEL_SETUP_DIFFICULTY_2,
    BUTTON_RIFT_LEVEL_SETUP_DIFFICULTY_3,
    BUTTON_RIFT_LEVEL_SETUP_MODIFIER_INFO
};

class AdaptorRiftLevelSetup : public HotUIAdaptor
{
public:

	RT_CLASS_DEFINE(AdaptorRiftLevelSetup, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorRiftLevelSetup();
    ~AdaptorRiftLevelSetup();
    
    // HUMAN INPUT
	void ButtonDepress(int i_buttonID) override;
    bool OnBackButtonPressed() override;
    
    // NON-HUMAN INPUT
    void SetEventNode(MapEventItem* i_event) { m_eventNodeToPlay = i_event; }
    void SetPlayLevelCallback(const Delegate1<const std::string&>& i_onPlayLevelCallback) { m_playLevelCallback = i_onPlayLevelCallback; }
    
protected:

	// UI View Link Handling
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

    void doAccept();
    void closeDialog();

    // zhousen
    void RefreshBonusContent(int difficulty);
    
private:
    void onRiftNetworkResponse(int i_context, int i_status);
    void onSuccessResponse();
    std::string getLevelToPlay();
    void startLevel();
    void selectDifficulty(int i_difficulty);
    void onDifficultySelected(int i_previousDifficulty);
	
	bool needToAddFirstClearBackground(int i_previousDifficulty);
	bool needToRemoveFirstClearBackground(int i_previousDifficulty);

	void InitMode(bool enable);
    
    MapEventItem* m_eventNodeToPlay;
    Sexy::Delegate1<const std::string&> m_playLevelCallback;
    
    int m_difficultySelected;
	bool m_inTransition;
    Sexy::Widget* m_bonusWidget;
    
    AdaptorRiftDifficultyList* m_difficultyList;
};

#endif

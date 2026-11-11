//
//  RiftOutro.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/29/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RiftOutro__
#define __PlantsVersusZombies2__RiftOutro__

#include <vector>
#include "AdaptorRiftPerkProgressScreen.h"
#include "AdaptorRiftResultsScreen.h"
#include "AdaptorRiftZombossProgress.h"
#include "OutroModule.h"
#include "RtObject.h"
#include "AwardDiff.hpp"

namespace Message
{
	void NotifyRiftPostEndPlay();
}

class RiftOutro : public OutroModule
{
public:
    enum RiftOutroState
    {
        RIFT_OUTRO_NOT_READY,
        RIFT_OUTRO_INIT,
        RIFT_OUTRO_QUEST_TOASTS,
        RIFT_OUTRO_SHOW_RESULTS,
        RIFT_OUTRO_YOU_WON_SCREEN,
		RIFT_OUTRO_FIRST_CLEAR_SCREEN,
        RIFT_OUTRO_PERK_PROGRESS_SCREEN,
        RIFT_OUTRO_ZOMBOSS_RESULT_SCREEN,
        RIFT_OUTRO_ZOMBOSS_AWARD_PRIZE,
        RIFT_OUTRO_FADING_OUT,
        RIFT_OUTRO_FIRST_REWARD,
        RIFT_OUTRO_DONE
    };
    
public:
    RT_CLASS_DEFINE(RiftOutro, OutroModule, RtClass);

	RiftOutro();
	virtual ~RiftOutro();
	
    void registerForEvents() override;

    void PennyPerkChooseEnd();

private:
    
    void onUpdate();

    
//    bool hasQuestToasts(QuestToastType i_toastType);
//    bool tryToShowQuestToasts(QuestToastType i_toastType);
    
    
    void startBoardFade();
    void onBoardFadeDone();

    void startWinOutro();
    void startLossOutro();
    void onLevelEnded();
    
    void showZombossResultsScreen(bool i_victory);
    void onZombossResultsScreenDismissed();
    void awardZombossPrize();
    void showZombossPrize();
    void onPinataRewardDialogEnded();
    void onPinataRewardFadeOut();
    
    void showResultsScreen(bool i_victory);
    void onResultsScreenDismissed();

    void onResultZombossNormalDismissed();// add for resultscreen -> zombossProgress
    
    void showPerkScreen();
    void onPerkScreenDismissed();
    
    void tryAwardRiftWin();
    
    void tryAward();
    void sendPostEndPlay(bool i_win);
    void dealPostEndPlay(bool i_win);
    void recordZombossData();
    void onRiftTimedEventGamePlaySend();

	void onRiftNetworkResponse(int i_context, int i_status);
	void onSuccessResponse();
	void onFailedResponse();

    // zhousen: penny perk ui should be added
	void CheckPopPennyPerkBattleStatementChooseUI();

    AdaptorRiftResultsScreen* m_resultsScreen;
    AdaptorRiftPerkProgressScreen* m_perkProgressScreen;
    AdaptorRiftZombossProgress* m_zombossResultsScreen;

    RiftOutroState m_state;
    
    int m_attemptPlayed;
    bool m_levelWasWon;
	bool m_unlockedZomboss;
    bool m_levelHasEnded;
	ZombossProgressDisplayData m_zombossProgress;
    
    AwardDiffSet m_awardDiffSet;
    bool m_isWin;
    bool m_waitForValidation;
};

class RiftOutroProperties : OutroModuleProperties
{
    RT_CLASS_DEFINE(RiftOutroProperties, OutroModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return RiftOutro::StaticGetClass();
	}
};

#endif

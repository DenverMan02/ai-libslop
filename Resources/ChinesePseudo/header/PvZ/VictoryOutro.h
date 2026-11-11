//
//  VictoryOutro.h
//  PlantsVersusZombies2
//
//  Created by jsola on 7/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_VictoryOutro_h
#define PlantsVersusZombies2_VictoryOutro_h

#include "LevelModule.h"
#include "OutroModule.h"
#include "Zombie.h"
#include "AnimationMgr.h"
#include "AwardEnums.h"
 
namespace Message
{
	void LevelRewardDropped();
    void CardPlayClose();
    void OutroNarrativeStarted();
    void OnEndLevelShow();

    void NotifyDangerRoomReward(int i_level, int i_currentScore, int i_totalScore);
}

class VictoryOutroModule : public OutroModule
{
public:
    RT_CLASS_DEFINE(VictoryOutroModule, OutroModule, RtClass);
	
    enum VictoryOutroState
    {
        VOS_Init,
        VOS_SpawningFlag,
        VOS_ShowingFlag,
        VOS_CollectedFlag,
        VOS_OutroNarrative,
        VOS_QuestToasts,
        VOS_WaitForFadingOut,
        VOS_FadingOut,
        VOS_Finished
    };
    
    void setState(VictoryOutroState state) { m_state = state; }
    
protected:
	
    virtual void		initializeModule() override;
    virtual void		registerForEvents() override;
	
	virtual void		onUpdate();

	void				startVictoryOutro();
	virtual void		startCoinShower();
	void				spawnCoinShower();
	
	void				awardAllRewards();
	
	bool				isFirstPlaythrough();
	bool				hasNarration();
	void				startNarration();
	
	virtual void		startBoardFade();

	virtual void		onBoardFadeDone();
	void				onLevelEnded();
	void				onCollectableCollected(class Collectable* i_collectable);
	virtual void		onCollectableFinishCollected(class Collectable* i_collectable);
	void				onEndOfLevelRewardCollected();
	virtual void		giveCustomRewards() {}
	void				onNarrationFinished();
    void                onCardPlayClose();
	
	void				showAwardScreen();
	void				onAwardScreenDismissed();
	
	void 				onArtifactDemoLevelContinue();
	void 				gotoArtifactPresentFromDemoLevel();

	bool				getPreventSave();

	void				onSpecialLevelFinished();

	void				checkUIWidgetsUnlock();

	/// Serialized values

	VictoryOutroState	m_state;
	pvztime_t			m_outroStartTime;
	pvztime_t			m_flagCollectEndTime;
	AwardType			m_awardType;
	std::string			m_awardParam;
	std::string			m_awardDialogTitle;
	std::string			m_awardDialogDescription;
	std::string			m_awardDialogImage;
    int                         m_startCoinCount;
	/// Transient values (used after load/save prevention)
	AnimationMgr		m_coinAnimMgr;
    
    class PopAnimRig* m_endLevelRig;
    CollectableTypePtr m_collectableType;
    
};
 
class VictoryOutroProperties : public OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(VictoryOutroProperties, OutroModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return VictoryOutroModule::StaticGetClass();
    }
 
    VictoryOutroProperties()
    {
		FlagSpawnTime = 1.f;
		
		BaseCoinAwardValue = 0;
		CoinsPerMower = 5;
		CoinShowerStartTime = 1.f;
		CoinShowerDuration = 0.25f;
		CoinShowerDelayBetweenMowers = 0.1f;
		CoinInitialHeight = 40.f;
		AdditionalEndingDelay = 1.0f;
		CoinCollectTime = 0.3f;
    }
	
	float FlagSpawnTime;
	int BaseCoinAwardValue;
	
	int CoinsPerMower;
	float CoinShowerStartTime;
	float CoinShowerDuration;
	float CoinShowerDelayBetweenMowers;
	float AdditionalEndingDelay;
	float CoinInitialHeight;
	float CoinCollectTime;
};

#endif

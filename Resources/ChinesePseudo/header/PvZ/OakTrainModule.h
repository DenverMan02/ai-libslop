//
//  OakTrainModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-8-21.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OakTrainModule__
#define __PlantsVersusZombies2__OakTrainModule__

#include "LevelModule.h"
#include "UIWidget.h"
#include "Effect_FloatingText.h"
#include "Zombie.h"
#include "Core.h"
#include "TimeLine.h"

enum ZombieTargetType
{
	ZombieTarget_Bottle,
    ZombieTarget_Arrow_Multiple,
    ZombieTarget_Arrow_Power,
    ZombieTarget_Arrow_Track,
    ZombieTarget_Archmage,
    ZombieTarget_Wizard,
    ZombieTarget_Gargantuar,
    ZombieTarget_Others,
    ZombieTarget_Count
};

enum oak_arrow_type
{
	OAK_ARROW_NORMAL,
    OAK_ARROW_POWER,
    OAK_ARROW_MULTIPLE,
    OAK_ARROW_TRACK,
    OAK_ARROW_COUNT
};

class OakTrainModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(OakTrainModule, LevelModule, RtClass);
    
    OakTrainModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    void         SetCanTouch(bool i_canTouch);
    void         SetCanTouchOakArrow(bool i_canTouch);
    
    ZombieTargetType GetZombieTargetType(const std::string& i_type_name);
    
    UIWidgetPtr      GetArrowWidgetPtr(oak_arrow_type i_type);
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
    bool         handleTouch(const Sexy::Touch& i_touch);
	void         cancelTouch();
	
private:

    enum OakTrainState
	{
		OTS_BeforeGameplay,
		OTS_Gameplay,
		OTS_Outro,
        OTS_Failed,
		OTS_DONE
	};
    
    void        setState(OakTrainState i_newState);
    
    void        onUpdate();
    void        onOakArrowTouch(const int i_type);
    void        onOakHeadShoot(const Sexy::SexyVector3& i_atLocation);
    void        onOakArrowAdd();
    
    void        onReviveCancel();
    void        onReviveOK();
    
    void        updateOutro();
    void        startOutro();
    
    void        PlayerLost();
    
    void        loadComplete();
    void        levelStarted();
    void        gameplayStarted();
    bool        CheckWinCondition();
    bool        preventSave();
    
    void        onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void        onMissTarget();
    
    void        updateScoreboard();
    void        updateGameplay();
    
    int         calcCoinReward(int i_score);
    void        spewGoldCoin(pvztime_t i_atTime);
	void        spewSilverCoin(pvztime_t i_atTime);
    
    void        CreateArrowUI();
    
    void        ShowReloadTip();
    
private:
    
    OakTrainState                           m_state;
    
    RtWeakPtr<class Effect_FloatingText>	m_scoreDisplay;
	//RtWeakPtr<class Effect_FloatingText>	m_minScoreDisplay;
    
    std::vector<ZombiePtr>                  m_zombiesKilledSinceLastUpdate;
    
    int                                     m_score;
	int                                     m_displayedScore;
    pvztime_t                               m_lastScoreChangeTime;
    float                                   m_scoreBounceScale;
    
    int                                     m_combo_count;
    bool                                    b_combo_hit;
    
    bool                                    b_playlose;
    bool                                    b_checkcondition;
    
    bool                                    b_canTouch;
    bool                                    b_canTouchOakArrow;
    
    std::vector<UIWidgetPtr>                m_arrow_widgets;
    int                                     m_select_arrow;
    
    PlantPtr                                m_oak_plant;
    
    // Outro
	pvztime_t                               m_outroStartTime;
	pvztime_t                               m_outroEndTime;
	TimeLine                                m_rewardCoinSpewTimeline;
	TimeLineTrack<int>                      m_outroScoreValue;
	TimeLineTrack<SexyVector3>              m_outroScorePosition;		// Using 'z' value for scale
	//TimeLineTrack<SexyVector3>              m_outroMinScorePosition;
};


class OakTrainProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(OakTrainProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return OakTrainModule::StaticGetClass();
	}
    
    OakTrainProperties()
    {
        TotalLife       = 1000;
        ArrowScore      = 100;
        HeadShootScore  = 100;
        WizardScore     = 300;
        ArchmageScore   = 500;
        BossScore       = 2000;
        
        HealNum         = 100;
        ArrowPowerNum   = 1;
        ArrowMultipleNum= 1;
        ArrowTrackNum   = 1;
        
        ShootInterval   = 0.3f;
    }
    
    int     TotalLife;
    int     ArrowScore;
    int     WizardScore;
    int     ArchmageScore;
    int     BossScore;
    int     HeadShootScore;

    int     HealNum;
    int     ArrowPowerNum;
    int     ArrowMultipleNum;
    int     ArrowTrackNum;
    
    pvztime_t ShootInterval;
    
    std::vector<int>    InitArrowsNum;
};

namespace Message
{
	void OakShootTouch(const Sexy::Point& i_atLocation);
    void OakArrowTouch(const int i_type);
    void OakArrowHitted(const int i_target_type, const int i_count);
    void OakHeadShoot(const Sexy::SexyVector3& i_atLocation);
    void OakArrowAdd();
    
    //Intro
    void OakArrowManualReload();
    void OakArrowAutoReload();
}

#endif /* defined(__PlantsVersusZombies2__OakTrainModule__) */

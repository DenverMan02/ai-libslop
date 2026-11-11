//
//  ZombieZombossQigong.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 1/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieZombossQigong_h
#define PlantsVersusZombies2_ZombieZombossQigong_h

#include "Zomboss.h"
#include "ZombiePropertySheet.h"
#include "CollectableSun.h"

struct ZombossQigongStage
{
    ZombossQigongStage()
    {
        HitPoints = 10000;
        SummonDelayMin = 5.0f;
        SummonDelayMax = 10.0f;
        SummonTimes = 5;
        
        PKIntervalTime = 60;
        JumpIdleTime = 5.0;
        SummonSunCount = 10;
        CureProbability = 100.0f;
    }
    
    int HitPoints;
    Sexy::Rect moveRect;
	CZombieSummonDataPool			ZombieSummonDataPool;
    
    float   SummonDelayMin;
    float   SummonDelayMax;
    int     SummonTimes;
    
    float   PKIntervalTime;
    float   JumpIdleTime;
    
    float   CureProbability;
    int     SummonSunCount;
};

class ZombieZombossQigongProps : public ZombossProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossQigongProps, ZombossProps, RtClass);

	ZombieZombossQigongProps()
	{

	}
    
    std::vector<ZombossQigongStage> 	Stages;
};


STATE_ENUM_CHILD_BEGIN(ZombossQigongState, ZombossState)
    ZombossQigong_Fly,
    ZombossQigong_Summon,
    ZombossQigong_FlyIdle,
    ZombossQigong_Fall,
    ZombossQigong_Flick,
    ZombossQigong_IceBall,
    ZombossQigong_PK,
    ZombossQigong_Cure,
    ZombossQigong_Jump,
STATE_ENUM_END(ZombossQigongState);

class ZombieZombossQigong : public Zomboss
{
public:
	RT_CLASS_DEFINE(ZombieZombossQigong, Zomboss, RtClass);

    virtual ImagePtr getHeadIcon() override;
    virtual Point GetGridExtents() const override;
    virtual void startFunctioning() override;
    virtual bool canChangeStage() const override;
    virtual void onChangeStageAnimDone(const std::string& i_label) override;
    
    const ZombossQigongStage& getStage(int i_stageIndex) const;
    const ZombossQigongStage& getActiveStage() const;
protected:
    DECLARE_STATE_FUNCTIONS(ZombieState, Fly);
    DECLARE_STATE_FUNCTIONS(ZombieState, Summon);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, Fall);
    DECLARE_STATE_FUNCTIONS(ZombieState, Flick);
    DECLARE_STATE_FUNCTIONS(ZombieState, IceBall);
    DECLARE_STATE_FUNCTIONS(ZombieState, PK);
    DECLARE_STATE_FUNCTIONS(ZombieState, Cure);
    DECLARE_STATE_FUNCTIONS(ZombieState, Jump);
    
    ZombieZombossQigong();
    ~ZombieZombossQigong();
    
    //interfaces from Zomboss
    virtual void onChangeActiveStage(int i_activeStageIndex) override;

    virtual void onZombieInitialize() override;
    void SummonSunFromSky();
    void OnCollectableBanked(Collectable* i_collectable);
    void OnBossWinPower(bool i_win);
    SexyVector2 getSunCollectPos();
    
    void onFlyAnimDone(const std::string& i_label);
    void onSummonAnimDone(const std::string& i_label);
    void onFallAnimDone(const std::string& i_label);
    void onFlickAnimDone(const std::string& i_label);
    void onJumpDownAnimDone(const std::string& i_label);
    void onPKAnimDone(const std::string& i_label);
    void onCureAnimDone(const std::string& i_label);

private:
    void initializeStageData(int i_zombossStageIndex);
    
private:
    bool m_summonEnd;
    pvztime_t m_summonNext;
    int m_summonTimes;
    
    pvztime_t m_pkNextTime;
    
    bool m_jumpEnd;
    pvztime_t m_jumpDownTime;
    pvztime_t m_cureTime;
    
    ValueRange m_summonInterval;
    
    std::vector<CollectableSun*> m_summonSuns;
    
    pvztime_t m_attachTime;
};

#endif

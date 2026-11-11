//
//  RiverCrossingModule.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/3/26.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RiverCrossingModule__
#define __PlantsVersusZombies2__RiverCrossingModule__

#include "LevelModule.h"
#include "ReviveUI.h"
#include "UIWidget.h"
#include "InitialGridItemPlacer.h"
#include "Zombie.h"
#include "Plant.h"
#include "SkatingGuacodile.h"
#include "RiverCrossingDodoRider.h"
#include "FloatingIce.h"
#include "StarvingChomper.h"
#include "ChallengeUI.h"
#include "PopAnimRig.h"

enum RiverCrossingTarget
{
    RCT_Crossing,
    RCT_SavingChomper
};

class RiverCrossingModule : public LevelModule
{
public:
    
    RT_CLASS_DEFINE(RiverCrossingModule, LevelModule, RtClass);
    
    RiverCrossingModule();
    ~RiverCrossingModule();
    
    void        setCanTouch(bool i_canTouch);
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    void onDodoRiderGoWithFloatingIce(float i_MoveToY);
    void onDodoRiderCorssedtheRiver();
    
    void SetTutorial(bool i_tutorial);
    bool IsInTutorial();
    void DodoRiderMoveTo(MoveDirection i_move);
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void postInitialize() override;
    
    bool         handleTouch(const Sexy::Touch& i_touch);
    void         cancelTouch();
    
    void onSpawnDodoRider(bool i_extern);

    virtual RiverCrossingDodoRider* CreateRider();
    virtual std::string GetRiderPam();
    virtual bool isInRiver(Point point);

    virtual void        RequireNextChomerGroup();
    virtual void		InitChomerGroup();
    virtual bool		IsRiderKilled();
    virtual void        onDodoRiderDying();
    virtual void		InitDodoRider(bool i_extern, RtWeakPtr<PopAnim> i_animPtr);
    virtual std::string GetReviveTip();
    virtual ImagePtr 	GetRiderUIImage();
    virtual ImagePtr	GetRemainUIImage();

    int                                     m_arrivedDodoRidersCount;
    RiverCrossingDodoRider*                 m_dodoRider;

private:
    
    bool        checkWin();
    void        onUpdate();
    
    void        loadComplete();
    void        levelStarted();
    void        gameplayStarted();
    bool        preventSave();
    
    void        onReviveCancel();
    void        onReviveOK();

    void        onDodoriderKilled(bool i_chompedByChomper);
    
    //    void        onFloatingIcesSpawned();
    //    void        onSkatingGuacodileSpawned();
    //    void        onZombieSpawned(class Zombie * i_zombie);
    //    void        onZombieRiseFromGround(class Zombie* i_zombie);

    void        OnDodoRiderLanding();
    void        onDodoRiderDied();
    void        onRiverEntitySpawned(class RiverEntity * i_entity);
    void        onRiverEntityCloseToEdge(class RiverEntity* i_entity);
    
    void        onDodoriderJumpIntoRiver();
    void        onStarvingChomperEatDodorider(StarvingChomper *i_chomper);
    // void        onLawnMowerDie(class LawnMower* i_mower);
    void        SpawnWaterSplashEffect(Sexy::SexyVector3 i_splashPoint, int i_renderOrder);
    // void        stopAllSnake();
    void        MakeDodoRiderArrival();
    // bool        FixArrivalPosition(SexyVector3 *pos, int i_level);
    // bool        hasArrivedDodoRiderIn(SexyVector3 pos);
    bool        CheckDodoRiderCrossedtheRiver();
    void        RequireNewDodoRider();

    SexyVector3 calcDodoRiderNextPosition(MoveDirection i_move);
    float       FixedToGridY(int i_y);
    void        CheckDodoRiderKilled();
    void        onPlayFloatingIceCarryingAnim();
    void        SetCarryingFloatingIce(FloatingIce * fi);
    void        RenderRemainDodoRiders(Graphics* i_g);
    // void        onAnimDone_RunOutBorder(class StandaloneEffect* i_effect);
    
private:
    bool                                    m_Tutorial;
    bool                                    m_GameStarted;
    bool                                    m_touchHasHandled;
    
    Sexy::TouchID                           m_touchIdent;
    SexyVector2                             m_touchStart;
    bool                                    m_hasWon;
    bool                                    m_touchIsMove;
    bool                                    m_bCanTouch;
    bool                                    m_isDodoRiderDying;
    
    //RiverCrossingDodoRider*                 m_dodoRider;
    int                                     m_savedChompersCount;
    int                                     m_starvingChompersCount;
    int                                     m_readyDodoriders;
    int                                     m_dodoRiderNeedCross;

    FloatingIce*                            m_carryingFloatingIce;
    RiverCrossingTarget                     m_riverCrossingTarget;
    
    bool                                    m_InReviveUI;
    pvztime_t                               m_TimeFailure;
    
    float                                   m_dodoRiderWalkingRate;
    float                                   m_dodoRiderFlyingRate;
    RiverEntitiesManager                    m_RiverEntitiesManager;
    
    RtWeakPtr<UIWidget>                     m_dodoRiderCrossedUI;
    RtWeakPtr<UIWidget>                     m_dodoRiderRemainUI;
    RtWeakPtr<UIWidget>                     m_chomperSavedUI;
    
    std::vector<StarvingChomper *>          m_starvingChompers;
    std::vector<RiverCrossingDodoRider *>   m_arrivedDodoRiders;
};

struct StarvingChomperProperties
{
    StarvingChomperProperties()
    {
        GridX = -1;
        GridY = -1;
        Wave = -1;
    }
    
    int				GridX;
    int				GridY;
    int             Wave;
    std::string		TypeName;
};

class RiverCrossingProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(RiverCrossingProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return RiverCrossingModule::StaticGetClass();
    }
    
    float GetDodoRiderWalkingRate() const;
    float GetDodoRiderFlyingRate() const;
    int GetStarvingChompersCount() const;
    int GetRetryTimes() const;
    int GetCrossTarget() const;
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
    RiverCrossingProperties()
    {
        RetryTimes = -1;
        CrossTarget = -1;
        StarvingChompersCount = -1;
        DodoRiderWalkingRate = 0.f;
        DodoRiderFlyingRate = 0.f;
    }
    
    int                                     RetryTimes;
    int                                     CrossTarget;
    int                                     StarvingChompersCount;
    float                                   DodoRiderWalkingRate;
    float                                   DodoRiderFlyingRate;
    std::vector<RiverEntityProperties>      RiverEntities;
    std::vector<StarvingChomperProperties>  StarvingChomperPlacements;
};

class CrossedRiverDodoRiderUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(CrossedRiverDodoRiderUI, ChallengeUI, RtClass);
    
    CrossedRiverDodoRiderUI();
    void SetCount(int count);
    void SetTarget(int target);
    
protected:
    virtual SexyString getCountText() override;
    
private:
    int	m_count;
    int m_target;
};

class RemainRiverDodoRiderUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(RemainRiverDodoRiderUI, ChallengeUI, RtClass);
    
    RemainRiverDodoRiderUI();
    void SetCount(int count);
    
protected:
    virtual SexyString getCountText() override;
    
private:
    int	m_count;
};

class RiverSplash : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(RiverSplash, PopAnimRig, RtClass) {}
    
    bool PlayRandomSplash(PopAnimRig::AnimStoppedDelegate i_onStopped);
    
protected:
    virtual void onPopAnimInitialized() override;
    virtual void onPreDraw(Graphics* i_g) override;
    virtual void onPostDraw(Graphics* i_g) override;
};

namespace Message
{
    void SpawnRiverEntity(RiverEntity * i_entity);
    void RiverEntityCloseToEdge(RiverEntity * i_entity);
    void SpawnDodoRider(bool i_extern);
    void DodoRiderDying();
    void StarvingChomperEatDodorider(StarvingChomper *i_chomper);
    void DodoriderJumpIntoRiver();
    void DodoRiderGoWithFloatingIce(float i_MoveToY);
    void RiverCrossingHandleTouch(int i_step);
    void DodoRiderDiedForIntro();
    void DodoRiderRunOutBorderWorning();
}

#endif /* defined(__PlantsVersusZombies2__RiverCrossingModule__) */


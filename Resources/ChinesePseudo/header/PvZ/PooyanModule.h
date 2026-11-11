//
//  PooyanModule.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/6/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PooyanModule__
#define __PlantsVersusZombies2__PooyanModule__

#include "LevelModule.h"
#include "ReviveUI.h"
#include "UIWidget.h"
#include "InitialGridItemPlacer.h"
#include "Zombie.h"
#include "Plant.h"
#include "ChallengeUI.h"
#include "PopAnimRig.h"
#include "PooyanShooter.h"
#include "PVZ2UIButton.h"

#define GROUP_MENBERS_COUNT 4

class PooyanModule;

struct PooyanShooterData
{
    int         Group;
    int         Attack;
    int         NextScore;
    float       ShooterRate;
    std::string pooyanShooterName;
    
    PooyanShooterData()
    {
        Group = 0;
        Attack = 0;
        NextScore = 99999;
        ShooterRate = 0.f;
        pooyanShooterName = "";
    }
};

struct PooyanShooterInfo
{
    PlantAnimRig*   m_pAniRig;
    int             m_nextScore;
    bool            m_bHasPlant;
};

struct PooyanBossBarage
{
    bool IsPooyanTarget;
    bool IsCycle;
    int StartRotation;
    int EndRotation;
    int BulletQuantity;
    float Interval;
    float NextInterval;
    std::string BossbarrageType;
    
    PooyanBossBarage()
    {
        IsPooyanTarget = false;
        IsCycle = false;
        StartRotation = 0;
        EndRotation = 0;
        BulletQuantity = 0;
        Interval = 0.f;
        NextInterval = 0.f;
        BossbarrageType = "PooyanBossBarrageSmall";
    }
};

class PooyanProperties;


enum PooyanShooterChooseUIButtons
{
    PooyanShooterChoose_close = 1,
    PooyanShooterChoose_team1,
    PooyanShooterChoose_team2,
    PooyanShooterChoose_team3,
    PooyanShooterChoose_left,
    PooyanShooterChoose_right,
    PooyanShooterChoose_Start,
};

class PooyanShooterChooseUI : public Widget, public ButtonListener
{
public:
    PooyanShooterChooseUI();
    virtual ~PooyanShooterChooseUI();
    
    virtual void Draw(Graphics* i_g);
    virtual void Update();
    virtual void ButtonPress(int i_id);
    virtual void ButtonDepress(int i_id);
    void GenerateShooterGroup(bool bAutoOpenPay,int iGetGem = 330);
    void ChangeShooterGroup(int i_group);
    void DeleteShooterGroupPreview();
    void CreateShipGroupPreview();
    void DeleteShipGroupPreview();
    void SetAllButtonEnable(bool i_enable);
    void GetBackToMap();
    
private:
    
    bool                            m_cannotStart = false;
    int                             m_choice = 0;
    Rect                            m_bksizeRect;
    std::vector<PooyanShooterData>  m_shooterDatas;
    PVZ2UIButton*                   m_closeButton = nullptr;
    PVZ2UIButton*                   m_startButton = nullptr;
    PVZ2UIButton*                   m_leftButton = nullptr;
    PVZ2UIButton*                   m_rightButton = nullptr;
    PVZ2UIButton*                   m_team1Button = nullptr;
    PVZ2UIButton*                   m_team2Button = nullptr;
    PVZ2UIButton*                   m_team3Button = nullptr;
    PooyanShooterInfo               m_shooterInfo[GROUP_MENBERS_COUNT];
    class Effect_PopAnim*           m_pAniRigShip[GROUP_MENBERS_COUNT];
};

class PooyanModule : public LevelModule
{
public:
    
    RT_CLASS_DEFINE(PooyanModule, LevelModule, RtClass);
    
    PooyanModule();
    ~PooyanModule();
    
    void setCanTouch(bool i_canTouch);
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    SexyVector3 GetShooterPosition();
    const PooyanProperties * GetPooyanProps();
    void ShowPooyanShooterChooseUI();
    void KillPooyanShooterChooseUI();
    PooyanShooterChooseUI * GetPooyanShooterChooseUI() { return m_pooyanShooterChooseUI; }
    void SetShooterGroup(int i_group);
    void KillPooyanShooter();
    RtWeakPtr<PooyanShooter> GetPooyanShooter() { return m_pooyanShooter; }
    bool IsPooyanShooterAlive();
    void SetPooyanShooterInvincible(float i_duration);
    void GiveTutorialPooyanShooter();
    void SetTutorial(bool i_tutorial);
    bool IsInTutorial();
    bool IsInReviveUI() { return m_InReviveUI; }
    void OnShooterTakeDamage();
    float GetBaseDamage();
    void takeShoot();
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void postInitialize() override;
    
    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    
private:
    bool checkWin();
    void onUpdate();
    
    void loadComplete();
    void levelStarted();
    void gameplayStarted();
    bool preventSave();
    bool CheckPerfect();
    
    void onReviveCancel();
    void onReviveOK();
    
    void onZombieSpawned(class Zombie * i_zombie);
    void onSpawnPooyanShooter();
    void onPooyanShooterKilled();
    void onZombieKilled(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onPlantFire();
    
    void ShooterLevelUp(const std::string& plant_name);
    void CheckPooyanShooterKilled();
    
private:
    
    bool                                    m_failScore;
    bool                                    m_GameStarted;
    bool                                    m_touchHasHandled;
    bool                                    m_touching;
    bool                                    m_hasWon;
    bool                                    m_touchIsMove;
    bool                                    m_bCanTouch;
    bool                                    m_isPooyanShooterDied;
    bool                                    m_InReviveUI;
    bool                                    m_Tutorial;
    bool                                    m_checkCondition;
    
    int                                     m_winScore;
    int                                     m_targetWinScore;
    int                                     m_score;
    int                                     m_targetScore;
    int                                     m_currShooterIndex;
    int                                     m_shooterHP;
    
    pvztime_t                               m_TimeFailure;
        
    Sexy::TouchID                           m_touchIdent;
    SexyVector2                             m_touchStart;
    
    PooyanShooterChooseUI *                 m_pooyanShooterChooseUI;
    RtWeakPtr<PooyanShooter>                m_pooyanShooter;
    std::vector<PooyanShooterData>          m_shooterDatas;
    
    RtWeakPtr<UIWidget>                     m_scoreUI;
};

class PooyanProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(PooyanProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return PooyanModule::StaticGetClass();
    }
    
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
    PooyanProperties()
    {
        InitShooterName = "PeaShooter";
        TargetScore = 0;
        TargetWeight = 0;
        BasicZombieScore = 0;
        ElectricBasicZombieScore = 0;
        GargantuarBasicZombieScore = 0;
        BattlePlaneWeight = 0;
        TwinsPlaneWeight = 0;
        InvisiblePlaneWeight = 0;
        BattlePlaneHP = 0;
        TwinsPlaneHP = 0;
        InvisiblePlaneHP = 0;
        BattlePlaneScore = 0;
        TwinsPlaneHP = 0;
        BattlePlaneScore = 0;
        InvisiblePlaneHP = 0;
        ShooterHP = 0;
        ShooterGroups = 0;
        TwinsPlaneScore = 0;
        InvisiblePlaneScore = 0;
    }
    
    int                                     ShooterHP;
    int                                     ShooterGroups;
    int                                     TargetScore;
    int                                     TargetWeight;
    
    int                                     BasicZombieScore;
    int                                     ElectricBasicZombieScore;
    int                                     GargantuarBasicZombieScore;
    
    int                                     BattlePlaneWeight;
    int                                     TwinsPlaneWeight;
    int                                     InvisiblePlaneWeight;
    
    int                                     BattlePlaneHP;
    int                                     TwinsPlaneHP;
    int                                     InvisiblePlaneHP;
    
    int                                     BattlePlaneScore;
    int                                     TwinsPlaneScore;
    int                                     InvisiblePlaneScore;
    
    std::vector<PooyanShooterData>          ShooterDatas;
    PooyanBossBarage                        BasicBarrageDatas;
    PooyanBossBarage                        PositiveBarrageDatas;
    PooyanBossBarage                        NegativeBarrageDatas;
    std::vector<PooyanBossBarage>           BattlePlaneBarrageDatas;
    std::vector<PooyanBossBarage>           TwinsPlaneBarrageDatas;
    std::vector<PooyanBossBarage>           InvisiblePlaneBarrageDatas;
    std::string                             InitShooterName;
    std::string                             BossbarrageType;
};

class PooyanModuleScoreUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(PooyanModuleScoreUI, ChallengeUI, RtClass);
    
    PooyanModuleScoreUI();
    void SetScore(int i_count);
    void SetTarget(int i_target);
	int GetScore() const { return m_score; }
	int GetTarget() const { return m_target; }
    
protected:
    virtual SexyString getCountText() override;
    
private:
    int	m_score;
    int m_target;
};

namespace Message
{
    void PooyanShooterTakeDamage();
    void PooyanIntroHandleTouch();
    void SpawnPooyanShooter();
    void PooyanShooterKilled();
    void PooyanShooterChoosed();
    void PooyanReady();
}

#endif /* defined(__PlantsVersusZombies2__PooyanModule__) */

//
//  ZombieAirMissile.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-6-15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAirMissile__
#define __PlantsVersusZombies2__ZombieAirMissile__

#include "ZombieSkyCity.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "GridItemBreakableTarget.h"
#include "PrimeTextWidget.h"

class ZombieAirMissileProps : public ZombieSkyCityProps
{
public:
    RT_CLASS_DEFINE(ZombieAirMissileProps, ZombieSkyCityProps, RtClass);
    float hitPlantDamage;
    ZombieAirMissileProps();
};

class ZombieAirMissile : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieAirMissile, Zombie, RtClass);
    void SetTargetRow(int row);
    void TakeDamage(const DamageInfo& i_damage) override;
    void onApplyCondition(ZombieConditions i_condition) override;
    int CalcRenderOrder() const override;
    ZombieAirMissile();
protected:
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    void CalcVelocity(int targetRow);
    void DamagePlantAtGrid(const Point& grid);
    void onZombieInitialize() override;
    void onPlaceOnBoard() override;
    void playDeathAnimation() override;
    bool allowElectrocuteState() const override;
    bool allowAshState() const override;
    bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
private:
    int GetTargetX();
    void Explode();
    void DamageAirShip(float damage);
    float GetVelocityRotation();
private:
    int m_targetRow;
    bool m_explodeOnBoard;
    SexyVector3 m_velocity;
    SexyVector3 m_accelerate;
};

STATE_ENUM_CHILD_BEGIN(ZombieAirMissileLauncherState, ZombieState)
ZS_AirMissileLauncher_PrepareLaunch,
ZS_AirMissileLauncher_RedEye,
ZS_AirMissileLauncher_Launching,
ZS_AirMissileLauncher_Launched,
ZS_AirMissileLauncher_Shake,
STATE_ENUM_END(ZombieAirMissileLauncherState)

class ZombieAirMissileLauncherProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieAirMissileLauncherProps, ZombiePropertySheet, RtClass);
    ZombieAirMissileLauncherProps();
    
    std::vector<int> DestroySwipeCount;
    std::vector<float> LaunchTime;
};

class AirMissileLauncher : public Zombie
{
public:
    RT_CLASS_DEFINE(AirMissileLauncher, Zombie, RtClass);
    void TakeDamage(const DamageInfo& i_damage) override;
    void onApplyCondition(ZombieConditions i_condition) override;
    int CalcRenderOrder() const override;
    Effect_PopAnim* PlaySwipeEffect(const SexyVector2& direction, const SexyVector2& position);
    AirMissileLauncher();
protected:
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Die);
    DECLARE_STATE_FUNCTIONS(ZombieState, PrepareLaunch);
    DECLARE_STATE_FUNCTIONS(ZombieState, RedEye);
    DECLARE_STATE_FUNCTIONS(ZombieState, Launching);
    DECLARE_STATE_FUNCTIONS(ZombieState, Launched);
    DECLARE_STATE_FUNCTIONS(ZombieState, Shake);
    void onZombieInitialize() override;
    void onPlaceOnBoard() override;
    void registerForEvents() override;
    void unregisterForEvents() override;
    bool allowElectrocuteState() const override;
    bool allowAshState() const override;
    bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
private:
    int GetDestroySwipeCount();
    void Launch();
    void Explode();
    void HandleTouchMove(const SexyVector2& location);
    bool HandleTouch(const Sexy::Touch& i_touch);
    void CancelTouch();
    void PrepareToMove();
    void OnAnimStopped(const std::string& label);
    float GetLaunchTime();
    float GetRedEyeTime();
    std::string GetExplodeName();
    std::string GetLaunchedName();
    std::string GetLaunchingName();
    std::string GetShakeName();
    std::string GetRedEyeShakeName();
private:
    int m_swipeCount;
    int m_wave;
    int m_targetRow;
    bool m_swiped;
    float m_timeElapsed;
    ZombieState m_oldState;
    SexyVector2 m_touchStart;
    SexyVector2 m_touchMove;
    Sexy::TouchID m_touchIdent;
};

class AirMissileGuide : public LevelModule
{
public:
    RT_CLASS_DEFINE(AirMissileGuide, LevelModule, RtClass);
    AirMissileGuide();
    ~AirMissileGuide();
protected:
    virtual void registerForEvents() override;
private:
    void Draw(class Sexy::Graphics* i_g);
    void OnUpdate();
    void PlaySwipeEffect();
    void AddToRenderQueue(class RenderQueue* i_queue);
    void OnPlaceOnBoard(Zombie* i_zombie);
    void OnGameplayStarted();
    void SetState(int state);
    void GenerateVelocity();
    void UpdateCountDown();
    void UpdateSwipe();
    float GetTimeElapsed();
private:
    int m_state;
    bool m_gameStart;
    bool m_guide;
    pvztime_t m_startTime;
    SexyVector3  m_handPos;
    SexyVector3  m_handVelocity;
    Sexy::PrimeTextWidget* m_countDown;
    RtWeakPtr<class Effect_PopAnim> m_handEffect;
    RtWeakPtr<class Effect_PopAnim> m_swipeEffect;
    RtWeakPtr<class AirMissileLauncher> m_missile;
    static const int handLeft = 520;
    static const int handRight = 650;
    static const int handTop = 510;
    static const int StateNotStart    = -1;
    static const int StateStart       = 0;
    static const int StateConcentrate = 1;
    static const int StateSwipe       = 2;
    static const int StateCountDown   = 3;
};

class AirMissileGuideProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(AirMissileGuideProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return AirMissileGuide::StaticGetClass();
    }
};

#endif /* defined(__PlantsVersusZombies2__ZombieAirMissile__) */

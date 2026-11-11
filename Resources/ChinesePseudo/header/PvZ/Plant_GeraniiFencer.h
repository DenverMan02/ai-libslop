//
//  Plant_GeraniiFencer.h
//  PlantsVersusZombies2
//  create by lfy

#ifndef __PLANT_GERANIIFENCER_H__
#define __PLANT_GERANIIFENCER_H__

// #include "Precompile.h"
#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "PlantAnimRig.h"


enum GeraniiFencerState
{
    GERANIIFENCER_IDLE = STATE_FRAMEWORK_BEGIN,
    GERANIIFENCER_WATER,
    GERANIIFENCER_NORMAL_ATTACK,
    GERANIIFENCER_CANCEL_NORMAL_ATTACK,
    GERANIIFENCER_ATTACK_FORWARD,
    GERANIIFENCER_ATTACK_BACK,
    GERANIIFENCER_PLANTFOOD,
};


class GeraniiFencerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(GeraniiFencerProps, PlantPropertySheet, RtClass);
    
    Sexy::Rect GetCollisionRect(Plant* i_plant) const override;

    pvztime_t BoostSkillCooldown;
    float BoostSkillDamage;
    float RepulseDistanceRate;
    float NormalAttackDamage;
    float Lv2Odds;
    float Lv3Odds;
};



class GeraniiFencerSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(GeraniiFencerSubsystem, GameSubSystem, RtClass);
    GeraniiFencerSubsystem() {}
    ~GeraniiFencerSubsystem() {}

    void StunZombies(int i_col, int i_row, float repulseDistanceRate, bool beStuned, bool isMid = true);

private:
    bool shouldStun(Zombie* i_zombie);
    void onFlyingEnd(Zombie *i_zombie);
};


class PlantGeraniiFencer : public PlantFramework
{
public:

    RT_CLASS_DEFINE(PlantGeraniiFencer, PlantFramework, RtClass);
    void Initialize() override;
    void UpdateActions() override;
    Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override; 
    void UpdatePlantfood() override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    void onAnimStoppedCallback(const std::string& i_animCommand) override;
    bool CanBeTargetedBy(const BoardEntity *i_entity) override;

    bool IsForward() { return m_isForward; }

protected:
    
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void DoSpecialForAvatarNormal() override;  // for avatar

private:
    
    void setState(GeraniiFencerState i_state);
    void jumpForward(bool stun);
    void jumpBackward();
    void normalAttack();
    std::vector<BoardEntity*> findAttackTartget();
    void supperSkill(float i_damage);
    Rect getSupperSkillRect();
    void setInvalidateRect();
    Rect normalRect();
    std::vector<BoardEntity*> findNormalTartget();


    pvztime_t m_plantfoodDamageEndTime{0.0};
    pvztime_t m_attackCooldown{0.0};
    bool m_isForward{false};
    bool m_isBackward{true};
    bool m_canSupperSill{false};
    pvztime_t m_boostSkillTime{0.0};
    float m_repulseDistanceRate{0.0};
    float m_odds = 0.0;
    pvztime_t m_waterEndtime{0.0};
    bool m_isStun = false;
    bool m_cancelNomal = false;
    bool m_isBoostSkill = false;
};


class PlantAnimRig_GeraniiFencer : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_GeraniiFencer, PlantAnimRig, RtClass);

    bool PlayIdleLooped() override;
    void SetBoost() { m_boost = true; }
    void SetStun(bool isStun) { m_stun = isStun; }
    bool GetStun() { return m_stun; }
    bool PlayNormalAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
private:
    std::string getPlantFoodMainAnimName() override;
    std::string getAttackAnimationName() override;

    bool m_boost{false};
    bool m_stun{false};
};

#endif

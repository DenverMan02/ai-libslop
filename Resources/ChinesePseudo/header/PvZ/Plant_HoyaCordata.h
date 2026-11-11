#ifndef __PLANT_HOYACORDATA_H__
#define __PLANT_HOYACORDATA_H__

#include "PlantFramework.h"
#include "PopAnimRig.h"
#include "PlantAnimRig.h"
#include "Zombie.h"
#include "Plant.h"
#include "Projectile.h"
#include "ZombieLaneChangingSubsystem.h"
#include "NewPVPUtils.h"
#include <vector>
#include "SexyMatrix.h"  
#include "PlantGroup.h"

STATE_ENUM_CHILD_BEGIN(HoyaCordataState, PlantState)

    HOYACORDATAIDLE,
    HOYACORDATABUFFERPLANTLOOP,
    HOYACORDATABUFFERPLANTEND,
    HOYACORDATABUFFERPLANTPLANTFOODLOOP,
    HOYACORDATABUFFERPLANTPLANTFOODEND,
    HOYACORDATACOOLDOWNLOOP,
    HOYACORDATACOOLDOWN,
STATE_ENUM_END(HoyaCordataState)

class PlantHoyaCordataProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantHoyaCordataProps, PlantPropertySheet, RtClass);

    PlantHoyaCordataProps()
    {
        AttackUpDuration = 10.0f;
        AttackUpCooldown = 10.0f;
        AttackUpLevelCooldown = 2.5f;
        TupleSpellRate = 0.3f;
        AvatarPlantfoodRate = 0.5f;
        TupleSpellLevelUpRate = 0.1f;
        Level5AttackUpPhase2Rate = 0.5f;
        speedUpPercent = 1.0f;
        AttackUpPercent = 0.2f;
    }
    float AttackUpDuration;
    float TupleSpellRate;
    float AvatarPlantfoodRate;
    float TupleSpellLevelUpRate;
    float Level5AttackUpPhase2Rate;
    float AttackUpCooldown;
    float AttackUpLevelCooldown;
    float speedUpPercent;
    float AttackUpPercent;
};

// class HoyaCordataAttachedEffectManager : public AttachedEffectManager
// {
// public:
// 	RT_CLASS_DEFINE(HoyaCordataAttachedEffectManager, AttachedEffectManager, RtClass);

// };

class PlantHoyaCordata : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantHoyaCordata, PlantFramework, RtClass);
    PlantHoyaCordata();
    virtual ~PlantHoyaCordata();
    void Initialize() override;
    void UpdateActions() override;
    void onDestroy() override;

    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void UpdatePlantfood() override;


    void CurePlant() ;
    void         onAnimStoppedCallback(const std::string& i_labelname) override;
    

    void BufferPlant(Plant* plant,float Scale = 1.0f);
    void Phase2BufferPlant(Plant* plant);
    void CancelPhase2BufferPlant(Plant* plant);
    void BufferPlantAttack(Plant* plant,float Scale = 1.0f);
	void BufferPlantHealth(Plant* plant,float Scale = 1.0f);
    void CancelBufferPlant(Plant* plant);
    void AllBufferPlant();
    void AllPhase2BufferPlant();
	void BufferPlantSpeed(Plant* plant,bool flag = true);
    void SetState(const uint i_state);
    // std::vector<Sexy::Point> FillSprayFields(Sexy::Point center);
    void TupleSpellPlantFood(Plant* plant);
    void StartLoopTupleSpell(Plant* plant);
    void CanTupleSpellPlantFood(Plant* plant);
    void PlayAttackEffect(std::string m_effectname);
    void AllPlayAttackEffect(std::string m_effectname,int i,BoardEntity* plant);
    void PlayPlantfoodeffect();
    std::string getImpactPam() { return "POPANIM_EFFECTS_HOYACORDATA";}
    void onSleeped(bool sleeped) override;
	void onApplyCondition(PlantConditions i_condition) override;
	virtual void onEndCondition(PlantConditions i_condition) override;
    void Idle() override;

    // void AllCurePlant();
private:
    pvztime_t Phase2Starttime;
    pvztime_t AttackUpDurationEndtime;
    pvztime_t IdleEndtime;
    // HoyaCordataState m_state;
    int AvatarPlantfoodCount;
    Sexy::Point TargetsPos;
    std::vector<BoardEntity*> AllBufferPlantTargets;
    std::vector<Sexy::Point> AllBufferPlantPoints;
    std::vector<BoardEntity*> AllAvatarBufferPlantTargets;
    pvztime_t WaterEndtime;
    bool Phase2flag;
    bool WaitPlantfood;
    std::vector<Plant*> WaitPlantfoodtarget;
    uint _m_state;
};

class PlantAnimRig_HoyaCordata : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HoyaCordata, PlantAnimRig, RtClass);

    PlantAnimRig_HoyaCordata():i_idleTag("idle")
    {
    }

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    void setIdleTag(const std::string& i_tag) { i_idleTag = i_tag; }
    virtual std::string getIdleAnimationName() override;

private:
    std::string i_idleTag;
public:
};  



#endif //__PLANT_HOYACORDATA_H__

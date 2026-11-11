

#ifndef __PLANT_HAPPYLEEK_H__
#define __PLANT_HAPPYLEEK_H__
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


STATE_ENUM_CHILD_BEGIN(HappyLeekState, PlantState)
    HAPPYLEEKYOUNG,
    HAPPYLEEKGROUND,
    HAPPYLEEKOLD,
STATE_ENUM_END(HappyLeekState)

class PlantHappyLeekProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantHappyLeekProps, PlantPropertySheet, RtClass);

    PlantHappyLeekProps()
    {
        // growtime = 60.0f;
        // growlevelsubtime = 10.0f;
        // shovelsuncount = 100;
        // producesunmaxcount = 5;
        // lv5growtime = 30.0f;
        // plantfoodAvatarlooptime = 5.0f;
    }
    float growtime;
    float growlevel2subtime;
    float shovelsuncount;
    float growlevel3subtime;
    float producesunmaxcount;
    float lv5growtime;
    float plantfoodAvatarlooptime;
    float LaneChangeTime;
};


class PlantHappyLeek : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantHappyLeek, PlantFramework, RtClass);
    void Initialize() override;
    void UpdateActions() override;

    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void ProduceSun(const PlantAction& i_fromAction) override;
    void ProduceSun(const PlantAction& i_fromAction,PowerContext i_context) ;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	BoardEntityHeight		GetEntityHeight() const override;

	float   GetRefundSunAmount() override;
    void    ShovelKill() override;
    void    SetState(const uint i_state);
    bool canZombieLaunch(Zombie* zombie);
    virtual void Idle() override;
    virtual void AutoFire() override;

private:
    bool hasValidTarget();
    void tryAttackZombies();
    void moveZombieByRows(Zombie* i_zombie, int numRows);

private:
    int m_attackcount;
    int m_Levelfreecount;
    float m_growtime;
    pvztime_t m_growcooldown;
    uint _m_state;
    int m_producesuncount;
    pvztime_t m_nextAttackTime = 0;
    bool Lv5Skill;
    pvztime_t m_nextlv5growtime;

};


class PlantAnimRig_HappyLeek : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HappyLeek, PlantAnimRig, RtClass);
    PlantAnimRig_HappyLeek():i_idleTag("young_idle"),m_attackcount(0)
    {
    }
    void setIdleTag(const std::string& i_tag) { i_idleTag = i_tag; }
    void SetLV5AttackCount(const int i_attackcount) { m_attackcount = i_attackcount; }
	bool PlayGrow(const int i_leaf, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayTapAttack(const int i_leaf,PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayTapProduceSun(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayTapAnimation(const std::string i_animtag, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    std::string getPlantFoodOnAnimName() override;
	virtual bool playPlantFoodOn() override;
    virtual std::string getWaterAnimName() override;

    virtual std::string getIdleAnimationName() override;

private:
    std::string i_idleTag;
    int m_attackcount;
};

class HappyLeek_badsmelleffect : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(HappyLeek_badsmelleffect, Effect_PopAnim, RtClass);
    void SetRect(Sexy::Rect i_takeeffectRect) {takeeffectRect = i_takeeffectRect;}
    HappyLeek_badsmelleffect():m_laneChangeTime(1.0f)
    {}
private:
	virtual void onUpdate() override;

	Sexy::Rect   takeeffectRect;
    float   m_laneChangeTime;
};

#endif //__PLANT_HAPPYLEEK_H__

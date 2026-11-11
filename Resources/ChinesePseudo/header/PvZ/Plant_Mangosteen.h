#ifndef PLANT_MANGOSTEEN_H
#define PLANT_MANGOSTEEN_H

#include "PlantFramework.h"
#include "Zombie.h"
#include "Projectile.h"
#include "BoardTransforms.h"

typedef RtWeakPtr<class PlantMangosteen> PlantMangosteenPtr;
typedef RtWeakPtr<class MangosteenElectricCircle> MangosteenElectricCirclePtr;
typedef RtWeakPtr<class MangosteenElectricExplode> MangosteenElectricExplodePtr;

STATE_ENUM_CHILD_BEGIN(MangosteenState, PlantState)
	STATE_MANGOSTEEN_IDLE,
	STATE_MANGOSTEEN_IDLE2,
	STATE_MANGOSTEEN_IDLE3,
	STATE_MANGOSTEEN_RECOVERY,
	STATE_MANGOSTEEN_ATTACKING,
	STATE_MANGOSTEEN_UPGRADING,
	STATE_MANGOSTEEN_ATTACK_INTERVAL,
STATE_ENUM_END(MangosteenState);

class MangosteenProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MangosteenProps, PlantPropertySheet, RtClass);

	pvztime_t 	StateChangeInterval = 5;
	pvztime_t   RecoveryTime = 10;
	pvztime_t   AttackInterval = 0.5;
	float 		AttackNormalRadius = 3;
	float 		AttackPlantfoodRadius = 3;
	float 		AttackExplodeRadius = 3;
	float 		AttackHitRadius = 3;
	std::string ElectricCirclePAMName;
	int 		OverLoadAttackTimes = 3;
	float 		LevelUpReduceCD = 5;
	int 		LevelUpTimesAdd = 1;
	float 		ProjectileTimeOfFlight = 1.2;
	float 		ProjectileLobHeight = 350;
	float 		GridVelocity = 300;
};


class PlantMangosteen : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMangosteen, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;

	virtual void DoSpecial(int i_extraParam = 0) override;
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void onAnimStoppedCallback(const std::string& i_animLabel) override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	MangosteenState getMyLastIdleState() const { return m_lastIdleState; }
    static bool canTarget(BoardEntity* i_entity);
//    void setElecExplodePtr(MangosteenElectricExplodePtr i_elecExplode) { m_elecExplode = i_elecExplode; }
    ZombiePtr getMyTarget() { return m_target; }
    void setCircleEffectValues(MangosteenElectricCircle* i_electricCircle);
//    void setExplodeEffectValues(MangosteenElectricExplode* i_electricExplode);

	void SetAttackState() { setState(STATE_MANGOSTEEN_ATTACKING); }
private:
	void setState(MangosteenState i_mangosteenState);
	void findTargets();
	void startAttack();
	std::string getIndexStr();

private:
	 pvztime_t 			m_nextStateChangeOn = PVZ_EOT();
	 pvztime_t 			m_recoverOn = PVZ_EOT();
	 pvztime_t 			m_readyAttackOn = PVZ_T();
	 MangosteenState 	m_lastIdleState = STATE_MANGOSTEEN_IDLE;
	 int 				m_attackTimes = 0;
	 int 				m_overLoadTimes = 0;
	 ZombiePtr 			m_target = ZombiePtr();
	 MangosteenElectricCirclePtr	m_elecCircle = MangosteenElectricCirclePtr();
};

class PlantAnimRig_Mangosteen : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Mangosteen, PlantAnimRig, RtClass);


    void setIdleAnimName(std::string i_idleAnimName) { m_idleAnimName = i_idleAnimName; }
    bool playAnimation(const std::string& i_animLabel, const std::string& i_animCallback);
    bool playIdleAnimation(const std::string& i_animLabel);
    std::string GetPriviewAnim() { return "idle2"; }
    bool PlayPreviewAnim(bool bHideLayer = false) override;
//	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0);

private:
    virtual std::string getIdleAnimationName() override { return m_idleAnimName; }
    virtual std::string getWaterAnimName() override;
    std::string m_idleAnimName;
};


struct ElectricCircleDescription {
	float currentRadius = 0;
	float startRadius = 0;
	float endRadius = 1.5 * BoardConstants::GRIDSQUARE_HEIGHT();
	float duration = 0.5;
	float aliveTime = 1.3;
	DamageInfo damageInfo;
	DamageInfo explodeInfo;
	std::string pamName;
	std::string animName;
	std::string explodePamName;
	std::string explodeAnimName;
	Sexy::SexyVector3 origin;
	pvztime_t paralysisDuartion = 0;
	MangosteenState idleState = STATE_MANGOSTEEN_IDLE;
	float explodeRadius = 1.5 * BoardConstants::GRIDSQUARE_HEIGHT();
	bool isAvatarEnable = false;
};

class MangosteenElectricCircle : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(MangosteenElectricCircle, Effect_PopAnim, RtClass);

public:
	void setValues(ElectricCircleDescription i_des);
	void setExplodeEffectValues(MangosteenElectricExplode* i_electricExplode);

protected:
	virtual void onUpdate() override;
	virtual void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

private:
	bool hasDamaged(BoardEntity* i_entity);

	bool m_isAvatarEnable = false;
	Sexy::SexyVector3 m_origin;
	bool m_isExploding = false;
	bool m_isAlive = false;
	float m_currentRadius = 0;
	float m_startRadius = 0;
	float m_endRadius = 1.5 * BoardConstants::GRIDSQUARE_HEIGHT();
	float m_duration = 0.3;
	float m_aliveTime = 1.3;
	std::vector<BoardEntity*> m_hasDamagedEntityList;
	DamageInfo m_damageInfo;
	pvztime_t m_paralysisDuartion = 0;
	MangosteenState m_idleState = STATE_MANGOSTEEN_IDLE;
	pvztime_t m_startTime = PVZ_T();
	std::string m_explodePamName;
	std::string m_explodeAnimName = "idle";
	float m_explodeRadius = 0;
	DamageInfo m_explodeInfo;
};

struct ElectricExplodeDescription
{
	std::string explodePamName;
	std::string explodeAnimName = "idle";
	Sexy::SexyVector3 origin;
	float explodeRadius = 0;
	DamageInfo explodeInfo;
};

class MangosteenElectricExplode : public Effect_PopAnim
{
	RT_CLASS_DEFINE(MangosteenElectricExplode, Effect_PopAnim, RtClass);

public:
	void setValues(ElectricExplodeDescription i_des);

protected:
	virtual void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

private:
	Sexy::SexyVector3 m_origin;
	std::string m_explodePamName;
	std::string m_explodeAnimName = "idle";
	float m_explodeRadius = 0;
	DamageInfo m_explodeInfo;
};


#endif

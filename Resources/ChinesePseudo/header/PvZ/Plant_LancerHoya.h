/*
 * Plant_LancerHoya.h
 *
 *  Created on: 2022-12-12
 *      Author: zhousen
 */

#ifndef PLANT_LANCERHOYA_H_
#define PLANT_LANCERHOYA_H_


#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "GridItemAnimation.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GameSubSystem.h"

////////////////////////////////////////
/// LancerHoyaProps
////////////////////////////////////////
class LancerHoyaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(LancerHoyaProps, PlantPropertySheet, RtClass);

	LancerHoyaProps()
	{
		ThrowLancerCoolDown = 2.0f;
		SpecialChargeDuration = 20.0f;
		SpecialChargeDuration2 = 17.5f;
		SpecialChargeDuration3 = 15.0f;
		ZombieFlickOffDuration = 1.5f;
		BaseDamage = 90.0f;
		Level5ExtraDamage = 500.0f;
		PlantfoodBaseDamage = 100.0f;
	}
	pvztime_t ThrowLancerCoolDown;
	pvztime_t SpecialChargeDuration;
	pvztime_t SpecialChargeDuration2;
	pvztime_t SpecialChargeDuration3;
	pvztime_t ZombieFlickOffDuration;
	float BaseDamage;
	float Level5ExtraDamage;
	float PlantfoodBaseDamage;
	ZombieRestrictionSet CannotBeSpeicalHit;// only for not level5
};

////////////////////////////////////////
/// PlantLancerHoya
////////////////////////////////////////
class PlantLancerHoya : public PlantFramework
{
public:
	enum LancerHoyaState
	{
		STATE_LANCERHOYA_IDLE = STATE_FRAMEWORK_BEGIN,
		STATE_THROW_LANCER,
		STATE_SPECIAL_ATTACK,
		STATE_TURN_TO_SPECIAL,
	};
	RT_CLASS_DEFINE(PlantLancerHoya, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void UpdateActions() override;
	virtual ZombiePtr FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams) override;
	BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override;
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	bool IsInSpecialStatus();

protected:
	void setState(uint i_plantState);
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	Projectile* normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);

	void UpdateStatus();
	bool onTouchEvent(const Sexy::Touch& i_touch);
	pvztime_t CalcSpecialChargeDuration();
	int CalcAttackDamage();
	int CalcPlantfoodAttackDamage();
	void DoSpecialAttack();
	void DoPlantfoodAttack();
	BoardEntity* FindSpecialTargetMelee(BoardEntityTypeFlag  flag);
	std::vector<BoardEntity*> FindSpecialTargets(BoardEntityTypeFlag flag);
	std::vector<BoardEntity*> FindPlantfoodTargets(BoardEntityTypeFlag flag);
	bool CheckValidZombie(Zombie* zombie, bool isSingle = false);

	void OnZombieLandEnd(Zombie* i_zombie);
	void OnZombieInSky(Zombie* i_zombie);

	void OnZombieInSkyPlantfood(Zombie* i_zombie);
	void OnZombieFlyEndPlantfood(Zombie* i_zombie);

    void onZombieDestroyed(class Zombie* i_zombie);

protected:
	pvztime_t m_specialStatusStartTime;// special status time
	bool m_inSpecialStatus;
	pvztime_t m_throwLancerStartTime;// throw lancer start
	float m_attackDamage;
	float m_speicalLevel5ExtraDamage;
	float m_plantfoodAttackDamage;
	Sexy::Rect m_collisionRect;
    std::vector<RtWeakPtr<class Zombie> > m_tossZombies;

    pvztime_t m_plantfoodDamageEndTime;
    pvztime_t m_specialMeleeAttackEndTime;
    RtWeakPtr<class Zombie> m_specialAttackZombieForMelee;
    RtWeakPtr<class Zombie> m_specialAttackExcludeZombieForMelee;

    std::vector<RtWeakPtr<class GridItem> > m_specialAttackGriditems;
    std::vector<RtWeakPtr<class GridItem> > m_plantfoodAttackGriditems;

    bool m_isMiniBoard;
};


////////////////////////////////////////
/// PlantAnimRig_LancerHoya
////////////////////////////////////////
class PlantAnimRig_LancerHoya : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_LancerHoya, PlantAnimRig, RtClass);

	void SetPlantPtr(PlantPtr ptr) { m_plantPtr = ptr; }

    void PlayTurnToSpecial(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
    void PlaySpecialAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);

protected:
	void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
    std::string getPlantFoodMainAnimName() override;

protected:
    PlantPtr m_plantPtr;
};

class PlantLancerHoyaTossSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PlantLancerHoyaTossSystem, GameSubSystem, RtClass);
    PlantLancerHoyaTossSystem();

    void SetZombieFlyEndFunc(Delegate1<class Zombie*> func);
    void SetZombieFlyEndFunc(class Zombie*, Delegate1<class Zombie*> func);
    void TossZombies(Zombie* i_zombie, Plant* i_plant, SexyVector3 pos, pvztime_t duration);
	void onFlyingEnd(Zombie* i_zombie);

private:
	Delegate1<class Zombie*> m_flyEndDelegate;
	std::map<class Zombie*, Delegate1<class Zombie*> > m_flyEndDelegateMap;
};

#endif /* PLANT_LANCERHOYA_H_ */

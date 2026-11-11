//
// GridItemFireCracker.h
// 12-16-21
//

#ifndef GRIDITEM_FIRECRACKER_H_
#define GRIDITEM_FIRECRACKER_H_

#include <iostream>
#include "Precompile.h"
#include "GridItem.h"
#include "zombieanimrig.h"
#include "Zombie.h"

enum FireCrackerState
{
	PVZ_BEGIN_ENUM(STATUESTATE_),
	STATUESTATE_APPEARING,
	STATUESTATE_IDLE,
	STATUESTATE_BURN_START,
	STATUESTATE_BURN_SMOKE_START,
	STATUESTATE_BURN_SMOKING,
	STATUESTATE_BURN_OUT,
	STATUESTATE_EXPLODING,
	PVZ_END_ENUM(STATUESTATE_)
};

class GridItemFireCrackerProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemFireCrackerProps, GridItemAnimationProps, RtClass);

	GridItemFireCrackerProps()
	: ExplodeDamageAmount(0)
	, ExplodeDelayTime(3)
	{}

	std::vector<std::string> CanFiredByZombieTypes;
	float ExplodeDamageAmount;
	float ExplodeDelayTime;
};


class GridItemFireCracker : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemFireCracker, GridItemAnimation, RtClass);

	GridItemFireCracker();

	int CalcRenderOrder() const override;
//	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	void setState(FireCrackerState i_state);
	void registerForEvents() override;

	virtual bool Activate();
	virtual bool Deactivate();

	void setValues(float i_hitpoints, float i_explodeAmount);

protected:
	void onGridItemInitialize() override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
	void onAnimDone(const std::string &i_animLabel);

	void onFireCrackerStateChanged(int i_flg);

	bool canActivated();
	bool canDeactivated();
	virtual void onActivated();
//	virtual void onDeactivated();

	bool OverrideProjectileCollision(Projectile* i_projectile) override;
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;

	virtual void updateState();
	void CheckGridZombies();

	virtual void onTakeDamage(const DamageInfo& i_damage);
	void OnAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);


	FireCrackerState m_state;
	pvztime_t m_explodeTime;
	float m_explodeDamageAmount;
};

class GridItemFireCrackerAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemFireCrackerAnimRig, PopAnimRig, RtClass);

	void PlayIdle();
	void PlayActivated(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlaySmoking(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlaySmokeStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayIdleOut();
	void PlayExplode(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayAppear(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	virtual const std::string getIdleAnimName();
	virtual const std::string getActivatedAnimName();
	virtual const std::string getSmokeStartAnimName();
	virtual const std::string getSmokingAnimName();
	virtual const std::string getIdleOutAnimName();
	virtual const std::string getExplodeAnimName();
	virtual const std::string getAppearAnimName();
};

namespace Message
{
	void GridItemFireCracker(bool i_flg);
}



#endif /* GRIDITEM_FIRECRACKER_H_ */

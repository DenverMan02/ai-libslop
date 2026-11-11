//
// GridItemSummerFireworks.h
// 22-4-22
//

#ifndef GRIDITEM_SUMMERFIREWORKS_H_
#define GRIDITEM_SUMMERFIREWORKS_H_

#include <iostream>
#include "Precompile.h"
#include "GridItem.h"
#include "zombieanimrig.h"
#include "Zombie.h"

enum SummerFireworksState
{
	PVZ_BEGIN_ENUM(SUMMERFIREWORKS_SUMMERFIREWORKS_STATUESTATE_),
	SUMMERFIREWORKS_STATUESTATE_APPEARING,
	SUMMERFIREWORKS_STATUESTATE_IDLE,
	SUMMERFIREWORKS_STATUESTATE_BURN_START,
	SUMMERFIREWORKS_STATUESTATE_BURN_SMOKE_START,
	SUMMERFIREWORKS_STATUESTATE_BURN_SMOKING,
	SUMMERFIREWORKS_STATUESTATE_BURN_OUT,
	SUMMERFIREWORKS_STATUESTATE_EXPLODING,
	PVZ_END_ENUM(SUMMERFIREWORKS_SUMMERFIREWORKS_STATUESTATE_)
};

class GridItemSummerFireworksProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemSummerFireworksProps, GridItemAnimationProps, RtClass);

	GridItemSummerFireworksProps()
	: ExplodeDamageAmount(0)
	, ExplodeDelayTime(3)
	{}

	std::vector<std::string> CanFiredByZombieTypes;
	float ExplodeDamageAmount;
	float ExplodeDelayTime;
};


class GridItemSummerFireworks : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemSummerFireworks, GridItemAnimation, RtClass);

	GridItemSummerFireworks();

	int CalcRenderOrder() const override;
//	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	void setState(SummerFireworksState i_state);
	void registerForEvents() override;

	virtual bool Activate();
	virtual bool Deactivate();

	bool ShouldClipWithWater() const override {return true;}
	void setValues(float i_hitpoints, float i_explodeAmount);

protected:
	void onGridItemInitialize() override;
//	void onPlaceOnBoard() override;
	void onUpdate() override;
	void onAnimDone(const std::string &i_animLabel);

	void onSummerFireworksStateChanged(int i_flg);

	bool canActivated();
	bool canDeactivated();
	virtual void onActivated();
//	virtual void onDeactivated();

	bool OverrideProjectileCollision(Projectile* i_projectile) override;
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;

	virtual void updateState();
	void CheckGridZombies();
	void throwPlant();

	virtual void onTakeDamage(const DamageInfo& i_damage);
	void OnAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);


	SummerFireworksState m_state;
	pvztime_t m_explodeTime;
	float m_explodeDamageAmount;
};

class GridItemSummerFireworksAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemSummerFireworksAnimRig, PopAnimRig, RtClass);

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
	void GridItemSummerFireworks(bool i_flg);
}



#endif /* GRIDITEM_SUMMERFIREWORKS_H_ */

//
//  ZombieExplosionProofPolice.h
//  PlantsVersusZombies2
//
//  Created by zhRed on 7/12/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieExplosionProofPolice_h
#define PlantsVersusZombies2_ZombieExplosionProofPolice_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieAnimRig_BeachBasic.h"
#include "ZombieWithActions.h"
#include "Projectile.h"
#include "GridItemPlantConditionTarget.h"

class BoardEntity;
class Effect_PopAnim;
class PlantGroup;
class Plant;

class ZombieExplosionProofPolice : public ZombieWithActions
{
public:
	RT_CLASS_DEFINE(ZombieExplosionProofPolice, ZombieWithActions, RtClass);
	PlantGroup* FindRangedTarget(std::vector<RtWeakPtr<BoardEntity> > i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity> >()) override;
protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	void onSetHelm() override;

	void onArmorDropped(std::string i_armorType) override;

	virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
	class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;

	virtual void refreshAnimRigForHelm();
	virtual void refreshHelmDamageState();

	bool isCanTargetFireGourd(Plant* target);
private:
	void onZombieInitialize() override;
	void doZap();
	pvztime_t m_nextCastTime = PVZ_EOT();

	int	m_helmDamageIndex;
};

class GridItemZombieGasSmoke : public GridItemPlantConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemZombieGasSmoke, GridItemPlantConditionTarget, RtClass);
	bool IsDamageable() const override;
	bool IsDamageableByPlants() const override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;

	void DestroySmoke();
	
};

class ZombieAnimRig_ExplosionProofPolice : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ExplosionProofPolice, ZombieAnimRig_Basic, RtClass) {}
	
protected:
	void onPopAnimInitialized() override;
	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::string getAttackAnimationName() override;
	virtual const std::string getEatAnimationName() override;
};

class ExplosionProofProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ExplosionProofProjectile, Projectile, RtClass) {}

	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool CollidesWithType(CollisionTypeFlags testTypes) const override;
	bool isCanTargetFireGourd(Plant* target);
};

#endif

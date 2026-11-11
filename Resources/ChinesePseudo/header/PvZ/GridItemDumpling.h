//
//  GridItemDumpling.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemDumpling__
#define __PlantsVersusZombies2__GridItemDumpling__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

enum DumplingState
{
	DUMPLING_IDLE,
	DUMPLING_UNDER_ATTACK,
	DUMPLING_DYING
};

class GridItemDumpling : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemDumpling, GridItemAnimation, RtClass);

	int CalcRenderOrder() const override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

	virtual void TakeDamage(const DamageInfo& i_damage) override;

protected:
	void onGridItemInitialize() override;
//	void onUpdate() override;
	void setState(DumplingState i_state);

private:
	void onAnimDone(const std::string& i_animName);
	void playAnimalIdle();
	void playAnimalDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void playAnimalUnderAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	DumplingState m_dumplingState = DUMPLING_IDLE;
};

// GridItemTurkey
enum TurkeyState
{
	TURKEY_IDLE,
	TURKEY_UNDER_ATTACK,
	TURKEY_DYING
};

class GridItemTurkey : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemTurkey, GridItemAnimation, RtClass);

	int CalcRenderOrder() const override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

	virtual void TakeDamage(const DamageInfo& i_damage) override;

protected:
	void onGridItemInitialize() override;
//	void onUpdate() override;
	void setState(TurkeyState i_state);

	void onAnimDone(const std::string& i_animName);
	void playAnimalIdle();
	void playAnimalDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void playAnimalUnderAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

protected:
	int m_state;
};


// GridItemTangYuan
enum TangYuanState : int
{
	TANGYUAN_IDLE,
	TANGYUAN_GUMZOMBIE,
	TANGYUAN_DYING
};

class GridItemTangYuan : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemTangYuan, GridItemAnimation, RtClass);
	GridItemTangYuan();

	int CalcRenderOrder() const override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

	virtual void TakeDamage(const DamageInfo& i_damage) override;

protected:
	void onGridItemInitialize() override;
//	void onUpdate() override;
	void setState(int i_state);

private:
	void GumZombie();
	bool CanGumZombie(ZombiePtr i_zombie);
	bool isInBlackList(ZombiePtr i_zombie);

	void onAnimDone(const std::string& i_animName);
	void playAnimalIdle();
	void playAnimalDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void playAnimalGumZombie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	int m_state = TANGYUAN_IDLE;
	int m_tangYuanNumber;
	ZombiePtr m_targetZombie;
}; 


#endif

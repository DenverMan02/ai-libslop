/*
 * 	GridItemPumpkinScarecrow.h
 *
 * 	Created on: 2022-8-24
 * 		Author: kkdud
 */

#ifndef __GRIDITEM_PUMPKIN_SCARECROW_H__
#define __GRIDITEM_PUMPKIN_SCARECROW_H__

#include "GridItemAnimation.h"

class GridItemPumpkinScarecrowProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemPumpkinScarecrowProps, GridItemAnimationProps, RtClass);

	GridItemPumpkinScarecrowProps()
	{
		Hitpoints = 1000.f;

	}

	std::vector<float> HitpointsPercentSeparators = { 0.66f, 0.33f, 0.f };
	float BirdEnterInterval = 10.f;
};

class GridItemPumpkinScarecrow : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemPumpkinScarecrow, GridItemAnimation, RtClass);

	GridItemPumpkinScarecrow();


	enum BirdPosType
	{
		BIRD_POSITION_TYPE_ON_INVALID = -1,
		BIRD_POSITION_TYPE_ON_LEFT,
		BIRD_POSITION_TYPE_ON_RIGHT,
		BIRD_POSITION_TYPE_ON_HEAD,
	};

	void onGridItemInitialize() override;
	void onUpdate() override;
	void onTakeDamage(const DamageInfo& i_damage) override;
	int CalcRenderOrder() const override;
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override	{ return true; }
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
    bool IsDamageableByPlants() const override { return true; }
    void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

	int calcDamageState();
	void setDamageState(int i_damageState);
	void onDamageStateChanged(int i_oldState);
	void startDying();
	void onDying();
	void onDeathAnimationDone(const std::string& i_animLabel);

	void updateBird();
	void flyInANewBird();
	void standUpNewBird();
	void flyOutABird();
	void pickBirdPosTypeToFlyOut();

	void playIdleWithoutBird();
	void playIdleWithBird();

	void playSpawnAnimation();
	void onSpawnAnimationDone(const std::string& i_animLabel);
	void thrownPlant();

	int m_damageState = -1;
	bool m_isDying = false;
	pvztime_t m_nextBirdEnterTime = PVZ_EOT();
	RtWeakPtr<Zombie> m_flyInBird = nullptr;
	bool m_birdHasFlewOut = false;
	BirdPosType m_nextFlyOutBirdPosType = BIRD_POSITION_TYPE_ON_INVALID;
};


#endif /* __GRIDITEM_PUMPKIN_SCARECROW_H__ */

//
//  GridItemBarrel.h
//  PlantsVersusZombies2
//
//

#ifndef GRIDITEMBARREL_H
#define GRIDITEMBARREL_H

#include "GridItemBoardEntityConditionTarget.h"



struct GriditemBarrelZombieDes
{
	int Level = 1;
	std::string TypeName = "pirate_imp";
};

struct GriditemBarrelParams
{
    float			BarrelHitPoints = 3000;
    float 			BarrelSpeed = 0.185;
	float			BarrelBlowDamageAmount = 3000;

	std::vector<GriditemBarrelZombieDes>		Zombies;
};

class GridItemBarrelProps : public GridItemBoardEntityConditionTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemBarrelProps, GridItemBoardEntityConditionTargetProps, RtClass);
	GridItemBarrelProps()
	: BarrelHitPoints({0, 0})
	, SpawnImpLevel({0, 0})
	, DamageAmount({0, 0}) {}


	float MoveVelocity = 0.2f;
	float AffectRadius = 0;
	float MoveTime = 50;

	std::vector<float>						BarrelHitPoints;
	std::vector<int>						SpawnImpLevel;
	std::vector<float>						DamageAmount;
	std::vector<GriditemBarrelZombieDes> 	Zombies;
};

class GridItemBarrel : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemBarrel, GridItemBoardEntityConditionTarget, RtClass);

public:
	void SetBarrelParams(GriditemBarrelParams i_params);
	static GridItemBarrel* AddGriditemWithParams(const std::string& i_gridItemTypeName, int i_gridX, int i_gridY, GriditemBarrelParams i_params, int i_level = 1);
	void TakeDamage(const DamageInfo& i_damage) override;

protected:
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void onGridItemInitialize() override;

	void onUpdate() override;
	void onDraw(Graphics* i_g) override;
    void updatePosition() override;
    Sexy::Rect calcCollisionRect() override;
	void SetFlyingDestinationWithTravelTime(Zombie* zombie, const SexyVector3 i_destination, const float i_timeToTravel, const float i_apex = 64.0f, bool i_invincibleWhileInAir = false);
	virtual void onBarrelBroken();

    virtual void crushEntities();

protected:
    void blowEntities();
    void spawnImp(const GriditemBarrelZombieDes i_zombieDes,const int i_row);
    void drawBarrelAnim(Graphics* i_g);

    float		m_barrelHitPoints = 3000;
    float 		m_barrelSpeed = 0.185;
	float		m_barrelBlowDamageAmount = 3000;

	std::vector<GriditemBarrelZombieDes>		m_zombies;

public:
	bool 		m_hasBroken = false;
};

// CardGameGridItemBarrel
class CardGameGridItemBarrel : public GridItemBarrel
{
public:
	RT_CLASS_DEFINE(CardGameGridItemBarrel, GridItemBarrel, RtClass);

protected:
	void onBarrelBroken() override;
	void onUpdate() override;
	void crushEntities() override;
};

class GridItemBarrelAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemBarrelAnimRig, PopAnimRig, RtClass);

    GridItemBarrelAnimRig() {}

    void PlayRoll();
};

namespace Message
{
	void OnZombiePowderKill(class Zombie* i_zombie);
}

#endif

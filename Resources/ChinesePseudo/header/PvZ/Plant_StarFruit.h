#ifndef __PLANT_STARFRUIT_H__
#define __PLANT_STARFRUIT_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"

class Zombie;

class StarFruitProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(StarFruitProjectile, Projectile, RtClass);
    
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class PlantStarFruit : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantStarFruit, PlantFramework, RtClass);

	virtual void 			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
    virtual Projectile*	    Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    ZombiePtr		FindTargetZombie(Rect& i_rect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    GridItemPtr		FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;

private:
	Projectile* fireProjectile(int i_index, ProjectilePropertySheetPtr i_projectileType, int i_pierceCount = 0);
    BoardEntityPtr FindTarget(PVZDB::TableIndex i_itemTableIndex);
	
	pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int m_shotsFired;
	int m_shotTotal;
	float m_rotation;
};

#endif //__PLANT_STARFRUIT_H__

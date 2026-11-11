//
//  ZombieZombossMech_Egypt.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/12/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Egypt__
#define __PlantsVersusZombies2__ZombieZombossMech_Egypt__

#include "ZombieZombossMech.h"

class ZombossRocket;

class ZombieZombossMechEgyptProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechEgyptProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechEgyptProps()
	{
		NumRocketGravestones = 2;
	}

	int NumRocketGravestones;
	ProjectilePropertySheetPtr BoneProjectileType;
};

class ZombieZombossMech_Egypt : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Egypt, ZombieZombossMech, RtClass);
    
    ZombieZombossMech_Egypt();
	
	void OnRocketHitGround(ZombossRocket* i_rocket) override;
    
    void DropAllLoot() override;
	
private:
	void getFreeSpacesNear(const Point& i_target, std::vector<Point>& o_freeSpaces) const;
	void pickRandomSpacesFrom(int i_numSpaces, const std::vector<Point>& i_allSpaces, std::vector<Point>& o_pickedSpaces) const;
	void tossGravestone(const Point& i_source, const Point& i_target);
    
    void OnZombieZombossDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Egypt__) */

#ifndef MeleePlantTargeter_h
#define MeleePlantTargeter_h

#include "Plant.h"

class GridItem;
class PlantFramework;
class Zombie;

class MeleePlantTargeter
{
public:
	enum TargetDirection
	{
		D_NONE,
		LEFT,
		RIGHT,
	};
	TargetDirection GetBestTargetDirection(Plant* i_plant, PlantWeapon i_plantWeapon, TargetDirection i_forbiddenDirection = TargetDirection::D_NONE);
	BoardEntity* GetBestTarget(Plant* i_plant, PlantWeapon i_plantWeapon, TargetDirection i_direction);
	std::vector<BoardEntity*> GetAdjacentTargets(Plant* i_plant, PlantWeapon i_plantWeapon);
	
private:
	bool hasZombieLeft(Plant* i_plant, PlantWeapon i_plantWeapon);
	bool hasZombieRight(Plant* i_plant, PlantWeapon i_plantWeapon);
	bool hasGridItemRight(Plant* i_plant, PlantWeapon i_plantWeapon);
	bool hasGridItemLeft(Plant* i_plant, PlantWeapon i_plantWeapon);
	GridItem* getGridItemTarget(Plant* i_plant, TargetDirection i_direction, PlantWeapon i_plantWeapon);
	Zombie* getZombieTarget(Plant* i_plant, TargetDirection i_direction, PlantWeapon i_plantWeapon);
	Rect getPlantAttackRect(Plant* i_plant, TargetDirection i_direction, PlantWeapon i_plantWeapon);
	PlantFramework* getPlantsFramework(Plant* i_plant);
};

#endif /* MeleePlantTargeter_h */

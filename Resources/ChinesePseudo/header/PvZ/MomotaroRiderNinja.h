/*
 * MomotaroRiderNinja.h
 *
 *  Created on: 2021-3-24
 *      Author: admin
 */

#ifndef MOMOTARORIDERNINJA_H_
#define MOMOTARORIDERNINJA_H_

#include "Plant_EggplantNinja.h"

class MomotaroRiderNinjaShuriken : public EggplantShuriken
{
public:
	RT_CLASS_DEFINE(MomotaroRiderNinjaShuriken, EggplantShuriken, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	//void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
};

class MomotaroRiderNinjaPropertySheet : public EggplantNinjaPropertySheet
{
public:
    RT_CLASS_DEFINE(MomotaroRiderNinjaPropertySheet, EggplantNinjaPropertySheet, RtClass);

    MomotaroRiderNinjaPropertySheet() : SearchGrids(1) {}

    int SearchGrids;
};

class MomotaroRiderNinja : public PlantEggplantNinja
{
public:
	RT_CLASS_DEFINE(MomotaroRiderNinja, PlantEggplantNinja, RtClass);

	bool CanApplyPlantfood() override;

	bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
};

namespace Message
{
    void TryKillRider();
}


#endif /* MOMOTARORIDERNINJA_H_ */

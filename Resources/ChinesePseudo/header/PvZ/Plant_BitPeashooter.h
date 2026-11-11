#ifndef __PLANT_BITPEASHOOTER_H__
#define __PLANT_BITPEASHOOTER_H__

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "PlantAnimRig_Peashooter.h"

class PlantBitPeashooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBitPeashooter, PlantFramework, RtClass);

	PlantBitPeashooter();

	virtual void			Initialize() override;
	virtual void			UpdateActions() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	void SetArtifactPraram(int i_extraDamageAmount, float i_timeToDie, bool i_random, int i_plantfoodNum);

protected:

	int GetProjectIndex();

    PeashooterPlantfood m_plantfood;
	int m_extraDamageAmount;
	float m_timeToDie;
	bool m_random;
	pvztime_t m_timer;
	int m_plantfoodNum;
};

#endif //__PLANT_PEASHOOTER_H__

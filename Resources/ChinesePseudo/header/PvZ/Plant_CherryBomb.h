#ifndef __PLANT_CHERRYBOMB_H__
#define __PLANT_CHERRYBOMB_H__

#include "PlantFramework.h"

/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class PlantCherryBomb : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCherryBomb, PlantFramework, RtClass) {}

	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
		
	void	Explode();
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;

	bool CanBeShoveled() override { return false; }
	bool CanBeTargeted() override { return false; }
	bool IsInvincible() const override { return true; }
    
private:
    
    bool ShouldGenerateSmallCherry();
};

#endif //__PLANT_CHERRYBOMB_H__

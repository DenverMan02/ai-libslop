#pragma once

#include "PlantFramework.h"
#include "PlantUtils.h"


class PlantRepeater : public PlantFramework 
{
public:
	RT_CLASS_DEFINE(PlantRepeater, PlantFramework, RtClass);

	virtual void Initialize() override;
private:
	enum States 
	{
		STATE_PLANTFOOD_FINALE  = STATE_FRAMEWORK_BEGIN,
	};

public:
	bool			CanApplyPlantfood() override;
	void			ApplyPlantfood() override;
	void 			UpdatePlantfood() override;
	void			CancelPlantfood() override;
	Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

private:
	virtual void	onAnimStoppedCallback(const std::string& i_animLabelName) override;

	PeashooterPlantfood m_plantfood;
};

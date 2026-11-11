//
//  Plant_PowerPlant.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_PowerPlant_h
#define PlantsVersusZombies2_Plant_PowerPlant_h

#include <string>

#include "PlantFramework.h"
#include "PlantType.h"
#include "RtObject.h"

class PlantPowerPlant : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPowerPlant, PlantFramework, RtClass);
	
	virtual void Initialize() override;
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
	virtual bool IsInvincible() const override;
	virtual bool CanBeShoveled() override;
	virtual bool HasShadow() override;
	
	bool HasCreatedTile() const
	{
		return m_createdTile;
	}
	
	int		CalcRenderOrder() override;
private:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void createTile();
	
	bool m_createdTile = false;
};

class PlantTypePowerPlant : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypePowerPlant, PlantType, RtClass) {}
	
	// PowerPlants rise in cost exponentially as the number of planted tiles increases
    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    
    // Powerplants can be planted on top of anything
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

#endif


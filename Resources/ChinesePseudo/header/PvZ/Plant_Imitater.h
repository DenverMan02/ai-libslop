//
//  Plant_Imitater.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Imitater_h
#define PlantsVersusZombies2_Plant_Imitater_h

#include "PlantFramework.h"

class PlantImitater : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantImitater, PlantFramework, RtClass);
	
	void SetImitatedPlant(PlantTypePtr i_plantType);
	
	PlantTypePtr GetImitatedPlant() const
	{
		return m_imitatedPlant;
	}
	
	bool HasSpawnedReplacement() const
	{
		return m_startedSwapping;
	}
	
	virtual void Initialize() override;
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual bool IsInvincible() const override;
	virtual bool CanBeShoveled() override;
	virtual bool HasShadow() override;
    void SyncPlantBoost(PlantBoostType type, PlantTypePtr plantType);
	
private:
	void swapForImitatedPlant();
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	
	PlantTypePtr m_imitatedPlant;
	bool m_startedSwapping = false;
};

#endif

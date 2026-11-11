//
//  BowlingMinigame.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 8/26/2014.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_BowlingMinigame_h
#define PlantsVersusZombies2_BowlingMinigame_h

#include <vector>

#include "Core.h"
#include "LevelModule.h"
#include "BoardEnums.h"

class PlantType;
class Plant;

class BowlingMinigameModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(BowlingMinigameModule, LevelModule, RtClass);

protected:

	void	initializeModule() override;
	void	registerForEvents() override;
	void	postInitialize() override;

private:

	void addToRenderQueue(class RenderQueue* i_queue);
	void onDraw(Graphics* i_g);
	void disableUI();

    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    void gatherPlantlessPlantingRestrictions(const Sexy::Point &i_gridPosition, std::vector<PlantingReason> *io_plantingReasons);

    int m_FoulLine = 0;
};

class BowlingMinigameProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(BowlingMinigameProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return BowlingMinigameModule::StaticGetClass();
	}

	BowlingMinigameProperties()
	{
		BowlingFoulLine = 8;
	}
	int BowlingFoulLine;
};

#endif //PlantsVersusZombies2_BowlingMinigame_h

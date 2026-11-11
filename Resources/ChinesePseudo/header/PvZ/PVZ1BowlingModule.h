// PVZ1BowlingModule.h
// create by lfy
// 2023.07.12

#ifndef __PVZ1BOWLINGMODULE_H__
#define __PVZ1BOWLINGMODULE_H__

#include "EgyptStage.h"
#include "BoardEnums.h"
#include "PlantType.h"

class NewBowlingMinigameModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(NewBowlingMinigameModule, LevelModule, RtClass);

protected:
    void registerForEvents() override;
    void unregisterForEvents() override;
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames);
private:
    void onGatherPlantlessPlantingRestrictions(const Sexy::Point& i_atLocation, std::vector<PlantingReason> *io_plantingErrors); 
    void disableUI();
    void addForegroundToRenderQueue(RenderQueue* i_queue);
    void renderForeground(Graphics* i_g);
};

class NewBowlingMinigameProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(NewBowlingMinigameProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return NewBowlingMinigameModule::StaticGetClass();
	}
};

#endif
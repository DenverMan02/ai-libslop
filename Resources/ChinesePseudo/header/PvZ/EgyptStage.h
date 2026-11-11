#ifndef PlantsVersusZombies2_EgyptStage_h
#define PlantsVersusZombies2_EgyptStage_h

#include "StageModule.h"

class EgyptStage : public StageModule
{
public:
    RT_CLASS_DEFINE(EgyptStage, StageModule, RtClass);
	
protected:
	virtual void registerForEvents() override;
	virtual void onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to) override;
	virtual void stopZombieGroans() override;
	
private:
	void					onGameWon();
	void					onLoadComplete();
};

class EgyptStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(EgyptStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return EgyptStage::StaticGetClass();
	}
	
};

#endif

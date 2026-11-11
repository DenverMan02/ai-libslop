#ifndef PlantsVersusZombies2_KongFuStage_h
#define PlantsVersusZombies2_KongFuStage_h

#include "StageModule.h"

class KongFuStage : public StageModule
{
public:
    RT_CLASS_DEFINE(KongFuStage, StageModule, RtClass);
    
protected:
	virtual void renderBackground(Graphics* i_g) override;
	virtual void registerForEvents() override;
	virtual void onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to) override;
	virtual void stopZombieGroans() override;
	
	virtual void onPostLoad() override;

private:
	void parseGearImages();

	/// Transient
	//ImagePtr m_gear;

};

class KongFuStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(KongFuStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return KongFuStage::StaticGetClass();
	}
	
	//std::string GearImage;
    
    bool HaveGearBG;
};

#endif

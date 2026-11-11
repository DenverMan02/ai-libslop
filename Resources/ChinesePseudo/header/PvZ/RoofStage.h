#include "StageModule.h"

class RoofStage : public StageModule
{
public:
    RT_CLASS_DEFINE(RoofStage, StageModule, RtClass);
	
protected:
	virtual void registerForEvents() override;
	
	virtual void onLevelLoaded() override;

private:
	void onLoadComplete();
	
};

class RoofStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(RoofStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return RoofStage::StaticGetClass();
	}	

	PlantRestrictionSet PlantsWhichCannotBePlantedOnRoof;
	PlantRestrictionSet PlantsWhichCanBeUpdateOnRoof;
};

class BoardRegionRoof : public BoardRegion
{
public:
    RT_CLASS_DEFINE(BoardRegionRoof, BoardRegion, RtClass);
    
    BoardRegionRoof();
    
    void GatherPlantingRestrictions(const Sexy::Point &i_atLocation, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors) override;    
protected:
	void onUpdate() override;

	RtWeakPtr<RoofStageProperties> m_cacheProps;
};
// PVZ1SeeingStarsModule.h
// create by lfy
// 2023.05.29


#ifndef __PVZ1SEEINGSTARSMODULE_H__
#define __PVZ1SEEINGSTARSMODULE_H__

#include "LevelModule.h"
#include "Wave.h"
#include "BoardEnums.h"

struct MatchPlantData
{
    MatchPlantData() : MatchPlantGridX(0), 
                     MatchPlantGridY(0),
                     MatchTypeName("sunflower")
                     {}
    int MatchPlantGridX;
    int MatchPlantGridY;
    std::string MatchTypeName;
};

class PVZ1SeeingStarsModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(PVZ1SeeingStarsModule, LevelModule, RtClass);
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    PVZ1SeeingStarsModule();
    ~PVZ1SeeingStarsModule();
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void postInitialize() override;
private:
    void playPlantShadowEffect();
    void onLoadComplete();
    void onUpdate();
    bool isWonGame();
    void onPlantPlaced(class Plant* i_plant);
    void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> * io_plantingErrors);
    void playPlacedEffect(const Sexy::Point& i_atLocation);
    bool checkWinCondition();    
private:
    pvztime_t m_finishStamp;
    bool m_isWon;
};

class PVZ1SeeingStarsModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PVZ1SeeingStarsModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return PVZ1SeeingStarsModule::StaticGetClass();
	}
    std::vector<MatchPlantData> MatchPlants;
    int CycleIndex;
    pvztime_t SettlementDuration;
};



#endif
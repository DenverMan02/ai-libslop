#ifndef HeroPlantModule_H_
#define HeroPlantModule_H_

#include "LevelModule.h"
#include "RtDb.h"

class HeroPlantModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(HeroPlantModule, LevelModule, RtClass);

	HeroPlantModule();
	~HeroPlantModule();

	void StopCollect();

protected:
	void registerForEvents() override;

private:
	void onInit();
	void onPaidSunmoneyAtGridForPlant(int i_sunCost, int i_gridX, int i_gridY);
	

	bool m_hasInit;
	bool m_stopCollect;
};

class HeroPlantModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(HeroPlantModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return HeroPlantModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> LevelBlacklist;
};

#endif

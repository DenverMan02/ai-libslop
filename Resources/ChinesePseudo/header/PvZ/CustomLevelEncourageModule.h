
#ifndef CUSTOM_LEVEL_ENCOURAGE_MODULE_H_
#define CUSTOM_LEVEL_ENCOURAGE_MODULE_H_

#include "LevelModule.h"
#include "RtDb.h"

class CustomLevelEncourageModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CustomLevelEncourageModule, LevelModule, RtClass);

	CustomLevelEncourageModule();
	~CustomLevelEncourageModule();

	bool CanBuySunmoney();
	bool CanBuyPlantfood();
	bool CanBuyMower();

protected:
	void registerForEvents() override;

	void OnLoadStarted();
	void OnGameplayStarted();

};

class CustomLevelEncourageModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CustomLevelEncourageModuleProperties, LevelModuleProperties, RtClass);

    CustomLevelEncourageModuleProperties()
    :BuySunmoney(true),
    BuyPlantfood(true),
    BuyMower(true)
    {

    }

	RtClass* GetModuleClass() const override
	{
		return CustomLevelEncourageModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

    bool BuySunmoney;
	bool BuyPlantfood;
	bool BuyMower;
};

#endif
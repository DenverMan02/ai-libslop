/*
 * CustomLevelModule.h
 *
 *  Created on: 2021-12-2
 *      Author: admin
 */

#ifndef CUSTOMLEVELMODULE_H_
#define CUSTOMLEVELMODULE_H_

#include "LevelModule.h"
#include "RtDb.h"

class CustomLevelModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CustomLevelModule, LevelModule, RtClass);

	CustomLevelModule();
	~CustomLevelModule();

protected:
	void registerForEvents() override;

	void OnLoadStarted();
	void OnGameplayStarted();

};

class CustomLevelModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CustomLevelModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return CustomLevelModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};


#endif /* CUSTOMLEVELMODULE_H_ */

/*
 * PennyClassroomModule.h
 *
 *  Created on: 2022-2-21
 *      Author: zhousen
 */

#ifndef PENNYCLASSROOMMODULE_H_
#define PENNYCLASSROOMMODULE_H_

#include "LevelModule.h"
#include "RtDb.h"

class PennyClassroomModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PennyClassroomModule, LevelModule, RtClass);

	~PennyClassroomModule();

protected:
	void registerForEvents() override;
};

class PennyClassroomModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PennyClassroomModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return PennyClassroomModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	int GetPlantLevel(std::string name);

	std::map<std::string, int> PlantMap;
};

// Preview Plant Module
class PresetPlantModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PresetPlantModule, LevelModule, RtClass);

	~PresetPlantModule();

protected:
	void registerForEvents() override;
};

class PresetPlantModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PresetPlantModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return PresetPlantModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	int GetPlantLevel(std::string name);
	bool IsPlant(std::string name);

	std::map<std::string, int> PlantMap;
};

#endif /* PENNYCLASSROOMMODULE_H_ */

/*
 * ArtifactModule.h
 *
 *  Created on: 2021-6-1
 *      Author: admin
 */

#ifndef ARTIFACTMODULE_H_
#define ARTIFACTMODULE_H_

#include "LevelModule.h"
#include "RtDb.h"

class ArtifactModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ArtifactModule, LevelModule, RtClass);

	~ArtifactModule();

protected:
	void registerForEvents() override;


private:
	void initializeArtifacts();
	void onInit();
	void onArtifactInit();
};

class ArtifactModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ArtifactModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return ArtifactModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> LevelBlacklist;
};


#endif /* ARTIFACTMODULE_H_ */

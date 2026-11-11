/*
 * RiftThemeModule.h
 *
 *  Created on: 2020-6-3
 *      Author: Administrator
 */

#ifndef RIFTTHEMEMODULE_H_
#define RIFTTHEMEMODULE_H_

#include "LevelModule.h"
#include "RtDb.h"
#include "RiftTheme.h"

class RiftThemeModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(RiftThemeModule, LevelModule, RtClass);

	~RiftThemeModule();

protected:
	void registerForEvents() override;


private:
	void initializeThemes();
	void onInit();
};

struct ThemeDisabledInfo
{
	ThemeDisabledInfo()
	: Type(Theme_Projectile_Hell)
	{

	}

	ThemeType Type;
	std::vector<std::string> LevelBlacklist;
};

class RiftThemeModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return RiftThemeModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> LevelBlacklist;
	std::vector<ThemeDisabledInfo> ThemeDisabledInfos;
};


#endif /* RIFTTHEMEMODULE_H_ */

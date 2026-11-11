/*
 * RiftThemeMgr.h
 *
 *  Created on: 2020-6-3
 *      Author: Administrator
 */

#ifndef RIFTTHEMEMGR_H_
#define RIFTTHEMEMGR_H_

#include "RiftTheme.h"
#include "Singleton.h"

struct ThemeData
{
	ThemeData()
	{
		PropsPtr = RiftThemePropertiesPtr();
	}
	RiftThemePropertiesPtr PropsPtr;
};

class RiftThemeMgr : public LazySingleton<RiftThemeMgr>
{
public:
	RiftThemeMgr();
	virtual ~RiftThemeMgr();

	void AddThemeModuleIfNeeded();

	bool IsThemeDisabled(const std::string& i_levelName);
	bool IsCurrentLevelThemeDisabled();

	bool IsThemeDisabled(ThemeType i_type, const std::string& i_levelName);

	std::vector<ThemeData> GetThemeList();

	ThemeData CreateThemeData(std::string i_themeName);

	void SyncTheme(int i_themeType);
	void SyncTheme(const std::vector<int>& i_themeTypes);

	RiftMainThemePropertiesPtr GetMainThemeById(ThemeType i_type);

	std::string GetThemeName(int i_type);
	std::string GetThemeDescription(int i_type);

	std::string GetModeName(int i_type);
	std::string GetModeDescription(int i_type);

private:
	bool themeDisabled(const std::string& i_levelName);
	bool themeDisabled(ThemeType i_type, const std::string& i_levelName);
	void syncTheme(int i_themeType);
	void addTheme(std::string i_themeName);
	void handleRandomTheme(const std::vector<std::string>& i_list);

	std::vector<ThemeData> m_currentThemeList;
};


#endif /* RIFTTHEMEMGR_H_ */

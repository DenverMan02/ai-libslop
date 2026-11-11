//
//  HotUIManager.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIManager__
#define __PlantsVersusZombies2__HotUIManager__

#include <string>
#include <vector>

#include "HotUIWidget.h"
#include "Singleton.h"

namespace Sexy {
class RtId;
}  // namespace Sexy

// TODO: Add test for UI json files for name conflicts and parties.
class HotUIManager : public LazySingleton<HotUIManager>
{
public:

	HotUIManager();

	// UI Loading and Unloading
	class HotUIFile*	LoadUIFile(const std::string& i_uiFileName);
	class HotUIFile*	LoadUIFile(const std::string& i_uiFileName, const HotUIStringMap& i_stringMap);
	HotUIFile*			LoadUIFile(const std::string& i_uiFileName, const HotUIStringMap& i_stringMap, WidgetContainer* i_parent);
	
	HotUIFile*			LoadUIPrefab(const std::string& i_uiFileName, const HotUIStringMap& i_stringMap, WidgetContainer* i_parent);
	
	
	void				UnloadUIFile(class HotUIFile* i_uiFile);
	void				UnloadLastUIFile();

	// LiveLink Hooks
	void				UpdateCurrentUIFromLiveLinkUpdate(const RtId& i_rtID);
	bool				IsUIFileLoaded(const std::string& i_uiFileName);
	
	// UI File Getters
	class HotUIFile*	GetUIFileForWidget(HotUIWidgetPtr i_widgetPtr);
	class HotUIFile*	GetLastUIFile() { return m_lastLoadedUIFile; }
    
    // Component Updater
    void                UpdateComponents();
	
private:

	HotUIFile*			populateWidgetsFromFile(const std::string& i_uiFileName, const HotUIStringMap& i_stringMap, WidgetContainer* i_parent);
	bool				loadUIFile(const std::string& i_uiFileName, PVZDB::TableIndex i_intoTable);
	HotUIWidgetPtr		createUIFromPropertySheet(const HotUIWidgetPropertiesPtr i_propSheet, const HotUIStringMap& i_stringMap);
    HotUIComponentPtr   createComponentFromPropertySheet(const HotUIComponentPropertiesPtr i_propSheet);

	void				removePropertySheetChildrenFromWidget(HotUIWidgetPtr i_widget);
	
	std::vector<class HotUIFile*>	m_loadedUIFiles;
	
	// This is currently for testing, should be a vector in the future
	class HotUIFile* m_lastLoadedUIFile;
};

#endif /* defined(__PlantsVersusZombies2__HotUIManager__) */

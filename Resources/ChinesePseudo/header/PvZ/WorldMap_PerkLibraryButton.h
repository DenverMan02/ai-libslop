//
//  WorldMap_PerkLibraryButton.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 9/12/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef WorldMap_PerkLibraryButton_h
#define WorldMap_PerkLibraryButton_h

#include "UIWidgetSheet.h"
#include "UIButtonWidget.h"

class WorldMap_PerkLibraryButton : public UIButtonWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_PerkLibraryButton, UIButtonWidget, RtClass);
	
	WorldMap_PerkLibraryButton();
	
protected:
	void onPerkLibraryClosed();
	void performButtonAction() override;
	void initLoadingResourcesGroupList() override;
    void onLoadComplete() override;

	class AdaptorPerkLibraryTabbedDialog* m_perkLibrary;
};

#endif /* WorldMap_PerkLibraryButton_h */

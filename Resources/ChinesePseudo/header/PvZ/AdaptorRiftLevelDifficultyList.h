//
//  AdaptorRiftDifficultyList
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/1/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftDifficultyList_h
#define AdaptorRiftDifficultyList_h

#include "HotUIAdaptor.h"
#include "MapEventItem.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "RtObject.h"

class AdaptorRiftLevelDifficultyEntry;
//class AdaptorLevelZombieResistanceItem;
struct RiftLevelDifficultyData;

class AdaptorRiftDifficultyList : public HotUIAdaptor, Sexy::ScrollWidgetListener
{
public:
	RT_CLASS_DEFINE(AdaptorRiftDifficultyList, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorRiftDifficultyList();
	virtual ~AdaptorRiftDifficultyList();
	
	void Configure(Sexy::WidgetContainer *i_parent, const std::string& i_levelName, MapEventSubType i_eventSubType, std::string i_uiFile = "RiftDifficultyList");
	void Update() override;
    void RefreshDifficultyView();
	void RefreshScrollArrows();

	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) {}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) {}

protected:
    void onLoadUIView() override;
    void onLinkToUIViewCreated() override;

private:
    void removeDifficultyWidgets();
    void sortDifficultyEntries(RiftLevelDifficultyData& io_difficultyData);
    
    WidgetContainer* m_parent;
    std::string m_levelName;
    MapEventSubType m_eventSubType;
	std::string m_uiFile;

    std::vector<AdaptorRiftLevelDifficultyEntry*> m_difficultyEntries;
    //std::vector<AdaptorLevelZombieResistanceItem*> m_resistanceEntries;
    
};


#endif

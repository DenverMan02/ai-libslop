//
//  AdaptorRiftLevelDifficultyEntry.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/2/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftLevelDifficultyEntry_h
#define AdaptorRiftLevelDifficultyEntry_h

#include "AwardEnums.h"
#include "HotUIAdaptor.h"
#include "LevelModule.h"
#include "RiftUtils.h"

class AdaptorRiftLevelDifficultyEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorRiftLevelDifficultyEntry, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorRiftLevelDifficultyEntry()
		: m_parent(nullptr)
	{}
	
	void Configure(WidgetContainer* i_parent, RtWeakPtr<LevelModuleDifficultyUIProps> i_config);
	
protected:
	void onLoadUIView() override;
	
private:
	WidgetContainer* m_parent;
	RtWeakPtr<LevelModuleDifficultyUIProps> m_config;
};

#endif

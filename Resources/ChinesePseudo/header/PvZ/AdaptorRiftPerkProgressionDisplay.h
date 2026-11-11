//
//  AdaptorRiftPerkProgressionDisplay.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 8/13/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftPerkProgressionDisplay_h
#define AdaptorRiftPerkProgressionDisplay_h

#include "Curve.h"
#include "HotUIAdaptor.h"
#include "RtObject.h"

class AdaptorRiftPerkProgressionDisplay : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRiftPerkProgressionDisplay, HotUIAdaptor, RtClass);
    AdaptorRiftPerkProgressionDisplay();
	virtual ~AdaptorRiftPerkProgressionDisplay();
	
	void Update() override;
	void ShowProgressAnimation();
	Point GetScrollPoint();
    
    SexyVector2 GetSizeOfPerkRegion();
	
protected:
	void onLinkToUIViewCreated() override;
	void refresh();
	
	std::vector<int> getWidgetXLocations();
	
private:
	void positionProgressBar(float i_progress);
	void startEntryAnimation(class AdaptorRiftPerkProgressionDisplayEntry* i_entry);
	void finishEntryAnimation(class AdaptorRiftPerkProgressionDisplayEntry* i_entry);
	
	int m_previousProgress;
	bool m_showAnimation;
	Curve<float> m_barAnimationCurve;
	Curve<int> m_numberIncrementCurve;
	std::vector<class AdaptorRiftPerkProgressionDisplayEntry*> m_entries;
	std::vector<class AdaptorRiftPerkProgressionDisplayEntry*> m_animatingEntries;
};

#endif /* AdaptorRiftPerkProgressionDisplay_h */

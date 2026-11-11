//
//  AdaptorPerkProgressionWidget.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 8/12/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorPerkProgressionWidget_h
#define AdaptorPerkProgressionWidget_h

#include "HotUIAdaptor.h"
#include "RtObject.h"

class AdaptorPerkProgressionWidget : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorPerkProgressionWidget, HotUIAdaptor, RtClass);
	
	AdaptorPerkProgressionWidget()
	{
		m_numScrollChecks = 0;
	}
	
	virtual ~AdaptorPerkProgressionWidget();
	void Update() override;
	void ShowProgressAnimation();
	
protected:
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
private:
	HotUIAdaptor* m_perkProgression;
	int m_numScrollChecks;
};

#endif /* AdaptorPerkProgressionWidget_h */

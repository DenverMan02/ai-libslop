//
//  AdaptorPerkLibraryWidget
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 9/12/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorPerkLibraryWidget_h
#define AdaptorPerkLibraryWidget_h

#include "AdaptorPerkInfoWidget.h"
#include "HotUIAdaptor.h"
#include "RtDb.h"

class AdaptorPerkLibraryWidget : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorPerkLibraryWidget, HotUIAdaptor, RtClass);
public:
	AdaptorPerkLibraryWidget();
	~AdaptorPerkLibraryWidget();
	
protected:
	void onLinkToUIViewCreated() override;
	void createPerkScrollList();
	
private:
	std::vector<AdaptorPerkInfoWidget*> m_perkWidgets;
};

#endif /* AdaptorPerkLibraryWidget */

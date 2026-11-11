//
//  AdaptorCarouselDotEntry.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 10/27/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorCarouselDotEntry_h
#define AdaptorCarouselDotEntry_h

#include "HotUIAdaptor.h"
#include "RtObject.h"

class AdaptorCarouselDotEntry : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorCarouselDotEntry, HotUIAdaptor, RtClass);
	
	void Configure(Sexy::WidgetContainer* i_parent);
	void SetFilled(bool i_filled);
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	Sexy::WidgetContainer* m_parent = nullptr;
	HotUIWidget* m_fillWidget = nullptr;
};


#endif

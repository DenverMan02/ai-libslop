//
//  AdaptorCarouselDots.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 10/27/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorCarouselDots_h
#define AdaptorCarouselDots_h

#include "HotUIAdaptor.h"
#include "RtObject.h"
#include <vector>

class AdaptorCarouselDotEntry;

class AdaptorCarouselDots : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorCarouselDots, HotUIAdaptor, RtClass);
	
	virtual ~AdaptorCarouselDots();
	//AdaptorCarouselDots& operator=(const AdaptorCarouselDots&) = delete;
	//AdaptorCarouselDots(const AdaptorCarouselDots&) = delete;
	
	void Configure(Sexy::WidgetContainer* i_parent, size_t numDots);
	void SetFilledDot(int dotIndex);
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	Sexy::WidgetContainer* m_parent = nullptr;
	size_t m_numDots = 0;
	std::vector<AdaptorCarouselDotEntry*> m_dotWidgets;
};

#endif

//
//  AdaptorJoustWinStreakDisplay.hpp
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 8/16/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustWinStreakDisplay_h
#define AdaptorJoustWinStreakDisplay_h

#include "HotUIAdaptor.h"
#include "RtObject.h"

class AdaptorJoustWinStreakDisplay : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustWinStreakDisplay, HotUIAdaptor, RtClass);
	AdaptorJoustWinStreakDisplay();
	~AdaptorJoustWinStreakDisplay();
public:
	void ShowCheckmarkAnimation();

protected:
	void onLinkToUIViewCreated() override;
	
private:
	void refresh();
	bool m_showCheckmarkAnimation;
};


#endif /* AdaptorJoustWinStreakDisplay_h */

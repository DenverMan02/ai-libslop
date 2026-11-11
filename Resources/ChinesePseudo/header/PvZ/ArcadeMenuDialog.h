//
//  ArcadeMenuDialog.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 6/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadeMenuDialog__
#define __PlantsVersusZombies2__ArcadeMenuDialog__

#include "HotUIAdaptor.h"

//class ArcadeMenu;

class ArcadeMenuDialog : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(ArcadeMenuDialog, HotUIAdaptor, Sexy::RtClass);
	
//	void SetMenuController(ArcadeMenu* i_menuController) { m_menuController = i_menuController; }
//	ArcadeMenu* GetMenuController() const { return m_menuController; }
	
	virtual void RefreshUnlockStatus() {}
	virtual ArcadeMenuDialog* Clone() const;
	
//private:
//	ArcadeMenu* m_menuController;
};

#endif /* defined(__PlantsVersusZombies2__ArcadeMenuDialog__) */

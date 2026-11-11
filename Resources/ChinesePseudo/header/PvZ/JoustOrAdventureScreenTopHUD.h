//
//  JoustOrAdventureScreenTopHUD.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/29/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustOrAdventureScreenTopHUD_h
#define JoustOrAdventureScreenTopHUD_h

#include "PVZGameStateTopHUDController.h"

class JoustOrAdventureScreenTopHUD : public PVZGameStateTopHUDController
{
public:
	RT_CLASS_DEFINE(JoustOrAdventureScreenTopHUD, PVZGameStateTopHUDController, Sexy::RtClass);
	
	void Open() override;
	
	void onShowingFUEChanged(bool i_showingFUE);
	
	bool canHandleInput() const override { return (m_showingFUE == false) && SuperClass::canHandleInput(); };
	
private:
	bool m_showingFUE = false;
	
};

#endif /* JoustOrAdventureScreenTopHUD_h */

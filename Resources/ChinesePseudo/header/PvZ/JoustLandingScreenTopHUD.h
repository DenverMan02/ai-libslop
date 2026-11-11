//
//  JoustLandingScreenTopHUD.hpp
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/17/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustLandingScreenTopHUD_hpp
#define JoustLandingScreenTopHUD_hpp

#include "PVZGameStateTopHUDController.h"

class JoustLandingScreenTopHUD : public PVZGameStateTopHUDController
{
public:
	RT_CLASS_DEFINE(JoustLandingScreenTopHUD, PVZGameStateTopHUDController, Sexy::RtClass);
	
	void Open() override;
};

#endif /* JoustLandingScreenTopHUD_hpp */

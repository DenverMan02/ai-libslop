//
//  EffectAnimRig_SwitchTile.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/28/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_SwitchTile__
#define __PlantsVersusZombies2__EffectAnimRig_SwitchTile__

#include "PopAnimRig.h"
#include "RtObject.h"

class EffectAnimRig_SwitchTile: public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_SwitchTile, PopAnimRig, RtClass);
	
	void SetBaseAnimName(const std::string& i_baseAnimName);
	
	void PlaySwitchUp();
	void PlaySwitchDown();
	
private:
	void onPopAnimInitialized() override;
	
	std::string m_upAnimName;
	std::string m_downAnimName;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_SwitchTile__) */

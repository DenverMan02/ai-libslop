//
//  ZombieAnimRig_PirateBarrel.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_PIRATEBARREL_H__
#define __ZOMBIEANIMRIG_PIRATEBARREL_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_PirateBarrel : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_PirateBarrel, ZombieAnimRig, RtClass);
	
	ZombieAnimRig_PirateBarrel();
	
	virtual void			SetLayerVisibilityForCurrentState();
	virtual void			SetBarrelDamageIndex(int i_newIndex);
	
	virtual SexyVector2 GetHeadOffset() override;

	void PlayRoll();
	
protected:
	virtual void			onPopAnimInitialized() override;
	virtual void			onNeedsToDie() override;
	
private:
	int						m_barrelDamageIndex;
};

#endif //__ZOMBIEANIMRIG_PIRATEBARREL_H__

//
//  ZombieAnimRig_DiscoMech.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_DiscoMech_h
#define PlantsVersusZombies2_ZombieAnimRig_DiscoMech_h

#include "ZombieAnimRig_Mech.h"

class ZombieAnimRig_DiscoMech : public ZombieAnimRig_Mech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DiscoMech, ZombieAnimRig_Mech, RtClass);

	ZombieAnimRig_DiscoMech();

	void StartDance();
	void DanceIdle();
	void EndDance();

	bool DanceHasEnded();
    
    void SetDamageState(int i_damageState) override;


private:
	void onDanceStartEnd(const std::string&);
	void onDanceIdleLooped(const std::string&, const std::string&, int);
	void onDanceEndEnd(const std::string&);
	bool m_endDance;
};

#endif

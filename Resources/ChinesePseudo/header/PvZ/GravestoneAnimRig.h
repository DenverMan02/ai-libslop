//
//  GravestoneAnimRig.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 10/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GravestoneAnimRig_h
#define PlantsVersusZombies2_GravestoneAnimRig_h

#include "PopAnimRig.h"
#include "RtDb.h"
#include "RtObject.h"

typedef RtWeakPtr<class GravestoneAnimRig> GravestoneAnimRigPtr;

class GravestoneAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GravestoneAnimRig, PopAnimRig, RtClass);
	
	virtual void SetDamageState(int i_damageState, bool i_isAnimated);
};

#endif

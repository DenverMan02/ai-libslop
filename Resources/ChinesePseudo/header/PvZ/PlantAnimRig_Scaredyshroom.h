//
//  PlantAnimRig_Scaredyshroom.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 8/30/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_SCAREDYSHROOM_H__
#define __PLANTANIMRIG_SCAREDYSHROOM_H__

#include <string>

#include "PlantAnimRig.h"
#include "RtObject.h"
#include "TimeMgr.h"

enum PlantAnimRigState_Scaredyshroom
{
	PLANTANIM_SCAREDYSHROOM_SCARED = PLANTANIM_USERDEFINED,
};

class PlantAnimRig_Scaredyshroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Scaredyshroom, PlantAnimRig, RtClass);
	
	virtual bool PlayScaredLooped();
	
protected:
	virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
};

#endif // __PLANTANIMRIG_SCAREDYSHROOM_H__

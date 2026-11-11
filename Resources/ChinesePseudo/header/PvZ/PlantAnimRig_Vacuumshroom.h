//
//  PlantAnimRig_Vacuumshroom.h
//  PlantsVersusZombies2
//
//  Created by Scott Eberline on 10/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef _PLANT_ANIM_RIG_VACUUM_SHROOM_H_
#define _PLANT_ANIM_RIG_VACUUM_SHROOM_H_

#include "PlantAnimRig.h"

enum PlantAnimRigStateVacuumshroom
{
	PLANTANIM_VACUUMSHROOM_VACUUMING = PLANTANIM_USERDEFINED,
};


class PlantAnimRig_Vacuumshroom : public PlantAnimRig
{
    
public:
	RT_CLASS_DEFINE(PlantAnimRig_Vacuumshroom, PlantAnimRig, RtClass);

	virtual bool	PlayVacuumAndStop();
	
	bool			IsVacuumPlaying() const;

protected:
	virtual const std::vector<std::string>&	getArmorStateLayerNames() const;
	
private:
	void			onVacuumingFinished(const std::string&);
    
};

#endif  // !defined(_PLANT_ANIM_RIG_VACUUM_SHROOM_H_)

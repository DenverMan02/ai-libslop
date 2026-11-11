#ifndef __PLANTANIMRIG_SHIELDED_H
#define __PLANTANIMRIG_SHIELDED_H

#include "PlantAnimRig.h"

class PlantAnimRig_Shielded : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE_ABSTRACT(PlantAnimRig_Shielded, PlantAnimRig, RtClass);

	virtual int GetArmorStateCount() = 0;
	virtual void SetArmorStateIndex(int i_index) = 0;
};

#endif

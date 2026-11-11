//
//  DamageFrost.h
//  PlantsVersusZombies2
//
//  Created by JEmery on 10/13/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

//
// Frost is implemented using a zone-styled system.
// Each stage of frostiness has a range.  Entering a stage snaps you into the middle of that new stage's range.
//
// This gives us a configurable resistance to changing zones, which avoids rapid jiggling back and forth if minor heat/cold emitters are nearby.
// It also lets us ensure we can jump one zone at a time at fixed intervals and start at a known point in the new zone.
//
// A downside to this is that we could slide up and down within a zone for some time without a visual change.
//
//	Zone  0           1           2           3
//	=====]o-----|-----o-----|-----o-----|-----o[====
//
//	o			Center snap points when entering a zone.
//  ==] [==		End boundary (cannot cross)
//	|			Zone boundary
//

#ifndef PlantsVersusZombies2_DamageFrost_h
#define PlantsVersusZombies2_DamageFrost_h

#include "DamageInfo.h"

// Frost Values
const int ICEAGE_FROST_STAGE_SIZE = 100;
const int ICEAGE_FROST_STAGE_ENTER_FROM_LESS_OFFSET = 50;	// Snap +X into the new level when coming from below
const int ICEAGE_FROST_STAGE_ENTER_FROM_MORE_OFFSET = 50;	// Snap -X into the new level when coming from above
const int ICEAGE_FROST_AMOUNT_TINY = 10;
const int ICEAGE_FROST_AMOUNT_MODERATE = 25;
const int ICEAGE_FROST_AMOUNT_STAGE = ICEAGE_FROST_STAGE_SIZE;

const int ICEAGE_FROST_STAGE_MINIMUM = 0;
const int ICEAGE_FROST_STAGE_MAXIMUM = 3;
const int ICEAGE_FROST_MINIMUM = (ICEAGE_FROST_STAGE_MINIMUM * ICEAGE_FROST_STAGE_SIZE) + ICEAGE_FROST_STAGE_ENTER_FROM_LESS_OFFSET;
const int ICEAGE_FROST_MAXIMUM = (ICEAGE_FROST_STAGE_MAXIMUM * ICEAGE_FROST_STAGE_SIZE) + ICEAGE_FROST_STAGE_ENTER_FROM_LESS_OFFSET;

class FrostInfo : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(FrostInfo, RtObject, RtClass);
	
	FrostInfo();	
	virtual ~FrostInfo()
	{}
	
public:
	bool AddFrost(int i_amount);
	int GetCurrentStage();
    float GetFrostAmount() { return m_amount; }
	void Clear();

private:
	float m_amount;
};

#endif

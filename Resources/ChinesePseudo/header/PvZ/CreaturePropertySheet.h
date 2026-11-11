//
//  CharacterPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __CHARACTERPROPERTYSHEET_H__
#define __CHARACTERPROPERTYSHEET_H__

#include <string>
#include <vector>

#include "BoardEntity.h"
#include "ObjectTypeDescriptor.h"
#include "PlatformAutodetect.h"
#include "RestrictionSet.h"
#include "Point.h"
#include "ProjectilePropertySheet.h"
#include "PropertySheetBase.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "ZombieEnums.h"
#include "dtypes.h"

class CreaturePropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CreaturePropertySheet, PropertySheetBase, RtClass);

	CreaturePropertySheet()
	: HitRect(0, 0, 42, 125), AttackRect(10, 10, 50, 125)
	, ArtCenter(135.0f, 160.0f), ShadowOffset(0.f, 0.f, 1.2f), ShadowScaling(1.0f, 1.0f)
	{
		Speed = 0.16f;
		SpeedVariance = 0.1f;
		ExitSpeedup = 1.0f;

		GridHeight = 1;

		AlmanacScale = 0.0f;

		GridExtents = Point(1,1);
	}

	float Speed;
	float SpeedVariance;
	float ExitSpeedup;
	
	float AlmanacScale;
	SexyVector2 AlmanacOffset;
	std::vector<BoardEntityStat> ZombieStats;
	
	int32 GridHeight;
	Sexy::Rect HitRect;
	Sexy::Rect AttackRect;

	SexyVector2 ArtCenter;
	SexyVector3 ShadowOffset;
	SexyVector2 ShadowScaling;
	std::string GroundTrackName;

	Sexy::Point GridExtents;

	// Sounds
	std::string SoundOnWalk;
	std::string SoundOnIdle;

	/// Actions
	//std::vector<RtWeakPtr<class ZombieActionDefinition>> Actions;
};

#endif

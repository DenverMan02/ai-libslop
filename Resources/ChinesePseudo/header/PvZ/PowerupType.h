//
//  PowerupType.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupType__
#define __PlantsVersusZombies2__PowerupType__

#include "RtDb.h"
#include "ObjectTypeDescriptor.h"
#include "LawnAppEnums.h"	//PVZ2_CHINESE_START

typedef RtWeakPtr<class PowerupType> PowerupTypePtr;

class PowerupType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(PowerupType, ObjectTypeDescriptor, RtClass);

	PowerupType()
	{
		Cost = 0;
		TotalTime = 0.f;
		TimePerUse = 0.f;
        AdditionDamage = 0.f;
        actid = 0;
		BoardTimerColor = Color(0, 0, 0, 0);
		m_purchaseType = PURCHASE_GEM;
	}

	std::string ClassName;

	// The UI to create
	std::string		UIImageName;
	std::string		UIBorderShortName;
	Color			BoardTimerColor;

	std::string		StringID;
	int				Cost;
    std::vector<int> AdditionCost;
    int             AdditionDamage;
    int             actid;
	float			TotalTime;
	float			TimePerUse;
	PurchaseType    m_purchaseType;	//PVZ2_CHINESE_START
};

#endif /* defined(__PlantsVersusZombies2__PowerupType__) */

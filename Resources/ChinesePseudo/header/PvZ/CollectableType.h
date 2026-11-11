//
//  CollectableType.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableType_h
#define PlantsVersusZombies2_CollectableType_h

#include "ObjectTypeDescriptor.h"
#include "TimeMgr.h"

class CollectableType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(CollectableType, ObjectTypeDescriptor, RtClass);
	
	// Default values
	CollectableType()
	{
		Scale = 1.f;
		Animation = "animation";
		ExpireDuration = PVZ_EOT();
		CollectOnExpire = false;
		FadeOutDuration = 0.15f;
		BlinkOutDuration = 0.f;
		
		RewardDoFancyCollect = false;
	}
	
	// Behavior class
	std::string		CollectableClass;
	
	// Interaction
	SexyVector2		Dimensions;
	float			ExpireDuration;
	float			FadeOutDuration;
	float			BlinkOutDuration;
	bool			CollectOnExpire;
	
	std::string		SpawnSound;
	std::string		GroundSound;
	std::string		CollectSound;
	
	// Visual properties
	std::string		PopAnim;
	float			Scale;
	std::string		Animation;
	std::string		StandaloneImage;
	SexyVector3		RenderOffset;
	
	// Reward text (only used when specified as end of level reward)
	std::string		RewardDialogTitle;
	std::string		RewardDialogDescription;
	std::string		RewardDialogImage;
	bool			RewardDoFancyCollect;
};


#endif

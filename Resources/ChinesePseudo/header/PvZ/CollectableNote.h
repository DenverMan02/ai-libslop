//
//  CollectableNote.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableNote_h
#define PlantsVersusZombies2_CollectableNote_h

#include "Collectable.h"

class CollectableNoteType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableNoteType, CollectableType, RtClass);
	
	CollectableNoteType()
	{
	}
	
	std::string		LoadGroup;
	std::string		BackgroundImage;
    std::string     NoteNarrative;
};

#endif

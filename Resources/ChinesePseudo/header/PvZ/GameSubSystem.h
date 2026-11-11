//
//  GameSubSystem.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 12/6/11.
//  Copyright (c) 2011 PopCap Games. All rights reserved.
//

#ifndef __GAMESUBSYSTEM_H__
#define __GAMESUBSYSTEM_H__

#include "RtObject.h"
#include "RtDb.h"
#include "GameObject.h"

class GameSubSystem : public GameObject
{
public:
	RT_CLASS_DEFINE(GameSubSystem, GameObject, RtClass);
	
	GameSubSystem()				{}
	virtual ~GameSubSystem()	{}

	/// Virtual public interface
	virtual void Update()
	{}
    virtual void AddToRenderQueue(class RenderQueue* i_queue)
    {}
};

#endif // __GAMESUBSYSTEM_H__

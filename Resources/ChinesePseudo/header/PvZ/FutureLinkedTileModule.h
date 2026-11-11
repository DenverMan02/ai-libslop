//
//  FutureLinkedTileModule.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FutureLinkedTileModule_h
#define PlantsVersusZombies2_FutureLinkedTileModule_h

#include "LevelModule.h"
#include "FutureStage.h"

class FutureLinkedTileModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(FutureLinkedTileModule, LevelModule, RtClass) {}
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void setupLinkedTiles();
};

class FutureLinkedTileProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(FutureLinkedTileProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return FutureLinkedTileModule::StaticGetClass();
	}
	
	std::vector<LinkedTileEntry> LinkedTiles;
};


#endif

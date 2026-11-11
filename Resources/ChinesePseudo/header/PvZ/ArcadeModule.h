//
//  ArcadeModule.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadeModule__
#define __PlantsVersusZombies2__ArcadeModule__

#include "LevelModule.h"

class ArcadeProgressDatabase;

class ArcadeModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ArcadeModule, LevelModule, RtClass);
	
	int GetEndlessWave() const;
	
	void StartEndless();
	void CompleteCurrentEndlessWave(bool& o_newRecord, std::string& o_unlockedPowerUp);
	
protected:
    void registerForEvents() override;
	void onLoadComplete();
	void onPostLoad() override;
	void onVictory();
	void onFailure();

	virtual void addPowerUpsToBoard();
private:
	void onAnyLoad();
	void cacheWhetherLevelWasPreviouslyCompleted();
	void saveCompletedArcadeProgress();
};

class ArcadeModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ArcadeModuleProperties, LevelModuleProperties, RtClass);
	virtual RtClass* GetModuleClass() const override { return ArcadeModule::StaticGetClass(); }
};

#endif /* defined(__PlantsVersusZombies2__ArcadeModule__) */

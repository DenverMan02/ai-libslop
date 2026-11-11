//
//  RiftStatus
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/1/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RiftStatus__
#define __PlantsVersusZombies2__RiftStatus__

//#include "CurrentProfileTracker.h"
#include "Singleton.h"

class RiftStatus : public LazySingleton<RiftStatus>
{
public:
    RiftStatus()
    {
        DifficultyForNextLevel = 0;
		ZombossPointOfLossExtensions = 0;
        LevelOverride = "";
    }

    void SetDifficultyForNextLevel(int i_difficulty) { DifficultyForNextLevel = i_difficulty; }
    int GetDifficultyForNextLevel() { return DifficultyForNextLevel; }
    void SetLevelOverride(const std::string& i_level) { LevelOverride = i_level; }
    const std::string& GetLevelOverride() { return LevelOverride; }
	int GetZombossPointOfLossExtensions() { return ZombossPointOfLossExtensions; }
	void SetZombossPointOfLossExtensions(int i_extensions) { ZombossPointOfLossExtensions = i_extensions; }


private:

    int DifficultyForNextLevel;
    std::string LevelOverride;
	int ZombossPointOfLossExtensions;
};

#endif

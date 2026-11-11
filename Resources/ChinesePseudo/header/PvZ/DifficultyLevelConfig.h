//
//  DifficultyLevelConfig.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 10/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DifficultyLevelConfig__
#define __PlantsVersusZombies2__DifficultyLevelConfig__

class DifficultyLevelConfig
{
public:
	DifficultyLevelConfig();
	
    int   NumResultsToStore;
    int   MinStreakLen;
    
	float LowerThreshold;
	float RaiseThreshold;
    
	static DifficultyLevelConfig& GetInstance();
};

#endif /* defined(__PlantsVersusZombies2__DifficultyLevelConfig__) */

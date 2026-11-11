//
//  ArcadeSaveDataEncoder.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/3/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadeSaveDataEncoder__
#define __PlantsVersusZombies2__ArcadeSaveDataEncoder__

#include <map>

class ArcadePackProgress;
class PowerUpCollectionProgress;

typedef unsigned int NameHash;

namespace ArcadeSaveDataEncoder
{
	void CompleteLevelInPack(const std::string& i_levelName, const std::string& i_packID, std::vector<ArcadePackProgress>& o_progress);
	void CheatUncompleteLevelInPack(const std::string& i_levelName, const std::string& i_packID, std::vector<ArcadePackProgress>& o_progress);
	bool IsLevelCompletedInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress);
	
	int GetCurrentEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress);
	void SetCurrentEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, int i_currentWave, std::vector<ArcadePackProgress>& o_progress);
	int GetCurrentEndlessLevelStateInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress);
	void SetCurrentEndlessLevelStateInPack(const std::string& i_levelName, const std::string& i_packID, int i_state, std::vector<ArcadePackProgress>& o_progress);
	int GetHighestCompletedEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, const std::vector<ArcadePackProgress>& i_progress);
	void SetHighestCompletedEndlessWaveInPack(const std::string& i_levelName, const std::string& i_packID, int i_highestWave, std::vector<ArcadePackProgress>& o_progress);
	
	void GetCurrentVaseBreakerEndlessState(const std::string& i_levelName, const std::string& i_packID, int &o_sunAmount, int &o_plantFoodCount, const std::vector<ArcadePackProgress>& i_progress);
	void SetCurrentVaseBreakerEndlessState(const std::string &i_levelName, const std::string& i_packID, int i_sunAmount, int i_plantFoodCount, std::vector<ArcadePackProgress>& o_progress);
	
	void UnlockPowerUpInCollection(const std::string& i_powerUpID, const std::string& i_collectionID, std::vector<PowerUpCollectionProgress>& o_progress);
	void CheatLockPowerUpInCollection(const std::string& i_powerUpID, const std::string& i_collectionID, std::vector<PowerUpCollectionProgress>& o_progress);
	bool IsPowerUpUnlockedInCollection(const std::string& i_powerUpID, const std::string& i_collectionID, const std::vector<PowerUpCollectionProgress>& i_progress);
	
	NameHash HashName(const std::string& i_name);
};

#endif /* defined(__PlantsVersusZombies2__ArcadeSaveDataEncoder__) */

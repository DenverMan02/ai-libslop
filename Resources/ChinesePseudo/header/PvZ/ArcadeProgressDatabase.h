//
//  ArcadeProgressDatabase.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/3/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadeProgressDatabase__
#define __PlantsVersusZombies2__ArcadeProgressDatabase__

class ArcadePropertySheet;
class PlayerInfo;

class ArcadeProgressDatabase
{
public:
	static ArcadeProgressDatabase Instance();
	
public:
	ArcadeProgressDatabase(PlayerInfo* i_profile, const ArcadePropertySheet* i_arcadeProps);

	// Command
	void CompleteLevel(const std::string& i_levelName);
	void CheatUncompleteLevel(const std::string& i_levelName);

	void UnlockPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID);
	void CheatLockPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID);

	// Query
	bool IsLevelComplete(const std::string& i_levelName) const;
	bool IsLevelUnlocked(const std::string& i_levelName) const;
	bool IsPackComplete(const std::string& i_packID) const;
	bool IsAnyLevelComplete() const;

	int GetCurrentEndlessWave(const std::string& i_levelName) const;
	int GetHighestCompletedEndlessWave(const std::string& i_levelName) const;
	void CompleteCurrentEndlessWave(const std::string& i_levelName);
	void ResetCurrentEndlessWave(const std::string& i_levelName);
	int GetHighestCompletedPackLevel(const std::string& i_packID) const;
	
	// Minigame-specific queries
	void GetCurrentVaseBreakerEndlessState(const std::string &i_levelName, int& o_sunAmount, int& o_plantFoodCount) const;
	void SetCurrentVaseBreakerEndlessState(const std::string &i_levelName, int i_sunAmount, int i_plantFoodCount);
	
	bool IsPowerUpUnlocked(const std::string& i_powerUpID, const std::string& i_collectionID) const;
	bool AreAllPowerUpsUnlockedInCollection(const std::string& i_collectionID) const;
	
private:
	std::string getSaveDataPackIDForLevelID(const std::string& i_levelID) const;

	PlayerInfo* m_profile;
	const ArcadePropertySheet* m_arcadeProps;
};

#endif /* defined(__PlantsVersusZombies2__ArcadeProgressDatabase__) */

/*
 * NewPVPUtils.h
 *
 *  Created on: 2022-10-10
 *      Author: admin
 */

#ifndef NEWPVPUTILS_H_
#define NEWPVPUTILS_H_

#include "BoardEntity.h"

namespace NewPVPUtils
{
	bool IsForcedSyncEvent(int i_event);
	bool IsPlayingNewPVP();
	bool IsPlayingNewPVPTutorial();
	void FinishNewPVPTutorial();
	bool IsPlayingFakeMatch();
	bool IsPlayingWithCPU();
	void TrySetTutorialStep(int i_step);
	int GetTutorialStep();
	void AddCurrentCPULevel();
	int  GetCurrentCPULevel();
	bool IsConcreteRegion(const Point& i_gridLoc);
	bool IsConcreteRegion(const Sexy::SexyVector3 &i_position);
	bool IsOppoentRegion(const Point& i_gridLoc);
	bool IsOppoentRegion(const Sexy::SexyVector3 &i_position);
	bool IsSameRegion(class BoardEntity* i_entity1, class BoardEntity* i_entity2);
	Point GetGridBySrcGrid(int i_event, int i_x, int i_y, bool i_self);
	ImagePtr	AvatarGetImagePtr(int i_index);
	ImagePtr	AvatarGetFrameImagePtr(int i_index);
	ImagePtr	AvatarGetBottomImagePtr(int i_index);
	int GetCurrentCoin();
	float GetBoardScale();
	void GetRankNum(int& i_bigRank, int& i_smallRank, int& i_star);
	int GetSmallRankNum(int i_bigRank);
	int GetStarNumInSmallRank(int i_bigRank, int i_smallRank);
	ImagePtr GetRankImage(int i_bigRank, int i_smallRank);
	bool HasRankReward();
	void ShowAreaHowToPlayScreen();

	void ShowHowToPlay();
	void ShowArmyHowToPlay();

	bool HasObtainedDailyChestReward();
	bool HasObtainedWeeklyChestReward();

	SexyString GetRandomPlayerName();
	void SplitString(std::wstring target, std::vector<std::wstring> &tokens, wchar_t delims);

	// Zombie LevelUp
	int GetZombieCost(int i_type, int i_level);
	float GetZombieHitpoints(int i_type, int i_level);
	float GetZombieDPS(int i_type, int i_level);
	float GetZombieSpeed(int i_type, int i_level);
	int GetZombieBattleType(int i_type);
	SexyString GetZombieBattleTypeDes(int i_type);
	SexyString GetZombieRareDes(int i_type);

	int   ApplyOverride_ZombieCost(int i_type, int i_packetLevel, int i_originalValue);
	int   ApplyOverride_ZombieCost(const std::string& i_typeName, int i_packetLevel, int i_originalValue);
	float ApplyOverride_ZombieHitpoints(const std::string& i_typeName, int i_packetLevel, float i_originalValue);
	float ApplyOverride_ZombieDPS(int i_battleType, const std::string& i_typeName, int i_packetLevel, float i_originalValue);
	float ApplyOverride_ZombieSpeed(const std::string& i_typeName, int i_packetLevel, float i_originalValue);
}

#endif /* NEWPVPUTILS_H_ */

/*
 * CustomLevelUtils.h
 *
 *  Created on: 2021-12-2
 *      Author: admin
 */

#ifndef CUSTOMLEVELUTILS_H_
#define CUSTOMLEVELUTILS_H_

#include "CustomLevelConfig.h"
#include "LevelEditorDefine.h"

typedef struct CustomNetworkUploadData NetworkUploadData;

namespace CustomLevelUtils
{
	// Level Definition
	bool IsCustomLevel();

	//Request Custom Level Fail
	void RequestLevelDefeat();
	void TryRestartLevel();

	// UIs
	// Main UI funcs: View, Filter, Search
	void TryGetLevelPreviews(std::vector<CustomLevelNetworkWorldType> i_worldTypeList,
			std::vector<CustomLevelNetworkLevelMode> i_modeList, ViewLevelType i_type, ViewRankType i_rankType, int i_index, int i_count);
	void TryFilterLevelPreviews(int i_index = 0, int i_count = 0);
	void TrySearchLevelPreviews(int i_networkLevelID);
	void TryPerformLikeDislike(bool i_like);
	void TryUpdateFavourite(bool i_add);
	void TryUpdateLevelName(const std::string& i_levelName);
	void TryGetLevelPlayCount();
	void TryUpdateDownloadable(bool i_enable);
	void SetTutorialDownloadURL(const std::string& i_url);
	const std::string& GetTutorialDownloadURL();
	void TryDownloadLevelData(const std::string& i_serverUrl, int i_retries = 0, bool i_save = true, bool i_self = false);

	// Editor: Invoke when upload the current level
	void TryUploadCurrentLevel();
	// Level Details UI: Invoke when delete the selected level
	void TryDeleteLevel();
	// Level Details UI: Invoke when challenge the selected level
	void TryStartNetworkLevel();
	// Creator UI: Invoke when load all levels
	const std::vector<CustomPreviewData> TryLoadLevels();
	// Creator UI: Invoke when save current level slot
	void TrySaveCurrentLevel();
	// Editor: Invoke when load the selected level
	const NetworkUploadData& TryLoadLevel(int i_index);
	// Editor: Invoke when start the selected level
	// Must invoke TryLoadLevels() after save level
	void TryStartLevel();
	// Level Details UI: Check selected level has downloaded
	bool IsLevelDownloaded();
	// Level Details UI: Basic level details info
	int GetLevelDetailsLevelID();
	int GetLevelDetailsAuthorID();
	const std::string& GetLevelDetailsLevelName();
	CustomLevelNetworkWorldType GetLevelDetailsWorldType();
	CustomLevelNetworkLevelMode GetLevelDetailsMode();
	bool GetLevelDetailsCanBeDownloaded();
	int GetLevelDetailsLikesOrDislikes(bool i_like);
	int GetLevelDetailsPlayCount();
	int GetLevelDetailsSuggested();
	int GetLevelDetailsAuthorHeadshotID();
	const std::string& GetLevelDetailsAuthorName();
	const std::string& GetLevelDetailsUploadedDate();
	const std::string& GetLevelDetailsUpdatedDate();
	int GetLevelDetailsRateResult();
	bool IsCertifiedAuthor();

	// Editor:
	// Level Pass
	void RecordFinishedLevel(pvztime_t i_playTime);
	bool HasFinishedLevel();
	void ResetFinishedLevel();
	bool IsCurrentLevelUploaded();

	// Worlds
	void SetWorld(CustomLevelNetworkWorldType i_type);
	// Starting Sun
	void SetStartingSun(int i_count);
	// Elements
	void UpdatePlantGrid(const std::string& i_typeName, int i_x, int i_y, int i_level = 1, bool i_add = true);
	void UpdateGridItemGrid(const std::string& i_typeName, int i_x, int i_y, int i_level = 1, bool i_add = true);
	void UpdateMoldGrid(int i_x, int i_y, bool i_add = true);

	// SeedBank Normal
	void SetSeedBankType(CustomSeedBankType i_type);
	void SetSeedBankGlobalLevel(int i_level);
	void AddSeedBankPlantBlackList(const std::string& i_typeName);
	void RemoveSeedBankPlantBlackList(const std::string& i_typeName);
	const std::vector<std::string>& GetSeedBankPlantBlackList();
	// SeedBank Preset
	void AddPresetSeedBankPlant(const std::string& i_typeName, int i_index);
	void RemovePresetSeedBankPlant(int i_index);
	// SeedBank Conveyor
	void AddConveyorSeedBankPlant(const std::string& i_typeName, int i_weight, int i_level, int i_index);
	void UpdateConveyorSeedBankPlant(int i_weight, int i_level, int i_index);
	void RemoveConveyorSeedBankPlant(int i_index);

	// Zombies
	void AddRandomZombies();
	void AddWaveZombie(int i_waveIndex, const std::string& i_typeName, int i_row, int i_col, int i_level = 1);
	bool UpdateWaveZombie(int i_waveIndex, int i_row, int i_col, int i_level);
	bool RemoveWaveZombie(int i_waveIndex, int i_row, int i_col);
	// Sandstrom
	void SetSandStormColumnEnd(int i_waveIndex, int i_colEnd);
	void SetSandStormColumnStart(int i_waveIndex, int i_colStart);
	void AddWaveEventSandStorm(int i_waveIndex, int i_index, const std::string& i_typeName);
	void RemoveWaveEventSandStorm(int i_waveIndex, int i_index);
	// Spider Storm
	void SetSpiderStormColumnStartEnd(int i_waveIndex, int i_col);
	void SetSpiderStormZombieCount(int i_waveIndex, int i_count);
	void RemoveWaveEventSpiderStorm(int i_waveIndex);
	// Raiding Party
	void SetRaidingPartySwashbucklerCount(int i_waveIndex, int i_count);
	// Portal
	bool IsWaveEventPortalValid(int i_waveIndex);
	void SetPortalColumn(int i_waveIndex, int i_col);
	void SetPortalRow(int i_waveIndex, int i_row);
	void SetPortalType(int i_waveIndex, const std::string& i_worldName);
	int GetPortalColumn(int i_waveIndex);
	int GetPortalRow(int i_waveIndex);
	const std::string& GetPortalType(int i_waveIndex);
	// Dino
	bool IsWaveEventDinoValid(int i_waveIndex);
	void SetDinoRow(int i_waveIndex, int i_row);
	void SetDinoTimeInterval(int i_waveIndex, float i_time);
	int GetDinoRow(int i_waveIndex);
	float GetDinoTimeInterval(int i_waveIndex);
	// Frost Wind
	void AddWaveEventFrostWind(int i_waveIndex, int i_row);
	void UpdateWaveEventFrostWind(int i_waveIndex, int i_index, int i_row);
	void RemoveWaveEventFrostWind(int i_waveIndex, int i_index);

	// Challenges
	// Last Stand
	void SetLastStandStartingSun(int i_count);
	void SetLastStandPlantfood(int i_count);
	void RemoveLastStand();
	// Statue Maze
	const StatueMazeSet& GetSet(int i_index);
	int GetSetSize();
	void AddSet(int i_matrixSize, int i_targetNum, float i_displayTime, float i_bonusLife);
	void UpdateSet(int i_index, int i_matrixSize, int i_targetNum, float i_displayTime, float i_bonusLife);
	void RemoveSet(int i_index);
	void SetSetRotateAndWaitTime(int i_setIndex, float i_rotateTime, float i_waitTime);
	const StatueMazeMatrix& GetSetMatrix(int i_setIndex, int i_matrixIndex);
	int GetSetMatrixSize(int i_setIndex);
	void AddSetMatrix(int i_setIndex, bool i_clockWise);
	void UpdateSetMatrix(int i_setIndex, int i_matrixIndex, bool i_clockWise);
	void RemoveSetMatrix(int i_setIndex, int i_matrixIndex);
	// Evil Dave
	bool IsEvilDaveValid();
	void SetEvilDaveStartingSun(int i_count);
	int GetEvilDaveStartingSun();
	void SetEvilDavePlantDistance(float i_distance);
	float GetEvilDavePlantDistance();
	void AddEvilDavePlant(int i_x, int i_y, const std::string& i_typeName);
	void RemoveEvilDavePlant(int i_x, int i_y);
	void AddEvilDaveZombie(int i_index, const std::string& i_typeName);
	void RemoveEvilDaveZombie(int i_index);
	bool GetEvilDavePlantGrid(int i_x, int i_y, std::string& i_typeName);
	const std::string& GetEvilDaveZombieTypeName(int i_index);
	// Tower Defend
	void SetTowerDefendStartingSun(int i_count);
	int  GetTowerDefendStartingSun();
	void SetTowerDefendPlantfood(int i_count);
	void AddTowerDefendRoad(int i_x, int i_y, const std::string& i_imgName);
	void RemoveTowerDefendRoad(int i_x, int i_y);
	bool GetTowerDefendRoad(int i_x, int i_y, std::string& i_typeName);
	void AddTowerDefendPresetSeedBankPlant(const std::string& i_typeName, int i_index);
	const std::string& GetTowerDefendPresetSeedBankPlant(int i_index);
	void RemoveTowerDefendPresetSeedBankPlant(int i_index);
	void AddUpgradeTree(int i_index, const std::string& i_upgradeTypeName, int i_cost);
	void AddTowerDefendWaveZombie(int i_waveIndex, const std::string& i_typeName, int i_row, int i_col);
	bool RemoveTowerDefendWaveZombie(int i_waveIndex, int i_row, int i_col);
	void GetTowerDefendWaveRowZombies(int i_waveIndex, int i_row, std::vector<std::string>& i_zombieList);
	TowerDefendWaveZombie GetTowerDefendWaveZombie(int i_waveIndex, int i_row, int i_col);
	// Single Handed
	void AddStartingPlant(const std::string& i_typeName);
	void RemoveStartingPlant();
	const std::string& GetStartingPlant();
	void AddUpgradePlant(int i_index, const std::string& i_srcTypeName, const std::string& i_upgradeTypeName, int i_killNum);
	void GetUpgradePlant(int i_index, std::string& i_upgradeTypeName, int& i_killNum);
	void RemoveUpgradePlant(int i_index);
	void AddSingleHandedWaveZombie(int i_waveIndex, const std::string& i_typeName, int i_row, int i_col);
	bool RemoveSingleHandedWaveZombie(int i_waveIndex, int i_row, int i_col);
	void GetSingleHandedWaveRowZombies(int i_waveIndex, int i_row, std::vector<std::string>& i_zombieList);
	SingleHandedWaveZombie GetSingleHandedWaveZombie(int i_waveIndex, int i_row, int i_col);
	// Vase Breaker
	void SetVaseBreakerMinMaxColumn(int i_min, int i_max);
	void GetVaseBreakerMinMaxColumn(int& i_min, int& i_max);
	void SetVaseBreakerContent(int i_index, VaseType i_type, const std::string& i_typeName, int i_count);
	void GetVaseBreakerContent(int i_index, VaseType& i_type, std::string& i_typeName, int& i_count);
	void RemoveVaseBreakerContent(int i_index);
	void SetVaseBreakerCount(int i_count);
	int GetVaseBreakerCount();
}

#endif /* CUSTOMLEVELUTILS_H_ */

/*
 * CustomLevelDataCreator.h
 *
 *  Created on: 2021-11-26
 *      Author: admin
 */

#ifndef CUSTOMLEVELDATACREATOR_H_
#define CUSTOMLEVELDATACREATOR_H_

#include "RtDb.h"
#include <vector>
#include <string>
#include "CustomLevelConfig.h"

typedef RtWeakPtr<CustomLevelData> LevelDataPtr;

class CustomLevelDataCreator
{
public:
	CustomLevelDataCreator();

	const std::vector<CustomLevelWorldParams>& GetLevelDatas() { return m_levelDatas; }
	bool DeleteLevelData(const CustomLevelWorldParams& i_params);
	bool DeleteLevelData(const std::string& i_levelId);
	const CustomLevelWorldParams& GetLevelData(const std::string& i_levelId);
	const CustomLevelWorldParams& GetLevelData(int i_index);

	CustomLevelWorldParams* GetLevelDataPtr(const std::string& i_levelId);
	CustomLevelWorldParams* GetLevelDataPtr(int i_index);

	std::string CreateLevelID();
	void Save(CustomLevelWorldParams i_params);
	bool Load();
	bool IsLevelDownload(const std::string& i_levelId);

private:
	void ConstructLevelData(const CustomLevelWorldParams& i_params);
	void FillLevelData(LevelDataPtr i_dataPtr);
	void RemoveLevelData(const std::string& i_levelId);
	void SortLevelDatas();
	void LoadLevelData(const std::string& i_path);
	void SaveLevelData(const CustomLevelWorldParams& i_params);
	bool LoadLevelDatas();
	void SetCurrentLevelIndex(int i_index) { m_currentLevelIndex = i_index; }
    std::string GenerateRandomLevelIDSegment();

	std::vector<CustomLevelWorldParams> m_levelDatas;
	int m_currentLevelIndex;

	LevelDataPtr m_levelDataPtr;
};

#endif /* CUSTOMLEVELDATACREATOR_H_ */

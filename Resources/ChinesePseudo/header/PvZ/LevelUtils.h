//
//  LevelGroups.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelGroups_h
#define PlantsVersusZombies2_LevelGroups_h

#include "Singleton.h"
#include "LevelDefinition.h"

/// Challenge querying
struct ChallengeInfo
{
	RtClass* ChallengePropsClass;
	RtClass* ChallengeClass;
	SexyString Description;
	SexyString DescriptiveName;
};

// wave manager info querying
struct WaveManagerInfo
{
	RtClass* WaveManagerPropsClass;
	RtClass* WaveManagerClass;
	SexyString Description;
	SexyString DescriptiveName;
};

struct LevelInfo
{
	LevelInfo()
			: ChallengesAlwaysAvailable(false)
	{}

	std::string LevelName;
	RtWeakPtr<GenericResFile> LevelResource;

	// Only partial because RtId links to modules cannot be retained
	LevelDefinition PartialDefinition;

	// Challenge information, pulled out of sub-modules
	bool ChallengesAlwaysAvailable;
	std::vector<std::vector<ChallengeInfo> > ChallengeSets;
	std::vector<WaveManagerInfo> WaveManagerInfos;
};

class LevelUtils : public LazySingleton<LevelUtils>
{
public:
	LevelUtils();

	/// Level loading / unloading
	bool DoesLevelExist(const std::string& i_levelName);
    bool DoesHardLevelExist(const std::string& i_levelName);

	LevelDefinitionPtr LoadLevelDefinition(const std::string& i_levelName, bool i_forceCheck = true);
    LevelDefinitionPtr SimpleLoadLevelDefinition(const std::string& i_levelName, bool i_hard);
	void UnloadLevelDefinition();

    bool LevelisEnableAutoHard(LevelDefinitionPtr i_level, bool i_hard);
    
	/// Level info querying
	int GetLevelCount() const;
	const LevelInfo* GetLevelInfoByIndex(int i_levelIdx);
	const LevelInfo* GetLevelInfo(const std::string& i_levelName);

    std::string GetHardLevelName(const std::string& i_levelName);
	// Iterates over all levels, loading each level's definition, pulling out any information
	// we might need to access quickly and safely while the game is running.
	void InitializeMetaDataStore();

private:
	void readLevelMetaData(const std::string& i_levelName);
	LevelDefinitionPtr loadLevelDefinitionFromResource(RtWeakPtr<GenericResFile> i_levelResource);
	bool m_levelMetaDataInitialized;
	std::map<std::string, LevelInfo> m_levelNameToInfoMap;
};

#endif

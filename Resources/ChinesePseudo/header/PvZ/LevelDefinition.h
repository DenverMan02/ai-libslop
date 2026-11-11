//
//  LevelDefinition.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelDefinition_h
#define PlantsVersusZombies2_LevelDefinition_h

#include "RtObject.h"
#include "RtDb.h"
#include "PropertySheetBase.h"
#include "LevelModule.h"
#include "AwardEnums.h"
#include "Loot.h"
#include "PresentTable.h"
#include "LawnAppEnums.h"

struct ZombieWarningInfo
{
	ZombieTypePtr		Type;
	std::string			Text;
	int					Level;

	ZombieWarningInfo()
	{
		Text = "";
		Level = 0;
	}
};

class LevelDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelDefinition, PropertySheetBase, RtClass);
	
    LevelDefinition();
	
	std::string			Name;
	std::string			Description;
	std::string			MainObjective;
	int16				StartingSun;
    int                 LevelIndex;
	int 				LevelNumber;
    
    int					FlickPowerupRightEdgeOffset;
    
    std::vector<std::string> ShowZombies;

	RtWeakPtr<const class StageModuleProperties> StageModule;
    RtWeakPtr<const class OutroModuleProperties> VictoryModule;
    RtWeakPtr<const class OutroModuleProperties> LossModule;
    RtWeakPtr<const class LevelMutatorModuleProperties> LevelMutator;
	std::vector<RtId>	Modules;

	LootConfigPtr		Loot;
	std::string			challengeDropGroupId;
	std::string			NormalPresentTable;
	std::string			ShinyPresentTable;
	
	bool				SuppressVictoryScreen;
	
	AwardType			FirstRewardType;
	std::string			FirstRewardParam;
	
	AwardType			ReplayRewardType;
	std::string			ReplayRewardParam;
    
    bool                GameOverDialogShowBrain;
    bool                GameOverDialogTaskFailed;
	
	std::string			FirstIntroNarrative;
	std::string			ReplayIntroNarrative;
	std::string			FirstOutroNarrative;
	std::string			ReplayOutroNarrative;
	
	std::string			ForceNextLevel;
	bool				ForceWarpTunnel;
    
	bool				IsVasebreaker;
    bool				IsDangerRoom;
    bool				IsBossFight;
    bool                IsArenaBattle;
    bool                IsArenaEdit;
	bool 				IsWorldCup;
	bool				IsJoust;
	bool				IsEpicTask;
	bool				DisablePeavine;
	bool				IsUnchartedModeTipsShow;
	bool 				IsUnchartedModeDifficultyTipsShow;
	
	std::string			CompletionAchievement;
	
	std::vector<GameFeature> GameFeaturesToUnlock;
	
	std::string			MusicType;
	std::string			LevelJam;

	std::vector<ZombieWarningInfo> ZombieWarningInfos;
    
    int                 ZombieMaxLevel;
    bool                IsLevelOfTheDay;
    bool                CanSaveGameState;
    bool                EnableAutoHard;
	bool				IsMiniGameMode;

    std::vector<std::string> RandomLevelSet;

    std::vector<std::string> PerksDisabledInLevel;
    std::vector<std::vector<std::string>> PerksDisabledPerDifficulty;

    std::string			LevelPowerupSet;

    std::vector<RtWeakPtr<const class LevelModifierDifficulty>> LevelDifficulties;

public:
    template<class T> bool HasLevelModule() const
	{
		for (int i = 0; i < Modules.size(); ++i)
		{
			LevelModulePropertiesPtr props = Modules[i];
			if (props->IsA<T>())
			{
				return true;
			}
		}

		return false;
	}

    template<class T> T* GetLevelModule() const
	{
		for (int i = 0; i < Modules.size(); ++i)
		{
			LevelModulePropertiesPtr props = Modules[i];
			if (props->IsA<T>())
			{
				return props->Cast<T>();
			}
		}

		return nullptr;
	}
};

typedef RtWeakPtr<LevelDefinition> LevelDefinitionPtr;

#endif

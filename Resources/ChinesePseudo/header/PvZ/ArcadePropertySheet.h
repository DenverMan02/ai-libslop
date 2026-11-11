//
//  ArcadePropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 6/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadePropertySheet__
#define __PlantsVersusZombies2__ArcadePropertySheet__

#include "PropertySheetBase.h"

namespace ArcadePropertySheetHelpers
{
	enum ArcadeRewardType
	{
		None,
		GiftBox,
		PowerUp,
	};
	
	struct ArcadeReward
	{
		ArcadeReward()
		: Type{None}
		{}
		
		ArcadeRewardType Type;
		std::string ID;
	};
	
	struct ArcadeLevel
	{
		std::string ID; // Used to launch level, matches LevelName in level data
	};
	
	struct ArcadeLevelPack
	{
		std::string ID;							// Unique ID
		std::vector<std::string> Toggles;		// All listed toggles must be enabled for this pack to be enabled
		std::string PackNameLocalizationKey;	// Should include brackets [] - can be omitted for unlocalized text
		std::string LayoutFile;
		std::string BackdropImage;
		std::string UnlockAfter;
		std::vector<ArcadeLevel> Levels;
		ArcadeReward Reward;
		
		bool IsEnabled() const;
		
		bool ContainsLevelID(const std::string& i_levelID) const;
		const ArcadeLevel& GetLevelByID(const std::string& i_levelID) const;
		int GetLevelIndexByID(const std::string& i_levelID) const;

		const ArcadeLevel& GetFirstLevel() const;
		bool IsLevelLastInPack(const std::string& i_levelID) const;
	};
	
	struct ArcadeEndlessLevel
	{
		ArcadeEndlessLevel()
		: RewardPowerUpAfterWave(1)
		{}
		
		ArcadeLevel Level;
		std::string RewardPowerUp;
		int RewardPowerUpAfterWave;
	};
	
	struct ArcadeMode
	{
		ArcadeMode()
		: DisplayInArcadeMenu(false)
		{}
		
		std::string ID;
		std::string ModeNameLocalizationKey;
		std::string PowerUpCollectionID;
		std::string ArcadeMenuImage;
		bool DisplayInArcadeMenu;
		ArcadeEndlessLevel EndlessLevel;
		std::string UnlockEndlessAfter;
		std::vector<ArcadeLevelPack> LevelPacks;
		
		std::vector<ArcadeLevelPack> GetLevelPacks() const;
		
		bool ContainsLevelPackID(const std::string& i_levelPackID) const;
		const ArcadeLevelPack& GetLevelPackByID(const std::string& i_levelPackID) const;
		
		bool ContainsLevelID(const std::string& i_levelID) const;
		const ArcadeLevel& GetLevelByID(const std::string& i_levelID) const;
		const ArcadeLevelPack& GetLevelPackByLevelID(const std::string& i_levelID) const;
		
		bool HasPowerUpCollection() const;
		
		void ForEachLevel(std::function<void(const ArcadePropertySheetHelpers::ArcadeLevel&)> i_function) const;
	};
	
	enum UnlockSourceType
	{
		LevelPack,
		EndlessLevel,
	};
	
	struct UnlockSource
	{
		UnlockSource(UnlockSourceType i_type, const std::string& i_id, int i_completionValue)
		: Type(i_type), ID(i_id), CompletionValue(i_completionValue)
		{}
		
		UnlockSourceType Type;
		std::string ID;
		int CompletionValue;
	};

	struct PowerUpMetaData
	{
		std::string ID;
		std::string UpImage;
		std::string DownImage;
		std::string GameFeature;
		std::string NameLocalizationKey;
		std::string DescriptionLocalizationKey;
		std::string UnlockHintLocalizationKey;
	};
	
	struct PowerUpCollection
	{
		std::string ID;
		std::vector<PowerUpMetaData> PowerUps;
		
		bool ContainsPowerUpID(const std::string& i_powerUpID) const;
		const PowerUpMetaData& GetPowerUpByID(const std::string& i_powerUpID) const;
	};
}

class ArcadePropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ArcadePropertySheet, PropertySheetBase, RtClass);
	
	static const ArcadePropertySheet* Get();
	
	const ArcadePropertySheetHelpers::ArcadeMode& GetModeByID(const std::string& i_modeID) const;
	const ArcadePropertySheetHelpers::ArcadeMode& GetModeByLevelPackID(const std::string& i_levelPackID) const;
	const ArcadePropertySheetHelpers::ArcadeMode& GetModeByLevelID(const std::string& i_levelID) const;
	
	const ArcadePropertySheetHelpers::ArcadeLevelPack& GetLevelPackByID(const std::string& i_packID) const;
	const ArcadePropertySheetHelpers::ArcadeLevelPack& GetLevelPackByLevelID(const std::string& i_levelID) const;
	
	bool HasLevel(const std::string& i_levelID) const;
	bool HasNextLevelInPack(const std::string& i_levelID) const;
	const ArcadePropertySheetHelpers::ArcadeLevel& GetLevelByID(const std::string& i_levelID) const;
	const ArcadePropertySheetHelpers::ArcadeLevel& GetNextLevelInPack(const std::string& i_levelID) const;
	
	bool HasPowerUpCollection(const std::string& i_collectionID) const;
	bool HasPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID) const;
	const ArcadePropertySheetHelpers::PowerUpCollection& GetPowerUpCollectionByID(const std::string& i_collectionID) const;
	const ArcadePropertySheetHelpers::PowerUpCollection& GetPowerUpCollectionByModeID(const std::string& i_modeID) const;
	const ArcadePropertySheetHelpers::PowerUpCollection& GetPowerUpCollectionByLevelPackID(const std::string& i_levelPackID) const;
	const ArcadePropertySheetHelpers::PowerUpCollection& GetPowerUpCollectionByLevelID(const std::string& i_levelID) const;
	const std::vector<std::string> GetUniqueArcadePowerUpTypeNames() const;
		
	const std::vector<ArcadePropertySheetHelpers::UnlockSource> GetUnlockSourcesForPowerUp(const std::string& i_powerUpID, const std::string& i_collectionID) const;
	
	// Iterator methods
	void ForEachLevel(std::function<void(const ArcadePropertySheetHelpers::ArcadeLevel&)> i_function) const;
	
	bool IsLevelEndless(const std::string& i_levelID) const;
	
	ArcadePropertySheet()
	{}
	
	std::vector<ArcadePropertySheetHelpers::ArcadeMode> ArcadeModes;
	std::vector<ArcadePropertySheetHelpers::PowerUpCollection> PowerUpCollections;
};

namespace Arcade
{
	bool IsAvailable();
	const ArcadePropertySheetHelpers::ArcadeMode* GetCurrentArcadeMode();
}

#endif /* defined(__PlantsVersusZombies2__ArcadePropertySheet__) */

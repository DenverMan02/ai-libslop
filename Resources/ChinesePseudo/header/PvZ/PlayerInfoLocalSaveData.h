//
//  PlayerInfoLocalSaveData.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 5/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlayerInfoLocalSaveData__
#define __PlantsVersusZombies2__PlayerInfoLocalSaveData__

#include "RtObject.h"
#include "RtDb.h"
#include "PlayerInfo.h"
#include "NetworkData.h"

typedef Sexy::RtWeakPtr<class PlayerInfoLocalSaveData> PlayerInfoLocalSaveDataPtr;

struct ArcadeLastPlayData : public Sexy::RtObject
{
	RT_CLASS_DEFINE(ArcadeLastPlayData, Sexy::RtObject, Sexy::RtClass);

	ArcadeLastPlayData()
	: LastPlayTime(PVZ_EOT())
	, Status(LastPlayStatus_None)
	, LastPlayWave(0)
	{}

	std::string		ModeID; // Unique within collection: Basically our key, but we can't serialize maps
	std::string		LevelID;
	time_t			LastPlayTime;
	int				LastPlayWave;
	LastPlayStatus	Status; // Could use -1, 0, 1 system for this, like board last play result?
};

struct Lv5Switch
{
	Lv5Switch()
	:plantName("")
	,on(false)
	{}
	std::string plantName;
	bool on;
};

class PlayerInfoLocalSaveData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(PlayerInfoLocalSaveData, Sexy::RtObject, Sexy::RtClass);
	PlayerInfoLocalSaveData()
	{
		ProfileIndex = 0;
		FacebookConnected = false;
		ProfileIcon = NULL;
		DangerRoomRandomSeed = 0;
		HasPurchasedExtraDRCard = false;
        DangerRoomRepickSeed = 0;
        ZombossUnlockedTime = 0;
        HasJustClearedRiftZomboss = false;
		LastDangerRoomTipsTime = 0;
		LastBattleZTipsTime = 0;
		LastPennyTipsTime = 0;
		LastPVZ1TipsTime = 0;
		PlantGeneAdditionVersion = 0;
		CurrentNewPVPCPULevel = 0;
	}
	~PlayerInfoLocalSaveData()
	{
		delete ProfileIcon;
	}

	// not serialized
	MemoryImage* ProfileIcon;

	// serialized
	int32 ProfileIndex;
	bool FacebookConnected;
	int32_t DangerRoomRandomSeed;
	bool HasPurchasedExtraDRCard;
    int32_t DangerRoomRepickSeed;
    std::vector<ArcadeLastPlayData> ArcadeLastPlays;
	std::vector<std::string> m_favoriteSeedChooserPlants;
	std::vector<int> m_dangerRoomSelectedList;

	serializable_time_t ZombossUnlockedTime;
	bool HasJustClearedRiftZomboss;

	serializable_time_t LastDangerRoomTipsTime;
	serializable_time_t LastBattleZTipsTime;
	serializable_time_t LastPennyTipsTime;
	serializable_time_t LastPVZ1TipsTime;
	int PlantGeneAdditionVersion;
	int CurrentNewPVPCPULevel;

	std::vector<Lv5Switch> Lv5SkillSwitch;

	Network_ArtifactImprovedPropertySheet ArtifactImprovedPropertySheet;
};

namespace LocalProfileSaveData
{
	void SetCanPostToFacebook(const PlayerInfo* i_playerInfo, const bool i_canPost);
	bool CanPostToFacebook(const PlayerInfo* i_playerInfo);

	void SetProfilePicture(const PlayerInfo* i_playerInfo, MemoryImage* i_image);
	MemoryImage* GetProfilePicture(const PlayerInfo* i_playerInfo);

	void LoadLocalProfileSaveData();
	PlayerInfoLocalSaveData* GetOrCreateLocalProfileData(const PlayerInfo* i_playerInfo);
	bool GetHasPurchasedExtraDRCard(const PlayerInfo* i_playerInfo);
	void SetHasPurchasedExtraDRCard(const PlayerInfo* i_playerInfo, bool i_purchasedCard);
	int32_t GetDangerRoomRandomSeed(const PlayerInfo* i_playerInfo);
	void SetDangerRoomRandomSeed(const PlayerInfo* i_playerInfo, int32_t i_randomSeed);

	ArcadeLastPlayData* GetOrCreateArcadeLastPlayData(const PlayerInfo* i_playerInfo, const std::string& i_modeID);
    
    int32_t GetDangerRoomRepickSeed(const PlayerInfo* i_playerInfo);
	void SetDangerRoomRepickSeed(const PlayerInfo* i_playerInfo, int32_t i_randomSeed);

	void							AddSeedChooserFavorite(const PlayerInfo* i_playerInfo, const std::string& i_plantType);
	void							RemoveSeedChooserFavorite(const PlayerInfo* i_playerInfo, const std::string& i_plantType);
	std::vector<std::string>&		GetSeedChooserFavorites(const PlayerInfo* i_playerInfo);
	bool							IsSeedChooserFavorite(const PlayerInfo* i_playerInfo, const std::string& i_plantType);

	void 							SetPlantLv5SkillSwitch(const PlayerInfo* i_playerInfo, const std::string& i_plantType, bool i_on);	
	bool 							GetPlantLv5SkillSwitch(const PlayerInfo* i_playerInfo, const std::string& i_plantType);
	
	void							SaveDangerRoomSelectedList(const PlayerInfo* i_playerInfo, const std::vector<int>& i_list);
	const std::vector<int>& 		GetDangerRoomSelectedList(const PlayerInfo* i_playerInfo);

	time_t		GetZombossUnlockedTime(const PlayerInfo* i_playerInfo);
	void 		SetZombossUnlockedTime(const PlayerInfo* i_playerInfo, time_t i_time);
	bool		GetHasJustClearedRiftZomboss(const PlayerInfo* i_playerInfo);
	void		SetHasJustClearedRiftZomboss(const PlayerInfo* i_playerInfo, bool i_cleared);

	int			GetCurrentNewPVPCPULevel(const PlayerInfo* i_playerInfo);
	void 		SetCurrentNewPVPCPULevel(const PlayerInfo* i_playerInfo, int i_level);

	bool		CheckDangerRoomTips();
	void		UpdateDangerRoomTipsTime();
	bool		CheckBattleZTips();
	void		UpdateBattleZTipsTime();
	bool		CheckPennyTips();
	void		UpdatePennyTipsTime();
	bool		CheckPVZ1Tips();
	void		UpdatePVZ1TipsTime();

	int			GetPlantGeneAdditionVersion();
	void		SetPlantGeneAdditionVersion(int i_newVersion);

	const Network_ArtifactImprovedPropertySheet& GetNetworkArtifactImprovedPropertySheet();
	void SetNetworkArtifactImprovedPropertySheet(const Network_ArtifactImprovedPropertySheet& i_sheet);
}

namespace Message
{
	void ProfileIconPictureTaken(const PlayerInfo* i_playerInfo, MemoryImage* i_image);
}

#endif /* defined(__PlantsVersusZombies2__PlayerInfoLocalSaveData__) */

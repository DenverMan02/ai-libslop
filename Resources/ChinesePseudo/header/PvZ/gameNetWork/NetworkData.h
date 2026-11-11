//
//  INetworkData.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-7-24.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__INetworkData__
#define __PlantsVersusZombies2__INetworkData__

#include "RtObject.h"
#include "PlayerInfo.h"
#include "PlaybackData.h"
#include "DRef.h"
#include "ArtifactBoost.h"
#define GAME_RANK_STAR_COUNT 4

class INetworkData : public RtObject,public DRef
{
public:
    RT_CLASS_DEFINE(INetworkData, RtObject, RtClass);
    
    virtual bool SerializeJson(const std::string &i_json);
    virtual std::string SerializeObj();
};

class INetworkErrorData : public INetworkData
{
public:
    RT_CLASS_DEFINE(INetworkErrorData, INetworkData, RtClass);
    INetworkErrorData() {}
    INetworkErrorData(int erro) { m_errorID = erro; }
    INetworkErrorData(const std::string &i_json);
    std::string       m_msgID;
    int             m_errorID = 0;
    std::wstring    m_errorStr;
};

class S2C_PlayerInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PlayerInfo, INetworkData, RtClass);
    
    S2C_PlayerInfo()
    : m_profileId(0)
    , m_uploadKey(0)
    , m_profileCreatedTime(0)
    , m_gold(0)
    , m_Gems(0)
    , m_gemCost(0)
    , m_Leafs(0)
    , m_freeGem(0)
    , m_paidGem(0)
    {        
    }
    
    // server 2.player
    int32           m_profileId;
    std::wstring	m_UserName;
    int32           m_uploadKey;
    int64           m_profileCreatedTime;
    int32           m_gold;     // both
    int32			m_Gems;     // both
    int32           m_gemCost;
    int32           m_Leafs;    // both
    // server 27.playerInfo more
    int32           m_freeGem;
    int32           m_paidGem;
    
    int32           m_addGem = 0;
};

struct S2C_BonusInfo
{
    int32 objectId;
    int32 quantity;
    int32 probability;
    S2C_BonusInfo()
    {
        objectId = 0;
        quantity = 0;
        probability = 0;
    }
};

struct S2C_UserInfo
{
    int32  headshot = 0;
    std::string name;
    std::string email;
    std::string phone;
    std::string address;
    int32  age = 0;
    int32  sex = 0;
    int32  isFirstGetReward = 1;
    int32  isFirstChangeName = 0;
    int32  currentRankAvatar = 0;
};

struct S2C_PlantListInfo
{
    int32       plantId;
    int32       starUpgrade;
    
    S2C_PlantListInfo()
    {
        plantId = 0;
        starUpgrade = 0;
    }
};

struct S2C_FightZodiacStateInfo
{
	int32       key;
    int32       all_num;
    int32       obtain_num;
    int32       enable;

    S2C_FightZodiacStateInfo()
    {
    	key = 0;
    	all_num = 0;
    	obtain_num = 0;
    	enable = 0;

    }
};

struct S2C_PlantPendantInfo
{
    int64           pendant_id;
    int32  			type_id;
    int32           level;
    
    S2C_PlantPendantInfo()
    {
        pendant_id = 0;
        type_id = 0;
        level = 1;
    }
};

struct S2C_PlantFamilyAttr
{
    std::string type;
    float value = 0;
    std::string replaceType;
    float replaceValue = 0;
    std::string md5;
};

struct S2C_PlantFamilyInfo
{
    int familyId;
    std::vector<S2C_PlantFamilyAttr> attrs;
};

struct S2C_ArtifactBoostInfo
{
	S2C_ArtifactBoostInfo()
	: BoostId(-1)
	, Value(0.0f)
	{

	}

	int BoostId;
	float Value;
};

struct S2C_ArtifactInfo
{
    int ArtifactId;
    int Level;
    int Rank;
    int Equip;
    std::vector<S2C_ArtifactBoostInfo> BoostInfos;
    std::vector<S2C_ArtifactBoostInfo> UnsavedBoostInfos;
};

struct S2C_AdInfo
{
    int ServerId;
    int WatchedTimes;
    int MaxWatchedTimes;
};

struct S2C_ShareInfo
{
    int ServerId;
    int LeftTimes;
};

struct S2C_CollectionInfo
{
    int CollectionId;
    int Rare;
    int Status;
};

struct S2C_GeneInfo
{
    int GeneID;
    int Level;
};

struct S2C_GeneEssenceInfo
{
    int GeneEssenceID;
    int Number;
};

struct S2C_GeneTalentInfo
{
    int GeneTalentID;
    int Level;
};

class Network_ArtifactImprovedPropertySheet : public INetworkData
{
public:
    RT_CLASS_DEFINE(Network_ArtifactImprovedPropertySheet, INetworkData, RtClass);

    std::vector<NetworkArtifactBoostConfig> Configs;
    std::vector<NetworkArtifactBoostData> Boosts;
};

class S2C_ICloud_GetPlayerInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetPlayerInfo, INetworkData, RtClass);
    
    S2C_PlayerInfo     m_playerInfo;
    S2C_UserInfo       m_userInfo;
    std::vector<S2C_PlantListInfo>  m_plantList;
    std::vector<S2C_BonusInfo>      m_plantChipInfo;
    std::vector<int>                m_avatarList;
    std::vector<S2C_BonusInfo>      m_avatarChipInfo;
    std::vector<int>                m_newAvatarList;
    std::vector<S2C_BonusInfo>      m_newAvatarChipInfo;
    std::vector<S2C_BonusInfo>      m_pendantChipInfo;
    std::vector<S2C_PlantPendantInfo> m_pendantInfo;
    std::vector<S2C_PlantFamilyInfo> m_plantFamilyInfo;
    std::vector<int>   m_constraintList;
    std::vector<int>   m_headShotList;
    int                m_totalCharge;
    bool               m_synHeadShot;
    
    std::vector<S2C_BonusInfo>      m_materialInfo;
    std::vector<S2C_ArtifactInfo>   m_artifactInfo;
    std::vector<int>   				m_rankAvatarList;
    std::vector<S2C_AdInfo>         m_adWatchInfo;
    std::vector<S2C_ShareInfo>      m_shareInfo;
    std::vector<S2C_CollectionInfo> m_collectionInfo;
    std::vector<S2C_GeneInfo>           m_geneInfo;
    std::vector<S2C_GeneEssenceInfo>    m_geneEssenceInfo;
    std::vector<S2C_GeneTalentInfo>     m_geneTalentInfo;
    Network_ArtifactImprovedPropertySheet m_artifactImprovedPropertySheet;
    bool m_hasSkippedTutorial;
    int m_artifactBlessLegendLeftCount;
};

class S2C_LeafConsume : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_LeafConsume, INetworkData, RtClass);
    S2C_PlayerInfo      m_playerInfo;
    int                 m_objectId;
    int                 m_quantity;
    
    S2C_LeafConsume()
    {
        m_objectId = 0;
        m_quantity = 0;
    }
    
};

//=========================================================
//  S2C_AuthInfo
//=========================================================
class S2C_AuthInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_AuthInfo, INetworkData, RtClass);
    
    int32 userId;
    std::string sessionKey;
    bool  newUser;
};

// new convert ios
class S2C_GetPlantInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GetPlantInfo, INetworkData, RtClass);
    
    std::vector<int>            m_plantList;
    std::vector<S2C_BonusInfo>  m_plantChipInfo;
    
    int           nfc;
};

class S2C_GetAvatarInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GetAvatarInfo, INetworkData, RtClass);
    
    std::vector<int>            m_avatarList;
    std::vector<S2C_BonusInfo>  m_avatarChipInfo;
    int                         nfc;
};

struct S2C_PlantLevelInfo
{
    int32 plantId;
    int level;
    S2C_PlantLevelInfo()
    {
        plantId = 0;
        level = 1;
    }
};

class S2C_PlantLevel : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PlantLevel, INetworkData, RtClass);
    
    S2C_BonusInfo                   m_plantChipInfo;
    S2C_PlantLevelInfo              m_plantLevelInfo;
    std::vector<S2C_BonusInfo>      m_materialInfo;
};

struct S2C_AvatarLevelInfo
{
    int32 avatarId;
    S2C_AvatarLevelInfo()
    {
        avatarId = 0;
    }
};

class S2C_AvatarLevel: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_AvatarLevel, INetworkData, RtClass);
    
    S2C_BonusInfo       m_avatarChipInfo;
    S2C_AvatarLevelInfo m_avatarLevelInfo;
};

class S2C_ICloud_ExchangePendant : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_ExchangePendant, INetworkData, RtClass);
    
    S2C_PlantPendantInfo    m_plantPendantInfo;
    S2C_BonusInfo           m_plantPendantChipInfo;
};

class S2C_ICloud_SoldPendant : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_SoldPendant, INetworkData, RtClass);
    
    int64 pendantId;
    std::vector<S2C_BonusInfo> consumeMats;
};

class S2C_ICloud_SteadyPendant : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_SteadyPendant, INetworkData, RtClass);
    
    int64 pendantId;
    std::vector<S2C_BonusInfo> consumeMats;
};

class S2C_ICloud_ResetPendant : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_ResetPendant, INetworkData, RtClass);
    
    int64 pendantId;
    int gems;
    std::vector<S2C_BonusInfo> consumeMats;
};

//=============================== Explore ================================
struct S2C_Explore_Team
{
    uint32 exploreEndTime;
    int32 dungeonId;
    int   chances;
    int   status;
    int   plantChipId;
    int   bonus;
    int   surpriseObjectId;
    int   surprise;
    int   coins;
    int   surprisePrice;
    int   bonusItem;
    std::vector<int> plantsList;
    int   addChanceCount;
    
    S2C_Explore_Team()
    {
        exploreEndTime = 0;
        dungeonId = -1;
        chances = 0;
        status = 0;
        plantChipId = 0;
        bonus = 0;
        surprise = 0;
        coins = 0;
        surprisePrice = 0;
        bonusItem = 0;
        addChanceCount = 0;
    }
};

struct S2C_Explore_Plant
{
    uint32 endTime;
    int32 plantId;
    int   status;
    
    S2C_Explore_Plant()
    {
        endTime = 0;
        plantId = 0;
        status = 0;
    }
};

class S2C_ExplorerStart : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ExplorerStart, INetworkData, RtClass);
    std::vector<S2C_Explore_Team>  m_teamList;
    S2C_PlayerInfo m_playerInfo;
    int needGems;
    int gemCost;
};

class S2C_ExplorerTeamStatus : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ExplorerTeamStatus, INetworkData, RtClass);
    
    S2C_ExplorerTeamStatus()
    {
        m_teamList.clear();
        m_serverTime = 0;
    }
    
    int64 m_serverTime;
    std::vector<S2C_Explore_Team>  m_teamList;
};

class S2C_ExplorerPlantStatus : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ExplorerPlantStatus, INetworkData, RtClass);
    std::vector<S2C_Explore_Plant>  m_plantList;
    int m_dungeonId;
};

class S2C_StopExplore : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_StopExplore, INetworkData, RtClass);
    
    int diamondLess;
    S2C_PlayerInfo m_playerInfo;
    std::vector<S2C_Explore_Team>   m_teamList;
    int m_flag;
    int m_adCount;
};

class S2C_ExploreReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ExploreReward, INetworkData, RtClass);
    
    std::vector<S2C_Explore_Team>   m_teamList;
    std::vector<S2C_BonusInfo>      m_plantChipInfo;
    int m_adCount;
};

class S2C_SurpriseReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SurpriseReward, INetworkData, RtClass);
    
    std::vector<S2C_BonusInfo>  m_plantSurpriseInfo;
    S2C_PlayerInfo m_playerInfo;
};

class S2C_SurpriseRewardNew : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SurpriseRewardNew, INetworkData, RtClass);

    S2C_LeafConsume m_plantSurpriseInfo;
    S2C_PlayerInfo  m_playerInfo;
};

class S2C_ExplorePlantRecover : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ExplorePlantRecover, INetworkData, RtClass);
    
    std::vector<S2C_Explore_Plant>  m_plantList;
    S2C_PlayerInfo m_playerInfo;
    int m_gemsRequired;
};

class S2C_ICloud_PlantTrialInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_PlantTrialInfo, INetworkData, RtClass);
    
    S2C_PlayerInfo                          m_playerInfo;
    std::vector<S2C_PlantListInfo>          m_plantList;
    std::vector<S2C_BonusInfo>              m_plantChipInfo;
};

class S2C_ChristmasLottery: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasLottery, INetworkData, RtClass);
    
    int                 m_plantIndex;
    S2C_BonusInfo       m_christmasLottery;
    S2C_PlayerInfo      m_playerInfo;
    
    S2C_ChristmasLottery()
    {
        m_plantIndex = 0;
    }
};

#ifdef HOST_ANDROID

struct S2C_LoadPlayerProfileData
{
	DeltaPlayerProfileInfo playerProfileData;
};

class S2C_LoadPlayerProfile : public INetworkData
{
	public:
		RT_CLASS_DEFINE(S2C_LoadPlayerProfile, INetworkData, RtClass);

		int32  							m_userId;
		uint32							m_lastUpdateTime;
		S2C_LoadPlayerProfileData		m_playerProfile;

		S2C_LoadPlayerProfile()
		{
			m_userId 			= -1;
			m_lastUpdateTime 	= 0;
		}
};

struct GemRequestInfo
{
	int mGem;
	GemRequestInfo():mGem(0)
	{}
};

class S2C_SubGemRequest: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_SubGemRequest, INetworkData, RtClass);
	GemRequestInfo m_info;
};

class S2C_AddGemRequest : public  INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_AddGemRequest, INetworkData, RtClass);
    GemRequestInfo m_info;
};

//=========================================================
//  GameRank
//=========================================================
struct S2C_GameRankInfo
{
    int32 userId;
    int time;
    std::string formation;
};

class S2C_ICloud_LoginResult : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ICloud_LoginResult, INetworkData, RtClass);
	
    S2C_ICloud_LoginResult()
	{
		m_UserId 		= -1;
        m_serverTime    = 0;
		m_sk			= "";
		m_signature		= "";
        m_OldKey		= "";
        m_NewKey		= "";
        m_encrypt		= true;
        m_saveInterval  = 120.f;
		m_createdTime 	= "";
		m_idEncryptIndex = 0;
		m_isNewUser = false;
		m_PlayerReturnDays = 0;
		m_bindUniqueID = false;
		m_newAccountBind = false;
		m_stageURL = "";
	}
	
    int32			m_UserId;
    int64           m_serverTime;
	std::string		m_sk;
	std::string     m_signature;
    std::string		m_OldKey;
    std::string		m_NewKey;
    bool			m_encrypt;
    pvztime_t		m_saveInterval;
	std::string     m_createdTime;
	int32			m_idEncryptIndex;
	bool			m_isNewUser;
	int 			m_PlayerReturnDays;
    bool			m_bindUniqueID;
    bool			m_newAccountBind;
    std::string		m_stageURL;
};

class S2C_ICloud_DisplayID : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ICloud_DisplayID, INetworkData, RtClass);

	std::string		m_displayID;
	std::string		m_displayUUID;
};

//=========================================================
//  Profile
//=========================================================
struct S2C_Profile
{
    int32 			userId;
    std::string 	profile;
    std::string 	md5;
    int32  			lastUpdateTime;
    
    S2C_Profile()
    {
    	userId 			= 0;
    	profile 		= "";
    	md5 			= "";
    	lastUpdateTime 	= 0;
    }
};

class S2C_ICloud_GetProfile: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ICloud_GetProfile, INetworkData, RtClass);

	S2C_Profile m_profile;
};

//=========================================================
//  ProfileMD5
//=========================================================
struct S2C_ProfileMD5
{
    std::string 	md5;
    std::string		summary;
    int32  			lastUpdateTime;
    
    S2C_ProfileMD5()
    {
    	md5 			= "";
    	summary			= "";
    	lastUpdateTime 	= 0;
    }
};

class S2C_ICloud_GetProfileMD5: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ICloud_GetProfileMD5, INetworkData, RtClass);

	S2C_ProfileMD5     m_profile;
};

//========================== DailySignInfo ==========================
struct S2C_DailySign
{
    int m_loginCount;
    int32 m_lastRequestTime;
    
    S2C_DailySign()
    {
        m_loginCount = 0;
        m_lastRequestTime = 0;
    }
};

struct S2C_DailySignContent
{
    int32 itemId;
    int32 amount;
    
    S2C_DailySignContent()
    {
        itemId = 0;
        amount = 0;
    }
};

class S2C_ICloud_SignReward: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_SignReward, INetworkData, RtClass);
    
    int m_needRefreshList;
    S2C_DailySign m_dailySign;
    std::vector<int> m_dateList;
    std::vector<S2C_DailySignContent> m_rewardList;
};

struct S2C_TimeLevelNodeContent
{
    int     iLevelId;
    uint32  iTime;
    
    S2C_TimeLevelNodeContent(): iLevelId(0), iTime(0) {}
};

class S2C_TimeLevelNodeList: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_TimeLevelNodeList, INetworkData, RtClass);
    
    int                                    m_iLevelID;
    std::vector<S2C_TimeLevelNodeContent>  m_vCDingNodeList;
};

class S2C_StartTimeLevel: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_StartTimeLevel, INetworkData, RtClass);
    
    S2C_TimeLevelNodeContent  m_TimeLevelNodeContent;
};

class S2C_DeleteTimeLevel: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_DeleteTimeLevel, INetworkData, RtClass);
    
    int  m_iLevelID;
};

//=========================================================
//  DangerRoom
//=========================================================
struct S2C_DangerRoomContent
{
    int32 period;
    int32 userId;
    int32 rank;
    int32 score;
    
    S2C_DangerRoomContent()
    {
        period = 0;
        userId = 0;
        rank = 0;
        score = 0;
    }
};

class S2C_UploadDangerRoomRank: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_UploadDangerRoomRank, INetworkData, RtClass);
    
    S2C_DangerRoomContent  m_content;
};

struct S2C_DangerRoom_Public
{
    std::string m_name;
    std::string m_score;
    int m_rank;
    S2C_DangerRoom_Public()
    {
        m_name = "";
        m_rank = 0;
        m_score = "";
    }
};

class S2C_ICloud_DangerRoomLeaderBoard : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_DangerRoomLeaderBoard, INetworkData, RtClass);

    std::vector<S2C_DangerRoom_Public> m_dangerRoomLeaderBoard;
};

struct S2C_GachaInfo
{
public:
    int                 profileId;
    int                 lastFreeTime;
    int                 isFirstPaidDrawDone;

    S2C_GachaInfo()
    {
        profileId = 0;
        lastFreeTime = 0;
        isFirstPaidDrawDone = 0;
    }
};

//=========================================================
//  RedPack
//=========================================================
struct S2C_RedPack_Public
{
    std::string m_name;
    std::string m_score;
    int m_rank;
    S2C_RedPack_Public()
    {
        m_name = "";
        m_rank = 0;
        m_score = "";
    }
};

class S2C_ICloud_RedPackLeaderBoard : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RedPackLeaderBoard, INetworkData, RtClass);
    
    std::vector<S2C_RedPack_Public> m_redPackLeaderBoard;
    int m_selfInRank;
};

//=========================================================
//  PlantPendantInfo
//=========================================================

struct S2C_RedPackContent
{
    int itemId;
    int amount;

    S2C_RedPackContent()
    {
        itemId = 0;
        amount = 0;
    }
};

//=========================================================
//  GachaInfo
//=========================================================
class S2C_ICloud_GetGachaInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ICloud_GetGachaInfo, INetworkData, RtClass);

    S2C_GachaInfo                 gachaInfo;
};

class S2C_ICloud_RedPackLeaderBoardReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RedPackLeaderBoardReward, INetworkData, RtClass);

    std::vector<S2C_PlantPendantInfo> m_pendantInfo;
    std::vector<S2C_RedPackContent> m_prizeInfo;
};

class S2C_SyncCachedObjectsInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SyncCachedObjectsInfo, INetworkData, RtClass);

    int                                 m_gems;
    int                                 m_gold;
    int                                 m_nfc;
    std::vector<S2C_BonusInfo>          m_bonusList;
    std::vector<S2C_PlantPendantInfo>   m_pendantInfo;
};

#else

class S2C_ICloud_LoginResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_LoginResult, INetworkData, RtClass);
    
    S2C_ICloud_LoginResult()
    {
        m_UserId 		= -1;
        m_sk			= "";
        m_signature		= "";
        m_serverTime    = 0;
        m_isNewAccount  = 1;
        m_PlayerReturnDays = 0;
        m_needPurge     = 0;
        m_useHttps      = true;
    }
   
    int32			m_UserId;
    std::string		m_sk;
    std::string     m_signature;
    int64           m_serverTime;
    int32			m_isNewAccount;
	int32 			m_PlayerReturnDays;
    int32           m_needPurge;
    bool            m_useHttps;
};

struct S2C_Profile
{
    int32 			userId;
    int32 			profileId;
    int32           versionNumber;
    std::string 	profile;
    std::string 	md5;
    int32  			lastUpdateTime;
    std::string     userName;
    
    S2C_Profile()
    {
        userId 			= 0;
        profile 		= "";
        md5 			= "";
        lastUpdateTime 	= 0;
        profileId       = -1;
        versionNumber   = 0;
        userName        = "";
    }
};

class S2C_ICloud_GetProfile: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetProfile, INetworkData, RtClass);
    
    S2C_ICloud_GetProfile()
    {
        
    }
    
    S2C_Profile     m_profile;
};

class S2C_ICloud_UploadFirstTimeResult: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_UploadFirstTimeResult, INetworkData, RtClass);
    
    S2C_ICloud_UploadFirstTimeResult()
    {
        profileId = -1;
        versionNumber = 0;
    }
    
    int32 			profileId;
    int32           versionNumber;
};

class S2C_VersionNumber : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_VersionNumber, INetworkData, RtClass);
    
    S2C_VersionNumber()
    {
        versionNumber = 0;
    }
    
    int32           versionNumber;
};


// class S2C_GetPlantInfo: public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_GetPlantInfo, INetworkData, RtClass);
    
//     std::vector<int>            m_plantList;
//     std::vector<S2C_BonusInfo>  m_plantChipInfo;
    
//     int           nfc;
// };

// class S2C_GetAvatarInfo: public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_GetAvatarInfo, INetworkData, RtClass);
    
//     std::vector<int>            m_avatarList;
//     std::vector<S2C_BonusInfo>  m_avatarChipInfo;
//     int                         nfc;
// };



class S2C_ICloud_GetCompensationInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetCompensationInfo, INetworkData, RtClass);
    
    S2C_PlayerInfo      m_playerInfo;
    int                 m_result;
    int                 m_compensationGem;
    int                 m_typeId;
    
    S2C_ICloud_GetCompensationInfo()
    {
        m_result = 0;
        m_compensationGem = 0;
        m_typeId = -1;
    }
};

struct S2C_GachaInfo
{
public:
    int                 profileId;
    int                 lastFreeTime;
    int                 isFirstPaidDrawDone;
    int64               serverTime;

    S2C_GachaInfo()
    {
        profileId = 0;
        lastFreeTime = 0;
        isFirstPaidDrawDone = 0;
        serverTime = 0;
    }
};

class S2C_ICloud_GetGachaInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetGachaInfo, INetworkData, RtClass);
    
    S2C_GachaInfo                 gachaInfo;
};

// struct S2C_PlantLevelInfo
// {
//     int32 plantId;
//     int level;
//     S2C_PlantLevelInfo()
//     {
//         plantId = 0;
//         level = 1;
//     }
// };

// class S2C_PlantLevel : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_PlantLevel, INetworkData, RtClass);
    
//     S2C_BonusInfo                   m_plantChipInfo;
//     S2C_PlantLevelInfo              m_plantLevelInfo;
//     std::vector<S2C_BonusInfo>      m_materialInfo;
// };

// struct S2C_AvatarLevelInfo
// {
//     int32 avatarId;
//     S2C_AvatarLevelInfo()
//     {
//         avatarId = 0;
//     }
// };

// class S2C_AvatarLevel: public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_AvatarLevel, INetworkData, RtClass);
    
//     S2C_BonusInfo       m_avatarChipInfo;
//     S2C_AvatarLevelInfo m_avatarLevelInfo;
// };

//========================== DailySignInfo ==========================

struct S2C_DailySign
{
    int m_loginCount;
    int32 m_lastRequestTime;
    
    S2C_DailySign()
    {
        m_loginCount = 0;
        m_lastRequestTime = 0;
    }
};

struct S2C_DailySignContent
{
    int32 itemId;
    int32 amount;
    
    S2C_DailySignContent()
    {
        itemId = 0;
        amount = 0;
    }
};

class S2C_ICloud_SignReward: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_SignReward, INetworkData, RtClass);
    
    int m_needRefreshList;
    S2C_DailySign m_dailySign;
    std::vector<int> m_dateList;
    std::vector<S2C_DailySignContent> m_rewardList;
    
    
};

struct S2C_TimeLevelNodeContent
{
    int     iLevelId;
    uint32  iTime;
    
    S2C_TimeLevelNodeContent()
    : iLevelId(0), iTime(0) {}
};

class S2C_TimeLevelNodeList: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_TimeLevelNodeList, INetworkData, RtClass);
    
    std::vector<S2C_TimeLevelNodeContent>  m_vCDingNodeList;
    int m_constraintId;
};

class S2C_StartTimeLevel: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_StartTimeLevel, INetworkData, RtClass);
    
    S2C_TimeLevelNodeContent  m_TimeLevelNodeContent;
};

class S2C_UnlockTimeLevel: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_UnlockTimeLevel, INetworkData, RtClass);
    
    S2C_TimeLevelNodeContent  m_TimeLevelNodeContent;
    int m_gem;
};

class S2C_ICloud_ReLoginResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_ReLoginResult, INetworkData, RtClass);
    S2C_ICloud_ReLoginResult()
    {
        m_UserId 		= -1;
        m_sk			= "";
    }
    int32			m_UserId;
    std::string		m_sk;
};

struct S2C_Endless
{
    int32 profileId;
    int remainLife;
    int32 lastRefreshTime;
    int purchaseCount;
    int periodId;
    
    S2C_Endless()
    {
        profileId           = -1;
        remainLife          = 0;
        lastRefreshTime     = 0;
        purchaseCount       = 0;
        periodId            = -1;
    }
};

struct S2C_ENDlessRank
{
    int32 profileId;
    int period;
    int rank;
    int score;
    
    S2C_ENDlessRank()
    {
        period              = 0;
        profileId           = -1;
        rank                = -1;
        score               = -1;
    }
};

struct S2C_ENDlessList
{
    int32 profileId;
    int rank;
    int score;
    std::wstring name;
    
    S2C_ENDlessList()
    {
        profileId           = -1;
        rank                = -1;
        score               = -1;
        name                = L"";
    }
};


class S2C_EndlessInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_EndlessInfo, INetworkData, RtClass);
    S2C_PlayerInfo                  m_playerInfo;
    S2C_Endless                     m_Endless;
    S2C_ENDlessRank                 m_EndlessRank;
    std::vector<S2C_ENDlessList>    m_EndLessList;
    
    S2C_EndlessInfo()
    {
    }
};

// class S2C_LeafConsume : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_LeafConsume, INetworkData, RtClass);
//     S2C_PlayerInfo      m_playerInfo;
//     int                 m_objectId;
//     int                 m_quantity;
    
//     S2C_LeafConsume()
//     {
//         m_objectId = 0;
//         m_quantity = 0;
//     }
    
// };

//Riddle
struct S2C_Riddle_Info
{
    int m_redPackNum;
    int m_riddleAnsweredDays;
    int m_canRiddleToday;
    int m_riddlePrizeGotIndex;
    int m_totalRedPackNum;
    int m_hasGotRankBonus;
    
    S2C_Riddle_Info()
    {
        m_redPackNum = 0;
        m_riddleAnsweredDays = 0;
        m_canRiddleToday = 0;
        m_riddlePrizeGotIndex = 0;
        m_totalRedPackNum = 0;
        m_hasGotRankBonus = 0;
    }
};

class S2C_ICloud_RiddleInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RiddleInfo, INetworkData, RtClass);
    
    S2C_Riddle_Info m_riddleInfo;
};

class S2C_ICloud_RiddleResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RiddleResult, INetworkData, RtClass);
    
    S2C_Riddle_Info     m_riddleInfo;
    
    int                 m_needRefreshList;
};

class S2C_ICloud_RiddlePrize : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RiddlePrize, INetworkData, RtClass);
    
    S2C_Riddle_Info     m_riddleInfo;
    
    std::vector<int>    m_riddlePrizeIndex;
};

// class S2C_ICloud_ExchangePendant : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ICloud_ExchangePendant, INetworkData, RtClass);
    
//     S2C_PlantPendantInfo    m_plantPendantInfo;
//     S2C_BonusInfo           m_plantPendantChipInfo;
// };

// class S2C_ICloud_SoldPendant : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ICloud_SoldPendant, INetworkData, RtClass);
    
//     int64 pendantId;
// };

//RedPack
struct S2C_RedPack_Self
{
    int m_rank;
    int m_score;
    S2C_RedPack_Self()
    {
        m_rank = 0;
        m_score = 0;
    }
};

struct S2C_RedPack_Public
{
    std::string m_name;
    std::string m_score;
    int m_rank;
    S2C_RedPack_Public()
    {
        m_name = "";
        m_rank = 0;
        m_score = "";
    }
};

struct S2C_RedPackContent
{
    int itemId;
    int amount;
    
    S2C_RedPackContent()
    {
        itemId = 0;
        amount = 0;
    }
};

class S2C_ICloud_RedPackInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RedPackInfo, INetworkData, RtClass);
    
    S2C_Riddle_Info     m_riddleInfo;
    
    S2C_RedPack_Self    m_redPackSelfInfo;
};

class S2C_ICloud_RedPackLeaderBoard : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RedPackLeaderBoard, INetworkData, RtClass);
    
    std::vector<S2C_RedPack_Public> m_redPackLeaderBoard;
    int m_selfInRank;
};

struct S2C_DangerRoom_Public
{
    std::string m_name;
    std::string m_score;
    int m_rank;
    S2C_DangerRoom_Public()
    {
        m_name = "";
        m_rank = 0;
        m_score = "";
    }
};

class S2C_ICloud_DangerRoomLeaderBoard : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_DangerRoomLeaderBoard, INetworkData, RtClass);
    
    std::vector<S2C_DangerRoom_Public> m_dangerRoomLeaderBoard;
};

class S2C_ICloud_RedPackLeaderBoardReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RedPackLeaderBoardReward, INetworkData, RtClass);
    
    std::vector<S2C_PlantPendantInfo> m_pendantInfo;
    std::vector<S2C_RedPackContent> m_prizeInfo;
    
};

struct S2C_ICLOUD_2015NewYearCharge
{
    int m_canAct;
    
    S2C_ICLOUD_2015NewYearCharge()
    {
        m_canAct = -1;
    }
};

class S2C_ICloud_2015NewYear_ChargeInfo :public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_2015NewYear_ChargeInfo, INetworkData, RtClass);
    
    S2C_ICLOUD_2015NewYearCharge m_nyc5;
};

class S2C_ICloud_PendantGacha : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_PendantGacha, INetworkData, RtClass);
    
    S2C_PlayerInfo                      m_playerInfo;
    std::vector<S2C_BonusInfo>          m_bonusList;
    std::vector<S2C_PlantPendantInfo>   m_pendantInfo;
    
    S2C_ICloud_PendantGacha()
    {
    }
};

class S2C_ICloud_RedPackOpenInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_RedPackOpenInfo, INetworkData, RtClass);
    
    S2C_Riddle_Info     m_riddleInfo;
    std::vector<std::vector<S2C_RedPackContent> > m_redPackPrize;
    std::vector<S2C_PlantPendantInfo> m_pendantInfo;
};

// class S2C_ICloud_PlantTrialInfo : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ICloud_PlantTrialInfo, INetworkData, RtClass);
    
//     S2C_PlayerInfo                          m_playerInfo;
//     std::vector<S2C_PlantListInfo>          m_plantList;
//     std::vector<S2C_BonusInfo>              m_plantChipInfo;
// };

class S2C_GetPendantInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GetPendantInfo, INetworkData, RtClass);
    
    std::vector<S2C_BonusInfo>          m_pendantChipInfo;
    std::vector<S2C_PlantPendantInfo>   m_pendantInfo;
    int                                 nfc;
};

struct ConsumptionRewardList
{
    int index;
    int objectId;
    int amount;
    ConsumptionRewardList()
    {
        index = 0;
        objectId = 0;
        amount = 0;
    }
};

struct ComsumptionRewardStat
{
    ComsumptionRewardStat()
    {
        costGem = 0;
        period = 0;
        canBeReward = 0;
        rewardIndex = 0;
        specialObjectId = 0;
    }
    
    int costGem;
    int period;
    int canBeReward;
    int rewardIndex;
    int specialObjectId;
};

class S2C_ConsumptionRewardStat : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ConsumptionRewardStat, INetworkData, RtClass);
    
    ComsumptionRewardStat comsumptionRewardStat;
};

class S2C_ConsumptionReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ConsumptionReward, INetworkData, RtClass);
    
    S2C_ConsumptionReward()
    {
        rewardCoins = 0;
    }
    
    ComsumptionRewardStat                   comsumptionRewardStat;
    int                                     rewardCoins;
    int                                     rewardGem;
    std::vector<S2C_BonusInfo>              m_avatarChipInfo;
    std::vector<int>                        m_avatarList;
    std::vector<S2C_PlantPendantInfo>       m_pendantInfo;
    std::vector<S2C_BonusInfo>              m_pendantChipInfo;
    std::vector<S2C_PlantListInfo>          m_plantList;
    std::vector<S2C_BonusInfo>              m_plantChipInfo;
    std::vector<ConsumptionRewardList>      m_bonusListInfo;
};

class S2C_EndlessBonus : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_EndlessBonus, INetworkData, RtClass);
    
    S2C_PlayerInfo m_playerInfo;
    std::vector<S2C_BonusInfo> m_plantChipInfo;
    int m_rewardCoins;
};

//=============================== Birthday =================================
class S2C_BirthdayReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BirthdayReward, INetworkData, RtClass);
    std::vector<S2C_PlantListInfo>  m_plantList;
    std::vector<S2C_BonusInfo>      m_plantChipInfo;
    int m_rewardCoins;
};

//=============================== Wechat Share ================================
class S2C_WechatShareReward : public INetworkData
{
    RT_CLASS_DEFINE(S2C_WechatShareReward, INetworkData, RtClass);
    S2C_PlayerInfo m_playerInfo;
    int m_rewardCoins;
};

//=============================== Pinata =================================
class S2C_PinataReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PinataReward, INetworkData, RtClass);
    std::vector<S2C_PlantListInfo>  m_bonusPlant;
    std::vector<S2C_BonusInfo>      m_bonusChip;
    S2C_PlayerInfo m_playerInfo;
    int m_rewardCoins;
};

// //=============================== Explore ================================
// struct S2C_Explore_Team
// {
//     uint32 exploreEndTime;
//     int32 dungeonId;
//     int   chances;
//     int   status;
//     int   plantChipId;
//     int   bonus;
//     int   surpriseObjectId;
//     int   surprise;
//     int   coins;
//     int   surprisePrice;
//     std::vector<int> plantsList;
    
//     S2C_Explore_Team()
//     {
//         exploreEndTime = 0;
//         dungeonId = -1;
//         chances = 0;
//         status = 0;
//         plantChipId = 0;
//         bonus = 0;
//         surprise = 0;
//         coins = 0;
//         surprisePrice = 0;
//     }
// };

// struct S2C_Explore_Plant
// {
//     uint32 endTime;
//     int32 plantId;
//     int   status;
    
//     S2C_Explore_Plant()
//     {
//         endTime = 0;
//         plantId = 0;
//         status = 0;
//     }
// };

// class S2C_ExplorerStart : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ExplorerStart, INetworkData, RtClass);
//     std::vector<S2C_Explore_Team>  m_teamList;
//     S2C_PlayerInfo m_playerInfo;
//     int needGems;
//     int gemCost;
// };

// class S2C_ExplorerTeamStatus : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ExplorerTeamStatus, INetworkData, RtClass);
    
//     S2C_ExplorerTeamStatus()
//     {
//         m_teamList.clear();
//         m_serverTime = 0;
//     }
    
//     int64 m_serverTime;
//     std::vector<S2C_Explore_Team>  m_teamList;
// };

// class S2C_ExplorerPlantStatus : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ExplorerPlantStatus, INetworkData, RtClass);
//     std::vector<S2C_Explore_Plant>  m_plantList;
//     int m_dungeonId;
// };

// class S2C_StopExplore : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_StopExplore, INetworkData, RtClass);
    
//     int diamondLess;
//     S2C_PlayerInfo m_playerInfo;
//     std::vector<S2C_Explore_Team>   m_teamList;
// };

// class S2C_ExploreReward : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ExploreReward, INetworkData, RtClass);
    
//     std::vector<S2C_Explore_Team>   m_teamList;
//     std::vector<S2C_BonusInfo>      m_plantChipInfo;
// };

// class S2C_SurpriseReward : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_SurpriseReward, INetworkData, RtClass);
    
//     std::vector<S2C_BonusInfo>  m_plantSurpriseInfo;
//     S2C_PlayerInfo m_playerInfo;
// };

// class S2C_ExplorePlantRecover : public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ExplorePlantRecover, INetworkData, RtClass);
    
//     std::vector<S2C_Explore_Plant>  m_plantList;
//     S2C_PlayerInfo m_playerInfo;
//     int m_gemsRequired;
// };

// class S2C_ChristmasLottery: public INetworkData
// {
// public:
//     RT_CLASS_DEFINE(S2C_ChristmasLottery, INetworkData, RtClass);
    
//     int                 m_plantIndex;
//     S2C_BonusInfo       m_christmasLottery;
//     S2C_PlayerInfo      m_playerInfo;
    
//     S2C_ChristmasLottery()
//     {
//         m_plantIndex = 0;
//     }
// };

class S2C_ChristmasGoldenEggInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasGoldenEggInfo, INetworkData, RtClass);
    
    int hammers;
    int hammersLeft;
    int dailyReward;
    std::vector<int> goldenEggStat;
    
    S2C_ChristmasGoldenEggInfo()
    {
        hammers = 0;
        hammersLeft = 0;
        dailyReward = 0;
        goldenEggStat.clear();
    }
};

class S2C_ChristmasGoldenEggStat : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasGoldenEggStat, INetworkData, RtClass);
    
    S2C_ChristmasGoldenEggInfo  m_ceInfo;
    int m_option;
};

class S2C_ChristmasGoldenEggTicket : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasGoldenEggTicket, INetworkData, RtClass);
    
    int m_type;
    S2C_ChristmasGoldenEggInfo  m_ceInfo;
    std::vector<S2C_BonusInfo>  m_chipsInfo;
    S2C_PlayerInfo m_playerInfo;
};

class S2C_ChristmasAccessoryInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasAccessoryInfo, INetworkData, RtClass);
    
    int freeChances;
    int coinChances;
    int gemChances;
    std::vector<int>  freeIndex;
    std::vector<int>  coinIndex;
    std::vector<int>  gemIndex;
    
    S2C_ChristmasAccessoryInfo()
    {
        freeChances = 0;
        coinChances = 0;
        gemChances = 0;
        freeIndex.clear();
        coinIndex.clear();
        gemIndex.clear();
    }
};

class S2C_ChristmasAccessoryStat : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasAccessoryStat, INetworkData, RtClass);
    
    S2C_ChristmasAccessoryInfo  m_caInfo;
    int m_option;
};

class S2C_ChristmasAccessoryTicket : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasAccessoryTicket, INetworkData, RtClass);
    
    S2C_ChristmasAccessoryInfo  m_caInfo;
    std::vector<S2C_BonusInfo>  m_pendantChipInfo;
    S2C_PlayerInfo m_playerInfo;
};

class S2C_SyncCachedObjectsInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SyncCachedObjectsInfo, INetworkData, RtClass);
    
    int                                 m_gems;
    int                                 m_gold;
    int                                 m_nfc;
    std::vector<S2C_BonusInfo>          m_bonusList;
    std::vector<S2C_PlantPendantInfo>   m_pendantInfo;
};

#endif

class S2C_InstanceStatus : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_InstanceStatus, INetworkData, RtClass);
    int32               m_instantId;
    int32               m_remainNum;
    int32               m_queryStatus;
    int32               m_gem = -1;
    S2C_PlayerInfo      m_playerInfo;
    int32               m_leftBuyTimes = 0;
    int					m_adTimes = 0;
};

class S2C_ICloud_Service_Status : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_Service_Status, INetworkData, RtClass);
    
    bool m_gemRestoreStatus;
    bool m_ifengfengStatus;
    bool m_stoneTabStatus;
    bool m_forceLuaStatus;
    bool m_forceConfigStatus;
    bool m_adsMapStatus;
    int  m_adsMapRate;
    bool m_adsMissionStatus;
    int  m_adsMissionLimit;
    int  m_adsMapLimit;
    bool m_coderewardStatus;
    bool m_updateRsbStatus;
    bool m_authStatus;
    float  m_authInterval;
    bool m_syncActions;
    bool m_isShowNewAvatarSwitch;
    bool m_reconnect;
    bool m_hmdEventOpen;
    // Android added
    bool m_adsPauseStatus;
    bool m_adsGameStartStatus;
    bool m_adsBoxStatus;
    std::vector<int> m_adsTotalRate;
    std::vector<std::string> m_adBlackList;
    std::vector<std::string> m_watchADBlackList;
    int m_maxAdPerDay;
    bool m_bNeedVersionLimit;
    bool m_bShowDIYMotivateButton;
    std::string m_strMaxVersion;
    std::string m_strMinVersion;
    std::vector<int> m_payCheckChannel;
    std::wstring m_authLimitDesc;
    std::wstring m_authDesc;
    std::string m_diyDefatulURL;
    float m_customLevelEvaluationParam;
    bool m_specialBackground;

#ifdef HOST_ANDROID // this is for android advertisement
    bool m_Ads_free_chest_gacha;
    bool m_Ads_plant_adventure_skip;
    bool m_Ads_battle_start;
    bool m_Ads_world_select;
    bool m_Ads_battle_statement;
    bool m_Ads_challenge;
    bool m_Ads_dailysign;
    bool m_Show_GM_Info;
    bool m_Show_GM_Info_SettingDialog;
    bool m_Show_Logout;
    bool m_Show_GM_Info_Complain;
#endif

    S2C_ICloud_Service_Status()
    {
        m_gemRestoreStatus = false;
        m_ifengfengStatus  = false;
        m_stoneTabStatus   = false;
        m_forceLuaStatus   = false;
        m_forceConfigStatus= false;
        m_adsMapStatus     = false;
        m_adsMapRate       = -1;
        m_adsMissionStatus = false;
        m_bNeedVersionLimit = false;
        m_bShowDIYMotivateButton = true;
        m_adsMissionLimit = -1;
        m_coderewardStatus = false;
        m_updateRsbStatus = false;
        m_authStatus = false;
        m_authInterval = 0.0f;
        m_syncActions = false;
        m_adsMapLimit = -1;
        // Android added
        m_adsPauseStatus = false;
        m_adsGameStartStatus = false;
        m_adsBoxStatus = false;
        m_isShowNewAvatarSwitch = false;
        m_maxAdPerDay = 0;
        m_customLevelEvaluationParam = 1.0f;
        m_reconnect = false;
        m_hmdEventOpen = false;

#ifdef HOST_ANDROID
    	m_Ads_free_chest_gacha = false;
    	m_Ads_plant_adventure_skip = false;
    	m_Ads_battle_start = false;
    	m_Ads_world_select = false;
    	m_Ads_battle_statement = false;
        m_Ads_challenge = false;
        m_Ads_dailysign = false;
        m_Show_GM_Info = true;
        m_Show_GM_Info_SettingDialog = true;
        m_Show_Logout = true;
        m_Show_GM_Info_Complain = true;
#endif
    }
};

class ChildrenDayItem : public INetworkData
{
public:
	RT_CLASS_DEFINE(ChildrenDayItem, INetworkData, RtClass);
	int id = 0;
	int count = 0;
};

class MonthlyCardStatus : public INetworkData
{
public:
    RT_CLASS_DEFINE(MonthlyCardStatus, INetworkData, RtClass);
    int32 status = -1;
    int32 leftDays = 0;
    int32 freeCuke = 0;
    int32 freeGem = 0;
    int32 bonusSun = 0;
};

class S2C_ChristmasProtect : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ChristmasProtect, INetworkData, RtClass);

	std::vector<S2C_BonusInfo>  m_rewardList;
	S2C_PlayerInfo m_playerInfo;
};

class S2C_ChristmasCheckRebate: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasCheckRebate, INetworkData, RtClass);

    std::vector<int> m_vStateFlag;

    bool CanGetReward()
    {
        for (auto z : m_vStateFlag)
        {
            if (z == 1)
                return true;
        }

        return false;
    }

    S2C_ChristmasCheckRebate()
    {
    }
};

class S2C_ICloud_GetPlayerInfoRecharge: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetPlayerInfoRecharge, INetworkData, RtClass);
    
    S2C_PlayerInfo      m_playerInfo;
    int                 m_used;
    int                 m_totalCharge;
    int                 m_activeTotalCharge;
    int                 m_objectId;
    std::vector<ChildrenDayItem> m_childrenDayItemList;
    MonthlyCardStatus   m_monthlyCard;
    
};

struct RebateRewardItem
{
    int iObjectId = 0;
    int iCount;

    RebateRewardItem() : iCount(0) {}
};

class S2C_ChristmasRebate: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ChristmasRebate, INetworkData, RtClass);

    RebateRewardItem m_PlantItem;
    RebateRewardItem m_AvatarItem;
    std::vector<int> m_vStateFlag;

    S2C_ChristmasRebate()
    {
    }
};

class S2C_ICloud_GetStatusThirdPart: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetStatusThirdPart, INetworkData, RtClass);
    
    std::string m_sinaUUID;
    std::string m_wechatUUID;
    std::string m_tencentUUID;
    
    S2C_ICloud_GetStatusThirdPart()
    {
        m_sinaUUID    = "";
        m_wechatUUID  = "";
        m_tencentUUID = "";
    }
};

// 1.0 yuan pay
class S2C_GemReturnRewardStat : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GemReturnRewardStat, INetworkData, RtClass);
    
    int                 m_isCharged;
    std::vector<int>    m_bonusList;
};

class S2C_GemReturnRewardInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GemReturnRewardInfo, INetworkData, RtClass);
    
    S2C_PlayerInfo      m_playerInfo;
    std::vector<int>    m_bonusList;
};

// active activity
struct SalesServerPrice
{
    int pieces;
    int price;
};

struct SpringSalesStates
{
    int opening;
    std::string configName;
    std::vector<SalesObject> salesList;
    std::vector<SalesServerPrice> priceList;
    
    SpringSalesStates()
    {
        opening = 0;
        configName = "";
        salesList.clear();
        priceList.clear();
    }
};

struct LevelOfTheDayInfo
{
    int opening;
//    std::string configName;
    LevelofTheDayActiveInfo activeStates;
    
    LevelOfTheDayInfo()
    {
        opening = 0;
//        configName = "";
    }
};

struct ChildrenDayStates
{
    int opening = 0;
    int refreshHour = 0;
    int buyLimit = 0;
    int startDays = 0;
    int remainDays = 0;
    std::string configName;
    std::vector<ChildrenDayItem> m_itemList;
};

struct LotteryBonus
{
    int BonusId = 0;
    int Quantity = 0;
    int Weight = 0;
};

struct NDLoginRewardBonus
{
	int BonusId = 0;
	int Quantity = 0;
};

struct SpringLoginRewardBonus
{
    int plantID = 0;
    int nDuration = 0;
};

struct ExpPlantLoginConfig
{
	ExpPlantLoginConfig(int i_sumdays, bool i_rewarded)
	{
		SumDays = i_sumdays;
		Rewarded = i_rewarded;
	}
	ExpPlantLoginConfig()
	{
		SumDays = 0;
		Rewarded = false;
	}
	int SumDays;
	bool Rewarded;
};

struct DaveClubBonus
{
	int ActionId = 0;
	int Order = 1;
	bool IsOpen = false;
};

struct DailyAwardBonus
{
	int alreadyAwardDay = 0;
	bool isRewardToday = false;
	std::string rewardTime;
	int curNationDay = 0;
	std::vector<std::vector<NDLoginRewardBonus>>  m_vecRewardBonus;
};

struct PlayerAddressInfo
{
    std::string Tel = "";
    std::string Email = "";
};

class S2C_GeilivableLotteryReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GeilivableLotteryReward, INetworkData, RtClass);
    
    int Period = 0;
    int TotalCost = 0;
    int OncePay = 0;
    int DollWon = 0;
    int DollLeft = 0;
    int LeftChance = 0;
    PlayerAddressInfo PlayerAddress;
    LotteryBonus Bonus;
    S2C_PlayerInfo PlayerInfo;
};

class S2C_StoneLotteryReward : public INetworkData
{
	RT_CLASS_DEFINE(S2C_StoneLotteryReward, INetworkData, RtClass);
	int Period = 0;
	int OncePay = 0;
	int TotalChance = 0;
	int LeftChance = 0;
	bool IsFirstToLottery = false;
	LotteryBonus Bonus;
};

class S2C_7DaysLoginReward : public INetworkData
{
	RT_CLASS_DEFINE(S2C_7DaysLoginReward, INetworkData, RtClass);
	std::vector<NDLoginRewardBonus> m_vecRewardBonus;
	int awardDay;
};

class S2C_7DaysLoginSpringReward : public INetworkData
{
    RT_CLASS_DEFINE(S2C_7DaysLoginSpringReward, INetworkData, RtClass);
    std::vector<SpringLoginRewardBonus> m_vecRewardBonus;
    //int awardDay;
    std::vector<ExpPlantLoginConfig> m_loginConfigs;
};

class S2C_buyPlantSpringReward : public INetworkData
{
    RT_CLASS_DEFINE(S2C_buyPlantSpringReward, INetworkData, RtClass);
    int plantID;
};

class S2C_RechargeReward : public INetworkData
{
	RT_CLASS_DEFINE(S2C_RechargeReward, INetworkData, RtClass);
	std::vector<NDLoginRewardBonus> m_vecRewardBonus;
	int leftAwardChance;
};


class S2C_unLockWorldTeam : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_unLockWorldTeam, INetworkData, RtClass);
    S2C_unLockWorldTeam()  : m_nTeamID(0) {}
	int m_nTeamID;
};

class S2C_TGResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_TGResult, INetworkData, RtClass);
    
    std::vector<S2C_BonusInfo> CostList;
    std::vector<S2C_BonusInfo> ProductList;
    S2C_PlayerInfo PlayerInfo;
    int GoldCost;
    int m_adTimes;
};

class S2C_ActActitityStates : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ActActitityStates, INetworkData, RtClass);
    
    int m_typeId;
    SpringSalesStates m_springSalesStates;
    LevelOfTheDayInfo m_levelOfTheDayInfo;
    ChildrenDayStates m_childrenDayStates;
    
    S2C_ActActitityStates()
    {
        m_typeId = -1;
        
        return;
    }
};

class S2C_ICloud_LuaGeneral : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_LuaGeneral, INetworkData, RtClass);
    std::string     m_strJsonInfo;
};

// Sales
struct S2C_SalesLevelUpInfo
{
    int levelUp;
    int plantId;
    int targetLevel;
    
    S2C_SalesLevelUpInfo()
    {
        levelUp = 0;
        plantId = -1;
        targetLevel = -1;
    }
};

class S2C_SalesStates : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SalesStates, INetworkData, RtClass);
#ifdef ANDROID
    std::vector<S2C_BonusInfo> m_bonusList;
//#if ANDROID_CONVERT_IOS // zhousen new add
    S2C_PlayerInfo m_playerInfo;
    S2C_SalesLevelUpInfo m_levelUpInfo;
//#endif
#else
    std::vector<S2C_BonusInfo> m_bonusList;
    S2C_PlayerInfo m_playerInfo;
    S2C_SalesLevelUpInfo m_levelUpInfo;
#endif
};

//ads
class AdsData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(AdsData, Sexy::RtObject, Sexy::RtClass);
    
public:
    int m_type = 0;
    int m_id = -1;
    int m_lastTimes = 0;
    std::vector<S2C_BonusInfo> m_bonusList;
};

class S2C_ADSReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ADSReward, INetworkData, RtClass);
    
    S2C_PlayerInfo m_playerInfo;
    std::vector<S2C_BonusInfo> m_bonusList;
    AdsData m_nextAds;
};

//=============================== PVE Board ================================
class S2C_ItemInfo
{
public:
    int     m_id = 0;
    int     m_num = 0;
};

class S2C_CurrencyInfo
{
public:
    void    SetToPlayerInfo();
public:
    int     m_gem = -1;     // in android, < 0 means substract, > 0 means add. in IOS, set the value directly.
    bool    m_gemValid = false;
    int     m_coin = -1;
    bool    m_coinValid = false;
    
    int     m_pvpCoin = -1; // -1 means invalid
    int     m_pvpMedal = -1;
    
    std::vector<S2C_ItemInfo> m_rewardList;
};

class S2C_NoticeInfo
{
public:    
    int             m_id = 0;
    std::wstring    m_wstrTitle;
    std::wstring    m_wstrContent;
    std::string     m_strImage;
    int            m_readStatus = 0;
    int            m_rewardStatus = 0;
    S2C_CurrencyInfo    m_currency;
};

class S2C_NoticeInfoList : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_NoticeInfoList, INetworkData, RtClass);
    std::vector<S2C_NoticeInfo> m_infoList;
};

class S2C_NoticeInfoGet : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_NoticeInfoGet, INetworkData, RtClass);
    int     m_id = 0;
    int     m_readStatus = 0;
    int     m_rewardStatus = 0;
    S2C_CurrencyInfo    m_currency;
};

class S2C_UUID_BindResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_UUID_BindResult, INetworkData, RtClass);
    
    S2C_UUID_BindResult()
    {
        m_OldUserId 		= -1;
        m_NewUserId         = -1;
    }
    
    int32			m_OldUserId;
    int32			m_NewUserId;
};

class S2C_UUID_InitResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_UUID_InitResult, INetworkData, RtClass);

    S2C_UUID_InitResult()
    {
    	uuid         = "";
    	access_token = "";
    }

    std::string        uuid;
    std::string        access_token;
};

class S2C_UUID_CheckResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_UUID_CheckResult, INetworkData, RtClass);

    S2C_UUID_CheckResult()
    {
    	result       = -1;
    	access_token = "";
    }

    int 			   result;
    std::string        access_token;
};

class S2C_ICloud_GetUserInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetUserInfo, INetworkData, RtClass);

    S2C_PlayerInfo      m_playerInfo;
};

struct S2C_NewGachaInfo
{
public:
    int                 profileId;
    int                 lastFreeTime;
    int                 isFirstPaidDrawDone;
    int64               serverTime;
    int                 type;

    S2C_NewGachaInfo()
    {
        profileId = 0;
        lastFreeTime = 0;
        isFirstPaidDrawDone = 0;
        serverTime = 0;
        type = 0;
    }
};

struct S2C_NewGachaKeyInfo
{
public:
    int m_nTypeId = 0;
    int m_nAmount = 0;
};

class S2C_ICloud_GetChargeRewardInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetChargeRewardInfo, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> m_bonusList;
    S2C_PlayerInfo m_playerInfo;
    int m_typeId = -1;
    int m_chargeNum = 0;
};

//-----------------------------------------------------------------------------
// PVP Data
//-----------------------------------------------------------------------------
class ServerItemID
{
public:
    virtual int         ToInt() = 0;        // server id
    virtual std::string ToString() = 0;
protected:
    int m_ID;
};

class ServerPlantID : public ServerItemID
{
public:
    ServerPlantID(int i_id);
    ServerPlantID(const std::string& i_name);
    
    virtual int         ToInt();
    virtual std::string ToString();
};

class ServerZombieID : public ServerItemID
{
public:
    ServerZombieID(int i_id);
    ServerZombieID(const std::string& i_name);
    
    virtual int         ToInt();
    virtual std::string ToString();
};

//=============================== PVP Login ================================
class S2C_PVP_Login : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_Login, INetworkData, RtClass);
    
    int m_remainChallenge;
    int m_coldTime;
    int m_pvpCup;
    int m_pvpCoin;
    int m_pvpMedal;
    int m_gemToday;
    int m_achievementTrainCoin;
    int m_achievementTrainSpace;
    int m_leagueId;
    uint64 m_maxBattleID;
    int m_trainingSeconds;
    int m_labSeconds;
    int m_baseLevel;
    PvPRankMonthReward m_rankMonthReward;
    
    S2C_PVP_Login()
    : m_remainChallenge(0)
    , m_coldTime(0)
    , m_pvpCup(0)
    , m_pvpCoin(0)
    , m_pvpMedal(0)
    , m_gemToday(0)
    , m_achievementTrainCoin(0)
    , m_achievementTrainSpace(0)
    , m_leagueId(0)
    , m_maxBattleID(0)
    , m_trainingSeconds(0)
    , m_labSeconds(0)
    , m_baseLevel(0)
    {
    }
    
};

//=============================== PVP Training ================================
struct S2C_Training_ZombieData
{
public:
    int     m_serverID;
    int     m_queueNum;
    int     m_firstLeftTime;
    int     m_haveNum;
    uint64   m_queueOrder;
};

struct S2C_PVP_ZombieData
{
public:
    int     m_serverID;
    int     m_level;
    S2C_PVP_ZombieData()
    {
        m_serverID = 0;
        m_level = 1;
    }
};

struct C2S_PVP_ZombieNum
{
public:
    int     m_serverID;
    int     m_num;
};

class C2S_PVP_SellZombies : public INetworkData
{
public:
    RT_CLASS_DEFINE(C2S_PVP_SellZombies, INetworkData, RtClass);
    
    std::vector<C2S_PVP_ZombieNum>    m_sellList;
};

class S2C_PVP_TrainingInfos : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_TrainingInfos, INetworkData, RtClass);
    
    int             m_maxSpace;
    std::vector<S2C_Training_ZombieData>    m_trainingList;
    std::vector<S2C_PVP_ZombieData>         m_zombieList;
    
    S2C_PVP_TrainingInfos()
    : m_maxSpace(0)
    {
    }
    
};

class S2C_PVP_TrainingZombie : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_TrainingZombie, INetworkData, RtClass);
    
    std::vector<S2C_Training_ZombieData>    m_trainingList;
    int         m_pvpCoin;
    
    S2C_PVP_TrainingZombie()
    : m_pvpCoin(0)
    {
    }
    
};

class S2C_PVP_TrainingFinishAtOnce : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_TrainingFinishAtOnce, INetworkData, RtClass);
    
    std::vector<S2C_Training_ZombieData>    m_trainingList;
    S2C_PlayerInfo                      m_playerInfo;
};

class S2C_PVP_TrainingFinishGems : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_TrainingFinishGems, INetworkData, RtClass);
    
    int m_Gems;
};

struct S2C_PVP_BigMapMainInfo
{
    int level;
    int medal;
    int medalMax;
    int gold;
    int goldMax;
    int cupSpeed;
    int goldSpeed;
    int zoneId;
    int zonePos;
    S2C_PVP_BigMapMainInfo()
    {
        level = 0;
        medal = 0;
        medalMax = 0;
        gold = 0;
        goldMax = 0;
        cupSpeed = 0;
        goldSpeed = 0;
        zoneId = 0;
        zonePos = 0;
    }
};

struct S2C_PVP_ZombieInfo
{
    int zombieId;
    int num;
    int level;
};

struct S2C_PVP_RankInfo
{
    int64             m_profileId;
    std::wstring      m_name;
    int32             m_order;
    int32             m_attackWin;
    int32             m_defendWin;
    int32             m_cupCount;
};

struct S2C_PVP_PreGardenRankInfo
{
    int64             m_profileId;
    std::wstring      m_name;
    int32             m_order;
    int32             m_cupCount;
};

#define LEAGUE_LEVEL            7   //1-7
#define LEAGUE_LEVEL_COUNT      3   //1-3
struct S2C_PVP_LeagueInfo
{
    int32             m_leagueId; //1-21, 0 means not in league
    int32             m_minCup;
    int32             m_maxCup;
    int32             m_winCoin;
    int32             m_winPVPCoin;
    
    int32   getLeagueLevel()
    {
        if (m_leagueId == 0)
        {
            return 1;
        }
        return (m_leagueId - 1) / LEAGUE_LEVEL_COUNT + 1;
    }
    
    int32   getLeagueLevelRank()
    {
        int32 rank = m_leagueId % LEAGUE_LEVEL_COUNT;
        if(rank == 0)
        {
            return LEAGUE_LEVEL_COUNT;
        }
        else
        {
            return rank;
        }
    }
};

struct S2C_PVP_GardenRewardInfo
{
    int32           m_order;
    int32           m_orderEnd;
    int32           m_rewardType;
    int32           m_rewardCount;
};

class S2C_PVP_MapInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_MapInfo, INetworkData, RtClass);
    
    int unlockPrice;
    std::vector<S2C_PVP_BigMapInfo> m_mapInfoList;
    std::vector<S2C_PVP_ZombieInfo> m_zombieInfoList;
    
    S2C_PVP_MapInfo()
    {
    }
    
};

class S2C_PvPRankInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PvPRankInfo, INetworkData, RtClass);
    
    int32                           m_rankType;
    int32                           m_startIdx = 0;
    int32                           m_totalCount;
    std::vector<S2C_PVP_RankInfo>   m_rankInfoList;
    std::vector<S2C_PVP_PreGardenRankInfo>   m_preGardenRankInfoList;
    S2C_PVP_RankInfo                m_myRankInfo;
    int32                           m_leagueRewardTime = 0;
    int32                           m_leagueTotalRewardTime = 0;
    
    S2C_PvPRankInfo()
    {
        m_rankType = 0;
        m_totalCount = 0;
    }
};

class S2C_PvPOtherUserZbInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PvPOtherUserZbInfo, INetworkData, RtClass);
    
    int64                               m_profileId;
    std::vector<S2C_PVP_ZombieInfo>     m_zbInfoList;
    
    S2C_PvPOtherUserZbInfo()
    {
        m_profileId = 0;
    }
};

class S2C_PVP_Achieve : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_Achieve, INetworkData, RtClass);
    
    int m_gold;
    int m_medal;
    int m_totalGold = 0;
    int m_totalMetal = 0;
    std::vector<S2C_PVP_BigMapInfo> m_mapInfoList;
    
    S2C_PVP_Achieve()
    {
        m_gold = 0;
        m_medal = 0;
    }
    
};

class S2C_PVP_PVPMapInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_PVPMapInfo, INetworkData, RtClass);
    
    int unlockPrice;
    std::vector<S2C_PVP_BigMapInfo> m_mapInfoList;
    std::vector<S2C_PVP_BigMapPVPInfo> m_mapPVPInfoList;
    std::vector<S2C_PVP_ZombieInfo> m_zombieInfoList;
    
    S2C_PVP_BigMapMainInfo mainInfo;
    
    int m_iEvilDavidStatus;
    
    S2C_PVP_PVPMapInfo()
    : m_iEvilDavidStatus(-1)
    {
        unlockPrice = 0;
    }
    
};

class S2C_PVP_Unlock : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_Unlock, INetworkData, RtClass);
    
    int m_gold;
    int m_unlockPrice = 0;
    std::vector<S2C_PVP_BigMapInfo> m_mapInfoList;
    std::vector<S2C_PVP_BigMapPVPInfo> m_mapPVPInfoList;
    
    S2C_PVP_Unlock()
    {
        m_gold = 0;
    }
    
};

class S2C_PVP_Entry : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_Entry, INetworkData, RtClass);
    
    int m_gold;
    int m_cup;
    int m_battlePingInterval;
    int m_defensePingInterval;
    int m_rankCacheInterval;
    std::vector<S2C_PVP_LeagueInfo> m_leagueInfoList;
    std::vector<S2C_PVP_GardenRewardInfo> m_gardenRewardInfoList;
    
    S2C_PVP_Entry()
    {
        m_gold = 0;
        m_cup = 0;
        m_battlePingInterval = 30;
        m_defensePingInterval = 30;
        m_rankCacheInterval = 60;
    }
    
};

class S2C_PVP_ChangeEnemy : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_ChangeEnemy, INetworkData, RtClass);
    
    int m_gold = 0;
    S2C_PVP_BigMapInfo m_mapInfo;
    S2C_PVP_BigMapPVPInfo m_mapPVPInfo;
    
    S2C_PVP_ChangeEnemy()
    {
        m_mapInfo.zoneId = -1;
        m_mapPVPInfo.zoneId = -1;
    }
    
};

struct S2C_PVP_DefenderInfo
{
    S2C_PVP_DefenderInfo()
    {
        m_name = L"";
        m_profileId = -1;
        m_winCup = 0;
        m_lostCup = 0;
        m_winCurrency = 0;
    }
    
    std::wstring  m_name;
    int32         m_profileId;
    int32         m_winCup;
    int32         m_lostCup;
    int32         m_winCurrency;
};

class S2C_PVP_PlayerInfos: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_PlayerInfos, INetworkData, RtClass);
    
    std::string m_info;
    std::string m_infoMD5;
    S2C_PVP_DefenderInfo m_defenderInfo;
    std::vector<S2C_PVP_ZombieInfo> m_zombieInfo;
    int32 m_currency;
    int32 m_cooldown;
    //std::string m_zombieInfo;
    
    S2C_PVP_PlayerInfos()
    {
        m_info    = "";
        m_infoMD5 = "";
        m_currency = 0;
        m_cooldown = 0;
        //m_zombieInfo = "";
    }
};

class S2C_PVP_EditInfos: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_EditInfos, INetworkData, RtClass);
    
    std::string m_info;
    std::string m_infoMD5;
    
    S2C_PVP_EditInfos()
    {
        m_info    = "";
        m_infoMD5 = "";
    }
};

struct S2C_Arena_Ending_Data
{
    int32 m_coolDown = 0;
    int32 m_remains = 0;
    int32 m_cup = 0;
    int32 m_arenaCurrency = 0;
    int32 m_leagueCurrency = 0;
    int32 m_leagueCup = 0;
    int32 m_leagueMetal = 0;
    int32 m_leagueId = 0;
    int32 m_medal = 0;
    
    int32 m_changedPVPCoin = 0;
    int32 m_changedPVPCup = 0;
    int32 m_changedPVPMedal = 0;
};

struct S2C_Occupy_Ending_Data
{
    S2C_Occupy_Ending_Data()
    {
        m_arenaCurrency = 0;
        m_cup = 0;        
    }
    
    int32 m_arenaCurrency;
    int32 m_cup;
    
    int32 m_changedPVPCoin = 0;
    int32 m_changedPVPCup = 0;
    int32 m_changedPVPMedal = 0;
};

class S2C_PVP_Ending : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP_Ending, INetworkData, RtClass);
    S2C_PVP_Ending()
    : m_iRoomStatus(0)
    {
        m_diamond = 0;
        m_bGemChange = false;
        m_mapInfo.occupyId = -1;
        m_iEvilDavidStatus = -1;
    }
    S2C_Arena_Ending_Data m_arenaEnding;
    S2C_Occupy_Ending_Data m_occupyEnding;
    S2C_PVP_BigMapInfo m_mapInfo;
    int m_iRoomStatus;
    int m_diamond;
    bool m_bGemChange;
    int m_iEvilDavidStatus;
};

class S2C_Playback_HistoryList : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_Playback_HistoryList, INetworkData, RtClass);
    std::vector<PlaybackBrief> m_historyList;
};

class S2C_PlaybackData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PlaybackData, INetworkData, RtClass);

    uint64    m_battleID;
    std::string m_info;
    std::string m_infoMD5;
};

class S2C_BuyPvpCoinData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BuyPvpCoinData, INetworkData, RtClass);
    S2C_BuyPvpCoinData();
    int32    m_diamond;
    int32    m_pvpCoin;
};

class AutoBuffer
{
public:
    AutoBuffer(unsigned long size);
    ~AutoBuffer();
    
    unsigned char*  GetData() { return m_pBuffer; }
    unsigned long   GetSize() const { return m_size; }
    
private:
    AutoBuffer() {}
    AutoBuffer(const AutoBuffer& r) {}
    void operator=(const AutoBuffer& r) {}
    
protected:
    unsigned char*  m_pBuffer;
    unsigned long   m_size;
};

class S2C_AchieveInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_AchieveInfo, INetworkData, RtClass);
    
    int m_achieveID;
    int m_targetCount;
};

class S2C_CompensationNoticeInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_CompensationNoticeInfo, INetworkData, RtClass);
    
    int m_type;
    int m_resourceNum;
    int m_coinNum;
    int m_medalNum;
};

struct S2C_AchieveConfigInfo
{
public:
    int m_activatedDate;
    std::vector<int> m_achieveList;
};

class S2C_DailyAchievementConfig : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DailyAchievementConfig, INetworkData, RtClass);
    
    int     m_activityStart;
    int     m_activityEnd;
    std::vector<S2C_AchieveInfo>        m_infoList;
    std::vector<S2C_AchieveConfigInfo>  m_configList;
};


struct PVPCUPData
{
    int32   m_iObjId;
    int32   m_iQuantity;
    int32   m_iPrice;
    int32   m_iState;
};

class S2C_PvpShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PvpShopData, INetworkData, RtClass);
    
    int32                           m_refreshCost;
    std::vector<PVPCUPData>         m_shopDataList;
    int32                           m_leftPvpCoin;
    int32                           m_leftPvpMetal;
};

struct PvpShopBuyItem
{
    int32 m_iObjectId;
    int32 m_iCount;
};

class S2C_BuyPvpShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BuyPvpShopData, INetworkData, RtClass);
    
    std::vector<PvpShopBuyItem>         m_buyList;
    int32                           m_leftPvpCoin;
    int32                           m_leftPvpMetal;
};

class S2C_SubPvpCoinData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SubPvpCoinData, INetworkData, RtClass);
    
    int32                           m_leftPvpCoin;
    int32                           m_leftPvpMetal;
};

//----------------- PVP Lab -------------------------
struct S2C_PVPLab_ZombieInfo
{
public:
    int     m_serverID;
    int     m_level;
    bool    m_canUpgrade;
    int     m_awakenLevel;
    bool    m_canAwaken;
};

struct S2C_PVPLab_SkillInfo
{
public:
    int     m_serverID;
    int     m_level;
    bool    m_canUpgrade;
};

struct S2C_PVPLab_PlantInfo
{
public:
    int     m_serverID;
    int     m_level;
};

class S2C_PVPLabData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVPLabData, INetworkData, RtClass);
    S2C_PVPLabData()
    : m_baseLevel(0), m_sunLevel(0), m_armyLevel(0)
    , m_upgradeID(0), m_itemID(0), m_remainTime(0)
    {
    }
    
    int     m_baseLevel;
    int     m_sunLevel;
    int     m_armyLevel;
    std::vector<S2C_PVPLab_ZombieInfo>  m_zombieList;
    std::vector<S2C_PVPLab_PlantInfo>   m_plantList;
    std::vector<S2C_PVPLab_SkillInfo>   m_skillList;
    int     m_upgradeID;
    int     m_itemID;
    int     m_remainTime;
    int     m_coin = 0;
    int     m_medal = 0;
};

class S2C_PVPBeinUpgradeData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVPBeinUpgradeData, INetworkData, RtClass);
    S2C_PVPBeinUpgradeData();
    int32    m_medal;
    int32    m_coin;
};

class S2C_PVPCompleteUpgradeData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVPCompleteUpgradeData, INetworkData, RtClass);
    S2C_PVPCompleteUpgradeData();
    int32    m_id;
    int32    m_level;
    int32    m_id2;
    int32    m_gem;
};

class S2C_PVP128Data: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PVP128Data, INetworkData, RtClass);
    S2C_PVP128Data();
    int32    m_gem;
};

struct VacationMaterialItem : public INetworkData
{
public:
    RT_CLASS_DEFINE(VacationMaterialItem, INetworkData, RtClass);
    VacationMaterialItem(int id = 0, int count = 0);
    int m_id;
    int m_count;
};

class S2C_VacationLevelEndData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_VacationLevelEndData, INetworkData, RtClass);
    S2C_VacationLevelEndData();
    VacationMaterialItem m_drop;
    std::vector<VacationMaterialItem> m_total;
};

class S2C_SummeryLotteryData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SummeryLotteryData, INetworkData, RtClass);
    S2C_SummeryLotteryData();
    VacationMaterialItem normalBonus;
    VacationMaterialItem specialBonus;
    std::vector<VacationMaterialItem> m_material;
    int m_luck;
    int m_totalLuck;
};

class S2C_SummeryLotteryData2018: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_SummeryLotteryData2018, INetworkData, RtClass);
    S2C_SummeryLotteryData2018();
    std::vector<VacationMaterialItem> normalBonus;
    std::vector<VacationMaterialItem> specialBonus;
    int m_luck;
    int m_totalLuck;
    int m_gems;
};

class S2C_BossChallengeLevelEndData: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BossChallengeLevelEndData, INetworkData, RtClass);
    S2C_BossChallengeLevelEndData();
    int m_score = 0;
    int m_medal = 0;
    int m_medalID  = 0;
    int m_medalAdd = 0;
};

class S2C_ICloud_IDCount : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_IDCount, INetworkData, RtClass);
    int m_id = 0;
    int m_count = 0;
    static bool Find (const std::vector<S2C_ICloud_IDCount>& src, int id, int count);
};

class S2C_ICloud_GetConsumeGemInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_GetConsumeGemInfo, INetworkData, RtClass);
    
    S2C_PlayerInfo      m_playerInfo;
    int                 m_needRefreshList;
    int                 m_actid;
    S2C_ICloud_IDCount  m_item;
    int					m_times;
    S2C_ICloud_GetConsumeGemInfo()
    {
        m_needRefreshList = 0;
        m_actid = 0;
    }
};

class S2C_ICloud_DoGacha : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_DoGacha, INetworkData, RtClass);
    
    std::vector<S2C_BonusInfo>  bonusList;
    S2C_GachaInfo               gachaInfo;
    S2C_PlayerInfo              playerInfo;
    int                         returnGems = 0;
    int                         times;
    
    S2C_ICloud_DoGacha()
    {
    }
};

class S2C_ICloud_DoSecretGacha : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_DoSecretGacha, INetworkData, RtClass);

    std::vector<S2C_BonusInfo>  bonusList;
    S2C_PlayerInfo              playerInfo;
    S2C_NewGachaKeyInfo			materialInfo;

    S2C_ICloud_DoSecretGacha()
    {
    }
};

class S2C_ICloud_DoNewGacha : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_DoNewGacha, INetworkData, RtClass);
    
    std::vector<S2C_BonusInfo>  bonusList;
    S2C_NewGachaInfo               gachaInfo;
    S2C_NewGachaKeyInfo         keyInfo;
    S2C_PlayerInfo              playerInfo;
    int                         coins;
    int							cost;
    int                         ad_times;
    
    S2C_ICloud_DoNewGacha()
    {
    	cost = 0;
        coins = 0;
        ad_times = 0;
    }
};

//=========================================================
//  Purchase Orders
//=========================================================

class S2C_Purchase_InitResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_Purchase_InitResult, INetworkData, RtClass);
    
    S2C_Purchase_InitResult()
    {
        orderId         = "";
        skuId = "";
    }
    
    std::string        orderId;
    std::string        skuId;
};

class S2C_Purchase_ValidateResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_Purchase_ValidateResult, INetworkData, RtClass);
    
    S2C_Purchase_ValidateResult()
    {
        orderId         = "";
        skuId = "";
        status = -1;
        objectId = 0;
    }
    
    std::string        orderId;
    std::string        skuId;
    int32			   status;
    int32              objectId;
};

struct PaymentBundleInfo
{
	PaymentBundleInfo()
	{
		objectId = 0;
		quantity = 0;
	}

	int objectId;
	int quantity;
};

class S2C_Payment_ValidateResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_Payment_ValidateResult, INetworkData, RtClass);

    S2C_Payment_ValidateResult()
    {
        skuId = "";
        status = -1;
        orderId = "";
    }

    std::string        skuId;
    int32			   status;
    std::string        orderId;
    std::vector<PaymentBundleInfo> bundleInfos;
};

struct PurchaseOrderInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(PurchaseOrderInfo, INetworkData, RtClass);
    PurchaseOrderInfo()
    {
        orderId = "";
        skuId = "";
        channelId = "";
    }
    std::string orderId;
    std::string skuId;
    std::string channelId;
};

class S2C_Purchase_LostPurchaseOrder: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_Purchase_LostPurchaseOrder, INetworkData, RtClass);
    
    std::vector<PurchaseOrderInfo> m_infos;
};

struct NetworkPaymentInfo
{
	NetworkPaymentInfo()
	{
		orderId = "";
		skuId = "";
	}

	std::string orderId;
	std::string skuId;
	std::vector<PaymentBundleInfo> bundleInfos;
};

class S2C_Payment_LostPurchaseOrder: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_Payment_LostPurchaseOrder, INetworkData, RtClass);

    std::vector<NetworkPaymentInfo> m_payments;
};

class S2C_Payment_SyncPaymentResult : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_Payment_SyncPaymentResult, INetworkData, RtClass);

public:
	std::string orderId;
	std::string skuId;
	int32 objectId;
	int32 activeTotalCharge;
	std::vector<S2C_BonusInfo> bonusList;
};

class S2C_BossChallengteRank : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BossChallengteRank, INetworkData, RtClass);
    int profileID = 0;
    int rank = 0;
    int percent = 0;
    int head = 0;
    int score = 0;
};

class S2C_BossChallengteReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BossChallengteReward, INetworkData, RtClass);
    S2C_BossChallengteRank m_rankInfo;
    S2C_PlayerInfo m_playerInfo;
    int m_coin = 0;
    int m_head = 0;
    int m_detaGem = 0;
};

struct S2C_DailySignWithTW_RewardInfo
{
public:
    int     m_rewardType;
    int     m_count;
};

class S2C_DailySignWithTW : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DailySignWithTW, INetworkData, RtClass);
    int m_day = 0;
    std::vector<S2C_DailySignWithTW_RewardInfo> m_infos;
};

struct S2C_CodeRewardPlantNum
{
public:
    int32     m_plantID = 0;
    int32     m_num = 0;
};

class S2C_CodeRewardResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_CodeRewardResult, INetworkData, RtClass);
    
    int32 m_codeRet = 0;
    std::string m_errMsg = "";
    std::vector<S2C_CodeRewardPlantNum>     m_plantNumList;
    S2C_PlayerInfo m_playInfo;
    std::string m_codeInfo = "";
};

struct S2C_WechatReward
{
	S2C_WechatReward()
	{
		ObjectId = 0;
		Quantity = 0;
	}
	int ObjectId;
	int Quantity;
};

class S2C_WechatShareResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_WechatShareResult, INetworkData, RtClass);

    S2C_PlayerInfo m_playInfo;
    std::vector<S2C_WechatReward> m_rewardList;
    int m_gold;
};

class S2C_MiniGameResult : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_MiniGameResult, INetworkData, RtClass);
	std::vector<S2C_WechatReward> m_vecMiniReward;
};

class S2C_LanternRiddlesResult : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_LanternRiddlesResult, INetworkData, RtClass);
	int m_finishDays;
	std::vector<S2C_WechatReward> m_rewardList;
	int m_specialRewardList;
};

class S2C_YuanBaoRewardResult : public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_YuanBaoRewardResult, INetworkData, RtClass);
	std::vector<S2C_WechatReward> m_rewardList;
};

class CDFReceiveReward : public INetworkData
{
public:
	RT_CLASS_DEFINE(CDFReceiveReward, RtObject, RtClass);
	CDFReceiveReward() : m_nErrorCode(0) {}

public:
	std::vector<S2C_WechatReward> m_vecAwardList;
	int m_nErrorCode;
};

class S2C_ICloud_DailySignInfo: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ICloud_DailySignInfo, INetworkData, RtClass);
    
    S2C_DailySign m_dailySign;
    std::vector<S2C_DailySignContent> m_dailySignSheet;
    std::vector<NDLoginRewardBonus> m_chestReward;
    std::vector<int> m_supplementarySignGemCostList;
    int m_needRefreshList;
    int m_hasGotBonusToday;
    int m_isActived;
    int m_adTimes;
};

//----------------- new danger room datas -------------------------
class S2C_DangerRoomPlantNum : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomPlantNum, INetworkData, RtClass);
    S2C_DangerRoomPlantNum() {}
    S2C_DangerRoomPlantNum(int i_id, int i_num)
        : m_plantID(i_id), m_num(i_num) {}
public:
    int     m_plantID = 0;
    int     m_num = 0;
};

class S2C_DangerRoomPlantNumArray : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomPlantNumArray, INetworkData, RtClass);
    void ToJason(std::string& js);
    bool PlantExist(int plantID);
    std::vector<S2C_DangerRoomPlantNum> m_plantNumList;
};

struct CthulhuDangerroomInfo
{
	std::string TypeName;
	int Energy;
	pvztime_t TriggerTimeSum;

	CthulhuDangerroomInfo() {
		TypeName = "";
		Energy = 0;// cthulhu current energy
		TriggerTimeSum = 0.0f;// cthulhu open time sum.
	}
};

class S2C_DangerRoomRecord : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomRecord, INetworkData, RtClass);
    bool Compress();
    bool Decompress();
    int     m_level = 0;
    int     m_maxLevel = 0;
    int     m_maxLastWeekLevel = 0;
    std::vector<int32>  m_mowers;
    int     m_plantfood = 0;
    int     m_plantfoodBuyCount = 0;
    std::string                              m_plantNumStr;
    std::string m_plantNumMD5;
    std::vector<S2C_DangerRoomPlantNum>     m_plantNumList;
    int     m_sunNum = 0;
    int     m_dayScore = 0;
    int     m_cukeNum = 0;
    int     m_cukeUsedNum = 0;
    int     m_medal = -1;
    int     m_jumpCost = 0;
    int     m_jumpLevel = 0;
    int     m_rankPredict = 0;
    int     m_scorePredict = 0;
    std::string m_artifactOrderId = "";
    int 	m_artifactLeftTimes = 0;
    int		m_artifactMaxTimes = 0;
    std::vector<CthulhuDangerroomInfo> m_cthulhuInfoList;
};

class S2C_DangerRoomSkipLevel : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomSkipLevel, INetworkData, RtClass);
    S2C_PlayerInfo m_playerInfo;
    S2C_DangerRoomRecord m_record;
    int m_sunAdd = 0;
};

class S2C_DangerRoomEndLevel : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomEndLevel, INetworkData, RtClass);
    int m_score = 0;
    int m_rewardMedal = 0;
    int m_sunAdd = 0;
    int m_isCheatingCheckWarningLevel = 0;// cheating check warning level
    S2C_DangerRoomRecord m_record;
    std::vector<S2C_DangerRoomPlantNum>     m_plantsAdd;
};

class S2C_DangerRoomBoostSync : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomBoostSync, INetworkData, RtClass);
    
    S2C_DangerRoomRecord m_record;
    S2C_PlayerInfo m_playerInfo;
};

class S2C_ZombieLevelStat : public INetworkData
{
    RT_CLASS_DEFINE(S2C_ZombieLevelStat, INetworkData, RtClass);
    float AttackLevel = 0.0f;
    float HitPointsLevel = 0.0f;
};

class S2C_DangerRoomPropertySheet : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomPropertySheet, INetworkData, RtClass);
    int                             MinWaveCount = 6;
    int                             MaxWaveCount = 15;
    int                             WaveAddEach  = 1;
    int                             WaveAddInterval = 5;
    
    int                             MinFlagWaveCount = 1;
    int                             MaxFlagWaveCount = 3;
    int                             MinLevelFlagWaveAdd = 10;
    float                           ZombieLevelBase = 0.9f;
    float                           ZombieLevelAdd = 0.1f;
    int                             ZombieTypeCount = 4;
    int                             BigZombieSureExistLevel = 50;
    int                             LeaderMinWaveCost = 100;
    float                           LeaderProbability = 0.4f;
    float                           LeaderStrengthenRate = 2.0f;
    float                           WealthGodProbability = 0.4f;
    int                             SunLimit   = 10000;
    int                             SunAddBase = 100;
    int                             SunAddEachLevel = 10;
    int                             SunAddBossBase  = 300;
    int                             SunAddBossEach  = 300;
    int                             BossInterval = 5;
    float                           BossHpBaseFactor = 0.2f;
    float                           BossHpAddFactor = 1.0f;
    int                             StartingPoints = 100;
    int                          	BasePointIncrementPerWave = 30;
    int                          	BasePointIncrementPerLevel = 5;
    std::vector<S2C_ZombieLevelStat>    ZombieLevelStats;
    std::vector<int32>              PlantPacketStart;
    std::vector<int32>              PlantPacketLimit;
    std::vector<int32>              PlantPacketAddEachLevel;
    int								MaxSelectedPlant;
    
};

class S2C_StaticConfig : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_StaticConfig, INetworkData, RtClass);
    S2C_DangerRoomPropertySheet m_dangerRoomInfo;
};

struct TinyCheatPlantInfo
{
    int32 plantId;
    int level;
    TinyCheatPlantInfo()
    {
        plantId = 0;
        level = 1;
    }
};

class S2C_DangerRoomCheatingInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomCheatingInfo, INetworkData, RtClass);
    std::vector<TinyCheatPlantInfo> m_plantList;
};

class S2C_DangerRoomConsumeData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomConsumeData, INetworkData, RtClass);
    int m_gem = 0;
    int m_cuke = 0;
    int m_plantfood = 0;
    std::vector<S2C_DangerRoomPlantNum> m_plantUsed;
};

class S2C_DangerRoomConsumeData2 : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DangerRoomConsumeData2, INetworkData, RtClass);
    int m_resetGem = 0;
};
//-----------------  -------------------------

// pvz2 cheating check networkdata
struct S2C_PlayerInfoCheatingCheckItemData
{
    int PlantID;// plant id
    int PlantLevel;// plant level
    // int IsAvatar;// plant has avatar

    S2C_PlayerInfoCheatingCheckItemData() {
        PlantID = 0;
        PlantLevel = 0;
        // IsAvatar =0;
    }
};

class S2C_PlayerInfoCheatingCheckData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PlayerInfoCheatingCheckData, INetworkData, RtClass);
    
    std::vector<S2C_PlayerInfoCheatingCheckItemData> PlantList;

    // odl data
    // int PlantSum;// all plant num
    // std::vector<S2C_BonusInfo> PlantLevelList;// all plant level list
    // std::vector<S2C_BonusInfo> PlantChipList;// all plant chip list
    // int AvatarSum;// all avatar num
    // std::vector<S2C_BonusInfo> AvatarChipList;// all avatar chip list
};

#ifdef HOST_ANDROID
#include "ACNetworkData.h"
class S2C_ProfileSync: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ProfileSync, INetworkData, RtClass);

    std::string strMissLogs;
    std::vector<S2C_ACLog> missLogs;
};
#endif

class S2C_SoccerGameEnd: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_SoccerGameEnd, INetworkData, RtClass);
    S2C_SoccerGameEnd() : m_nTeamId(0) {}

	std::vector<S2C_WechatReward> m_rewardList;
    int m_nTeamId;
};


struct ZMatchShopData
{
    int32   m_iObjId;
    int32   m_iQuantity;
    int32   m_iPrice;
    int32   m_iState;
    bool    m_bIsUnLock;
    int     m_nLockIndex;

    ZMatchShopData() : m_iObjId(0),
    m_iQuantity(0),
    m_iPrice(0),
    m_iState(0),
    m_bIsUnLock(false),
    m_nLockIndex(1)
    {

    }
};

class ZMatch_ShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(ZMatch_ShopData, INetworkData, RtClass);
    
    std::vector<int>                           m_vecRefreshCost;
    std::vector<ZMatchShopData>     m_shopDataList;
    int32                           m_leftZMatchCoin;
    int                             m_alreadyRefrashTimes;
    int								m_adTimes;
};

struct ZMatchShopBuyItem
{
    int32 m_iObjectId;
    int32 m_iCount;
};

class S2C_BuyZMatchShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BuyZMatchShopData, INetworkData, RtClass);
    
    ZMatchShopBuyItem         m_buyList;
    int32                           m_leftZMatchCoin;
};

// platform gift data 

struct GiftItem {
    int _id;// item id
    int _count;// item count
};

class S2C_PlatformGiftData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_PlatformGiftData, INetworkData, RtClass);

    std::vector<GiftItem>  _giftList;// gift list
};

class S2C_LimitLotteryReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_LimitLotteryReward, INetworkData, RtClass);

    std::vector<NDLoginRewardBonus>     normalBonus;
    std::vector<NDLoginRewardBonus>     rareBonus;
    std::vector<NDLoginRewardBonus>     cupBonus;
    int                                 crystalAmounts;
};

class S2C_LimitLotteryCrystalBuy : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_LimitLotteryCrystalBuy, INetworkData, RtClass);

    int                                 leftCrystalNum;
};

class S2C_S2C_LimitLotteryCupShop : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_S2C_LimitLotteryCupShop, INetworkData, RtClass);    

    int                                 leftCup;
    int                                 itemId;
    int                                 itemNum;
};

class S2C_RankListEffect: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_RankListEffect, INetworkData, RtClass);

    int                                 rankListType;
    std::vector<int>                    playerIdList;
};

class S2C_ShopItemPurchaseInfo: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_ShopItemPurchaseInfo, INetworkData, RtClass);

	int									shop;
	int									item;
	int									amount;
	int									currency;
	int									price;
};

class S2C_PiggyBankReward: public INetworkData
{
public:
	RT_CLASS_DEFINE(S2C_PiggyBankReward, INetworkData, RtClass);

	int itemId;
	int amount;
	int gems;
};

class S2C_GroupBuyReturnReward: public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_GroupBuyReturnReward, INetworkData, RtClass);

    int gems;
    std::vector<int> itemList;
};

class S2C_ConsumeAndReceiveData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ConsumeAndReceiveData, INetworkData, RtClass);

    int plantid;
    std::vector<int> list; //which can be get
    int number;
};

class S2C_BillingReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_BillingReward, INetworkData, RtClass);

    std::vector<LotteryBonus> billList;
};

struct NetworkItemInfo
{
    int         m_count;
    int         m_objectId;

    NetworkItemInfo(int i_id, int i_count)
    {
        m_count = i_count;
        m_objectId = i_id;
    }

    NetworkItemInfo()
    {
        m_count = 0;
        m_objectId = 0;
    }
};

class New_S2C_ItemAddInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_ItemAddInfo, INetworkData, RtClass);

    std::vector<NetworkItemInfo>   m_itemList;
};

class New_S2C_BuySecretAreaReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_BuySecretAreaReward, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> BonusList;
};

class NetworkCreatePaymentInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkCreatePaymentInfo, INetworkData, RtClass);

public:
    std::string m_orderNumber;
};


#endif /* defined(__PlantsVersusZombies2__INetworkData__) */

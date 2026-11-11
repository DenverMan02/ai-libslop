//
//  PVZVersion.h
//  PlantsVersusZombies2
//
//  Created by David Siems 3/6/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PVZVERSION_H__
#define __PVZVERSION_H__

#include "PropertySheetBase.h"
#include "PVZDB.h"

enum UpdateRewardType
{
	E_UPDATE_COINS_REWARD = 0,
	E_UPDATE_GEMS_REWARD,
	E_UPDATE_KEY_REWARD,
	E_UPDATE_PLANT_REWARD,
	E_UPDATE_AVATAR_REWARD,
	E_UPDATE_PLANT_PIECE_REWARD,
	E_UPDATE_AVATAR_PIECE_REWARD,
	E_UPDATE_ACCESSORY_REWARD,
	E_UPDATE_ACCESSORY_PIECE_REWARD,

	E_UPDATE_REWARD_COUNT,
};

struct UpdateRewardData
{
	UpdateRewardData()
	{
		rewardItem = "";
		rewardType = E_UPDATE_COINS_REWARD;
		rewardAmount = 0;
	}

	std::string rewardItem;
	UpdateRewardType rewardType;
	int rewardAmount;
};

struct RandomRewardData
{
	RandomRewardData()
	{
		weight = 0;
	}

	UpdateRewardData randomData;
	int weight;
};

struct TotalRewardData
{
	std::vector<UpdateRewardData> regularRewardList;
	std::vector<RandomRewardData> randomRewardList;
};

struct FileVersionEntry
{
	FileVersionEntry()
	{
		FileName = "";
        FileMD5  = "";
        
        FileVersion = 0;
        
        TableIndex  = PVZDB::TABLE_INVALID;
	}
    
	std::string FileName;
	std::string FileMD5;
    int         FileVersion;
    
    PVZDB::TableIndex TableIndex;
};

struct VersionUpdateInfo
{
	VersionUpdateInfo()
	{
		VersionCode = 0;
		TitleImage = "";
		NoticeTextContent = "";
		VersionUrl = "";
	}

	int VersionCode;
	std::string TitleImage;
	std::string NoticeTextContent;
	std::string VersionUrl;
};

class PVZVersion : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PVZVersion, PropertySheetBase, RtClass);

	PVZVersion()
	{
		major = -1;
		minor = -1;
		content = -1;
        
        version_app = "";
        new_version_app = "";
        update_url  = "";
        FilesVersion.clear();
        
        rvs_enable = true;
        
        manifest_md5 = "";

        reward_activated = false;
        reward_valid_date = 0;
        reward_text_content = "";
	}

	PVZVersion(int i_major, int i_minor, int i_content)
	{
		major = i_major;
		minor = i_minor;
		content = i_content;
        
        version_app = "";
        new_version_app = "";
        update_url  = "";
        FilesVersion.clear();
        
        rvs_enable = true;
        
        manifest_md5 = "";

        reward_activated = false;
        reward_valid_date = 0;
        reward_text_content = "";
	}

	int major;
	int minor;
	int content;
    
    bool rvs_enable;
    
    std::string version_app;
    std::string new_version_app;
    std::string update_url;
    VersionUpdateInfo version_notice;
    std::vector<FileVersionEntry> FilesVersion;
    
    std::string manifest_md5;

    // First and second reward
    TotalRewardData first_reward;
    TotalRewardData second_reward;
    bool reward_activated;
    int reward_valid_date; // If leaves 0 default is no out-date
    std::string reward_text_content;

	bool IsValid() const { return major != -1 && minor != -1 && content != -1; }

	bool operator==(const PVZVersion &i_rhs) const { return major == i_rhs.major && minor == i_rhs.minor && content == i_rhs.content; }
	bool operator!=(const PVZVersion &i_rhs) const { return !(*this == i_rhs); }
	bool operator<(const PVZVersion &i_rhs) const;

	std::string AsString() const { return StrFormat("%d.%d.%d", major, minor, content); }
	void FromString(const std::string& i_version);

	TotalRewardData& GetUpdateReward(bool i_firstReward);
};

namespace Version
{
	PVZVersion LoadedRSB();
	PVZVersion App();
}

#endif

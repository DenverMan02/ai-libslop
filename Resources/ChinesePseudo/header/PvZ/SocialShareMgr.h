/*
 * SocialShareMgr.h
 *
 *  Created on: 2022-8-1
 *      Author: admin
 */

#ifndef SOCIALSHAREMGR_H_
#define SOCIALSHAREMGR_H_

#include "Singleton.h"
#include "ShareDriverMgr.h"
#include "NetworkData.h"

enum ShareType
{
	ShareType_None,
	ShareType_DIY = 1,
    ShareType_Invitation
};

struct ShareRewardBonusInfo
{
	ShareRewardBonusInfo()
    {
        Id = 0;
        Quantity = 0;
    }
    int Id;
    int Quantity;
};

class ShareRewardData : public INetworkData
{
public:
    RT_CLASS_DEFINE(ShareRewardData, INetworkData, Sexy::RtClass);

public:
    int Id;
    int RewardTimes;
    std::vector<ShareRewardBonusInfo> Rewards;
};

class SocialShareMgr : public LazySingleton <SocialShareMgr>
{
public:
	enum ShareResult
	{
		SHARE_SUCCESS = 0,
		SHARE_FAILED,
		SHARE_CANCELED
	};

	enum SaveResult
	{
		SAVE_SUCCESS = 0,
		SAVE_FAILED
	};

	SocialShareMgr();
    ~SocialShareMgr();

    void SaveScreenImageToLocal(int screenX, int screenY, int screenWidth, int screenHeight);

    void ShareWithImage(SharePlatform i_platform, int screenX, int screenY, int screenWidth, int screenHeight);
    void SaveScreenImageToGallery(int screenX, int screenY, int screenWidth, int screenHeight);

    void ShareCallback(int i_result, const std::string& i_platform);
    void SaveCallback(int i_result);

    void RequestReward();
    void InitDefaultShareInfoMaps();
	int GetShareRewardCount(ShareType i_type);
	void SetShareRewardCount(ShareType i_type, int i_count);
	bool HasShareReward(ShareType i_type);
	void InitShareInfoMaps(const std::vector<S2C_ShareInfo>& i_infos);
	void SetCurrentShareType(ShareType i_type) { m_currentShareType = i_type; }
	bool HasShareCode(const std::string& i_packageName);
    void Update();

private:
    void saveScreenImageToLocal(ScreenInfo i_info);
    void shareResultDialogClose();
    void saveResultDialogClose();
    void gatherScreenInfo(int screenX, int screenY, int screenWidth, int screenHeight);

    ScreenInfo m_currentScreenInfo;

    ShareType m_currentShareType;
    std::map<ShareType, int> m_shareInfoMaps;
    bool m_requestSave;
    bool m_saving;
};

namespace Message
{
    void NotifyShareSaveFinished();
    void NotifyShareRewardFinished();
    void NotifyShareSaveBegin();
}

#endif /* SOCIALSHAREMGR_H_ */

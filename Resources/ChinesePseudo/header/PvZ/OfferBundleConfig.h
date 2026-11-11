/*
 * OfferBundleConfig.h
 *
 *  Created on: 2017-12-15
 *      Author: Administrator
 */

#ifndef OFFERBUNDLECONFIG_H_
#define OFFERBUNDLECONFIG_H_

//for oppo
#ifdef HOST_ANDROID
#include "Precompile.h"
#include "RtObject.h"
struct BundleInfo
{
	BundleInfo()
	{
		sku_id = "";
		gem_amount = 0;
		display_img = "";
	}
	std::string sku_id;
	int gem_amount;
	std::string display_img;
};

struct rewardItem
{
	int id;
	int count;
};

struct OppoNewerDailyReward
{
	std::vector<rewardItem> items;
};

class OfferBundleConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(OfferBundleConfig, Sexy::RtObject, RtClass);

    OfferBundleConfig(){}
    ~OfferBundleConfig(){}

    void Refresh();

    int GetBundleOfferGemAmount(const std::string& i_sku);

    const std::string& GetBundleDisplayImageName(const std::string& i_sku);

    int GetPlantIDByCreatedTime(time_t createdTime);
    int GetRechargeLevel(int recharge);
    const std::vector<OppoNewerDailyReward>& GetDailyReward() const { return m_loginReward; }
    int GetRechargeValue(int levelIndex);
    int GetPlantPiecesRewardCount(int plantRare, int rechargeLevelIndex);
    int GetAvatarPiecesRewardCount();
    bool ShouldGetAvatarPieces(int rechargeLevel);

private:
    std::vector<BundleInfo> m_bundleInfoList;
    const std::string m_invalidDisplayImageName;
    std::vector<OppoNewerDailyReward> m_loginReward;
    std::vector<int> m_rechargeReward;
    std::vector<int> m_rechargeLevel;
    std::vector<int> m_rechargeRewardPlantPiecesBlue;
    std::vector<int> m_rechargeRewardPlantPiecesGreen;
    int m_rechargeRewardAvatarPicecs;
};
#endif


#endif /* OFFERBUNDLECONFIG_H_ */

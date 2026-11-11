#ifndef BILLINGREWARDMGR_H
#define BILLINGREWARDMGR_H

#include "Singleton.h"
#include "NetworkData.h"
#include "MagentoService.h"

class NewRecallBillingRewardManager : public LazySingleton<NewRecallBillingRewardManager>
{
public:
    //for ios v219
    void iosBillingReward(const std::vector<ChildrenDayItem>& i_bonus);

    //for android player handle purchase
    void androidBillingReward(const MagentoProductPropsPtr i_purchasedItem, const std::vector<PaymentBundleInfo>& i_bundleInfos);

    int GetNewRecallBundleIdBySku(const std::string& i_str);

    void SetBundleSku(const std::string& i_sku);
    std::string GetBundleSku();
private:
    void showBundleReward(const std::vector<PaymentBundleInfo>& i_bundleInfos, bool i_addtoProfile = true);
    void showBundleReward(const std::vector<ChildrenDayItem>& i_bundleInfos, bool i_addtoProfile = true);
    std::string currentSku;
private:
    void LogFightZodiac(const std::vector<ChildrenDayItem>& i_bundleInfos);
    void LogFoolData(const std::vector<ChildrenDayItem>& i_bundleInfos, int price);
    void LogCallofWish(const std::vector<ChildrenDayItem>& i_bundleInfos, int price);
    void LogGrowthPackage(const std::vector<ChildrenDayItem>& i_bundleInfos, int price);
    void LogBattleOrderPackage(const std::string& i_sku, int i_price, int i_exp);
    void LogLimitedSummonPackage(const std::vector<ChildrenDayItem>& i_bundleInfos, const std::string& i_sku, int i_price);
    void LogCarnival(const std::vector<ChildrenDayItem>& i_bundleInfos, int i_matChange);
    void LogNewYearGoods(const std::vector<ChildrenDayItem>& i_bundleInfos, int i_price);
    void LogGeneFactor(const std::vector<ChildrenDayItem>& i_bundleInfos);
    void LogLevelPackage(const std::vector<ChildrenDayItem>& i_bundleInfos);
    void LogLevelPackage(const std::vector<PaymentBundleInfo>& i_bundleInfos);
    void LogWishingPool(const std::vector<ChildrenDayItem>& i_bundleInfos, int price);
    void LogGiftFoReturn(const std::vector<ChildrenDayItem>& i_bundleInfos);
    void LogDaveKitchen(const std::vector<ChildrenDayItem>& i_bundleInfos, const std::string& i_sku, int i_price);
    void LogDragonTreasure(const std::vector<ChildrenDayItem>& i_bundleInfos, const std::string& i_sku, int i_price);
};

#define gNewRecallBillingMgr NewRecallBillingRewardManager::GetInstancePtr()

namespace Message
{
    void BuyLionDanceGacha(int index);
    void BuyRenaiEgg(int index);
    void BuyCallofWish(int index);
    void BuyGoldenEgg(int index);
    void BuyArborDayKettle(int index);  
    void BuyIOSCukePacket();
    void BuyGrowthPackage(int index);
    void BuyLimitedSummon(int index);
    void BuyCarnivalPacket(int index);
    void BuyNewYearGoods(int index);
    void BuyGeneFactor(int index);
    void BuyWishingPool(int index);
    void BuyPlantCultivate(int index);
    void BuyGiftFoReturn(int index);
    void BuyDaveKitchen(int index);
    void BuyDragonTreasure(int index);
};

#endif

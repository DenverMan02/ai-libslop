//
//  RechargeBundleConfig.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/12/7.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef RechargeBundleConfig_h
#define RechargeBundleConfig_h

#include "Core.h"
#include "RtObject.h"
#include "Precompile.h"
#include "NetworkData.h"

struct BundlePushCondition
{
    std::string condition = "";
    std::string levelName = "";
    int refreshTime = 0;
    //TODO
};

struct BundleItem
{
    std::vector<int> priceLimit;
    int objectId = 0;
    int timesToBuy = 5;
};

struct BundleDetail
{
    std::vector<S2C_BonusInfo> itemList;
    std::string title = "";
    std::string description = "";
    std::string type = "";
    int objectId = 0;
    int price = 0;
    int discount = 1;
};

struct BundleTypeList
{
    std::vector<BundleItem> bundleList;
    BundlePushCondition pushCondition;
    std::string typeDescription = "";
    int bundleTypeId = 0;
};

//The following part is for UI display.
//Since most configurations are obtained from server, I don't want to build up a json file since there aren't too many of it.
enum RechargeUIType
{
    RechargeUIType_Default,
    RechargeUIType_Fragments,
    RechargeUIType_Plants,
};

struct RechargeUIConfig
{
    std::string type;
    std::string image;
    RechargeUIType UItype;
    
    RechargeUIConfig(const std::string& i_type, const std::string& i_img, const RechargeUIType& i_UItype)
    {
        type = i_type;
        image = i_img;
        UItype = i_UItype;
    }
};

STATIC_VECTOR_INIT(RechargeUIConfig, k_recharge_ui_config,
                   {"gem",      "IMAGE_UI_RECHARGEBUNDLE_BG_GEM",           RechargeUIType_Default},
                   {"family",   "IMAGE_UI_RECHARGEBUNDLE_BG_PLANT_PIECE",   RechargeUIType_Fragments},
                   {"plant",    "IMAGE_UI_RECHARGEBUNDLE_BG_PLANT",         RechargeUIType_Plants},
                   {"grow",     "IMAGE_UI_RECHARGEBUNDLE_BG_GROW_UP",       RechargeUIType_Plants},
                   // todo: modify temporarily, for adding a new type in recharge bundle
                   // it's avoiding change data struct
                   {"grow1",     "IMAGE_UI_RECHARGEBUNDLE_BG_GROW_UP1",       RechargeUIType_Plants},
                   {"grow2",     "IMAGE_UI_RECHARGEBUNDLE_BG_GROW_UP2",       RechargeUIType_Plants},
                   {"grow3",     "IMAGE_UI_RECHARGEBUNDLE_BG_GROW_UP3",       RechargeUIType_Plants},

                   {"pendant",  "IMAGE_UI_RECHARGEBUNDLE_BG_ACCESSORY",     RechargeUIType_Fragments},
                   {"gold",     "IMAGE_UI_RECHARGEBUNDLE_BG_GOLD",          RechargeUIType_Default},
                   {"general",  "IMAGE_UI_RECHARGEBUNDLE_BG_DEFAULT",       RechargeUIType_Default},
                   {"nutrient", "IMAGE_UI_RECHARGEBUNDLE_BG_NUTRIENT",      RechargeUIType_Fragments}
                   );


enum EventBundleType
{
	E_UNLIMIT_BUNDLE = 54014,
};

class RechargeBundleConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(RechargeBundleConfig, Sexy::RtObject, Sexy::RtClass);
    
public:
    BundleDetail* chooseRandomBundleFromType(int bundleTypeId, bool i_ignoreListCheck, const int& rechargeAmount);
    
    BundleDetail* getBundleDetailById(int objectId);
    BundleItem* getBundleById(int bundleTypeId, int objectId);
    
    int getBundleListBuyTimes(int bundleTypeId, int objectId);
    int getBundleListExpireTime(int bundleTypeId);
    
    std::string getBundlePushConditionStrById(int bundleTypeId);
    
    BundlePushCondition* getBundleListPushCondition(int bundleTypeId);
    
    void makeAvailableBundleList(const BundleTypeList& i_list, std::vector<BundleItem>& i_availableList, bool i_ignoreListCheck, const int& rechargeAmount);
    
    bool IsBundleListAvailable(const BundleTypeList& i_list);
    bool IsBundleAvailable(const BundleItem& i_item, const int& rechargeAmount);
    bool IsBundleListSingleton(int bundleTypeId);
    
    static std::string getBGImageByType(const std::string& type);
    static RechargeUIType getUITypeByType(const std::string& type);
    
    std::vector<BundleDetail> bundleDetail;
    std::vector<BundleTypeList> bundleList;
    int bundleRefreshTime = 3600;
};



#endif /* RechargeBundleConfig_h */

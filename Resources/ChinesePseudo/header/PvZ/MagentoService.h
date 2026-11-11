//
//  MagentoService.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MagentoService__
#define __PlantsVersusZombies2__MagentoService__

#include "NetworkServiceManager.h"
#include "NetworkStatusDecider.h"
#include "PropertySheetBase.h"
#include "IPurchaseDriver.h"
#include "LawnAppEnums.h"
#include "PlantGiftPropertySheet.h"

typedef RtWeakPtr<class MagentoProductProps> MagentoProductPropsPtr;
typedef RtWeakPtr<class MagentoCategoryProps> MagentoCategoryPropsPtr;
typedef RtWeakPtr<class PlantGiftMagentoProps> PlantGiftMagentoPropsPtr;

struct LevelUpPriceData
{
    int iCurrentLevel;
    int iPieceCount;
    int iSpecialPieceCount;
    int iCurrentPrice;
    PurchaseType eType;
    
    LevelUpPriceData()
    {
        iCurrentLevel = 0;
        iPieceCount = 0;
        iSpecialPieceCount = 0;
        iCurrentPrice = 0;
        eType = PURCHASE_GEM;
    }
};

class MagentoCategoryProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(MagentoCategoryProps, PropertySheetBase, RtClass);

	MagentoCategoryProps()
	{
	//PVZ2_CHINESE_START
		DisplayNames.resize(MAGENTOLANGUAGE_Count);
	//PVZ2_CHINESE_END
	}

	std::string GetLocalizedName() const;
	std::string GetInternalName() const;

//PVZ2_CHINESE_START
    std::string Name;
	std::vector<std::string> DisplayNames;
//PVZ2_CHINESE_END
	std::vector<MagentoProductPropsPtr> Defaults;
	std::vector<MagentoCategoryPropsPtr> ChildCategories;
	std::vector<MagentoProductPropsPtr> Products;
    
    
    //raoyj
    static std::string CalAllPriceSign();
    static void        RestAllPriceSign();
    static bool        CheckAllPriceSign();
    static std::string                  MagentoAllPricesSign;//for anti-hack
};

class MagentoProductProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(MagentoProductProps, PropertySheetBase, RtClass);

	MagentoProductProps()
	{
		ObjectCount = 0;
		PriceIndex = 0;
        PoolIdx = 0;
        actid = 0;
        
        AvailableFromGacha = true;
        SpecialWay = false;
        SpecialWayContent = "";

		Names.resize(MAGENTOLANGUAGE_Count);
		Descriptions.resize(MAGENTOLANGUAGE_Count);
		ShortDescriptions.resize(MAGENTOLANGUAGE_Count);
	}

	float GetPriceInUSD(bool doCheckSign = false) const; // always returns USD
    float GetPriceByTypeName(const std::string strTypeName, bool doCheckSign = false) const;
    
	SexyString GetLocalizedPriceString(bool *bRMB=NULL) const;
	std::string GetCombinedSkuTierName() const;
	void SetPriceTier(const std::string& i_tier);
	bool ContainsItem(const std::string& i_objectType, const std::string& i_objectItem);
    
    bool GetCurrentLevelPriceData(int nCurrentLevel, LevelUpPriceData & strData);
    const std::vector<LevelUpPriceData> & GetCurrentLevelPriceDataArray() { return m_strLevelUpPriceDataArray; }
    
	std::string GetLocalizedName() const;
	std::string GetInternalName() const;
	std::string GetLocalizedDescription() const;
	std::string GetLocalizedShortDescription() const;
    PurchaseType GetPurchaseType() const;	//PVZ2_CHINESE_START

	std::string Sku;
    int32       actid;
	std::vector<std::string> Names;
	std::vector<std::string> Descriptions;
	std::vector<std::string> ShortDescriptions;
    std::string Image;

	int PriceIndex;
    int PoolIdx;

	std::string ObjectType;
	std::string ObjectItem;
	std::string ObjectPurchaseType;		//PVZ2_CHINESE_START
	int ObjectCount;

	std::vector<MagentoProductPropsPtr> BundleProps;

	struct TierPrice
	{
		std::string Name;
		float Price;
	};
	std::vector<TierPrice> Prices;
    
    std::vector<LevelUpPriceData> m_strLevelUpPriceDataArray;
    
    bool AvailableFromGacha;
    bool SpecialWay;
    std::string SpecialWayContent;
};

class PlantGiftMagentoProps : public MagentoProductProps
{
public:
	RT_CLASS_DEFINE(PlantGiftMagentoProps, MagentoProductProps, RtClass);

	PlantGiftMagentoProps()
	{
		Level = 0;
	}

	int Level;
	PlantGiftPropertySheetPtr PlantGiftType;
};

namespace Magento
{
    void                   InitMagentoDataSign();//for anti-hack,call this when magento refresh immediately
    bool                   IsMagentoDataSafe();
    MagentoProductPropsPtr GetProductPtr(const std::string& i_productId);
	MagentoCategoryPropsPtr GetStore(const std::string& i_storeName);
	MagentoCategoryPropsPtr GetStoreCategory(const std::string& i_storeName, const std::string& i_categoryName);
	MagentoProductPropsPtr FindStoreProduct(const std::string& i_storeName, const std::string& i_categoryName, const std::string& i_objectType, const std::string& i_objectItem);
    //PVZ2_CHINESE_START
	MagentoProductPropsPtr GetGesturePtr(const std::string& i_productId);
    MagentoProductPropsPtr GetPlantLevelUpPlant(const std::string & sPlantName);
    MagentoCategoryPropsPtr GetPlantLevelUp();
    MagentoCategoryPropsPtr GetPlantPieceProductsData(bool bIsAvatar);
    PlantGiftMagentoPropsPtr FindPlantGiftByLevel(const int i_level);
    MagentoProductPropsPtr GetBundleProductPtrByPrice(float i_price);
    MagentoProductPropsPtr EventGetBundleProductPtrByPrice(float i_price);

    MagentoProductPropsPtr GetProduct(const std::string& i_productName);

    
	//PVZ2_CHINESE_END
}

#endif /* defined(__PlantsVersusZombies2__MagentoService__) */

//
//  StoreGiftData.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-6-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StoreGiftConfig_h
#define PlantsVersusZombies2_StoreGiftConfig_h

#include "RtObject.h"
#include "MagentoService.h"
#include "PVZDB.h"
#include "ProfileMgr.h"

//-----------------------------------------------------------------

struct GiftPlantData
{
    std::string sPlantName;
    std::string sNameContent;
    int         iPieceCount;
    
    GiftPlantData()
    {
        sPlantName = "";
        sNameContent = "";
        iPieceCount = 0;
    }
};

//-----------------------------------------------------------------

struct GiftPlantAvatarData
{
    std::string sAvatarPlantName;
    std::string sNameContent;
    int         iPieceCount;
    
    GiftPlantAvatarData()
    {
        sAvatarPlantName = "";
        sNameContent = "";
        iPieceCount = false;
    }
};

//-----------------------------------------------------------------

struct StoreGiftDataInfo
{
    MagentoProductPropsPtr PropPtr;
    int iAddCoin;
    std::vector<GiftPlantData> strGiftPlantArray;
    std::vector<GiftPlantAvatarData> strGiftAvatarPlantArray;
    std::vector<std::string> sUnlockAvatarPlantArray;
    std::string sImage;
    
	StoreGiftDataInfo()
    {
        iAddCoin = 0;
        strGiftPlantArray.clear();
        strGiftAvatarPlantArray.clear();
        strGiftAvatarPlantArray.clear();
        sImage = "";
    }
};

//-----------------------------------------------------------------

class StoreGiftConfig : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(StoreGiftConfig, Sexy::RtObject, RtClass);
    
    int  GetGiftCoin(const std::string & sSku);
    bool GetGiftPlantArray(const std::string & sSku, const std::vector<GiftPlantData> *& dataArray);
    bool GetGiftAvatarPlantPieceArray(const std::string & sSku, const std::vector<GiftPlantAvatarData> *& dataArray);
    bool GetGiftUnlockAvatarPlantArray(const std::string & sSku, const std::vector<std::string> *& dataArray);
    
    bool GetGiftImage(const std::string & sSku, std::string & sImage);
    bool ActiveGift(const std::string & sSku);
    
private:
    
	std::vector<StoreGiftDataInfo> m_StoreGiftDataArray;
};

//-----------------------------------------------------------------

#endif

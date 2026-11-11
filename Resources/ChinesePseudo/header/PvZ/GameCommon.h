//
//  GameCommon.h
//  PlantsVersusZombies2
//
//  Created by Ruoqian, Chen on 05/20/2016.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//
//  This file create for collect some common operation.
//  If somebody find some common method not useful, improve it for make us code more easy :)

#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

#include <string>
#include "SexyString.h"
#include "ProfileUtils.h"

struct GAME_ITEM_INFO
{
	int m_nId = 0;
	int m_nTypeSet = 0;
	int m_nPieceRequire = 0;
	std::string m_strTypeName;
	std::string m_strCollectableTypeName;
	std::string m_strImageId;
	SexyString m_xstrName;
};

enum
{
	FIND_ITEM_SET_PLANT = 1 << 0,
	FIND_ITEM_SET_PLANT_CHIP = 1 << 1,
	FIND_ITEM_SET_AVATAR = 1 << 2,
	FIND_ITEM_SET_AVATAR_CHIP = 1 << 3,
	FIND_ITEM_SET_ACCESSORY = 1 << 4,
	FIND_ITEM_SET_ACCESSORY_CHIP = 1 << 5,
	FIND_ITEM_SET_SERVER_GEM = 1 << 6,
	FIND_ITEM_SET_SERVER_COIN = 1 << 7,
    FIND_ITEM_SET_MATERIAL = 1 << 8,
    FIND_ITEM_SET_CUKE = 1 << 9,
    FIND_ITEM_SET_SERVER_FREE_GEM = 1 << 10,
    FIND_ITEM_SET_SERVER_PAID_GEM = 1 << 11,
    FIND_ITEM_SET_NEW_AVATAR = 1 << 12,
	FIND_ITEM_SET_NEW_AVATAR_CHIP = 1 << 13,
	FIND_ITEM_SET_ARTIFACT = 1 << 14,
	FIND_ITEM_SET_HEADSHOT = 1 << 15,
	FIND_ITEM_SET_RANK_AVATAR = 1 << 16,
    FIND_ITEM_SET_COLLECTION = 1 << 17,
	FINE_ITEM_SET_EXPRCT = 1 << 18,
	FIND_ITEM_SET_CARDGAME = 1 << 19,
    FIND_ITEM_SET_GENE = 1 << 20,
    FIND_ITEM_SET_GENEESSENCE = 1 << 21,
    FIND_ITEM_SET_EXP = 1 << 22,
    FIND_ITEM_SET_TRIALCARD = 1 << 23,
	FIND_ITEM_SET_ALL = 0x7FFFFFFF,
};

enum CarrierType
{
	CARRIER_NONE = 0,
	CARRIER_CHINAMOBILE = 0x01,
	CARRIER_UNICOM = 0x02,
	CARRIER_TELECOM = 0x04,
};

int GetPlantUnlockOrLevelUpPieceRequire(std::string strPlant, int nCurLevel = -1);
GAME_ITEM_INFO GetGameItemInfo(int nId, int nFindSet = FIND_ITEM_SET_ALL, int nAid = 0);
GAME_ITEM_INFO GetGameItemInfoByName(const std::string& name, int nFindSet, int nAid = 0);

int ProfileGetItemAmount(int nTypeId);
GAME_ITEM_INFO ProfileChangeItemAmount(int nTypeId, int nDeltaAmount, bool bLocalGen);

void ShowRewardUI(int nTypeId);

void PurchaseBrokerRequestPayment(const std::string& product_id);

void PurchaseBrokerQueryOrder(const std::string& product_id);

std::string GetTargetPlatform(void);

bool IsCarrier(CarrierType carrier);

std::string GetScreenType();

template<typename T>
void SerializeDataPoint(const std::string& name,T** obj,const RtSerializeContext& inContext)
{
    if (*obj == nullptr && inContext.GetSync()->IsWriting())
    {
        return;
    }
    
    if(inContext.GetSync()->SyncBeginObject(name))
    {
        if (inContext.GetSync()->IsReading())
        {
            std::string className;
            inContext.GetSync()->SyncString("objclass", className);
            (*obj) = RtClass::StaticGetClassNamed(className.c_str())->New()->CastChecked<T>();
        }
        if(inContext.GetSync()->IsWriting())
        {
            std::string className = (*obj)->GetClass()->GetName();
            inContext.GetSync()->SyncString("objclass", className);
        }
        
        (*obj)->Serialize(RtSerializeContext(inContext.GetSync(), "objdata"));
        
        inContext.GetSync()->SyncEndObject();
    }
}

template<typename T>
void SerializeArrayDataPoint(const std::string& name,std::vector<T*>& array,const RtSerializeContext& inContext)
{
    if (inContext.GetSync()->IsReading())
    {
        uint32 size;
        inContext.GetSync()->SyncBeginArray(name, size);
        
        for (int i = 0; i < size; ++i)
        {
            T* obj = nullptr;
            SerializeDataPoint("",&obj,inContext);
            array.push_back(obj);
        }
        inContext.GetSync()->SyncEndArray();
    }
    
    if(inContext.GetSync()->IsWriting())
    {
        auto size = static_cast<uint32>(array.size());
        inContext.GetSync()->SyncBeginArray(name, size);
        for (int i = 0; i < size; ++i)
        {
            SerializeDataPoint("",&array[i],inContext);
        }
        inContext.GetSync()->SyncEndArray();
    }
}

const StructuredData::Value* GetSexyJsonData(const StructuredData& json, const std::string& strTotalPath);

template<typename T>
bool FetchSexyJsonData(const StructuredData& json, const std::string& strTotalPath, T& data)
{
    auto node = GetSexyJsonData(json, strTotalPath);
    if (nullptr == node) {
        return false;
    }
    
    auto typeSrc = node->Type();
    
    // as we don't allow rtti support, no typeid() to use
    std::stringstream ssData;
    switch (typeSrc) {
        case StructuredData::SD_STRING:
            ssData << node->GetString();
            break;
        case StructuredData::SD_NUMBER:
            ssData << node->GetNumber();
            break;
        case StructuredData::SD_INTEGER:
            ssData << node->GetInteger();
            break;
        case StructuredData::SD_BOOLEAN:
            ssData << node->GetBoolean();
            break;
        default:
            return false;
            break;
    }
    
    ssData >> data;
    return true;
}

template<>
inline bool FetchSexyJsonData<std::string> (const StructuredData& json, const std::string& strTotalPath, std::string& data)
{
    auto node = GetSexyJsonData(json, strTotalPath);
    if (nullptr == node) {
        return false;
    }
    
    auto typeSrc = node->Type();
    switch (typeSrc) {
        case StructuredData::SD_STRING:
            {
                auto pszStr = node->GetString();
                data = pszStr ? pszStr : "";
            }
            break;
        default:
            return false;
            break;
    }

    return true;
}

std::string StructuredData2String(const Sexy::StructuredData::Value* root, bool i_addQuote = true);

// lua
void Cpp2Lua(const std::string& strEvent);

template<typename T>
void Cpp2Lua(const std::string& strEvent, T argv1)
{
    std::stringstream ss;;
    ss << strEvent << "##" << argv1;
    Cpp2Lua(ss.str());
}

// maybe move json away from class PlayerInfo later, so put method here instead of PlayerInfo
template<typename T>
bool FetchLuaSharedData(const std::string& strTotalPath, T& data)
{
    auto playerInfo = ProfileMgr::GetInstance().GetCurrentProfile();
    if (nullptr == playerInfo) {
        return false;
    }
    
    auto json = playerInfo->GetLuaShareJson();
    return FetchSexyJsonData(json, strTotalPath, data);
}

template<typename T>
T GetLuaSharedData(const std::string& strTotalPath, T retDefault)
{
    T ret;
    if (FetchLuaSharedData(strTotalPath, ret)) {
        return ret;
    }
    
    return retDefault;
}

void xxtea_encrypt(Buffer& rBuff, const char *pszKey);
void xxtea_decrypt(Buffer& rBuff, const char *pszKey);

#ifdef RELEASEFINAL
#define MY_TAG_TRACE(...)     do {} while (0)
#else
#define MY_TAG_TRACE      MyTagTraceF
#endif

void MyTagTraceF(const char *pszTag, const char *pszFormat, ...);
void MyTagTrace(const char *pszTag, const char *pszInfo);

void PopReport(const char *pszText, const char *pszTitle = nullptr);

int Version2Int(const std::string& strVersion);

SexyString ToTimeString(const char *pszKey, const tm& tmTime);
SexyString ReplaceSexyString(const SexyString& xstrOrg, const SexyString& xstrSrc, const  SexyString& xstrDst);
SexyString AddSexyString(const SexyString& xstr1, const SexyString& xstr2);

SexyString LangTransSexyString(const char* pszKey);
SexyString LangTransSexyString(const std::string& rStr);

std::string GetEncryptIDString(std::string id, int index);


#define LANG_TRANS_SEXY_STRING(x) TodStringTranslate(_S(x))

#ifdef _USE_WIDE_STRING

#define SexyStringToStringSafe(x)	WStringToUTF8String(x)
#define SexyStringToWStringSafe(x)	(x)
#define StringToSexyStringSafe(x)	UTF8StringToWString(x)
#define WStringToSexyStringSafe(x)	(x)

#else

#define SexyStringToStringSafe(x)	(x)
#define SexyStringToWStringSafe(x)	UTF8StringToWString(x)
#define StringToSexyStringSafe(x)	(x)
#define WStringToSexyStringSafe(x)	WStringToUTF8String(x)

#endif

#endif

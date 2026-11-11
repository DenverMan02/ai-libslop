//
//  INetworkData.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-7-24.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IACNetworkData__
#define __PlantsVersusZombies2__IACNetworkData__

#include "RtObject.h"
#include "PlantEnums.h"
#include "LawnKeyField.h"
#include "PVZTypes.h"
#include <string>
#include <vector>

struct ACLOG_PlantStarLevel
{
    int iCurrentPlantId;
    int iCurrentLevel;

    ACLOG_PlantStarLevel()
    {
        iCurrentPlantId = -1;
        iCurrentLevel = 0;
    }
};

struct ACLOG_PlantPieceRecord
{
	ACLOG_PlantPieceRecord()
    {
        PlantId     = -1;
        PieceCount  = 0;
    }

    int PlantId;
    int PieceCount;
};

struct ACLOG_PlantAvatarInfo
{
	ACLOG_PlantAvatarInfo()
	{
		iPlantID = 0;
		eAvatar = E_AVATAR_NONE;
		vecAvatarUnlocked.resize(E_AVATAR_ALL);
	}
	int iPlantID;
	PlantAvatarType eAvatar;
	std::vector<uint8> vecAvatarUnlocked;
};

struct ACLOG_PlantAvatarPiecesInfo
{
	ACLOG_PlantAvatarPiecesInfo()
	{
		iPlantID = 0;
		vecAvatarPiecesCount.resize(E_AVATAR_ALL);
	}
	int iPlantID;
	std::vector<int> vecAvatarPiecesCount;
};

struct ACLOG_AccessoryPiece
{
	ACLOG_AccessoryPiece()
	{
		Type     = "";
		PieceCount  = 0;
	}

	std::string Type;
	int PieceCount;
};

struct ACLOG_MaterialInfo
{
    int32 id;
    LawnKeyField count;

    ACLOG_MaterialInfo()
    {
    	id    = 0;
    	count = 0;
    }
};

class S2C_ACLog : public RtObject
{
public:
    RT_CLASS_DEFINE(S2C_ACLog, RtObject, RtClass);

    S2C_ACLog();
    void SetGems(GemCurrency gems);
    void SetPurchaseMoney(float rmb);
    void SetUnlockPlant(int plantId);
    void SetPlantLevel(int plantId, int level);
    void SetPlantPieces(int plantId, int pieces);
    void SetPlantAvatar(int plantId, PlantAvatarType avatar);
    void SetPlantAvatarPieces(int plantId, PlantAvatarType avatar, int pieces);
    void SetAccessoryPieces(const std::string& type, int pieces);
    void SetMaterial(int i_id, int i_num);
    uint32 GetIndex(){ return m_id; }

    static void ClearLogIndex() { m_logIndex = 0; }
    static void RefreshLogIndex();

private:
    uint32 m_id;
    float m_rmb;
    GemCurrency m_gems;
    std::vector<int> m_unlockedPlants;
    std::vector<ACLOG_PlantStarLevel> m_plantStarLevelArray;
    std::vector<ACLOG_PlantPieceRecord> m_plantPieceRecords;
    std::vector<ACLOG_PlantAvatarInfo> m_listPlantAvatarsAvatarInfo;
    std::vector<ACLOG_PlantAvatarPiecesInfo> m_listPlantAvatarPiecesInfo;
    std::vector<ACLOG_AccessoryPiece> m_accessoryPieces;
    std::vector<ACLOG_MaterialInfo>   m_materialList;

private:
    static uint32 m_logIndex;
};

class ACLogProfile : public RtObject
{
public:
    RT_CLASS_DEFINE(ACLogProfile, RtObject, RtClass);

    std::vector<S2C_ACLog> logList;
};

#endif /* defined(__PlantsVersusZombies2__IACNetworkData__) */

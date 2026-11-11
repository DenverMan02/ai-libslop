/*
 * MonthlyCardMgr.h
 *
 *  Created on: 2020-9-9
 *      Author: Administrator
 */

#ifndef MONTHLYCARDMGR_H_
#define MONTHLYCARDMGR_H_

#include "Singleton.h"
#include "NetworkData.h"

namespace Message
{
	void NotifyColorChanged();
	void NotifyFreeItemGot(const std::string& i_type);
}

enum MonthlyColor
{
	C_Brown,
	C_Red,
	C_Yellow,
	C_Blue,
	C_Green,
	C_Purple,
	C_Count
};

enum MonthlyChangeNameType
{
	N_Free,
	N_MonthlyCard,
	N_Normal
};

enum MonthlyFreeType
{
	Free_MysteryCrystal,
	Free_Fuel,
	Free_PVZ1Mode_TimeEnergy,
};

struct ColorDataVector
{
	ColorDataVector(int i_red, int i_green, int i_blue, int i_alpha)
	: Red(i_red), Green(i_green), Blue(i_blue), Alpha(i_alpha)
	{

	}

	ColorDataVector()
	{
		Red = 0;
		Green = 0;
		Blue = 0;
		Alpha = 0;
	}

	int Red;
	int Green;
	int Blue;
	int Alpha;
};

struct MonthlyCardCommonData
{
	MonthlyCardCommonData()
	: FreeCrystalAmount(0), FreeFuelAmount(0), FreeTimeEnergyAmount(0), FreeChangeNameCount(0), MonthlyChangeNamePrice(0), NormalChangeNamePrice(0)
	{

	}

	MonthlyCardCommonData(int i_freeCrystalAmount, int i_freeFuelAmount, int i_freeChangeNameCount, int i_monthlyChangeNamePrice, int i_normalChangeNamePrice, int i_freeTimeEnergyCount)
	: FreeCrystalAmount(i_freeCrystalAmount), FreeFuelAmount(i_freeFuelAmount), FreeChangeNameCount(i_freeChangeNameCount)
	, MonthlyChangeNamePrice(i_monthlyChangeNamePrice), NormalChangeNamePrice(i_normalChangeNamePrice), FreeTimeEnergyAmount(i_freeTimeEnergyCount)
	{

	}

	int FreeCrystalAmount;
	int FreeFuelAmount;
	int FreeTimeEnergyAmount;
	int FreeChangeNameCount;
	int MonthlyChangeNamePrice;
	int NormalChangeNamePrice;
};

class NetworkUploadColor : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkUploadColor, INetworkData, RtClass);

public:
	int m_id;
};

class MonthlyCardMgr : public LazySingleton <MonthlyCardMgr>
{
public:
	MonthlyCardMgr();
    ~MonthlyCardMgr();

    const ColorDataVector& GetColor(MonthlyColor i_color);
    MonthlyChangeNameType GetChangeNameType();
    int GetMonthlyCardType();
    bool CanGetFreeMysteryCrystal();
    bool CanGetFreeFuel();
    bool CanRefreshFreeStatus(MonthlyFreeType i_type);

    void SetCommonData(const MonthlyCardCommonData& i_data);
    void SetCurrentColor(MonthlyColor i_color) { m_currentColor = i_color; }
    MonthlyColor GetCurrentColor() { return m_currentColor; }
    const ColorDataVector& GetColor();
    void UpdateCurrentColor();
    bool CanChangeColor();

    int GetChangeNameCost();
    int GetFreeChangeNameCount() { return m_commonData.FreeChangeNameCount; }
    void SetFreeChangeNameCount(int i_count) { m_commonData.FreeChangeNameCount = i_count; }

    void SetCommonData(int i_p1, int i_p2, int i_p3, int i_p4, int i_p5, int i_p6);

    // packet ids
    void UploadColor();
    void RequestFreeItems(MonthlyFreeType i_type);

private:
    void OnLuaNotify(const std::string& rStrEvent);

    MonthlyCardCommonData m_commonData;
    MonthlyColor m_currentColor;
};

#endif /* MONTHLYCARDMGR_H_ */

/*
 * PVPShopConfigData.h
 *
 *  Created on: 2015-12-22
 *      Author: Tiger
 */

#ifndef PVPShopConfigData_H_
#define PVPShopConfigData_H_

#include "PVZDB.h"
#include "NetworkData.h"

enum
{
    STATE_NOTBUY = 0,
    STATE_ALREADYBUY,
};

enum
{
    PVPCOIN_COIN = 1,
    PVPCOIN_METAL = 2,
};

struct PvpShopItemData
{
    int32   m_iObjId;
    int32   m_iQuantity;
    int32   m_iPrice;
    int32   m_iProbility;
};

class PVPShopConfigData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(PVPShopConfigData, Sexy::RtObject, Sexy::RtClass);

	PVPShopConfigData();
	virtual ~PVPShopConfigData();
    
    void   initData();
    void   clear();

    void   requestShopShowList(bool isRfresh);
    void   onResponseShopList(const S2C_PvpShopData& pvpData);
    void   setShopShowList(int32 refreshCost, const std::vector<PVPCUPData>& showList);
    bool   getShopShowList(std::vector<PVPCUPData>& showList);
    
    void   requestBuyShopObject(int32 objId);
    void   onResponseBuyResult(const S2C_BuyPvpShopData& pvpData);
    
    void   onResponseSubPvpCoin(int32 leftCoin, int32 leftMetal);
    
    void   addObjToPlayerInfo(int32 objId, int32 count);
    const PvpShopItemData* GetItemData(int32 i_id);

    int32   m_ibaseCount;
    int32   m_irandomCount;
    int32   m_ipadCount;
    
	std::vector<PvpShopItemData> m_baseList;
    std::vector<PvpShopItemData> m_randomList;
    std::vector<PvpShopItemData> m_padList;
    
    int32                   m_refreshTime;
    std::vector<int32>      m_refreshCostList;
    
    int32                   m_currentRefreshCount;
    int32                   m_currentRefreshCost;
    std::vector<PVPCUPData> m_currentShowList;
    
    bool                    m_isRefreshList;
    bool                    m_IsBuyObj;
    int32                   m_buyObjId;
    bool                    m_bRefreshPVP = false;
    
private:
    void    checkReset();
    void    randomShowList(std::vector<PVPCUPData>& showList, std::vector<int32>& sellList);
    PVPCUPData getPVPCUPDataById(int32 objId);
};

//---------------------------------------------------------
namespace Message
{
    void PvpShopRefreshed();
    void PvpShopBuyFinish(int32 objId);
}


#endif /* PVPShopConfigData_H_ */

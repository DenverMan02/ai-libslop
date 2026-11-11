/*
 * DangerRoomSpecialOfferConfig.h
 *
 *  Created on: 2020-1-4
 *      Author: zhousen
 */

#ifndef DANGERROOMSPECIALOFFSERCONFIG_H_
#define DANGERROOMSPECIALOFFSERCONFIG_H_

#include "RtObject.h"
#include "RtSerial.h"
#include "RtDb.h"
#include "DRef.h"
#include "PVZDB.h"
#include "Singleton.h"
#include "PlayerInfo.h"
#include "NetworkData.h"

class DangerRoomSpecialOfferBonus : public RtObject
{
public:
    RT_CLASS_DEFINE(DangerRoomSpecialOfferBonus, RtObject, RtClass);
    DangerRoomSpecialOfferBonus();

    std::vector<LotteryBonus> _plantList;// plant list, i = plantid, q = level
    std::vector<LotteryBonus> _otherBonusList;// other bonus list, i = item id, q = count
};

class DangerRoomSpecialOfferConfig : public RtObject
{
public:
	RT_CLASS_DEFINE(DangerRoomSpecialOfferConfig, RtObject, RtClass);
    DangerRoomSpecialOfferConfig();

    int GetOrgPrice() { return _orgPrice; }
    int GetGiftID() { return _giftID; }
    std::vector<LotteryBonus>& GetPlantList() { return _bonus._plantList; }
    std::vector<LotteryBonus>& GetOtherBonusList() { return _bonus._otherBonusList; }
    bool IsInLevelLimit(int level);// check if level is in the limit level
    LotteryBonus GetPlant();
    LotteryBonus GetBonus();

protected:
    int _giftID;// gift bag id
    std::vector<int> _levelLimitList;// item0 : min level, item1 : max level
    DangerRoomSpecialOfferBonus _bonus;// bonus
    int _orgPrice;
};

///////////////////////////////////////////////////////////////////////
/// global func
///////////////////////////////////////////////////////////////////////

// through rules to filer the suitable config
DangerRoomSpecialOfferConfig FilterDangerRoomSpecialOfferConfig(PlayerInfo* player, std::vector<DangerRoomSpecialOfferConfig> list);

// through rules to filter plant
bool FilterDangerRoomSpecialOfferPlant(PlayerInfo* player, DangerRoomSpecialOfferConfig config, int& giftID, int& plant);

// check icon enable
bool CheckShowDangerRoomSpecialOfferIcon(PlayerInfo* player);

// check ui pop up enable
bool CheckShowDangerRoomSpecialOfferUI(PlayerInfo* player);

// TODO: after buy gift, set data._hasBought true.


#endif /* DANGERROOMSPECIALOFFSERCONFIG_H_ */

/*
 * GameInfoUtil.h
 *
 *  Created on: 2019-4-8
 *      Author: zhousen
 */

#ifndef GAMEINFOUTIL_H_
#define GAMEINFOUTIL_H_

enum {
    COINS_ID = 4013,// coins id
    GEMS_ID = 3008,// gems id
};

struct GameItemInfo {
    SexyString _name;// item name
    int _type;// item type, use FIND_ITEM_SET_XXX
    int _rare;// rare
    Image* _img;// img ptr, if no img will be nullptr
    UIRewardFrame::RewardType _rewardType;// for ui reward frame

    GameItemInfo(){
        _name = _S("");
        _type = FIND_ITEM_SET_PLANT;
        _rare = 0;
        _img = nullptr;
        _rewardType = UIRewardFrame::Reward_Others;
    }
};

class GameInfoUtil
{
public:
    static bool GetItemInfoById(int id, GameItemInfo& info);
    static SexyString GetDescriptionById(int id);
private:
    static bool GetRareByPlantName(std::string name, int& rare);
    static bool GetRareByAccessaryName(std::string name, int& rare);
};

#endif /* GAMEINFOUTIL_H_ */

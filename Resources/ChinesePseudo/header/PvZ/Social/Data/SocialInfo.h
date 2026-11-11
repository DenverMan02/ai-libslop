//
//  SocialInfo.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-7-22.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SocialInfo__
#define __PlantsVersusZombies2__SocialInfo__

#include "StructuredData.h"
#include "RtObject.h"
#include "NetworkData.h"

const int g_send_gift_interval = 24*3600;

struct FriendInfo
{
    FriendInfo()
    {
        userId  = -1;
        imageId = -1;
        plantId = -1;
        giftLeftTime = -1;
    }
    int32 userId;
    SexyString name;
    int imageId;
    int star;
    int giftLeftTime;
    int plantId;
    std::string  icon_url;
};

struct GameRankInfo
{
    int32 userId;
    int time;
    std::string formation;
};


class SocialInfo : public RtObject
{
public:
    RT_CLASS_DEFINE(SocialInfo, RtObject, RtClass);
    
    SocialInfo();
    virtual ~SocialInfo();

#ifdef HOST_ANDROID
    //void UpdateBorrowedPlantList(S2C_BorrowedPlantList &i_borrowedplants);
    //void UpdateFriendList(S2C_FriendList &i_friends);
    //void UpdateGitList(S2C_GiftList & i_gifts);
    //void UpdateGameRank(S2C_GameRankList &i_gameRankList);
#endif
    std::vector<int32>& GetBorrowedPlantList();
    void AddBorrowedPlantList(int32 userId);
    
    
    std::vector<FriendInfo>& GetFriendList();
    SexyString GetFriendNameById(int32 i_userId);
    void SetFriendLeftTime(int32 i_userId, int i_time);

    std::vector<int32>&		 GetReceivedSunList();

    

    void RemoveUsedFriendSunList(int32 userId);
    

    
    void GetGameRank(std::vector<GameRankInfo> &i_info, int i_star);
    std::vector<int32> getUsedSunList() {return m_usedsunList;}
    void setUsedSunList(const std::vector<int32>& aList) {m_usedsunList = aList;}

    
private:
    std::vector<FriendInfo> m_friendList;
    std::vector<int32>      m_borrowedplantList;
    std::vector<GameRankInfo> m_gameRankList[GAME_RANK_STAR_COUNT];
    std::vector<int32>      m_receivesunList;
    std::vector<int32>		m_usedsunList;
};



#endif /* defined(__PlantsVersusZombies2__SocialInfo__) */

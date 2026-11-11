//
//  DataForIwatch2.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15/11/5.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef __DataForIwatch_h__
#define __DataForIwatch_h__

#include <vector>

struct RewardItemInfo
{
    RewardItemInfo(std::string n, int c) : strName(n), iCount(c) {}
    std::string strName;
    int iCount;
};

class DataForIwatch
{
    
public:
    
    static DataForIwatch GetInstance() { return m_DataForIwatch; }
    
    void SaveLoginInfo();
    
    void SendMessageToWatch();
    
    int GetRewardMoney();
    
    std::vector<RewardItemInfo> GetRewardPlantPiece();
    
    std::vector<RewardItemInfo> GetRewardAvatarPiece();
    
    std::vector<RewardItemInfo> GetRewardAccessoryPiece();
    
    void RemoveWatchDate();
    
    bool IsHaveWatchDate();
    
private:
    
    static DataForIwatch m_DataForIwatch;
};


#endif

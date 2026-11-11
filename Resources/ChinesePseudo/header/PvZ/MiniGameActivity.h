//
//  GachaConfig.h
//  PlantsVersusZombies2
//
//  Created by Rain Chen on 14-05-18.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MiniGameActivity__ 
#define __PlantsVersusZombies2__MiniGameActivity__

#include "PVZDB.h"
#include "ProfileMgr.h"
#include "Color.h"

struct MiniGame
{
    std::string strName;
    int         iProbability;
    std::string strImg;
    ImagePtr    pImg;
    
    MiniGame():iProbability(0)
    {
    }
};

struct MiniGameReward
{
    std::string strSku;
    int         iCount;
    std::string strType;
    
    MiniGameReward():iCount(1)
    {
        
    }
    
};

struct MiniGameRewardList
{
    std::vector<MiniGameReward> vecMiniGameRewards;

    std::string strImg;
    int     iProbability;
    int     iLevel;
    ImagePtr pImg;
    MiniGameRewardList():iProbability(0),iLevel(0)
    {
        
    }
    
};
//-----------------------------------------------

class MiniGameActivity : public Sexy::RtObject
{
public:
    
	RT_CLASS_DEFINE(MiniGameActivity, Sexy::RtObject, Sexy::RtClass);
    
    
    typedef std::vector<MiniGame>             VECMINIGAMES;
    typedef std::vector<MiniGameRewardList>   VECMINIGAMEREWARDPOOL;
    
  
    MiniGame*   ChooseGame();
    MiniGameRewardList* ChooseRewardLst(int iLevel);
private:
    
    VECMINIGAMES            m_vecMiniGames;
    VECMINIGAMEREWARDPOOL   m_vecMiniGameRewardPool;

    struct SMiniGameRwdInfo
    {
        int m_iIdx;
        int m_iWeight;
        bool operator <(const SMiniGameRwdInfo& rwd) const
        {
            return m_iWeight<rwd.m_iWeight;
        }
    };
    
    static const int s_iLvSize = 3;
    
    std::set<SMiniGameRwdInfo>  m_setMiniGameRewordPool[s_iLvSize];
    int     m_iMaxWMiniGameRwd[s_iLvSize];
    
    struct SMiniGameInfo
    {
        int m_iIdx;
        int m_iWeight;
        bool operator <(const SMiniGameInfo& rwd) const
        {
            return m_iWeight<rwd.m_iWeight;
        }
    };
    std::set<SMiniGameInfo> m_setMiniGameInfo;
    int     m_iMaxWMiniGame;
    

    void    Initialize();
};

#endif /* defined(__PlantsVersusZombies2__GachaConfig__) */

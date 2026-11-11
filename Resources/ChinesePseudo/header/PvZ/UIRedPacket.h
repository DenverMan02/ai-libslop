//
//  UIRedPacket.hpp
//  PlantsVersusZombies2
//
//  Created by lzjseed on 2016/11/28.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIRedPacket_h
#define UIRedPacket_h

#include "DNode/DNodeWidget.h"
#include "NetworkMgr.h"
#include "GameStateMgr.h"

namespace Message
{
	void ResultClosed();
	void NotifyTutorialReward();
}

struct S2C_RedPackSth
{
    int32 itemId = 0;
    int32 amount = 0;
};

class S2C_RedPackReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_RedPackReward, INetworkData, RtClass);
    
    int32                         m_bigRedpackCount;
    int32                         m_smallRedpackCount;
    std::vector<int32>            m_coinInfos;
    std::vector<S2C_RedPackSth>   m_prizeInfos;
};

struct New_S2C_RedPackSth
{
    int32 itemId = 0;
    int32 amount = 0;
};

class New_S2C_RedPackReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_RedPackReward, INetworkData, RtClass);

    int32                         m_redpackCount;
    std::vector<New_S2C_RedPackSth>   m_prizeInfos;
};

class OpenRedPackInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(OpenRedPackInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<New_S2C_RedPackSth>     displayInfos;
    int32 m_redpackCount;
};

class UIRedPacket:public DNodeWidget
{
public:
    static bool createWithNetwork();
    
    static UIRedPacket* create(bool focus = true, FestivalEventType i_type = Event_RedPack);
    
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void onMsgErrorRequest(int erroId, const std::string& i_reqID);
    
    static bool isActive(){return s_isActive;}
    void setUnactive();
    
    UIRedPacket();
    virtual ~UIRedPacket();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    void loadWithNetMessage();
    
    void requestOpenRedPacket(int type,int num);
    void requestGetMsg();
    
    //New red packets
    void requestNetwork();
    void requestOpenNewRedPacket(int num);
    void requestOpenDumpling(int num);
    void updateNewNetInfo();

    void updateNetInfo(class S2C_RedPackMsg* msg);
    void updateRedPacketCount();
    void updateDumplingCount();
public:
    static UIRedPacket* s_pWidgetHandler;
    static bool s_isActive;
    static FestivalEventType m_eventType;
    
    int    m_bigRedPacketCount = 0;
    int    m_smallRedPacketCount = 0;
    
    int    m_redpackCount = 0;

private:
    
    bool   m_bShowMsg = false;
};

class UIRedPacketReward:public DNodeWidget
{
public:
    static UIRedPacketReward* create(const New_S2C_RedPackReward& reward,const std::map<int,int>& mergeItemInfo,const std::vector<int>& list,bool isBig,bool focus = true);
    static UIRedPacketReward* create(bool focus = true);
    
    virtual ~UIRedPacketReward();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    void skipAni();
    void nextAni();
public:
    static UIRedPacketReward* s_pWidgetHandler;
    New_S2C_RedPackReward         m_reward;
    std::map<int,int>         m_mergeItemInfo;
    std::vector<int>            m_list;
    bool m_isBig = false;
    int  m_currentIndex = 0;
    bool m_isGold = false;
    bool m_isSkip = false;
};

class UIRedPacketResult:public DNodeWidget
{
public:
    static UIRedPacketResult* create(const std::map<int,int>& reward,const std::vector<int>& list,bool focus = true);
    static UIRedPacketResult* create(const std::vector<int>& countList,const std::vector<int>& list,bool focus = true);
    static UIRedPacketResult* create(bool focus = true);
    
    virtual ~UIRedPacketResult();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    static bool isActive(){return s_isActive;}
    void setUnactive();

    void setTitle(const SexyString& i_string);
    DStringNode* GetTitleNode();

public:
    static UIRedPacketResult* s_pWidgetHandler;
    std::map<int,int>         m_mergeItemInfo;
    std::vector<int>          m_list;
    std::vector<int> 		  m_countList;// according to m_list, each item is the count of m_list.
    static bool s_isActive;
};

#endif /* UIRedPacket_h */

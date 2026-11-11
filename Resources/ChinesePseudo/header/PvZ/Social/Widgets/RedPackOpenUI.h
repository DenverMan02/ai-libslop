//
//  RedPackOpenUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15-1-21.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RedPackOpenUI__
#define __PlantsVersusZombies2__RedPackOpenUI__

#include <stdio.h>
#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "RedPackUI.h"
#include "Effect_PopAnim.h"

struct RedPackContent
{
    std::string m_strName;
    int m_itemId;
    int m_amount;
    RedPackContent()
    {
        m_itemId = 0;
        m_amount = 0;
    }
    
    RedPackContent(std::string& strName, int iAmount)
    : m_strName(strName)
    , m_amount(iAmount) { }
};

struct RedPackAnimStatus
{
    pvztime_t   m_animPlayTime;
    pvztime_t   m_animFlyStartTime;
    bool        m_isOpening;
    bool        m_hasOpened;
    
    RedPackAnimStatus()
    {
        m_animPlayTime = PVZ_EOT();
        m_animFlyStartTime = PVZ_EOT();
        m_isOpening = false;
        m_hasOpened = false;
    }
};

class RedPackOpenUI : public Widget, public Sexy::ButtonListener
{
public:
    RedPackOpenUI(int i_redPackOpenNum);
    virtual ~RedPackOpenUI();
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    virtual void TouchEnded(const Sexy::Touch& i_touch);
#ifdef HOST_ANDROID    
    void SetPrizePool(int iOpenNum);
#else
    void SetPrizePool(const std::vector<std::vector<S2C_RedPackContent> >& i_info);
#endif
    void DrawPrizePool(Graphics *i_g, int i_prizePoolIndex);
    
    //forgive me for this interface cuz this f...ing s..t really drives me mad
    SexyVector2 GetDrawPosById(int i_drawId, int i_prizePoolIndex);
    
private:
    void InitView();
    SexyString getRedPackRewardName(std::string& strCompleteName, const std::string& plantName);
    void SaveOpenRedPackReward();
    SexyString getRedPackRewardName(int i_objectId, const std::string& plantName);
    
    std::vector<std::vector<RedPackContent> >       m_contentList;
    std::vector<class Effect_PopAnim* >             m_redPackAnim;
    std::vector<RedPackAnimStatus>                  m_redPackAnimStatus;
    int                                             m_openNum;
    Sexy::Rect                                            m_intersectRect;
};

#endif /* defined(__PlantsVersusZombies2__RedPackOpenUI__) */

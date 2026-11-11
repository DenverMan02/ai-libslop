//
//  BoxOpenUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/9/18.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BoxOpenUI__
#define __PlantsVersusZombies2__BoxOpenUI__

#include <stdio.h>
#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "Effect_PopAnim.h"

struct BoxContent
{
    std::string m_strName;
    int m_amount;
    BoxContent() : m_amount(0) {}
    
    BoxContent(std::string& strName, int iAmount)
    : m_strName(strName)
    , m_amount(iAmount) { }
};

struct ServerBoxContent
{
    int objectId = 0;
    int amount = 0;
};

struct BoxAnimStatus
{
    pvztime_t   m_animPlayTime;
    pvztime_t   m_animFlyStartTime;
    bool        m_isOpening;
    bool        m_hasOpened;
    
    BoxAnimStatus()
    {
        m_animPlayTime = PVZ_EOT();
        m_animFlyStartTime = PVZ_EOT();
        m_isOpening = false;
        m_hasOpened = false;
    }
};

class BoxOpenUI : public Widget, public Sexy::ButtonListener
{
public:
    BoxOpenUI(const std::string& i_animType = "plant");
    virtual ~BoxOpenUI();
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    virtual void TouchEnded(const Sexy::Touch& i_touch);
    
    void SetContentList(const std::map<std::string, int>& i_prizePool);
    virtual void DrawPrizePool(Graphics *i_g);
    void StartPlayingAnimation();
    
    void SetPlayingAnimTime(pvztime_t i_animTime);
    bool ShouldDrawPrize() { return m_shouldDrawPrize; }
    
    //forgive me for this interface cuz this f...ing s..t really drives me mad
    virtual SexyVector2 GetDrawPosById(int i_drawId);
    
    std::string GetTypeName() { return m_animType; }
    class Effect_PopAnim* GetPopAnim() { return m_BoxAnim; }
    
    void SetAnimName(std::string i_animName);
    virtual void ResetAnimName();
    
    void InitView();
    
protected:
    pvztime_t                     m_animPlayTime;
    pvztime_t                     m_animFlyStartTime;       //prize begin to fly out
    bool                          m_shouldDrawPrize;
    int                           m_prizeNum;
    
private:
    
    SexyString getBoxRewardName(std::string& strCompleteName, const std::string& plantName);
    
    std::vector<BoxContent>       m_contentList;
    
    class Effect_PopAnim*         m_BoxAnim;

    std::string                   m_BoxAnimName;
    std::string                   m_animType;
};

class ServerBoxOpenUI : public BoxOpenUI
{
public:
    ServerBoxOpenUI();
    virtual ~ServerBoxOpenUI();
    
    void Update() override;
    void Draw(Graphics *i_g) override;
    void SetContentList(const std::map<int, int>& i_prizePool);
    virtual void DrawPrizePool(Graphics *i_g) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    void SetTitle(SexyString i_str) { m_titleStr = i_str; }
    
protected:
    Effect_PopAnim* m_plantEffect;
    std::vector<ServerBoxContent> m_prizePool;
private:
    SexyString m_titleStr;
};

class PlantOfferOpenUI : public ServerBoxOpenUI
{
public:
	PlantOfferOpenUI();
	virtual ~PlantOfferOpenUI();
	void Draw(Graphics *i_g) override;
	void DrawPrizePool(Graphics *i_g) override;
	void TouchEnded(const Sexy::Touch& i_touch) override;
	SexyVector2 GetDrawPosById(int i_drawId) override;
};

#endif /* defined(__PlantsVersusZombies2__BoxOpenUI__) */

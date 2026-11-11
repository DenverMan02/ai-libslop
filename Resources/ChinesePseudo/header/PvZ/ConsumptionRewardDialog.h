//
//  ConsumptionRewardDialog.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 15-5-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ConsumptionRewardDialog_h
#define PlantsVersusZombies2_ConsumptionRewardDialog_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "ConsumptionRewardInfo.h"
#include "Effect_PopAnim.h"
#include "PrimeTextWidget.h"

//---------------------------------------------------------------------------------

class ItemButton
: public PVZ2UIButton
{
public:
    
    ItemButton(int i_id
               , Sexy::ButtonListener* i_listener
               , RewardItem& item
               , bool bGeted = false
               , bool bHighLight = false
               , bool bSuper = false);
    ~ItemButton();

    void Draw(Sexy::Graphics* i_g) override;
    
    void DrawReward(Sexy::Graphics* i_g);
#ifdef HOST_ANDROID    
    static SexyString GetRewardName(std::string& strCompleteName, const std::string& plantName);
#else    
    static SexyString GetRewardName(std::string& strCompleteName, const std::string& plantName, bool i_title = false);
#endif
    void SetGeted(bool bGet) { m_bGeted = bGet; m_iStartScaleTime = PVZ_T(); }
    
    void DrawFlag(Sexy::Graphics* i_g);
    
private:
    
    bool m_bGeted;
    
    bool m_bHighLight;
    
    bool m_bSupper;
    
    RewardItem   m_stCurrentRewardItem;
    
    pvztime_t    m_iStartScaleTime;
    
    bool         m_bScaling;
};

class TipsWidget : public Widget
{
    
public:
    
    TipsWidget(Sexy::ButtonListener* pListener, bool bButton = false);
    
    ~TipsWidget();
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void RefreshTips();
    
    void AddDesButton(Sexy::ButtonListener* pListener);
    
    void DesButtonRefresh();
    void SetTipsImg(const std::string &imgID);
private:
    
    bool m_bShowButton;
    
    PVZ2UIButton* m_PVZ2UIButton;
    
    PVZ2UIButton* m_vReDesButton[2];
    
    Sexy::Image * m_pTipsImg;
};

class RewardAnimWidget
: public Widget
, public Sexy::ButtonListener
{
    
public:
    
    RewardAnimWidget(RewardItem& item, pvztime_t iWait);
    
    ~RewardAnimWidget();
    
    void Update() override;
    
    void Draw(Sexy::Graphics* i_g) override;
    
    bool IsValid() { return m_bIsValid; }
    
    void SetValid(bool bValid);
    
    bool IsComplete() { return !m_bScaling; }
    
private:
    
    void AnimUpdate();
    
    void AnimDraw(Sexy::Graphics* i_g);
    
    void CreateAnim();
    
    void DrawReward(Sexy::Graphics* i_g);
    
    bool IsPause();
    
private:
    
    Effect_PopAnim* m_pEffect_PopAnim;
    
    RewardItem      m_stRewardItem;
    
    pvztime_t       m_iStartTime;
    
    pvztime_t       m_iWaitTime;
    
    bool            m_bScaling;
    
    bool            m_bIsValid;
    
    Sexy::PrimeTextWidget* m_pDialogTextWidget;
    
};


class ConsumptionRewardDialog
: public Widget
, public Sexy::ButtonListener
{
public:
    
    ConsumptionRewardDialog();
    ~ConsumptionRewardDialog();
    void Update() override;
    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void OnGotConsumptionReward(bool i_success);
    
private:
    
    void InitView();
    
    void AddItem();
    
    void AddBuyTips();
    
    void AddCloseButton();
    
    void RecvReward(int iIndex);
    
    void DrawTips(Sexy::Graphics* i_g);
    
    bool CanPress();
    
    bool IsAllAnimComplete();
    void onCloseDialog();
    
private:
    
    TopicItem   m_stCurrentTopicItem;
    std::vector<ItemButton*> m_vItemButton;
    TipsWidget* m_pTipsWidget;
    std::vector<RewardAnimWidget*> m_vRewardAnimWidget;
    pvztime_t m_iAnimEndTime;
    int m_iBaseX;
    int m_iBaseY;
    //c03 add for dlc patch
public:
    void SetTopTileImg(const std::string & imgID);
    void SetTipsImg(const std::string &imgID);
    void SetSubTileImg(const std::string &imgID);
private:
    Sexy::Image * m_pTopTileImg;
    Sexy::Image * m_pSubTileImg;
    
    //end of dlc path
};

//---------------------------------------------------------------------------------

#endif

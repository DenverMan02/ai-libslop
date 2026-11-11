//
//  ChristmasGoldenEgg.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/12/4.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef ChristmasGoldenEgg_h
#define ChristmasGoldenEgg_h

#include "Core.h"
#include "Widget.h"
#include "PVZTypes.h"
#include "PlayerInfo.h"
#include "ActiveCenterTab.h"
#include "RealObject.h"

//#include "Precompile.h"
//#include "GameButton.h"
//#include "PropertySheetBase.h"

//#include "PVZ2UIButton.h"
//#include "NetworkData.h"
//#include "NetworkMsgProcess.h"


//#include "Effect_PopAnim.h"
//#include "PlantDisplayBoard.h"

#endif /* ChristmasGoldenEgg_h */

struct EggContent
{
    std::string m_bonusName;
    int m_quantity;
    int m_posId;
    
    EggContent()
    {
        m_bonusName = "";
        m_quantity = 0;
        m_posId = 0;
    }
};

class GoldenEggOpenUI : public Widget, public Sexy::ButtonListener
{
public:
    GoldenEggOpenUI();
    virtual ~GoldenEggOpenUI();
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    virtual void TouchEnded(const Sexy::Touch& i_touch);
    
    void AddBonus(std::string i_bonusName, int i_quantity, int i_posId);
    bool HasBonus();
    void DrawPrizePool(Graphics *i_g);
    
    //forgive me for this interface cuz this f...ing s..t really drives me mad
    SexyVector2 GetDrawPosById(int i_drawId);
    
    void InitView();
    
private:
    SexyString getBoxRewardName(std::string& strCompleteName, const std::string& plantName);
    std::vector<EggContent> m_contentList;
    
    bool        m_started;
    int         m_prizeNum;
    pvztime_t   m_animFlyStartTime;
};

class GoldenEgg : public RealObject
{
public:
    RT_CLASS_DEFINE(GoldenEgg, RealObject, RtClass);
    
    GoldenEgg();
    ~GoldenEgg();
    
    void OnUpdate();
    void OnDraw(Graphics* i_g);
    
    bool Valid();
    void onAnimStopped(const std::string &i_animName);
    void InitGoldenEgg(int i_index, std::string i_popAnim, Rect i_rect);
    void PlayIdleLooped();
    void OpenEgg();
    
    void SetRefresh(bool i_needRefresh);
    void OnEggOpened();
    bool IsEggOpened();
    void PlayEggOpened();
    
private:
    bool m_opened;
    bool m_needRefresh;
    int m_goldenEggIndex;
    CGE_Stat m_eggStat;
    pvztime_t m_LastEggAnimTime;
    pvztime_t m_eggAnimTime;
    
    Rect m_rect;
    class Effect_PopAnim* m_popAnimRig;
    RtWeakPtr<class PopAnimRig> m_animRig;
};

class GoldenEggBackgroundWidget : public Widget
{
public:
    GoldenEggBackgroundWidget();
    ~GoldenEggBackgroundWidget();
    
    virtual void Resize(const Rect& theRect) override;
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    
    bool IsSelected() { return m_selected; }
    void SetSelected(bool i_selected) { m_selected = i_selected; }
    void InitView();
    void ResetRewardImage();
    
private:
    bool m_selected = false;
    ImagePtr m_rewardPieces;
    
    time_t m_endTime = 0;
    time_t m_lastRefreshTime = 0;
    
    SexyString m_daysDes;
    SexyString m_timeDes;
    SexyString m_subtractHammersOnceDes;
    SexyString m_subtractGemsOnceDes;
    SexyString m_HammerInfoDes;
    SexyString m_dailyRewardsCountDes;
    SexyString m_hammersDes;
    SexyString m_hammersLeftDes;
    SexyString m_chancesDes;
    
    Sexy::Rect m_Rect;
    Sexy::Rect m_timeLebelRect;
    Sexy::Rect m_daysRect;
    Sexy::Rect m_timeRect;
    Sexy::Rect m_chancesRect;
    Sexy::Rect m_subtractHammersOnceRect;
    Sexy::Rect m_subtractGemsOnceRect;
    Sexy::Rect m_HammerInfoRect;
    Sexy::Rect m_dailyRewardsRect;
    Sexy::Rect m_dailyRewards2Rect;
    Sexy::Rect m_dailyRewardsCountRect;
    Sexy::Rect m_hammersRect;
    Sexy::Rect m_hammersLeftRect;
    class ActivityConfig* m_activityConfig = nullptr;
    Effect_PopAnim* m_rewardAnimRig = nullptr;
};

class GoldenEggUI : public ActiveCenterTabBase, public ButtonListener
{
public:
    GoldenEggUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~GoldenEggUI();
    
    virtual void SetSelect(bool setting) override;
    virtual void DrawForeground(class Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    
    void OnGotGoldenEggStat(bool i_success);
    void OnRefreshGoldenEggStat(bool i_success);
    void OnGoldenEggOpened(bool i_success);
    
    bool IsConnecting();
    void SetConnecting(bool i_connecting);
    void SetOpening(bool i_opening);
    bool IsOpening();
    
    Sexy::Point GetDrawOffsetPoint();
    
    void ConfirmToPay();
    
    void AddBonus(int i_eggIndex, int i_chipId, int i_chipsCount, bool i_needRefresh);
    void KillBonusUI();
    
    void SetRefreshStat(std::vector<int> i_eggsStat);
    std::vector<int> GetRefreshEggsStat() { return m_refreshEggsStat; }
    Rect GetBonusRect(int i_drawId);
    
private:
    void InitView();
    
private:
    bool m_opened;
    bool m_inited;
    bool m_connecting;
    bool m_opening;
    
    int m_lastOpenedEgg;
    pvztime_t m_startOpenTime;
    pvztime_t m_startConnectTime;
    
    Sexy::Rect m_Rect;
    Sexy::Rect m_contentRect;
    Sexy::Rect m_BuyBtnRect;
    
    Sexy::Rect m_Egg1Rect;
    Sexy::Rect m_Egg2Rect;
    Sexy::Rect m_Egg3Rect;
    
    GoldenEgg egg1;
    GoldenEgg egg2;
    GoldenEgg egg3;
    
    class ActiveCenter* m_activeCenter;
    std::vector<class PVZ2UIButton *> m_centerBtns;
    GoldenEggBackgroundWidget* m_background;
    std::vector<int> m_refreshEggsStat;
    class PVZ2UIButton* m_buyBtn;
    class PVZ2UIButton* m_closeBtn;
    class PVZ2UIButton* m_egg1Btn;
    class PVZ2UIButton* m_egg2Btn;
    class PVZ2UIButton* m_egg3Btn;    
};

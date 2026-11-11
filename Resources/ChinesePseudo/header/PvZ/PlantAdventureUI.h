//
//  PlantAdventureUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAdventureUI__
#define __PlantsVersusZombies2__PlantAdventureUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "EASquared.h"

enum PlantAdventureUITutorialStep
{
    PAUIT_Step1,
    PAUIT_Step2,
    PAUIT_Step3,
    PAUIT_Step4,
    PAUIT_Step5,
    PAUIT_Step6,
    PAUIT_Step7,
    PAUIT_End,
};

enum DungeonRequestingState
{
	DungeonRequestingState_None,
	DungeonRequestingState_Skip,
	DungeonRequestingState_BonusCount
};

class DungeonWidget : public Widget, Sexy::ButtonListener
{
public:
    DungeonWidget(WorldDungeonInfo i_info);
    virtual ~DungeonWidget();
    
    virtual void Resize(const Rect& theRect) override;
    virtual void Update() override;
    virtual void Draw(Graphics *i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void NotifyRequestingStateFinish();

    const SexyString GetDungeonNameForShow(std::string i_name);
    void Init();
    
    void ClearPlantAdventureInfo();
    
    void WatchAD(class UIMessageBox* box, int buttonID);
    void ConrirmPayForSkip(class UIMessageBox* box, int buttonID);
    void CancelPay();
    
    void WatchADAddChance(class UIMessageBox* box, int buttonID);
    void ConrirmPayForAddChance(UIMessageBox* box, int buttonID);
    void CancelPayAddChance();

    void ConrirmForSuspend();
    void CancelSuspend();
    
    int GetAddChanceGemCost();
    int GetSkipGemCost();
    int GetDungeonId() { return m_dungeonInfo.dungeonId; }
    WorldDungeonInfo GetDungeonInfo() { return m_dungeonInfo; }
    
    Sexy::Widget* GetStartBtn() { return m_startButton; }
    Sexy::Widget* GetSkipBtn() { return m_skipButton; }
    Sexy::Widget* GetFinishBtn() { return m_finishedButton; }
    std::string GetDungeonName(){ return m_dungeonInfo.dungeonName; }
    Sexy::Widget* GetAddChanceBtn() { return m_addChanceButton; }
    
    void RealStartAdventure();
    void RealStopAdventure(int i_newState);
    void RealFinishAdventure();
    void SetClipRect(Rect i_clipRect) { m_clipRect = i_clipRect; }
    void SetFreeSkip(bool i_skip) { m_freeSkip = i_skip; }
    void SkipAdventure(uint32 i_now);
    void AddChance();
    
private:
    void StartAdventure(uint32 i_now);
    void SuspendAdventure(uint32 i_now);
    void TryToSkipAdventure(uint32 i_now);
    void FinishAdventure(uint32 i_now);
    
    // zhousen for ads watching
private:
    void onADFinished(int i_type);
    void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    bool IsAdvertisementEnable();
    void refreshAddChance();
    bool canAddChance();

private:
    bool m_inited;
    bool m_freeSkip;
    int m_leftChances;
    
    WorldDungeonInfo m_dungeonInfo;
    PlantAdventureInfo m_AdventureInfo;
    
    Sexy::Rect m_dialogRect;
    Sexy::Rect m_titleRect;
    Sexy::Rect m_bgAwardRect;
    Sexy::Rect m_awardRect;
    Sexy::Rect m_awardChipsRect;
    Sexy::Rect m_awardCoinsRect;
    Sexy::Rect m_inAdventureRect;
    Sexy::Rect m_inSurpriseRect;
    Sexy::Rect m_timeHintRect;
    Sexy::Rect m_finishedRect;
    Sexy::Rect m_adventuredOutRect;
    Sexy::Rect m_timeLebelRect;
    Sexy::Rect m_closeHintRect;
    Sexy::Rect m_chancesRect;
    Sexy::Rect m_clipRect;
    
    ImagePtr m_bgImage;
    ImagePtr m_rewardPieces;
    
    SexyString m_closedInfo;
    SexyString m_title;
    SexyString m_award;
    SexyString m_timeHint;
    SexyString m_timeHint2;
    SexyString m_timeLebel;
    SexyString m_timeLeft;
    SexyString m_chanceLeft;
    std::string m_dungeonName;
    DungeonState m_dungeonState;
    
    PVZ2UIButton* m_startButton;
    PVZ2UIButton* m_suspendButton;
    PVZ2UIButton* m_skipButton;
    PVZ2UIButton* m_finishedButton;
    PVZ2UIButton* m_advertisementButton;// mutex show with m_skipButton.
    PVZ2UIButton* m_addChanceButton;

    std::string m_plantPieceType;
    bool m_watchingAD;
    int m_addChanceLeft;
    DungeonRequestingState m_requestingState;
};

class AdventureDungeonScrollPanel : public Widget, public ButtonListener
{
public:
    AdventureDungeonScrollPanel(Sexy::Rect &i_rect);
    virtual ~AdventureDungeonScrollPanel();
    
    std::vector<DungeonWidget *> GetDungeonList() { return m_dungeonList; }
    void RemoveAllDungeonWidget();
    
private:
    void InitView();
    
private:
    PlantAdventureConfig m_adventureConfig;
    std::vector<DungeonWidget *> m_dungeonList;
};

class PlantAdventureUI : public Sexy::Widget, public ButtonListener , public Sexy::ScrollWidgetListener
{
public:
    PlantAdventureUI();
    PlantAdventureUI(std::string i_dungeonName);
    ~PlantAdventureUI();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    // implement of Sexy::ScrollWidgetListener
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    
    void InitPlantAdventureUI(std::string i_dungeonName);
    void UpdateTimeLabel(Sexy::Graphics* i_g);
    void SetTabIndex(int i_tabIndex);
    
    void OnGotExplorePlantStatus(int i_dungeonId, bool i_success);
    void OnAdventureStarted(int i_dungeonId, bool i_real, bool i_success);
    void OnStopExplore(int i_dungeonId, int i_newState, bool i_success);
    void OnFreeExplore(int i_dungeonId, bool i_free);
    void OnAdventureFinished(int i_dungeonId, bool i_real, bool i_success);
    
    DungeonWidget* GetDungeonWidget(int i_dungeonId);
    
    Sexy::Widget* GetDungeonWidgetStartBtn(std::string i_dungeonName);
    Sexy::Widget* GetDungeonWidgetSkipBtn(std::string i_dungeonName);
    Sexy::Widget* GetDungeonWidgetFinishBtn(std::string i_dungeonName);
    
    void OnBackToMap();
    void OnRefreshAdventureEditor();
    
private:
    PlantAdventureUITutorialStep m_tutorialStep;
    bool m_inited;
    //    Sexy::Rect m_timeRect;
    SexyString m_teamCount;
    
    Sexy::Rect m_rectDialog;
    Sexy::Rect m_itemRect;
    Sexy::Rect m_itemScollRect;
    Sexy::Rect m_dungeonListRect;
    Sexy::Rect m_dungeonListScollRect;
    Sexy::Rect m_teamRect;
    
    PVZ2UIScrollingWidget* m_itemScollingWdget;
    PVZ2UIScrollingWidget* m_dungeonScollingWdget;
    
    AdventureDungeonScrollPanel* m_dungeonScollingPanel;
    class BouncingArrow* m_tutorialArrow;
    //    SexyString m_strTime;
    //    PVZ2UIButton* m_startButton;
};

class PlantAdventureScrollPanel : public Widget, public ButtonListener
{
public:
    PlantAdventureScrollPanel(Sexy::Rect &i_rect, std::string i_dungeonName);
    virtual ~PlantAdventureScrollPanel();
    
    virtual void Draw(Graphics *i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
private:
    void InitView();
    
private:
    PlantAdventureConfig m_adventureConfig;
    std::string m_dungeonName;
};

class AdventureOpenedUI : public Sexy::Widget, public ButtonListener
{
public:
    AdventureOpenedUI();
    ~AdventureOpenedUI();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void OnOpenPlantAdventure(bool i_success);
    void BackToMap();
    
private:
    Sexy::Rect m_rectDialog;
    Sexy::Rect m_innerDialog;
    Sexy::Rect m_contentRect;
    SexyString m_hintTitle;
    SexyString m_hintInfo;
    PVZ2UIButton* m_goButton;
    class BouncingArrow* m_tutorialArrow;
};

class AdventureBonusUI : public Sexy::Widget, public ButtonListener
{
public:
    AdventureBonusUI(int i_dungeonId, SexyString i_dungeonName);
    AdventureBonusUI();
    ~AdventureBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void OnGotExploreReward(bool i_success);
    void SetBought();
    void SetWorldName(const std::string& i_worldName);
    void WatchAD();
    
private:
    void onADFinished(int i_type);
    void Init(int i_dungeonId, SexyString i_dungeonName);
    
private:
    class BouncingArrow* m_tutorialArrow;
    int m_dungeonId;
    int m_bonusPieces;
    int m_bonusCoins;
    int m_bonusItemsId;
    int m_bonusItems;
    ImagePtr m_rewardPieces;
    bool m_hasSurprise;
    bool m_hasChecked;
    Sexy::Rect m_rectDialog;
    Sexy::Rect m_piecesRect;
    Sexy::Rect m_coinsRect;
    Sexy::Rect m_itemRect;
    Sexy::Rect m_innerDialog;
    Sexy::Rect m_contentRect;
    SexyString m_hintTitle;
    SexyString m_hintInfo;
    SexyString m_crystalInfo;
    SexyString m_crystalLimitedInfo;
    bool m_reachLimit;
    PVZ2UIButton* m_finishedButton;
    PVZ2UIButton* m_surpriseButton;
    PVZ2UIButton* m_adButton;
    std::string m_plantPieceType;
    std::string m_worldName;

    bool m_watchingAD;
    bool m_isADReward;
    SexyString m_adInfo;
    std::vector<class UIRewardFrame*> m_frames;
};

class AdventureSurpriseUI : public Sexy::Widget, public ButtonListener
{
public:
    AdventureSurpriseUI(int i_dungeonId);
    ~AdventureSurpriseUI();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void OnGotExploreSurprise(bool i_success);
    void OnExploreSurpriseBoxOpend();
    
private:
    int m_dungeonId;
    int m_bonusPieces;
    int m_surprisePrice;
    ImagePtr m_rewardPieces;
    Sexy::Rect m_piecesRect;
    Sexy::Rect m_rectDialog;
    Sexy::Rect m_innerDialog;
    Sexy::Rect m_contentRect;
    Sexy::Rect m_hintRect;
    SexyString m_hintTitle;
    SexyString m_hintInfo;
    std::string m_surpriseTypeName;
    std::string m_surpriseName;
    PVZ2UIButton* m_giveupButton;
    PVZ2UIButton* m_buyButton;
    std::string m_plantPieceType;
    int m_objectId;
};

class OpenSurpriseUI : public BoxOpenUI
{
public:
    OpenSurpriseUI(const std::string i_animName);
    ~OpenSurpriseUI();
    
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void ResetAnimName() override;
    
private:
};

namespace Message
{
    void AdventureStart(int i_dungeonId, bool i_real, bool i_success);
    void AdventureFinished(int i_dungeonId, bool i_real, bool i_success);
    void ExploreSurpriseBoxOpend();
    void RefreshAdventureEditorAll();
}

#endif /* defined(__PlantsVersusZombies2__PlantAdventureUI__) */

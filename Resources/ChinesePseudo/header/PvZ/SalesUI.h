//
//  SalesUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/3/10.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef SalesUI_h
#define SalesUI_h

#include "PopingWidget.h"
#include "RealObject.h"
#include "Core.h"
#include "MagentoService.h"
#include "StateMachine.h"
#include "StateMachineTableBuilder.h"
#include "EffectAnim_UIAnim.h"
#include "Image.h"
//#include <queue>

STATE_ENUM_BASE_BEGIN(SalesButtonState)
SalesButtonState_READY,
SalesButtonState_IDLE,
SalesButtonState_CLICKING,
SalesButtonState_BACK,
SalesButtonState_SELECTED,
SalesButtonState_BUYING,
STATE_ENUM_END(SalesButtonState);

enum SalesButtonIndex
{
    None = -1,
    SBI_1,
    SBI_2,
    SBI_3,
    SBI_Count,
};

class SalesButton : public RealObject
{
public:
    RT_CLASS_DEFINE(SalesButton, RealObject, RtClass);
    
    SalesButton();
    ~SalesButton();
    
    void OnUpdate();
    void OnDraw(Graphics* i_g);
    
    void SetVisible(bool i_visible);
    
    void HandleAnimStopped(const std::string &i_animName);
    void InitSalesButton(Rect i_rect, SalesButtonIndex i_index);
    SalesButtonIndex GetSalesButtonIndex() { return m_index; }
    
    bool isInState(SalesButtonState i_state) const;
    void setState(SalesButtonState i_newState);
    SalesButtonState getState();
    
    bool IsBuyingLocked() { return m_buyingLock; }
    void LockBuying() { m_buyingLock = true; }
    void UnlockBuying() { m_buyingLock = false; }
    
    void SetBuyBtn(class PVZ2UIButton* i_buyBtn) { m_buyBtn = i_buyBtn; }
    class PVZ2UIButton* GetBuyBtn() { return m_buyBtn; }
    
    ImagePtr GetImgPtrFromObjectId(int i_objectId);
    void InitImgsRects();
    void UpdateImgRects();
    
    void OnRefresh();
    
protected:
    DECLARE_STATE_FUNCTIONS(SalesButtonState, READY);
    DECLARE_STATE_FUNCTIONS(SalesButtonState, IDLE);
    DECLARE_STATE_FUNCTIONS(SalesButtonState, CLICKING);
    DECLARE_STATE_FUNCTIONS(SalesButtonState, BACK);
    DECLARE_STATE_FUNCTIONS(SalesButtonState, SELECTED);
    DECLARE_STATE_FUNCTIONS(SalesButtonState, BUYING);
    
private:
    void SetIndex(SalesButtonIndex i_index);
    void Resize(Rect i_rect);
    
    int32 getSalesButtonStateSerialization();
    void setSalesButtonStateSerialization(int32 i_state);
    
    void ShowPriceLayer(std::string i_layerName);
    void ShowDiscountLayer(std::string i_layerName);
    void ShowPiecesLayer(std::string i_layerName);
    
private:
    Rect m_buttonRect;
    
    bool m_buyingLock;
    bool m_visible;
    int m_pricesCount;
    int m_pieceOffsetX;
    int m_pieceOffsetY;
    SalesButtonIndex m_index;
    
    StateMachine<SalesButtonState>  m_state;
    
    std::string m_currentAnim;
    
    pvztime_t m_lastAnimTime;
    pvztime_t m_animTime;
    
    EffectAnim_UIAnim       m_popAnimRig;
    class PVZ2UIButton*     m_buyBtn;
    
    ImagePtr m_pieceImg;
    ImagePtr m_multiImg;
    ImagePtr m_numImg1;
    ImagePtr m_numImg2;
    
    Rect m_pieceImgRect;
    Rect m_multiImgRect;
    Rect m_numImg1Rect;
    Rect m_numImg2Rect;
    
    float       m_startScale;
    float       m_destScale;
    float       m_pieceScale;
    float       m_currentScale;
    
    pvztime_t   m_startTime;
    pvztime_t   m_popingTime;
    pvztime_t   m_endTime;
    std::string m_plantPieceType;
};

class SalesTimer
{
public:
    SalesTimer();
    ~SalesTimer();
    
    void StartTimer(float i_time);
    void EndTimer();
    bool IsTimeUp();
    float GetTimerScale();
    
private:
    bool        m_started;
    
    pvztime_t   m_startTime;
    pvztime_t   m_progressingTime;
    pvztime_t   m_endTime;
};

class SalesProgressBar : public RealObject
{
public:
    SalesProgressBar();
    ~SalesProgressBar();
    
    void OnUpdate();
    void OnDraw(Graphics* i_g);
    
    void SetVisible(bool i_visible);
    
    void InitView(Rect i_rect);
    void InitAnims(bool i_changePlant);
    void StartToShow();
    void OnRefresh(bool i_changePlant = false);
    void OnChangePlant();
    
    void RefreshAdvanceProgress();
    void MoveAdvanceProgressTo(int i_pieces);
    
    bool IsLevelUp();
    int GetCurrentLevel();
    int GetAdvanceLevel();
    int GetCurrentPieces();
    int GetAdvancePieves();
    
private:
    void SetProgress(int i_pieces);
    void SetAdvanceProgress(int i_pieces);
    
    void RefreshProgress();
    void MoveProgressTo(int i_pieces);
    
    void StartProgressTimer();
    void StartAdvanceProgressTimer();
    
    void UpdatePieceToShow();
    void UpdateAdvancePieceToShow();
    
    void HandleAdvanceProgress();
    void InitProgressBar();
    void Resize(Rect i_rect);
    
private:
    bool m_visible;
    
    int m_bonusId;
    int m_maxLevel;
    int m_maxPieces;
    int m_currentLevel;
    int m_realLevel;
    int m_advanceLevel;
    int m_lastRealLevel;
    int m_lastAdvanceLevel;
    
    Rect m_progressRect;
    Rect m_percentRect;
    Rect m_advancePercentRect;
    Rect m_progressStartRect;
    
    Point m_progresslevelPoint[5];
    
    ImagePtr m_progressBarBG;
    ImagePtr m_advanceProgressBar;
    ImagePtr m_progressBar;
    ImagePtr m_progressStart;
    ImagePtr m_seprator;
    
    EffectAnim_UIAnim m_levelAnim[5];
    
    int m_pieces;
    int m_advancePieces;
    int m_piecesShow;
    int m_advancePiecesShow;
    int m_lastPieces;
    int m_lastAdvancePieces;

    SalesTimer m_progressTimer;
    SalesTimer m_advanceProgressTimer;
    
    std::map<int, int> m_levelUp;
};

class SalesRewardBox : public PopingWidget, public ButtonListener
{
public:
    SalesRewardBox();
    ~SalesRewardBox();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    bool IsInited() { return m_inited; }
    void InitBox(bool i_levelUp, int i_bonusId, int i_level, int i_advanceLevel, int i_pieces, int i_advancePieces);
    
private:
    void InitView();
    
    void InitPlantView();
    void InitProgressBar();
    void InitDescription();
    void InitShiningAnims();
    
    void StartToShow();
    void SetProgress(int i_pieces);
    void PlayProgress();
    void UpdatePieceToShow();
    
private:
    bool m_inited;
    bool m_levelUp;
    
    int m_bonusId;
    
    int m_level;
    int m_advanceLevel;
    
    int m_pieces;
    int m_advancePieces;
    int m_totalPieces;
    int m_notPieces;
    
    Rect m_titleRect;
    Rect m_plantViewRect;
    Rect m_progressRect;
    Rect m_progressBGRect;
    Rect m_descriptionRect;
    
    Rect m_progLeftRect;
    Rect m_progRightRect;
    
    SalesTimer m_progressTimer;
    
    SexyString              m_title;
    SexyString              m_description;
    class PVZ2UIButton*     m_closeBtn;
    
    ImagePtr          m_levelImg;
    ImagePtr          m_nextLevelImg;
    
    EffectAnim_UIAnim m_openAnimRig;
    EffectAnim_UIAnim m_backAnimRig;
    EffectAnim_UIAnim m_popAnimRig;
    EffectAnim_UIAnim m_levelAnimRig;
};

class SalesUI : public PopingWidget, public ButtonListener
{
public:
    SalesUI();
    ~SalesUI();
    
    virtual bool Init();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void UpdateTimeLabel();
    void OnSalesBought();
    void OnSetUpSalesBought();
    void OnVerifiedSales(bool i_success);
    
    bool IsRewardBoxValid() { return m_rewardBox != NULL; }
    bool IsRewardBoxInited();
    void CreateRewardBox();
    void InitRewardBox(bool i_levelUp, int i_targetLevel);
    void ShowRewardBox();
    void KillRewardBox();
    class SalesRewardBox* GetRewardBox() const { return m_rewardBox; }
    
    bool HasLoadedGroup(std::string i_loadingResGroupName);
    void AddLoadingGroup(std::string i_loadingResGroupName);
    
    void OnChangePlant();
    void OnRefresh();
    
    int GetRewardQuantity();
    int GetPrices();
#ifdef HOST_ANDROID
    std::string GetSkuId();
#endif
    
private:
    void InitView();
    
    void InitSalesButtons();
    void RemoveAllSalesButtons();
    
    void InitPlantPreview();
    void InitBoardView();
    void ReleaseBoardView();
    void RefreshSalesButtons();
    
    void PreviewSalesBtn(SalesButtonIndex i_index);
    void BuySalesBtn(SalesButtonIndex i_index);
    
    void SecondConfirmBuy();
    void SecondConfirmCancel();
    
    void AddResourceGroups();
    void ReleaseResourceGroups();
    void ResetLevelImg();
    
    void BackToMap();
    
private:
    Rect m_titleRect;
    Rect m_timeLebelRect;
    Rect m_timeShowRect;
    Rect m_plantNewRect;
    Rect m_plantViewRect;
    Rect m_miniMapRect;
    Rect m_buyingPanelRect;
    Rect m_progressRect;
    
    bool        m_refreshed;
    bool        m_isNew;
    int         m_bonusId;
    int         m_activeButtonID;
    int         m_pricesCount;
    SexyString  m_title;
    SexyString  m_timeToShow;
    
    EffectAnim_UIAnim   m_animNew;
    EffectAnim_UIAnim   m_plantAnim;
    
    std::vector<SalesButton*>   m_salesButtons;
    std::vector<std::string>    m_loadedGroup;
    
    ImagePtr            m_levelImg;
    SalesProgressBar    m_progress;
    std::vector<Rect>   m_salesButtonsRect;
    SalesButton*        m_salesBtn1;
    SalesButton*        m_salesBtn2;
    SalesButton*        m_salesBtn3;
    class PVZ2UIButton* m_previewBtn1;
    class PVZ2UIButton* m_previewBtn2;
    class PVZ2UIButton* m_previewBtn3;
    class PVZ2UIButton* m_buyBtn1;
    class PVZ2UIButton* m_buyBtn2;
    class PVZ2UIButton* m_buyBtn3;
    
    Color m_timeColor;
    
    class PVZ2UIButton*         m_closeBtn;
    class SalesRewardBox*       m_rewardBox;
    
    class PlantLevelUpListView* m_plantPreview;
    
    //fix quick touch
    bool      m_BuyCanTouch;
    pvztime_t m_timeTouch;
};

//-----------------------------------------------------
// ActiveSalesConfig
//-----------------------------------------------------
struct ActiveSalesObject
{
    int newArrival;
    int ObjectId;
    uint32 refreshTimes;
    
    ActiveSalesObject()
    {
        newArrival = 0;
        ObjectId = -1;
        refreshTimes = 0;
    }
};

struct ActiveSalesPriceList
{
    int pieces;
    int price;
    
    ActiveSalesPriceList()
    {
        pieces = 0;
        price = 0;
    }
};

class ActiveSalesConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(ActiveSalesConfig, RtObject, RtClass);
    ActiveSalesConfig();
    
public:
    std::vector<ActiveSalesObject> salesList;
    std::vector<ActiveSalesPriceList> priceList;
    
};

namespace Message
{
    void SalesBought();
    void SetUpSalesBought();
}

void SalesUI_SetPriceIndexLayerNames(const std::map<int, std::string>& rMap);
void SalesUI_SetDiscountIndexLayerNames(const std::map<int, std::string>& rMap);
void SalesUI_SetPiecesIndexLayerNames(const std::map<int, std::string>& rMap);

void SalesUI_SetPriceLayerNames(const std::vector<std::string>& rLayerNames);
void SalesUI_SetDiscountLayerNames(const std::vector<std::string>& rLayerNames);
void SalesUI_SetPiecesLayerNames(const std::vector<std::string>& rLayerNames);


#endif /* SalesUI_h */

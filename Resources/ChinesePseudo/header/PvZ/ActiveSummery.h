//
//  ActiveSummery.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.7.18.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _ActiveSummery_h_
#define _ActiveSummery_h_

#include "UISingletonDialog.h"
#include "RtObject.h"
#include "RestrictionSet.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "DString.h"
#include "PVZ2UIButton.h"
//#include "ActivityManager.h"

//-----------------------------------------------------
// LuckyProgressUtil
//-----------------------------------------------------
class LuckyProgressUtil
{
public:
    void            Init(Sexy::Widget* pClipWidget, Sexy::Widget* pProgressWidget, class UIWidgetAnim* pFullAnim);
    void            SetProgerss(float i_progress, bool i_bAnim);
    void            Update();
    Sexy::Widget*   GetProgressWidget();
protected:
    void            refreshUI(float i_progress);
    void            updateAnimation();
protected:
    Sexy::Widget*   m_pClipWidget = nullptr;
    Sexy::Widget*   m_pProgressWidget = nullptr;
    class UIWidgetAnim*     m_pFullAnim = nullptr;
    float           m_fProgress = 0.0f;
    float           m_fAnimProgress = 0.0f;
};

//-----------------------------------------------------
// ActiveSummeryConfig
//-----------------------------------------------------
class ActiveSummeryConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(ActiveSummeryConfig, Sexy::RtObject, Sexy::RtClass);
    
    bool Init();
    ActiveSummeryConfig();
public:
    float m_fitPlantDamageRate;
    float m_unFitPlantDamageRate;
    std::string m_fireStartLevel;
    std::string m_iceStartLevel;
    std::vector<std::string>            m_firePlants;
    std::vector<std::string>            m_icePlants;
    std::string                         m_compositPlantName;
    std::string                         m_compositMatName;
    int32                               m_compositPlantNeedNum = 0;
    int32                               m_compositMatNeedNum = 0;
    int32                               m_materialCostEachLottery = 0;
    PlantRestrictionSet	m_redPlants;
    PlantRestrictionSet m_bluePlants;
    std::vector<S2C_ICloud_IDCount>  m_fireLotteryList;
    std::vector<S2C_ICloud_IDCount>  m_iceLotteryList;
    S2C_ICloud_IDCount  m_fireSpecialLottery;
    S2C_ICloud_IDCount  m_iceSpecialLottery;
};

//-----------------------------------------------------
// LotterySelectFrame
//-----------------------------------------------------

class LotterySelectFrame  : public Sexy::Widget
{
public:
    const static int Infinite = -1;
    struct Item
    {
    public:
        int         m_id = 0;
        int         m_count = 0;
        SexyVector2 m_position;
    };
    
    typedef Sexy::Delegate1<LotterySelectFrame*> CallbackEvent;
public:
    LotterySelectFrame();
    void Update() override;
    void Draw(Graphics* i_g) override;
    void Start();
    void Stop();
    bool IsStop();
    void SetDest(int itemID, int itemCount);
    void SetItemPool(const std::vector<Item>& item);
    void SetStopCallBack(CallbackEvent callback);
    int GetDestIndex();
private:
    void UpdatePosition();
    void UpdateIndex();
    bool SelectDest();
    void PlaySelectEffect();
    void OnAnimationFinish(const std::string& label);
private:
    const float Acceleration = 15.0f;
    const float Deceleration = -10.0f;
    const float StartSpeed = 5.0f;
    const float MinSpeed  = 2.0f;
    const float LowSpeed  = 5.0f;
    const float StopSpeed = 2.5f;
    const float MaxSpeed  = 30.0f;
    
    const static int StateStop       = 0;
    const static int StateAccelerate = 1;
    const static int StateMaxSpeed   = 2;
    const static int StateDecelerate = 3;
    const static int StateMinSpeed   = 4;
    const static int StateSelect     = 5;
    
    int m_state = StateStop;
    int m_index = 0;
    float m_speed = 0.0f;
    int m_destIndex = 0;
    pvztime_t m_nextJump = 0;
    pvztime_t m_stateTime = 0;
    std::vector<Item> m_item;
    UIWidgetAnim* m_selectEffect = nullptr;
    CallbackEvent	 m_callback;
};

//-----------------------------------------------------
// UISummeryLotteryItemTip
//-----------------------------------------------------

class UISummeryLotteryItemTip : public Sexy::Widget
{
public:
    void Draw(Sexy::Graphics* i_g) override;
    void SetTip(const SexyString& tip);
private:
    SexyString m_tip;
};

//-----------------------------------------------------
// UISummeryLotteryItem
//-----------------------------------------------------

class UISummeryLotteryItem  : public PVZ2UIButton, public ButtonListener
{
public:
    enum LotteryType
    {
        LotteryTypeUnknown = 0,
        LotteryTypeCoin,
        LotteryTypeGem,
        LotteryTypeFireSoil,
        LotteryTypeNationalCurrency,
        LotteryTypePlantPiece,
        LotteryTypeAvatarPiece,
        LotteryTypeAccessoryPiece,
    };
public:
    UISummeryLotteryItem(int itemID, int itemCount);
    void Setbackground(Image* background);
    void Draw(Graphics* i_g) override;
    void SetTransparent(bool trans);
    int  GetItemID();
    LotteryType GetItemType();
    Image* GetImage();
    float GetImageScale();
    std::string GetPlantType();
    std::string GetPlantPieceType();
    SexyString GetItemName();
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void	 ButtonMouseLeave(int i_id) override;
    static void ShowTip(const SexyString& tip, const SexyVector2& pos);
    static void KillTip();
private:
    void GetItemTypeAndImage();
    void GetFrame();
    int GetPlantPieceRare(int id);
    int GetAccessoryQuality(int id);
private:
    int m_itemID = 0;
    int m_itemCount = 0;
    bool m_transparent = false;
    std::string m_plantType;
    std::string m_plantPieceType;
    SexyString m_itemName;
    LotteryType m_itemType = LotteryTypeUnknown;
    Image* m_image = nullptr;
    float m_imageScale;
    Image* m_frame = nullptr;
    Image* m_background = nullptr;
    static UISummeryLotteryItemTip* m_tip;
};

//-----------------------------------------------------
// LotteryPanelData
//-----------------------------------------------------

class LotteryPanelData
{
public:
    LotteryPanelData();

    int m_activeTypeID;
    std::string m_remainDayWidgetName;
    SexyString m_materialTextFormat;
    SexyString m_materialName;
    std::string m_materialType;
    Image* m_itemBackground = nullptr;
    
    int m_materialEach  = 0;
    int m_materialID    = 0;
    int m_materialCount = 0;
    int m_materialDetaCount = 0;
    int m_luck = 0;
    int m_totalLuck = 1;
    int m_serverLotteryType = 0;
    int m_normalBonusID = 0;
    int m_normalBonusCount = 0;
    int m_specialBonusID = 0;
    int m_specialBonusCount = 0;
    Widget* m_panel = nullptr;
    Widget* m_exclamation  = nullptr;
    Widget* m_luckProgressBack = nullptr;
    UIWidgetText* m_materialText = nullptr;
    LuckyProgressUtil* m_luckProgress = nullptr;
    UIWidgetAnim* m_specialBounsUI = nullptr;
    LotterySelectFrame* m_selectFrame = nullptr;
    
    S2C_ICloud_IDCount m_specialItem;
    std::vector<S2C_ICloud_IDCount> m_itemIdList;
    std::vector<UISummeryLotteryItem*>  m_ItemUiList;

public:
    void updateLuckUI(bool animated);
    void updateMaterialUI();
    void InitLotteryItemUI();
    void initSelectFrame();
    UISummeryLotteryItem* GetLotteryItem(int itemID);
private:
    SexyVector2 getLotteryItemSize();
    void initLotteryItemPosition();
    void UpdateSpecialBonusUI();
    std::vector<SexyVector2> m_lotteryItemPosition;
};

//-----------------------------------------------------
// ActiveSummery
//-----------------------------------------------------

class ActiveSummery : public UISingletonDialog<ActiveSummery>, public UI::TabControlListener
{
public:
public:
	ActiveSummery();
	virtual ~ActiveSummery();
	virtual bool							OnCreate() override;
	virtual std::string                 GetLayoutName() override { return "ActiveSummery"; }
    virtual void							Draw(Sexy::Graphics* i_g) override;
    virtual void							Update() override;
    virtual void TabSelectionChanged(int tabID) override;
	// ButtonListener
	virtual void							ButtonDepress(int i_id) override;
    void                                ResponsePlantCompositMsg(const std::string& i_jsonstr);
    
    static void                         RequestDatas();
    static bool                         IsHaveNewTips();
    static bool                         IsInBossBattle();
    static bool                         IsOpened();
    static void                         RefreshMaterial(const std::set<int>& i_activeList);
    static void                         showTip(const SexyString& tip);
    class UITabControl*   				GetInnerDialog() { return m_pTabControl; }
protected:
    void                                initTabZombieBoss();
    void                                initTabPlantComposit();
    void                                initTabFireLottery();
    void                                initTabIceLottery();
    void                                initTabLottery(LotteryPanelData* data);
    void                                refreshTabPlantComposit();
    void                                refreshRemainDays(const class ActiveItem* pActiveItem, const std::string& widgetName);
    bool                                checkPlantComposit(int i_num);
    void                                setPlantPiece(int i_id, int i_num, int& o_numChanged);
    void                                setButtonsDisabled(bool i_bDisabled);
    void                                showLackMaterial(SexyString materialName);
    void                                confirmBuy(class UIMessageBox* box, int buttonID);
    void                                onPlantAnimStopped(const std::string& i_animLabelName);
    void                                onRequestSummeryLottery(int result, const class S2C_SummeryLotteryData& data);
    void                                onNotifySummeryMaterialBuy(class MsgResultInfo* io_result, const class S2C_ICloud_GetConsumeGemInfo* pInfo, const class S2C_PlayerInfo* pGemChanged);
    void                                addItem(int id, int count);
    void                                onSelectFrameStop(LotterySelectFrame* frame);
    void                                getLotteryResultInfo(UISummeryLotteryItem* ui, int itemCount, class LotteryResultIconInfo& dest);
    void                                onNetworkError(int erroId, const std::string& requestID);
private:
    ActiveSummeryConfig                 m_config;
    class UITabControl*                 m_pTabControl = nullptr;
    class UIWidgetAnim*                 m_pAnimPlant = nullptr;
    class UIWidgetText*                 m_pTextPlantNum = nullptr;
    class UIWidgetText*                 m_pTextMatNum = nullptr;
    
    class UIWidgetText*                 m_pTextAlert = nullptr;
    float                               m_timerAlert = -1;
    int                                 m_numAlert = 0;
    Color                               m_colorSrcAlert;
    
    int                                 m_buttonClickedID = 0;
    int                                 m_matCurNum = 0;
    int                                 m_matNeedNum = 0;
    
    LuckyProgressUtil                   m_progressUtilFire;
    LuckyProgressUtil                   m_progressUtilIce;

    bool                                        m_buttonsDisabled = false;

    LotteryPanelData* m_fireLotteryData = nullptr;
    LotteryPanelData* m_iceLotteryData = nullptr;
    LotteryPanelData* m_currentLotteryData = nullptr;
};

//-----------------------------------------------------
// message datas
//-----------------------------------------------------
class SummerBossData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(SummerBossData, Sexy::RtObject, Sexy::RtClass);
    
public:
    int     m_fireLeftTimes = 0;
    int     m_iceLeftTimes = 0;
};

class SummerPlantCompositData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(SummerPlantCompositData, Sexy::RtObject, Sexy::RtClass);
    
public:
    int     m_matCurNum = 0;
    int     m_matNeedNum = 0;
};


class SummeryLotteryMaterialData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(SummeryLotteryMaterialData, Sexy::RtObject, Sexy::RtClass);
    
public:
    int  m_count;
    int  m_luck;
    int  m_luckTotal;
};

#endif

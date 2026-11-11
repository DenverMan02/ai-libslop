//
//  TransGenosisUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 2016/10/26.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef TransGenosisUI_h
#define TransGenosisUI_h

#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

enum RareTypes
{
    rare_0 = 0,
    rare_1,
    rare_2,
    rare_3,
    rare_4,
    rare_end
};

enum TG_PayType
{
    TGPT_None = 0,
    TGPT_Coin,
    TGPT_Gem,
    TGPT_Tutorial,
    TGPT_AD,
    TGPT_ADAvatar
};

struct SelectBox
{
    int selectId = 0;
    Rect boxRect;
    Rect box1Rect;
};

struct RateOfRares
{
    int quantity = 0;
    RareTypes rare = rare_0;
    Rect iconRect;
    Rect barRect;
    Rect rateRect;
    SexyString rateString = _S("");
};

class TGConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TGConfig, RtObject, RtClass);
    TGConfig() {}
    
public:
    int MinChips = 2;
    float Lost = 0.5f;
    
    int ActiveLR = 0;
    int GemCost = 20;
    int GoldCost = 5000;
    
    float GoldGain = 0.f;
    float GemGain = 25.f;
    
    std::vector<int> BaseValue;
    std::vector<int> ASWeight;
};

class TGButton : public PVZ2UIButton
{
public:
    TGButton(int i_id, Sexy::ButtonListener* i_listener);
    TGButton(int i_id, Sexy::ButtonListener* i_listener, TG_PayType i_type, int i_price);
    ~TGButton();
    
    virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    
    void SetPayType(TG_PayType i_type);
    void SetPrice(int i_price);
    void InitView();
    
    void SetIsInTutorial(bool i_tutorial);
    
private:
    ImagePtr m_imgCurrency = nullptr;
    TG_PayType m_payType = TGPT_None;
    
    bool m_tutorial = false;
    
    int m_price = 0;
    int m_currencyOffsetX = 0;
    
    Rect m_titleRect;
    Rect m_currencyRect;
    Rect m_priceRect;
    
    SexyString m_titleS = _S("");
    SexyString m_priceS = _S("");
    int m_id = 0;
};

class Effect_Whirlpool : public RtObject
{
public:
    Effect_Whirlpool(SexyVector2 i_center, int i_drawW, int i_objectId, float i_radius, float i_rotAng, bool i_revise, float i_startScale = 1.f);
    ~Effect_Whirlpool();
    
    void StartEffect();
    bool IsStarted();
    bool IsEnd();
    
    bool IsActive();
    
    void OnUpdate();
    void OnDraw(Graphics* i_g);
    
    void SetSpeedOfAng(float i_speedOfAng);
    void SetSpeedOfScale(float i_speedofScale);
    void SetSpeedOfRadius(float i_speedofRadius);
    
private:
    void DrawCurrent(Graphics* i_g);
    
private:
    bool m_revise = false;
    bool m_started = false;
    bool m_finished = false;
    
    int m_objectId = 0;
    int m_drawW = 0;
    
    float m_radius = 0.f;
    float m_startAng = 0.f;
    float m_startScale = 1.f;
    
    float m_speedofAng = 0.f;
    float m_speedofRadius = 0.f;
    float m_speedofScale = 0.f;
    
    pvztime_t m_startTime = 0.f;
    SexyVector2 m_center;
};

class TGProduct : public Sexy::Widget, public ButtonListener
{
public:
    TGProduct();
    ~TGProduct();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void AddTGProducts(std::vector<S2C_BonusInfo> i_productList, bool i_tutorial);
    void InitView();
    void ShowTGProducts();
    void ShowProduct(S2C_BonusInfo i_product, int i_num);
    void SetSource(std::vector<int> i_src);
    SexyString GetProductDes(int i_productId, int i_quantity);
    void StartEffect();
    void SetRevise(bool i_revise);
    
private:
    int m_productId[3] = {0};
    int m_quantity[3] = {0};
    
    bool m_tutorial = false;
    bool m_revise = false;
    bool m_openPlayed = false;
    
    PVZ2UIButton* m_closeProductBtn = nullptr;
    
    Rect m_titleRect;
    Rect m_productRect[3];
    Rect m_productTitleRect[3];
    Rect m_closeProductRect;
    
    SexyString m_productDes[3] = {_S(""),_S(""),_S("")};
    SexyVector2 m_lightPos;
    
    EffectAnim_UIAnim m_productAnimLeft;
    EffectAnim_UIAnim m_productAnimCenter;
    EffectAnim_UIAnim m_productAnimRight;
    EffectAnim_UIAnim m_popAnim;
    
    std::vector<Effect_Whirlpool *> m_whirlpoolEffects;
    std::vector<S2C_BonusInfo> m_products;
};

class TransGenosisUI : public PopingWidget, public ButtonListener
{
public:
    TransGenosisUI();
    ~TransGenosisUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    void AddToSelectBoxs(int i_id);
    void SetSelectBoxs(std::vector<int> seeds, bool i_return);
    void SetAvatarSelectBoxs(std::vector<int> seeds, bool i_return);
    void ShowWindow();
    void SetConfig(TGConfig i_config);
    void OnTGResultGot(bool i_success);
    void OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
    
    std::vector<int> GetSelectedBoxIDs();
    std::vector<int> GetAvatarSelectedBoxIDs();
    void CreateTGProducts();
    void AddTGProducts(std::vector<S2C_BonusInfo> i_productList);
    void ShowProductUI();
    void CloseProductUI();
    
    void CalcChipsForAS(std::map<int, int>& i_restore);
    void CalcAvatarChipsForAS(std::map<int, int>& i_restore);
    int DoAutoSelect(std::map<int, int>& i_restore, int i_index, bool& i_notEnough);
    int DoAvatarAutoSelect(std::map<int, int>& i_restore, int i_index, bool& i_notEnough);
    bool CanStartTrans();
    
    TG_PayType GetCurrentTGType();
    
    static TransGenosisUI* GetTGWidget();
    Point GetCorePoint();
    
private:
    void ClearSelectBoxs();
    void ClearSimpleRates();
    void ClearSeniorRates();
    void InitSelectBoxs();
    void InitSimpleRates();
    void InitSeniorRates();
    
    void UpdateSelectedValues();
    void UpdateSimpleRates();
    void UpdateSeniorRates();
    void DrawSimpleRates(Graphics* i_g);
    void DrawSeniorRates(Graphics* i_g);
    
    void UpdateButtons();
    
    void DrawBanks(Graphics* i_g);
    void DrawSelectBoxs(Graphics* i_g);
    void DrawAwaitPanel(Graphics* i_g);
    void DrawTransPanel(Graphics* i_g);
    
    bool HasRareOf(std::map<int, int>& i_restore, RareTypes i_type);
    
    void ShowPiecesTable();
    void ShowAvatarPiecesTable();
    void AutoSelecting();
    void AvatarAutoSelecting();
    void DoSimpleTrans();
    void SimpleTrans();
    void DoSeniorTrans();
    void SeniorTrans();

    void DoAvatarSimpleTrans();
    void AvatarSimpleTrans();
    void DoAvatarSeniorTrans();
    void AvatarSeniorTrans();
    void DoAvatarTrans(int i_type);

    void ADTrans();
    void DoADTrans();

    void ADAvatarTrans();
    void DoADAvatarTrans();

    void onADFinished(int i_type);

    int GetInsertIndex();
    bool CanSelectBoxAdd();
    
    int GetValueByPlantchipId(int i_chipId);
    void SetSimpleRates(std::vector<int> i_rates);
    void SetSeniorRates(std::vector<int> i_rates);
    
    void ShowCoinStore();
    void ShowGemStore();
    
    void InitTutorialState();
    void StartOpenTutorial();
    void StartTGTutorial();
    void RecoverEverthingToNomal();

    void SwitchHiden(bool i_flag);
    
private:
    bool m_inited = false;
    bool m_tutorial = false;
    bool m_switchHidenFlag = true;
    
    int m_selectedValue = 0;
    
    TGConfig m_config;
    TG_PayType m_currentTpe = TGPT_None;
    
    TGProduct* m_productUI = nullptr;
    
    SexyString m_title = _S("");
    SexyString m_simpleTitle = _S("");
    SexyString m_seniorTitle = _S("");
    SexyString m_rateTitle = _S("");
    SexyString m_avatarSimpleDes = _S("");
    SexyString m_avatarSeniorDes = _S("");
    
    SexyString m_simpay = _S("");
    SexyString m_senpay = _S("");
    SexyString m_avatarSimpay = _S("");
    SexyString m_avatarSenpay = _S("");
    
    std::vector<SelectBox *> m_selectBoxs;
    std::vector<SelectBox *> m_avatarSelectBoxs;
    std::vector<RateOfRares *> m_simpleRate;
    std::vector<RateOfRares *> m_seniorRate;
    std::vector<S2C_BonusInfo> m_products;
    
    Rect m_titleImgRect;
    Rect m_titleRect;
    Rect m_closeRect;
    Rect m_coinRect;
    Rect m_gemRect;
    Rect m_coinBankRect;
    Rect m_gemBankRect;
    Rect m_panelRect;
    Rect m_bannerBoarderRect;
    Rect m_bannerRect;
    Rect m_frameBoarderLeftRect;
    Rect m_frameBoarderRightRect;
    Rect m_autoSelectBoarderRect;
    Rect m_autoSelectRect;
    Rect m_resultRect;
    
    Rect m_simpleTitleRect;
    Rect m_simpleSlipRect;
    Rect m_avatarSimpleDesRect;
    Rect m_simpleRect;
    Rect m_simpleBtnRect;
    Rect m_simpleRatePanel;
    
    Rect m_seniorTitleRect;
    Rect m_seniorSlipRect;
    Rect m_avatarSeniorDesRect;
    Rect m_seniorRect;
    Rect m_seniorBtnRect;
    Rect m_seniorRatePanel;
    
    Rect m_adBtnRect;

    EffectAnim_UIAnim m_resultAnim;
    
    PVZ2UIButton* m_switchHidenBtnPlant = nullptr;
    PVZ2UIButton* m_switchHidenBtnAvatar = nullptr;
    PVZ2UIButton* m_avatarDesBtn = nullptr;
    PVZ2UIButton* m_switchBtn = nullptr;
    PVZ2UIButton* m_avatarSwitchBtn = nullptr;
    PVZ2UIButton* m_autoSelect = nullptr;
    PVZ2UIButton* m_avatarAutoSelect = nullptr;
    TGButton* m_simpleBtn = nullptr;
    TGButton* m_seniorBtn = nullptr;
    TGButton* m_avatarSimpleBtn = nullptr;
    TGButton* m_avatarSeniorBtn = nullptr;
    PVZ2UIButton* m_closeBtn = nullptr;
    TGButton* m_adBtn = nullptr;
    TGButton* m_adAvatarBtn = nullptr;
};

class TGPiece : public Sexy::Widget
{
public:
    TGPiece(int i_id, ButtonListener * btnListener, bool i_tutorial);
    ~TGPiece();
    
    virtual void Update();
    virtual void Draw(Graphics* i_g);
    virtual void Resize(const Rect& theRect);
    
    void InitView();
    void SetSelected(bool i_selected);
    
    int GetPieceId();
    int GetQuantity();
    
private:
    int m_pieceId = 0;
    int m_quantity = 0;
    
    bool m_tutorial = false;
    bool m_selected = false;
    
    PVZ2UIButton * m_btn = nullptr;
    
    Sexy::Rect m_rect;
    Sexy::Rect m_selectRect;
    Sexy::Rect m_quantityRect;
    Sexy::Image* m_avatarPieceImage;
};

class TGTableScrollPanel : public Widget, public ButtonListener
{
public:
    TGTableScrollPanel(Sexy::Rect &i_rect, bool i_tutorial);
    virtual ~TGTableScrollPanel();
    
//    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void InitView();
    void SelectPiece(int i_id);
    
    void OnAddToBox(int i_selectId, bool i_setSelected = true, bool i_dec = true);
    void OnRemoveFromBox(int i_removeId);
    
    TGPiece* GetTGPieceButtonId(int i_id);
    std::vector<TGPiece *> GetTGPiece();
    void RemoveLastSelect();
    
private:
    bool IsSelectedValid(int i_id);
    void SolveCurrentSelect(int i_selectId);
    
private:
    bool m_tutorial = false;
    int m_lastSelect = -1;
    Sexy::Rect m_widgetRect;
    std::vector<TGPiece *> m_pieceTable;
};

class TGPieceTableUI : public PopingWidget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    TGPieceTableUI();
    virtual ~TGPieceTableUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    // implement of Sexy::ScrollWidgetListener
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override;
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    virtual void InitView();
    void SetSelectBoxs(std::vector<int> seeds);
    virtual bool AddToSelectBoxs(int i_id);
    void AddPieceSummary(int i_rare, int i_quantity);
    std::vector<int> GetSelectedBoxIDs();
    
    void SetMinChips(int i_mc);
    void SetIsInTutorial(bool i_tutorial);
    
protected:
    void ClearSelectBoxs();
    virtual void InitSelectBoxs();
    void DrawSelectBoxs(Graphics* i_g);
    
    void ClearSummary();
    void InitSummary();
    void UpdateSummary();
    void DrawSummary(Graphics* i_g);
    virtual bool CanStartTrans();
    
    virtual void AutoSelecting();
    virtual void DeleteFromSelectBoxs(int i_index);
    int GetInsertIndex();
    virtual bool CanSelectBoxAdd();
    void TryReturnToTGMain();
    void RemoveWaste();
    virtual void ReturnToTGMain();
    
    virtual bool CheckWaste();
    void ShowWasteHint();
    virtual bool CheckIsHighValue();
    void ShowHighValueHint();
    void StartSelectTutorial();
    void StartSelectEndTutorial();
    
protected:
    bool m_inited = false;
    bool m_tutorial = false;
    
    int minChips = 2;
    
    std::vector<SelectBox *> m_selectBoxs;
    std::vector<RateOfRares *> m_summary;
    std::vector<PVZ2UIButton*> m_selectBoxBtns;
    
    SexyString m_title = _S("");
    
    Rect m_titleRect;
    Rect m_bannerBoarderRect;
    Rect m_bannerRect;
    Rect m_autoSelectRect;
    Rect m_tableRect;
    Rect m_tablePanelRect;
    Rect m_ratePanel;
    Rect m_closeBtnRect;
    
    PVZ2UIButton* m_autoSelect = nullptr;
    PVZ2UIButton* m_closeBtn = nullptr;
    
    PVZ2UIScrollingWidget * m_tablePanel = nullptr;
    TGTableScrollPanel* m_tablePanelWidget = nullptr;
};


class TGAvatarPieceTableUI : public TGPieceTableUI
{
public:
    virtual void Draw(Graphics* i_g) override;
    virtual void InitView() override;
    virtual void InitSelectBoxs() override;
    virtual bool CanStartTrans() override;
    virtual bool CanSelectBoxAdd() override;
    virtual bool CheckWaste() override;
    virtual bool CheckIsHighValue() override;
    virtual void ReturnToTGMain() override;
    virtual void AutoSelecting() override;
    virtual void DeleteFromSelectBoxs(int i_index) override;
};

class TransGenosisBlackList : public INetworkData
{
public:
	RT_CLASS_DEFINE(TransGenosisBlackList, INetworkData, RtClass);

    std::vector<int> m_blackList;
};

#endif /* TransgenosisUI_h */

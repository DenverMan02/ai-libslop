//
//  StoreUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StoreUI_h
#define PlantsVersusZombies2_StoreUI_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "MagentoService.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
//PVZ2_CHINESE_BEGIN
#include "Effect_BouncingArrow.h"
#include "socialInfo.h"
#include "NetworkData.h"
//PVZ2_CHIENSE_END

namespace Message
{
    void ShowNextRechargeNode();
    void GachaInitFinished();
//    void RefreshGemsStore();
    void CoinStoreClose();
}

enum StoreButtons
{
	STOREBUTTON_Close = -1,
	STOREBUTTON_Plant = 0,
	STOREBUTTON_Coins,
	STOREBUTTON_GEMS,
	STOREBUTTON_GIFT,
	STOREBUTTON_Upgrade,
	STOREBUTTON_Bundle,
    STOREBUTTON_PeripheryStore,
	STOREBUTTON_Merch = 100,
    
    STOREBUTTON_PlantBag = 1000, //PVZ2_CHINESE PlantBag
    STOREBUTTON_Restore  = 2000,
    STOREBUTTON_Treasure = 3000,

    STOREBUTTON_TIPS,
};

enum StoreTutorialState
{
	// These must be in the ORDER THAT THEY APPEAR. Do not place an end-game tutorial
	// in the beginning of this list...
	STORE_TUTORIAL_NONE,
	STORE_TUTORIAL_STORE_1,
    STORE_TUTORIAL_GACHA_1,
};

struct PlantBagItemData
{
	std::string PlantBagItemName;
	uint16		PlantBagItemWeight;
    MagentoProductPropsPtr   Plantprops;
    
	PlantBagItemData()
	{
        PlantBagItemName   = "";
        PlantBagItemWeight = 0;
	}
};

class StorePanelUI : public Sexy::Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	StorePanelUI(){}
	StorePanelUI(const Sexy::Rect& i_rect, const MagentoCategoryPropsPtr& i_category);
	~StorePanelUI();

	void AddComingSoonButtonIfNeeded();

    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* theFlags, Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

    virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override {}
    virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override {}
    
    //PVZ2_CHINESE_BEGIN
	void                    OnOK();
    void                    onLeafsCost(bool i_success);
	static void					OnServerGemCallBack(const bool& i_Success, MagentoProductPropsPtr theProps);

    static void OnServerGemCallBack_AndroidConvertIos(const bool& i_Success, MagentoProductPropsPtr i_props);
    static void OnServerGemCallBack_Gacha_AndroidConvertIos(const bool& i_Success, MagentoProductPropsPtr i_props);
    
    static void					PaySucess(MagentoProductPropsPtr theProps, bool i_alreadyGot = false);
    bool					IsGemStore();
    //PVZ2_CHINESE_END
	std::string m_panelName;
	std::vector<class PVZ2UIStoreItemDisplayer*> m_offerings;
    //PVZ2_CHINESE_BEGIN
    MagentoProductPropsPtr	m_tempPropsPtr;
    MagentoProductPropsPtr  m_pMagentoProductProps;

    //PVZ2_CHINESE_END
    
    //PVZ2_CHINESE_START PlantBag
private:
    void                    onCancel();
    void                    onRechargeNow();
    void                    OnNotifySyncActivityData(bool i_success);
    
    std::vector<PlantBagItemData> m_PlantWeights;
    int m_buttonId;
    class PVZ2UIDialog*	m_hintDialog;
    //PVZ2_CHINESE_END
};

class RechargeRewardDisplayer : public Sexy::Widget, public ButtonListener
{
public:
    RechargeRewardDisplayer(RechargeNode i_node);
    RechargeRewardDisplayer(bool bActivityReward, int iGemCount);
    ~RechargeRewardDisplayer();
    
    void GetRechargeRewardInfo(RechargeNode i_node);
    
    void ButtonDepress(int i_id);
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g);
    
private:
    Image* m_imgReward;
    SexyString m_strReward;
    SexyString m_strTitle;
    
    bool m_bActivityReward;
};

class RechargeProgress : public Sexy::Widget
{
public:
    RechargeProgress();
    ~RechargeProgress();
    
	void AddRechargeNode(RechargeNode i_node);
    Image* GetRechargeNodeItemImage(RechargeNode i_node);
    void ResetProgress();
    void onRechargeCurrencyChanged();
    void UnlockNextRechargeNode();
    void UnlockRandomPlant();
    
	virtual void Draw(Graphics* i_g) override;
private:
	std::vector<RechargeNode> m_rechargeNodes;
    float m_rechargeProgress;
};

class StoreGiftPanelUI : public StorePanelUI
{
public:
	StoreGiftPanelUI(const Sexy::Rect& i_rect, const MagentoCategoryPropsPtr& i_category);
	~StoreGiftPanelUI();

	virtual void Draw(Graphics* i_g) override;
	void RefreshItems();

	virtual void ButtonDepress(int i_id) override;
	void onPopRewardPressed();

private:
	std::vector<MagentoProductPropsPtr> m_vecGiftItems;
	std::vector<PVZ2UIStoreItemDisplayer*> m_vecItemDisplayers;

	int m_iProductCount;
    
    void onUseGemFinish(const bool& isSuccess);
    int m_buttonId = 0;
};

class StorePlantGiftPanelUI : public StorePanelUI
{
public:
	StorePlantGiftPanelUI(const Sexy::Rect& i_rect, const MagentoCategoryPropsPtr& i_category);
	~StorePlantGiftPanelUI();
    
	virtual void Draw(Graphics* i_g) override;
	void RefreshItems();
    
	virtual void ButtonDepress(int i_id) override;
    
private:
	std::vector<MagentoProductPropsPtr> m_vecGiftItems;
	std::vector<PVZ2UIStoreItemDisplayer*> m_vecItemDisplayers;
    
	int m_iProductCount;
};

class StoreUI : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:

	StoreUI(const std::string &i_focusPanel);
    virtual ~StoreUI();
    
    void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g) override;
    virtual void Update() override;
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override {}
    virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override {}
    
    //PVZ2_CHINESE_BEGIN
    void ShowPanel(const std::string &i_focusPanel);
    //PVZ2_CHINESE_END
    

private:
    //PVZ2_CHINESE_START PlantBag
    void onGetCoinsFromPlantBag();
    //PVZ2_CHINESE_END
	void onItemPurchasedFromStore(class MagentoProductProps* i_props);
	void removeItemFromStore(const std::string& i_objectType, const std::string& i_objectItem);
    //PVZ2_CHINESE_START
	void onBombUnlocked();
    void onPurchaseDialogClosed();
    void onGachaTutorialFinished();
    void OnPlantPackageBuy(class PlantPackage* pPackage);
	//PVZ2_CHINESE_END
	void createPanel(MagentoCategoryPropsPtr i_categoryProps);
    void InitMagento(const std::string &i_focusPanel);
    void OnGachaInitFinished();
    void InitADCount(const std::string& i_name);

	std::vector<MagentoCategoryPropsPtr> m_panelCategories;
	StorePanelUI* m_panel;
	class PVZ2UIScrollingWidget* m_scrollingWidget;

	StoreTutorialState					m_tutorialState;
	class BouncingArrow*				m_tutorialArrow;
	std::vector<class PVZ2UIButton*>	m_tabButtons;
	PVZ2UIButton*						m_closeButton;
    PVZ2UIButton*						m_PeripjeryStoreButton;
	//PVZ2UIButton*						m_merchButton;
    Image*                              m_tipsImg;
    
    int                                 m_shownCategoryIndex;
	//PVZ2_CHINESE_START
    bool                                m_unlockBomb;
    
    RechargeProgress*                   m_rechargeProgress;
    float                               m_dialogHeight;
    std::string                         m_focusPanel;
	//PVZ2_CHINESE_END
#ifdef HOST_ANDROID
	SexyString 							m_removeAdHint;
#endif
	bool								m_hasInit;
	int									m_adCount;
    bool                                m_removeADTips;
    
    void onGetGachaInfo(S2C_GachaInfo* info);
    void OnLuaNotify(const std::string& rLuaEvent);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void OnNetworkError(int erroId, const std::string& i_reqID);
    void onADFinished(int i_type);
};

//PVZ2_CHINESE_START
class CoinStore : public Sexy::Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	//PVZ2_CHINESE_START
	CoinStore(StoreType type = STORE_TYPE_COIN);
	//PVZ2_CHINESE_END
	virtual ~CoinStore();

    //PVZ2_CHINESE_BEGIN
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Update() override;
    //PVZ2_CHINESE_END
    
	virtual void Draw(Graphics* i_g) override;
    virtual void DrawOverlay(Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

    virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override {}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override {}
    
    void RefreshRechargeBanner();
    void AddRechargeNode(RechargeNode i_node);
    Image* GetRechargeBanner(RechargeNode i_node);
    
    //PVZ2_CHINESE_BEGIN
    void         EnableTutorial(bool i_enable);
    //PVZ2_CHINESE_END
    

private:
    static void PaySucess(MagentoProductPropsPtr i_props, StoreType i_storeType);
    static void OnServerGemCallBack(const bool& i_Success, MagentoProductPropsPtr i_props, StoreType i_storeType);

    static void OnServerGemCallBack_AndroidConvertIos(const bool& i_Success, MagentoProductPropsPtr i_props, StoreType i_storeType);
    static void OnServerGemCallBack_Gacha_AndroidConvertIos(const bool& i_Success, MagentoProductPropsPtr i_props, StoreType i_storeType);

	void onItemPurchasedFromStore(class MagentoProductProps* i_props);
	void onPurchaseDialogClosed();
    void onChangeAvatarSuccess(const std::string i_plantName);
	//PVZ2_CHINESE_START
    void onBombUnlocked();
    void onGemCurrencyAdd(int i_delta);
    void createPurchasePanel(MagentoCategoryPropsPtr i_categoryProps);
    void OnLuaNotify(const std::string& rLuaEvent);

	//PVZ2_CHINESE_END
    void InitCoinStore();
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void OnNetworkError(int erroId, const std::string& i_reqID);
    void ShowTipsDialog();
    
    void InitADCount();
    void onADFinished(int i_type);

private:
    SexyString                      m_titleString;
	int m_dialogWidth;
	int m_dialogHeight;
	MagentoCategoryPropsPtr m_storeProps;
	std::vector<class PVZ2UIStoreItemDisplayer*> m_offerings;
	//PVZ2_CHINESE_START
	StoreType                       mStoreType;
    class PVZ2UIScrollingWidget*    m_scrollingWidget;
    bool                            m_tutorialEnable;
    class BouncingArrow*            m_tutorialArrow;
    PVZ2UIButton*                   m_closeButton;
    PVZ2UIButton*					m_tipsButton;// store tips button
    Image*                          m_tipsImg;
    int                             m_nextRechargeCurrency;
    std::vector<RechargeNode>       m_rechargeNodes;
    
    bool                            m_unlockBomb;

    MagentoProductPropsPtr			m_cachePropPtr;//for server gem call back
	//PVZ2_CHINESE_END
    
    int                             m_buttonId;
#ifdef HOST_ANDROID
	SexyString 						m_removeAdHint;
#endif
	bool							m_hasInit;
    static int s_gemBeforePurchase;
    static int s_freeGemBeforePurchase;
    int								m_adCount;

    bool                            m_removeADTips;
};
//PVZ2_CHINESE_END

#endif

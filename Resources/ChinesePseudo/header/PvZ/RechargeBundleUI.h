//
//  RechargeBundleUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/12/6.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef RechargeBundleUI_h
#define RechargeBundleUI_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "RechargeBundleConfig.h"
#include "RechargeRewardConfig.h"
#include "RechargeRewardUI.h"
#include "NetworkData.h"
#include "GameCommon.h"

class ActiveItem;

//for oppo
#ifdef HOST_ANDROID
namespace Message
{
    void BundleBuy(const std::string& i_sku);
}
#endif

struct BundleUIDetail
{
    BundleDetail detail;
    int bundleTypeId;
    time_t expireTime = 0;
    int buyTimes = 0;
    std::string pushType;
    
    BundleUIDetail(const BundleDetail& i_detail, const int& typeId, const int& i_buyTimes, const time_t& i_expireTime, const std::string& pushCondition)
    {
        detail = i_detail;
        expireTime = i_expireTime;
        buyTimes = i_buyTimes;
        bundleTypeId = typeId;
        pushType = pushCondition;
    }
};

//================================================
//              BundlePieceWidget
//================================================
class BundlePieceWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    BundlePieceWidget(const std::string& type, const std::string& objectName, const int& quantity);
    virtual ~BundlePieceWidget();
    
    void Resize(int theX, int theY, int theWidth, int theHeight) override;
    void Draw(Graphics* i_g) override;
    
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void ButtonMouseLeave(int i_id) override;
    
private:
    std::string m_type;
    std::string m_objectName;
    int m_quantity;
    SexyString m_detailStr;
    
    PVZ2UIButton* m_detailButton;
    
    GAME_ITEM_INFO m_itemInfo;
};

//================================================
//              BundleDescWidget
//================================================
class BundleDescWidget : public Sexy::Widget
{
public:
    BundleDescWidget(const std::string& type, const SexyString& description, int rare = 0);
    virtual ~BundleDescWidget();
    
    int GetStringWidth();
    
    void Draw(Graphics* i_g) override;
    
private:
    ImagePtr m_iconImg;
    SexyString m_description;
};

//================================================
//              BundleDisplayWidget
//================================================
class BundleDisplayWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    enum
    {
        Bundle_Purchase,
    };
    BundleDisplayWidget(const BundleUIDetail& i_detail);
    virtual ~BundleDisplayWidget();
    
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void Resize(int theX, int theY, int theWidth, int theHeight) override;

    void Draw(Graphics* i_g) override;
    
    void RechargeBundleBeforePurchased(int objectId);
    virtual void RechargeBundlePurchased(int objectId);
    
    void SetIsDuplicateWidget(bool i_duplicate) { m_isDuplicateWidget = i_duplicate; }
    
    int getDisplayingObjectId() { return m_objectId; }
    
protected:
    void SetWidgetUIType(RechargeUIType type);
    SexyString getDescriptionById(int objectId, int quantity);
    MagentoProductPropsPtr GetProductByTypeAndPrice(int bundleTypeId, float price);
    
    PVZ2UIButton* m_purchaseButton;
    
    std::vector<BundleDescWidget*> m_descWidgets;
    
    ImagePtr m_bgImage;
    ImagePtr m_plantImage;
    
    RechargeUIType m_UIType;
    
    bool m_isDuplicateWidget = false;   //Duplicate widget is only used to create a circle scrolling effect, it won't receive message.
    
    Sexy::Point m_desStartPos;
    int m_bundleTypeId = 0;
    int m_objectId = 0;
    int m_price = 0;
    int m_originalPrice = 0;
    int m_discount = 1;
    int m_buyTimes = 0;
    
    std::string m_bundleType;
    
    time_t m_expireTime = 0;
    
    SexyString m_title = _S("");
    SexyString m_description = _S("");
    std::vector<S2C_BonusInfo> m_itemList;
    //for oppo
#ifdef HOST_ANDROID
	bool m_offeredBundle = false;
	ImagePtr m_offerBundleImage;
public:
	void RefreshBundle(const std::string& i_sku);
#endif
};

class EventBundleDisplayWidget: public BundleDisplayWidget
{
public:
	EventBundleDisplayWidget(const BundleUIDetail& i_detail);
	virtual ~EventBundleDisplayWidget();

	void Draw(Graphics* i_g) override;
    
    void RechargeBundlePurchased(int objectId) override;
    
    void RefreshUI(const std::vector<S2C_BonusInfo>& itemList);
    
protected:
	SexyString m_priceShow;
	SexyString m_timeLimit;
};

//================================================
//              BundleDisplayScrollWidget
//================================================
class BundleDisplayScrollWidget : public PVZ2UIScrollingWidget
{
public:
    BundleDisplayScrollWidget(Sexy::ScrollWidgetListener* i_listener);
    
    void disableManualScroll() { mScrollPractical = ScrollWidget::SCROLL_DISABLED; }
};

//================================================
//              RechargeBundleDotWidget
//================================================
class RechargeBundleDotWidget : public Sexy::Widget
{
public:
    RechargeBundleDotWidget(int dotsCount);
    void Draw(Graphics* i_g) override;
    void SetDotIndex(int i_index) { m_dotIndex = i_index; }
    
protected:
    int m_dotIndex;
    int m_dotsCount;
    
};

//================================================
//              RechargeBundleUI
//================================================

class RechargeBundleUI : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    enum
    {
        RechargeBundle_btnClose,
        RechargeBundle_scrollLeft,
        RechargeBundle_scrollRight,
    };
    
    RechargeBundleUI();
    virtual ~RechargeBundleUI();
    
    void createFromNetworkResponse();
    void onRechargeRewardCurrencyChanged(int num);
    
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void Update() override;
    void Draw(Graphics* i_g) override;
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    
    static void requestNetwork();
    static void refreshBundleConfig(class ActiveItem* i_item);
    
protected:
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    
private:
    void Init();
    
    void CreateNewBundle(RechargeBundleConfig* bundleData, int bundleTypeId, bool i_ignoreListCheck);
    
    void checkLogSendCondition();
    
    BundleDisplayWidget* CreateBundleDisplayWidget(const BundleUIDetail& i_detail);
    
    RechargeRewardProgress* m_rewardProgress;
    BundleDisplayScrollWidget* m_scrollingWidget;
    RechargeBundleDotWidget* m_dotWidget;
    
    std::vector<BundleUIDetail> m_bundleConfig;
    std::vector<int> m_bundleLogStatus;
    std::vector<EventBundleDisplayWidget*> m_eventBundleWidgets;
    
    Rect m_dialogRect;
    
    PVZ2UIButton* m_closeButton;
    PVZ2UIButton* m_scrollLeftButton;
    PVZ2UIButton* m_scrollRightButton;
    
    bool m_receivedResponse;
    bool m_focusOnQueuedBundle = false;
    
    pvztime_t m_autoScrollTimer = PVZ_EOT();
    int m_autoScrollCounter = 0;
    int m_totalBundleCount = 0;
    
    int m_currentRechargeAmount = 0;
    
//for oppo
#ifdef HOST_ANDROID
    std::vector<BundleDisplayWidget*> m_displayWidgets;
    void RefreshBundles(const std::string& i_sku);
    void OnBundleBuy(const std::string& i_sku);
#endif
};




#endif /* RechargeBundleUI_h */

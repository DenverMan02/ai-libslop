//
//  ZMatchShopDlg.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 2015.11.20.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ZMatchShopDlg_h_
#define _ZMatchShopDlg_h_

#include "UISingletonDialog.h"
#include "PlaybackData.h"
#include "NetworkData.h"


class ZMatchShopDlg;

enum  ZMatch_Type {
    ZMatch_Begin,
    ZMatch_Steal,
    ZMatch_Bronze,
    ZMatch_Silver,
    ZMatch_Gold,
    ZMatch_Emerald
};

enum Buy_type {
    Buy_gem,
    Buy_money
};

enum btn_buyTicket
{
    btn_buyClose = 0,
    btn_buyTicket_Gem,
    btn_buyTicket_one,
    btn_buyTicket_six
};

namespace Message
{
	void ZMatchShopItemBuyFinish(int objID, int leftZMatchCoin);
}

class ZShopItemWidget : public Sexy::Widget
{
public:
    ZShopItemWidget(ZMatchShopDlg* pZMatchShopDlg, ZMatch_Type type = ZMatch_Steal);
    virtual void			Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    void                    TouchBegan( const Sexy::Touch& i_touch ) override;
    void                    TouchEnded( const Sexy::Touch& i_touch ) override;

    void                    SetShopData(const ZMatchShopData& shopData);
    
    bool            GetIsUnLock() const; 

    void OnNotifyShopItemBuyFinish(int objID, int leftZMatchCoin);

    void  SetZMatchType(ZMatch_Type type);
public:

    ZMatchShopDlg*         m_pZMatchShopDlg;
    int32                   m_iScrollTouchID;
    ZMatchShopData              m_shopInfo;
    
    SexyString              m_strName;
    ImagePtr                m_shopImage;

    int                     m_itemType;
    std::string				m_plantPieceType;
    ZMatch_Type m_ZMatchType;
};


////////////////////////////////////////////////////////////////////////////////////
enum
{
    CONFIRM_REFRESH,
    CONFIRM_NOTENOUGH,
    CONFIRM_BUY,
    CONFIRM_LOCK
};

class ZShopConfirmDlg : public UISingletonDialog<ZShopConfirmDlg>
{
public:
    ZShopConfirmDlg();
    virtual ~ZShopConfirmDlg();
    virtual bool            OnCreate();
    virtual std::string     GetLayoutName() { return "ZMatchShopDlgRefreshConfirm"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void            Update();
    
    // ButtonListener
    virtual void            ButtonDepress(int i_id);
    
    void                    SetConfirm(int confirmState);
    void                    SetConfirmBuy(const ZMatchShopData& shopData, const SexyString& name);
    
    void 					onADFinished(int i_type);

    int                     m_confirmState;
    ZMatchShopData              m_shopInfo;
    SexyString              m_shopName;
};

////////////////////////////////////////////////////////////////////////////////////
#define Exchange_Item_Count     6

class ZMatchShopDlg : public UISingletonDialog<ZMatchShopDlg>
{
public:
    ZMatchShopDlg();
    virtual ~ZMatchShopDlg();
    virtual bool            OnCreate();
    virtual std::string     GetLayoutName() { return "ZMatchShopDlg"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void            Update();
    
    // ButtonListener
    virtual void            ButtonDepress(int i_id);
    
    void                    SetZMatchShopData();
    void                    BuyFinish(int32 objId);

    int     getMatchCoin() const;
    void    setMatchCoin(int matchCoin);
	void updateShopUI();

    void UpdateTimeLabel();
private:
    ZShopItemWidget*        m_pZShopItemWidget[Exchange_Item_Count];
    class UIWidgetText*     m_pTextCoin;
    class UIWidgetText*     m_pTextRefresTime;
    int m_nZMatchCoin;
    SexyString m_timeLebal;
    bool m_bIsAlreadyRefrash;
};



////////////////////////////////////////////////////////////////////////////////////
class ZMatchTicketShop : public UISingletonDialog<ZMatchTicketShop>
{
public:
	ZMatchTicketShop();
	virtual ~ZMatchTicketShop();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIBuyZKey"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
    void OnNotifyBuyZWatchTicket(bool i_success);
    void onUseGemFinish(const bool& isSuccess);

private:
    Buy_type m_curBuyType;
    int m_nBuyChallengesNum;
};


//-----------------------------------------------------------------
// ZMatchShopMgr
//-----------------------------------------------------------------
class ZMatchShopMgr : public LazySingleton<ZMatchShopMgr>
{
public:
	ZMatchShopMgr();
	virtual ~ZMatchShopMgr();

    void loadData(const ZMatch_ShopData& shopData);

    const ZMatch_ShopData& getZMatchShopData() const;

    int getRefrashZMShopCost();
    int getAfterRefreshCost();

    void setCurBuyCost(int curCost);
    int getCurBuyCost() const;

    void BuyFinish(const S2C_BuyZMatchShopData& itemData);

    void setMatchTicket(int matchTicket);
    void addMatchTicket(int matchTicket);
    void SubtractMatchTicket(int matchTicket = 1);
    int getMatchTicket() const;
    void OnNotifyBuyZWatchTicket(bool i_success);
    void onUseGemFinish(const bool& isSuccess);
    
    void BuyTicket(btn_buyTicket i_type);

private:
    ZMatch_ShopData m_shopData;
    int m_nCurBuyCost;
    int m_nZMatchTicket;
    Buy_type m_curBuyType;
    int m_nBuyChallengesNum;
};

#endif

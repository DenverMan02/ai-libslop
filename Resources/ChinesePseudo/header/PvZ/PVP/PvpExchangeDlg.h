//
//  PvpExchangeDlg.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 2015.11.20.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _PvpExchangeDlg_h_
#define _PvpExchangeDlg_h_

#include "UISingletonDialog.h"
#include "PlaybackData.h"
#include "NetworkData.h"


class PvpExchangeDlg;

class ExchangeItemWidget : public Sexy::Widget
{
public:
    ExchangeItemWidget(PvpExchangeDlg* pPvpExchangeDlg);
    virtual void			Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    void                    TouchBegan( const Sexy::Touch& i_touch ) override;
    void                    TouchEnded( const Sexy::Touch& i_touch ) override;

    void                    SetShopData(const PVPCUPData& shopData);
    
    PvpExchangeDlg*         m_pPvpExchangeDlg;
    int32                   m_iScrollTouchID;
    PVPCUPData              m_shopInfo;
    
    SexyString              m_strName;
    ImagePtr                m_shopImage;

    std::string				m_plantPieceType;
};


////////////////////////////////////////////////////////////////////////////////////
enum
{
    CONFIRM_REFRESH,
    CONFIRM_NOTENOUGH,
    CONFIRM_BUY,
};

class PvpExchangeConfirmDlg : public UISingletonDialog<PvpExchangeConfirmDlg>
{
public:
    PvpExchangeConfirmDlg();
    virtual ~PvpExchangeConfirmDlg();
    virtual bool            OnCreate();
    virtual std::string     GetLayoutName() { return "PvpExchangeRefreshConfirm"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void            Update();
    
    // ButtonListener
    virtual void            ButtonDepress(int i_id);
    
    void                    SetConfirm(int confirmState);
    void                    SetConfirmBuy(const PVPCUPData& shopData, const SexyString& name);
    
    int                     m_confirmState;
    PVPCUPData              m_shopInfo;
    SexyString              m_shopName;
};

////////////////////////////////////////////////////////////////////////////////////
#define Exchange_Item_Count     6

class PvpExchangeDlg : public UISingletonDialog<PvpExchangeDlg>
{
public:
    PvpExchangeDlg();
    virtual ~PvpExchangeDlg();
    virtual bool            OnCreate();
    virtual std::string     GetLayoutName() { return "PvpExchange"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void            Update();
    
    // ButtonListener
    virtual void            ButtonDepress(int i_id);
    
    void                    SetPvpShopData();
    void                    BuyFinish(int32 objId);
    
private:
    ExchangeItemWidget*     m_pExchangeItemWidget[Exchange_Item_Count];
    class UIWidgetText*     m_pTextCoin;
    class UIWidgetText*     m_pTextRefresTime;
    
};


#endif

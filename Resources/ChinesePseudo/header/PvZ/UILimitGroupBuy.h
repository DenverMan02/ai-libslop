#ifndef UILIMITGROUPBUY_H
#define UILIMITGROUPBUY_H

#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"

struct LimitGroupBuyItemInfo
{
    int BonusId = 0;
    int Quantity = 0;
    int Type = 0;
    int Discount = 0;
    int Cost = 0;
};

class LimitGroupBuyInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(LimitGroupBuyInfo, INetworkData, RtClass);

    std::vector<NDLoginRewardBonus> Notice;
    std::vector<LimitGroupBuyItemInfo> ItemVoteList;
    std::vector<LimitGroupBuyItemInfo> ItemList;
    int DaveTicket;
    int ResourceId;
};

class LimitGroupBuyGridItemUIButton : public PVZ2UIButton
{
public:
	LimitGroupBuyGridItemUIButton(int i_id, Sexy::ButtonListener* i_listener);
    virtual ~LimitGroupBuyGridItemUIButton();

    virtual void Resize(const Rect& theRect) override;
    virtual void Draw(Graphics* i_g) override;

    void setText(const SexyString& i_cost){
        m_daveCost = i_cost;
    }
    void setImage(ImagePtr i_image){
        m_ptrImage = i_image;
    }
    void setFont(Sexy::PrimeTypeface* i_font){
        m_font = i_font;
    }
private:
    SexyString m_daveCost = _S("");
    Rect m_daveCostRect;
    ImagePtr m_ptrImage;
    Sexy::PrimeTypeface* m_font;
	Rect m_imageRect;
    int m_btnId;
};

class LimitGroupBuyGridItem : public Widget, public ButtonListener
{
public:
    LimitGroupBuyGridItem();
    virtual ~LimitGroupBuyGridItem();

    virtual void                        Draw(Sexy::Graphics* i_g) override;
    virtual void                        ButtonDepress(int i_id) override;

    ImagePtr                            LevelCornerMark(int i_level);
    ImagePtr                            RareBackgroundImage(int i_rare);
    void                                EnableEasyStyle(){ m_isEasyStyle = true; };
    void                                LoadData(const LimitGroupBuyItemInfo& i_itemInfo);
    const LimitGroupBuyItemInfo&        GetInfo(){ return m_itemInfo; };

protected:
    LimitGroupBuyItemInfo       m_itemInfo;
    SexyString                  m_title;
    ImagePtr                    m_background;
    Rect                        m_itemRect;
    ImagePtr                    m_itemImage;
    Rect                        m_levelRect;
    ImagePtr                    m_levelImage;
    SexyString                  m_quantity;
    Rect                        m_quantityRect;
    SexyString                  m_description;
    Rect                        m_descriptionRect;
    bool                        m_isEasyStyle;
    bool                        m_isPlantChip;
    std::string                 m_bonusName;
    PVZ2UIButton*               m_submit = nullptr;
};

class ShowVotingGridItem : public Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    void Init(const LimitGroupBuyItemInfo& data);
private:
    SexyString                  m_title;
    SexyString                  m_description;
    ImagePtr                    m_plantImage;
    ImagePtr                    m_background;
};

class VotedDisplayUI : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();

private:
    PVZ2UIButton* m_closeButton;
};

class UILimitGroupBuyConfirm : public UISingletonDialog<UILimitGroupBuyConfirm>
{
public:
    UILimitGroupBuyConfirm();
    virtual ~UILimitGroupBuyConfirm();

    virtual bool                    OnCreate() override;
    virtual std::string             GetLayoutName() override { return "UIConfirmBuy"; }
    virtual void					ButtonDepress(int i_id) override;
    void                            LoadData(const LimitGroupBuyItemInfo& i_itemInfo, SexyString str);
private:
    void							OnLimitGroupBuyExchange(bool success, const S2C_ShopItemPurchaseInfo* pData); 

    LimitGroupBuyItemInfo           m_itemInfo;
};

class UILimitGroupShowReward : public UISingletonDialog<UILimitGroupShowReward>
{
public:
     UILimitGroupShowReward();
    virtual ~UILimitGroupShowReward();

    virtual bool                    OnCreate() override;
    virtual std::string             GetLayoutName() override { return "UILimitGroupBuyReward"; }
    virtual void					ButtonDepress(int i_id) override;
    void                            LoadData(int i_id,int i_quantity);
    void                            SetTitle(SexyString str);
};

class UILimitGroupBuyDiscount : public UISingletonDialog<UILimitGroupBuyDiscount>
{
public:
    UILimitGroupBuyDiscount();
    virtual ~UILimitGroupBuyDiscount();

    virtual bool                    OnCreate() override;
    virtual void			        Update() override;
    virtual std::string             GetLayoutName() override { return "UILimitGroupBuyDiscount"; }
    virtual void					ButtonDepress(int i_id) override;

    void                            UpdateTimerLabel();
    void                            LoadData(const LimitGroupBuyItemInfo& i_itemInfo);
private:
    void							OnLimitGroupBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData); 
private:
    LimitGroupBuyItemInfo           m_itemInfo;
    PVZ2UIButton*                   m_submit = nullptr;
};

class UILimitGroupBuyNotice : public UISingletonDialog<UILimitGroupBuyNotice>
{
public:
    UILimitGroupBuyNotice();
	virtual ~UILimitGroupBuyNotice();

	virtual bool	                OnCreate() override;
    virtual std::string             GetLayoutName() override { return "UILimitGroupBuyNotice"; }
	virtual void					ButtonDepress(int i_id) override;
    void							ShowWindow();
};

class UILimitGroupBuy : public UISingletonDialog<UILimitGroupBuy>
{
public:
    UILimitGroupBuy();
	virtual ~UILimitGroupBuy();

	virtual bool	                OnCreate() override;
    virtual std::string             GetLayoutName() override { return "UILimitGroupBuy"; }
	virtual void				    Draw(Sexy::Graphics* i_g) override;
	virtual void					DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void					Update() override;
	virtual void					ButtonDepress(int i_id) override;

    void                            UpdateTimer();
    void                            UpdateTicket();
    void							ShowWindow();
	void							InitView();
    void							OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
	void 							Refresh(bool i_close = false);

    void                            ShowVotedDisplay();
    void                            CloseVotedDisplay();

private:
    Widget*                             m_mainPanel;
    std::vector<LimitGroupBuyGridItem*> m_itemList;
    LimitGroupBuyInfo                   m_info;
    VotedDisplayUI*                     m_votedDisplay;
};

class LimitGroupBuyManager : public LazySingleton<LimitGroupBuyManager>
{
public:
    LimitGroupBuyManager();
    virtual ~LimitGroupBuyManager();

    void AddDaveTicket(int i_charge);
    void SynchronizeGroupBuyRecord();
};

namespace Message{
    void ShowRewardFinish();
}

#endif
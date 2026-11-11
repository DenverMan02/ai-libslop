//
//  UIUtil.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/7/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIUtil_h
#define UIUtil_h

#include "UIWidgetType.h"
#include "Precompile.h"
#include "RtDelegate.h"
#include "UIRewardFrame.h"
#include "UIScrollWidget.h"
#include "UISingletonDialog.h"
#include "PopingWidget.h"

namespace Sexy
{
    class Graphics;
    class Widget;
}

class PopAnimRig;

class UIUtil
{
public:
    //for UI Editor
    template<typename T>
    static void SetChildrenIgnoreMouseInput(Sexy::Widget* widget,bool ignore)
    {
        if (widget == nullptr)
        {
            return;
        }
        
        for (auto w : widget->mWidgets)
        {
            if (w->mWidgetType == WidgetFactory<T *>::GetTypeName())
            {
                w->SetIgnoreMouseInput(ignore);
            }
            SetChildrenIgnoreMouseInput<T>(w,ignore);
        }
    }
    
    static void DrawPopAnim(Sexy::Graphics *g,PopAnimRig* anim,int x,int y,float scale = 1.0f,float anchorPointX = 0.5f,float anchorPointY = 0.5f);
    
    static void SetPopAnimTransform(PopAnimRig* anim,int x,int y,float scale = 1.0f,float anchorPointX = 0.5f,float anchorPointY = 0.5f);

    static void ShowDialog(Widget* i_widget);
    static void CloseDialog(Widget* i_widget);
};

#pragma mark - CommonRewardItemData

struct CommonRewardItemData
{
    int ItemId;
    int Amount;
    int CurrencyId;
    int Price;
    int Purchases;

    CommonRewardItemData()
    :Purchases(-1)
    {

    }
};

#pragma mark - CommonRewardItemWidget
//通用的商店内商品Item界面
class CommonRewardItemWidget : public Sexy::Widget
{
public:
    typedef Delegate1<const CommonRewardItemData&> TouchEndDelegate;

    CommonRewardItemWidget();
    virtual ~CommonRewardItemWidget();

    virtual void            TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void            TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;

    virtual void            LoadData(const CommonRewardItemData& i_data);
    void                    RegisterTouchCallBackFunc(TouchEndDelegate i_delegate);

    void                    SetCurrencyImage(Sexy::Image* i_image);
    int                     GetItemId();
    void                    SetSoldOut(bool i_flag);
    void                    SetUnlock(bool unlock) { m_isUnlock = unlock; }
    void                    SetBgImageRare(bool isPlant, int rare = 1);

protected:
    virtual void                    init();

    int                     m_touchId;
    CommonRewardItemData    m_data;
    Rect                    m_rewardRect;
    SexyString              m_rewardName;
    Sexy::Image*            m_rewardImage;
    Sexy::Image*			m_headshotFrame1;
    Sexy::Image*			m_headshotFrame2;
    Sexy::Image*            m_currencyImage;
    int                     m_rewardType;
    std::string             m_bonusName;
    bool                    m_soldOut;
    TouchEndDelegate        m_touchEnd;
    bool                    m_isUnlock;// if this widget is lock

    Sexy::Image*            m_BgImage;
};


#pragma mark - TextScollingWidget
//可滑动的文字框
class TextScollingWidget : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    TextScollingWidget();
    ~TextScollingWidget();

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Resize(int theX, int theY, int theWidth, int theHeight) override;
    
    void SetString(SexyString i_sexyString, class Sexy::PrimeTypeface* i_font);
    void SetStringExtra(SexyString i_sexyStringExtra, class Sexy::PrimeTypeface* i_fontExtra);
    void SetStringColor(const Color& i_color);

private:
    void Refresh();

    ScrollWidget::ScrollMode m_scrollMode;
    Widget* m_container;
    class UIWidgetText* m_textWidget;
    class UIWidgetText* m_textWidgetExtra;
    class PVZ2UIScrollingWidget* m_scrollingWidget;
};

#pragma mark - ActivityDescriptionUI
//活动规则提示框
class ActivityDescriptionUI : public Widget, public ButtonListener
{
public:
    ActivityDescriptionUI();
    virtual ~ActivityDescriptionUI();
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void RegisterTouchCallBackFunc(Sexy::Delegate0 i_delegate);

    void SetFont(class Sexy::PrimeTypeface* i_font) { m_cacheFont = i_font; }

    void InitView(const SexyString& i_des, const SexyString& i_title);
    void InitView(const SexyString& i_des, const SexyString& i_desExtra, const SexyString& i_title);

private:
    SexyString m_title;
    Sexy::Delegate0 m_buttonOK;
    TextScollingWidget* m_scollWidget;
    Sexy::PrimeTypeface* m_cacheFont = nullptr;
};

class ActivityDescriptionManager : public LazySingleton<ActivityDescriptionManager>
{
public:
    ActivityDescriptionManager();
    virtual ~ActivityDescriptionManager();

    ActivityDescriptionUI* ShowDescription(const SexyString& i_des, const SexyString& i_title);
    void CloseDescription();
private:
    ActivityDescriptionUI* m_descriptionUI;
};

#define gActivityDescriptionManager (ActivityDescriptionManager::GetInstancePtr())


#pragma mark - TinyRewardDisplayUI
//单个奖励的展示界面
class TinyRewardDisplayUI : public Widget, public ButtonListener
{
public:
    static TinyRewardDisplayUI* ShowDialog(int i_itemID, int i_quantity, const SexyString& i_title = _S(""), const SexyString& i_subTitle = _S(""));
    static void CloseDialog();
private:
    static TinyRewardDisplayUI* s_ptr;
public:
    TinyRewardDisplayUI();
    virtual ~TinyRewardDisplayUI();
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView(int i_itemID, int i_quantity, const SexyString& i_title = _S(""), const SexyString& i_subTitle = _S(""));
    void SetTextLabel(const SexyString& i_title, const SexyString& i_subTitle = _S(""));
    void SetCallBack(std::function<void()> i_callBack);

private:
    int Id;
    SexyString m_title;
    SexyString m_subtitle;
    SexyString m_description;
    std::function<void()> m_callBack;
};


#pragma mark - UIRewardFrameSelect
//可以点击的RewardFrame
class UIRewardFrameSelect : public UIRewardFrame
{
public:
    static UIRewardFrameSelect* CreateUIRewardFrame(int objectId, int num, bool hasFrame);
    static UIRewardFrameSelect* CreateUIRewardFrame(UIRewardFrameSelect* i_copy);

    void SetSelectDescription(SexyString sexyStr);
    SexyString GetSelectDescription() { return m_des; }

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void TouchesCanceled() override;

public:
    UIRewardFrameSelect(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
private:
    int m_touchId;
    SexyString m_des;
    class StoneLotteryItemTipUI* m_tipUI;
};


#pragma mark - TouchWidget
//按下时展现信息
class TouchWidget : public Widget
{
public:
    TouchWidget();
    ~TouchWidget();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void TouchesCanceled() override;

    virtual void UpdateTouchInfo();

    void SetTouchDescription(const SexyString& i_sexyString);
    void SetTouchDescription(const std::string& i_string);
    void SetDisplayScale(float i_scaleX, float i_scaleY);

    class StoneLotteryItemTipUI* GetTipUI() { return m_tipUI; }

protected:
    int m_touchId;
    SexyString m_des;
    class StoneLotteryItemTipUI* m_tipUI;
    float m_scaleX;
    float m_scaleY;
};

#pragma mark - UtilEasyDisplayWidget
//带有点击和绘制回调的简单界面
class UtilEasyDisplayWidget : public Widget
{
public:
    UtilEasyDisplayWidget();
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void Draw(Graphics* i_g) override;

    void SetDrawFunction(std::function<void(Graphics*)> i_func) { m_drawfunc = i_func; }
    void SetTouchFunction(std::function<void()> i_func) { m_touchfunc = i_func; }

private:
    int m_touchId;
    std::function<void()> m_touchfunc;
    std::function<void(Graphics*)> m_drawfunc;
};

#pragma mark - MoreOptionsShopItem

class MoreOptionsShopItem  : public UISingletonDialog<MoreOptionsShopItem>
{
public:
    MoreOptionsShopItem();
    ~MoreOptionsShopItem();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "MoreOptionsShopItem"; }
    void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int theId) override;

    void SetTitle(const SexyString& i_sexyString);
    void SetTitle(const std::string& i_string);
    void SetItemBottom(const SexyString& i_sexyString);
    void SetItemBottom(const std::string& i_string);

    void SetData(int i_itemNum1, int i_currencyNum1, int i_itemNum2, int i_currencyNum2);
    void SetMaterial(int i_materialID);
    void SetMaterial(Sexy::Image* i_materialImg);
    void SetItemId(int i_itemID, Sexy::Image* i_itemImg = nullptr);

    void SetPressBuyOne(std::function<void()> i_func) { m_pressBuyOne = i_func; }
    void SetPressBuyMore(std::function<void()> i_func) { m_pressBuyMore = i_func; }

protected:
    std::function<void()> m_pressBuyOne;
    std::function<void()> m_pressBuyMore;

};


#pragma mark - PopingBonusUI

//弹出式奖励
class PopingBonusUI : public PopingWidget, public ButtonListener
{
public:
	PopingBonusUI();
    ~PopingBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    void InitBonus(const std::vector<std::pair<int,int>>& i_bonus);
    void SetCloseFuction(std::function<void()> i_func) { m_closeFunction = i_func; }
private:
    void InitShiningAnims();
private:
    int m_bonusStartX;
    int m_bonusStartY;
    int m_bonusWidth;
    int m_bonusHeight;

    Rect m_titleImgRect;
    Rect m_titleRect;
    SexyString m_title = _S("");

    Rect m_bonusRect;
    
    Rect m_submitRect;
    PVZ2UIButton* m_submit = nullptr;
    std::vector<class UIRewardFrameSelect*> m_vecBonus;

    class EffectAnim_UIAnim* m_openAnimRig;
    class EffectAnim_UIAnim* m_backAnimRig;

    std::function<void()> m_closeFunction;
};


#pragma mark - CommonRewardDisplay
//仿照UIRedpacket的奖励展示页面
class CommonRewardDisplay  : public UISingletonDialog<CommonRewardDisplay>, public Sexy::ScrollWidgetListener
{
public:
    CommonRewardDisplay();
    ~CommonRewardDisplay();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "CommonRewardDisplay"; }
    void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int theId) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void AddItemWidget(Widget* i_widget);
    void SetCloseFuction(std::function<void()> i_func) { m_closeFunction = i_func; }
    void SetTitle(const SexyString& i_title);

private:
    int m_contentNumber;
    class PVZ2UIScrollingWidget* m_mainScroll;
    std::function<void()> m_closeFunction;
};

#pragma mark - EmptyDialog
//空的用来阻挡输入的界面
class EmptyDialog  : public UISingletonDialog<EmptyDialog>
{
public:
    std::string GetLayoutName() override { return "EmptyDialog"; }
};

#pragma mark - AdaptiveMessageBox
//能够自动调节大小，展示一个Widget的MessageBox,带有确定和取消按钮
class AdaptiveMessageBox : public UISingletonDialog<AdaptiveMessageBox> 
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "AdaptiveMessageBox"; }
    virtual void ButtonDepress(int theId) override;

    void SetContentWidget(Widget* i_widget);
    void SetConfirmFunction(std::function<void()> i_func){ m_confirmFunction = i_func; }
    void SetCloseFunction(std::function<void()> i_func){ m_closeFunction = i_func; }

private:
    void AdaptiveAdjust(int i_widthAddition, int i_heightAddition);

    Widget* m_contentWidget;
    std::function<void()> m_confirmFunction;
    std::function<void()> m_closeFunction;
};

class QuickButton : public PVZ2UIButton
{
public:
    QuickButton();
    QuickButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);

	virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void SetDepressFunction(std::function<void(int)> i_func) { m_depressFunction = i_func; }

protected:
    std::function<void(int)> m_depressFunction;
};


#endif /* UIUtil_h */

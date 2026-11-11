//
//  ChildrenDayUI.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/5/3.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef ChildrenDayUI_h
#define ChildrenDayUI_h

#include "UISingletonDialog.h"
#include "Image.h"
#include "TimeMgr.h"
#include "NetworkMsgProcess.h"
#include "EffectAnim_UIAnim.h"
#include "PVZ2UIButton.h"

namespace Message
{
    void CheatChildrenDayNextItem();
}


class ChildrenDayUI : public UISingletonDialog<ChildrenDayUI>
{
private:
    class ItemData
    {
    public:
        int id = 0;
        int count = 0;
    };
    
    class ItemListButton : public PVZ2UIButton
    {
    public:
        ItemListButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
        ~ItemListButton();
        void TouchBegan(const Sexy::Touch& touch) override;
        void TouchEnded(const Sexy::Touch& touch) override;
        void Draw(Sexy::Graphics* i_g) override;
        void Update() override;
        void Resize(int theX, int theY, int theWidth, int theHeight) override;
    private:
        const float BlinkInterval = 5;
        pvztime_t m_nextListBlink = 0;
        EffectAnim_UIAnim m_listButton;
    };
    
    class BuyButton : public PVZ2UIButton
    {
    public:
        BuyButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
        ~BuyButton();
        void PlaySelect();
        void TouchBegan(const Sexy::Touch& touch) override;
        void TouchEnded(const Sexy::Touch& touch) override;
        void Draw(Sexy::Graphics* i_g) override;
        void Update() override;
        void Resize(int theX, int theY, int theWidth, int theHeight) override;
    private:
        EffectAnim_UIAnim m_buyButton;
    };
public:
    void Update() override;
    ChildrenDayUI();
    virtual ~ChildrenDayUI();
     bool							OnCreate() override;
     std::string				GetLayoutName() override { return "ChildrenDay"; }
    void							Draw(Sexy::Graphics* i_g) override;
    // ButtonListener
     void							ButtonDepress(int i_id) override;
    void			                        ButtonPress(int i_id) override;
    void                                SetCurrentIndex(int index);
private:
    void InitItemList();
    void SetItem(int index, int item, float price, int count);
    void SetTimeLeft(int second);
    void SelectItem(int item);
    void SetBuyCount(int left, int total);
    void DisableUnclickableWidget();
    void Refresh();
    void GetChildrenDayReturn(const class ChildrenDayStates* info);
    void CloseActivity();
    int GetRefeshCount();
    void SetRefreshCount(int count);
    void SaveNextRefreshTime(time_t time);
    void RequestRefresh();
    int GetBuyCount();
    void OnRequestCharge(const std::string& sku, ParaMap* para);
    void OnConfirmChildDayItem(const std::vector<ChildrenDayItem>& item);
    void ShowTip(const SexyString& tip);
    time_t GetNextRefreshTime();
    time_t CalcNextRefreshTime(time_t currentTimej, int interval);
    Widget* GetItem(int index);
    ImagePtr GetImgPtrFromObjectId(int i_objectId);
    void InitBuyButton();
    void InitListButton();
    std::vector<ItemData> RemoveRepeateItem(const std::vector<ItemData>& src);
    void OnCheatChildrenDayNextItem();
private:
    bool m_requestRefresh = false;
    int m_buyLimit = 0;
    int m_selectItem = -1;
    pvztime_t m_nextRefreshLocal = 0;
    std::vector<int> m_itemDataOnSale;
    std::vector<ItemData> m_itemListData;
    UIWidgetImage* m_itemListWidet = nullptr;
    ItemListButton* m_listButton = nullptr;
    BuyButton* m_buyButton = nullptr;
};


#endif /* ChildrenDayUI_h */

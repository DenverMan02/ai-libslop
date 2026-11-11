
#ifndef UINewPlayerCollectionExtra_H_
#define UINewPlayerCollectionExtra_H_

#include "UIActivityCollectionExtra.h"
#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"


struct NewPlayerSignItemData
{
    int objectId;
    int quantity;
    int obtained;
};

class NewPlayerSignData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPlayerSignData, INetworkData, RtClass);

    std::vector<NewPlayerSignItemData> RewardList;
    int TodayObtaind;
    int SignDays;
};


class NewPlayerSignItemWidget : public Widget
{
public:
    virtual void Draw(Graphics* i_g) override;

    void InitView(int i_index, NewPlayerSignItemData i_bonus);
    void SetObtained(bool i_flag);

private:
    int m_index;
    int m_obtained;

    Sexy::Image* m_background;
    SexyString m_title;
    Sexy::Image* m_contentImage;
    Sexy::Rect m_contentRect;
    SexyString m_name;
    Sexy::Rect m_nameRect;
    SexyString m_number;
    Sexy::Rect m_numberRect;
};

class ActivityCollectionNewPlayerSign : public ActivityCollectionContainerBase
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void Sign();
    virtual SexyString GetLockDesc() override;
private:
    PVZ2UIButton* m_signBtn = nullptr;
    NewPlayerSignItemWidget* m_itemWidget = nullptr;
};

class UINewPlayerSignPreview : public UISingletonDialog<UINewPlayerSignPreview>, public Sexy::ScrollWidgetListener
{
public:

    virtual bool OnCreate() override;
    virtual void OnClose() override;
    virtual std::string GetLayoutName() override { return "UINewPlayerSignPreview"; }
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(const std::vector<int>& i_plantList);
    void SwitchPlant(int i_buttonId, int i_plantId);

    std::vector<int> FillPlantList(NewPlayerSignData data);

private:
    bool m_hasChanged = false;
    PlantTypePtr m_plantType;
    SexyString m_plantName;
    class PopAnimRig*  m_pAnimRig = nullptr;
    class PlantDisplayBoard* m_plantDisplay = nullptr;
    std::vector<class QuickButton*> m_buttonList;
    std::vector<class UIWidgetImage*> m_selectedList;
};




class ActivityCollectionNoviceSevenDays : public ActivityCollectionContainerBase
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    virtual SexyString GetLockDesc() override;
};



class NewPlayerDiscountShopData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPlayerDiscountShopData, INetworkData, RtClass);

    std::vector<std::vector<S2C_BonusInfo>> RewardList;
    std::vector<int> Price;
    std::vector<int> Limit;
};

class NewPlayerDiscountShopItem : public Widget, public Sexy::ButtonListener
{
public:
    NewPlayerDiscountShopItem();
    ~NewPlayerDiscountShopItem();

    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g) override;
    void Init(int i_index, int i_price, int i_limit, const std::vector<S2C_BonusInfo>& i_bonus);
    void Refresh();
    void BuyConfirm(class UIMessageBox* box, int buttonID);

private:
    int m_index;
    int m_price;
    int m_limit;
    SexyString m_name;
    PVZ2UIButton* m_buyButton;
    Rect m_bgRect;
};

class ActivityCollectionNewPlayerDiscountShop : public ActivityCollectionContainerBase
{
public:
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    virtual SexyString GetLockDesc() override;
};




class ActivityCollectionPennyClassroom : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    virtual SexyString GetLockDesc() override;
};




class NewPlayerSpecialGiftData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPlayerSpecialGiftData, INetworkData, RtClass);

    std::vector<std::vector<S2C_BonusInfo>> RewardList;
    std::vector<int> ObtainState;
    int CurrentDay;
    int Privilege;
};

class NewPlayerSpecialGiftItem : public Widget, public Sexy::ButtonListener
{
public:
    NewPlayerSpecialGiftItem();
    ~NewPlayerSpecialGiftItem();

    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    void Init(int i_index, bool i_canObtain, const std::vector<S2C_BonusInfo>& i_bonus, NewPlayerSpecialGiftData data);
    void Refresh();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    
private:
    int m_index;
    bool m_canObtain;
    SexyString m_name;
    PVZ2UIButton* m_obtainButton;
    NewPlayerSpecialGiftData m_cacheData;
};


class ActivityCollectionNewPlayerSpecialGift : public ActivityCollectionContainerBase
{
public:
	ActivityCollectionNewPlayerSpecialGift();

    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    virtual SexyString GetLockDesc() override;

    void Refresh();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    NewPlayerSpecialGiftData m_cacheData;
private:
    PVZ2UIButton* m_buyButton;
	bool m_thisRequest;
};




#endif

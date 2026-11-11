#ifndef UI_GROWTH_PACKAGE_H
#define UI_GROWTH_PACKAGE_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"
#include "RepeatUIComponent.h"
#include "functional"

struct GrowthPackageReward
{
    int Part;
    int Obtained;
    std::vector<S2C_BonusInfo> Rewards;
};

class GrowthPackageData : public INetworkData
{
public:
	RT_CLASS_DEFINE(GrowthPackageData, INetworkData, RtClass);

    int                                         Integral;
    std::vector<int>                            BundleLimit;
    std::vector<std::vector<S2C_BonusInfo>>     BundleList;
    std::vector<GrowthPackageReward>            RewardList;
    std::vector<S2C_BonusInfo>                  RequestReward;
};


class GrowthPackageBundle : public Widget, public ButtonListener
{
public:
    GrowthPackageBundle();
    ~GrowthPackageBundle();
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitData(int i_index, const std::vector<S2C_BonusInfo>& i_list, int i_limit);
    void OnBuyGrowthPackage(int i_index);
private:
    int m_index;
    int m_limit;
    class PVZ2UIButton* m_purchaseButton;
};

class GrowthPackageRewardButton : public Widget
{
public:
    GrowthPackageRewardButton();
    virtual ~GrowthPackageRewardButton();
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;

    void InitData(int i_index, bool i_obtained, int i_target);
    void UpdateButtonState(int i_target);
protected:
    void RequestReward();

    int m_index;
    bool m_obtained;
    int m_target;
    int32 m_iTouch;
};

class UIGrowthPackage : public UISingletonDialog<UIGrowthPackage>
{
public:
    UIGrowthPackage();
    virtual ~UIGrowthPackage();
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIGrowthPackage"; }
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void AddIntegral(int i_add);
    void ObtainReward(int i_index);
    void RefreshProgressBar();
    int GetIntegral(); 
private:
    void InitBundle();
    void InitReward();

    GrowthPackageData m_cacheData;
    std::vector<GrowthPackageRewardButton*> m_vecRewardButton;
};



#endif
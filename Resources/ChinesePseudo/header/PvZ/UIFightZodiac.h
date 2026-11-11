#ifndef UIFightZodiac_H
#define UIFightZodiac_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"
#include "Curve.h"
#include "PlantSpecialOffer.h"

class ProgressDisappear : public Widget
{
public:
    ProgressDisappear();

    void StartEffect(pvztime_t i_rate, pvztime_t i_delay);

    void Draw(Graphics* i_g) override;
    virtual void Update() override;

private:
    IntCurve m_curve;
    Color m_color;
    int m_offsetY;
};

class UIFightZodiacIntro : public UISingletonDialog<UIFightZodiacIntro>
{
public:
    UIFightZodiacIntro();
    virtual ~UIFightZodiacIntro();
    bool OnCreate() override;
    std::string GetLayoutName() override {
    	return "UIFightZodiacIntro";
//    	return "UIFightZodiacIntroChristmas";
    }
    void ButtonDepress(int i_id) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

private:
    void showDescriptionWidget();
    void closeDescriptionWidget();
    class ActivityDescriptionUI* m_descriptionUI;
};


class CustomDisplayBoardDialog : public CustomDisplayBoard
{
public:
    CustomDisplayBoardDialog(const std::string& i_plantName, const Rect& i_rect);
    ~CustomDisplayBoardDialog();

    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void ButtonDepress(int i_id) override;
};

class FightZodiacGachaWidget : public Widget, public Sexy::ButtonListener
{
public:
    FightZodiacGachaWidget();
    virtual ~FightZodiacGachaWidget();

    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;

    void setIndex(int i_index, int i_limit);
    void onBuyGacha(int i_index);
private:
    int m_index;
    int m_limit;
};


class UIFightZodiac : public UISingletonDialog<UIFightZodiac>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIFightZodiac();
    virtual ~UIFightZodiac();
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override {
//    	return "UIFightZodiac";
    	return "UIFightZodiacDave";
    }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void TabSelectionChanged(int tabID) override;

    void InitView();
    void StartEffect(int i_from, int i_to);

    void showDisplayBoardWidget();
    void closeDisplayBoardWidget();
    void CheckTips(bool i_isInit = false);
    void UpdateFireWorksNumber();

public:
    int m_ZodiacHP;
    int m_ZodiacIndex;
    int m_FireWorks;
    int m_PennyReward;
    int m_type = 3; //类型判断  3潘妮  4回忆之旅  5diy
    int all_num = 0;
	int obtain_num = 0;
    bool m_MonthlyCardReward;
    bool m_FreeReward;
    bool m_SwtichReward;
    bool m_isLastUseTenFireworks;

protected:
    void onBuyGacha(int i_index);
    void setZodiacIndex(int i_number);
    void setZodiacHP(int i_number, bool i_isInit = false);
    void setFireWorksNumber(int i_number);
    void updateTimer();
    void showRewardDisplay();
    void closeRewardDisplay();
    void showDescriptionWidget();
    void closeDescriptionWidget();
    void FightZodiacWithFireWorks(int i_number);

private:
    bool m_needRefresh;
    bool m_ignoreInput;
    std::string m_plantName;
    std::vector<std::pair<int,int>> m_rewards;
    std::vector<ProgressDisappear*> m_disappears;
    class CustomDisplayBoard* m_board;
    class ActivityDescriptionUI* m_descriptionUI;
};


class UIFightZodiacReward : public UISingletonDialog<UIFightZodiacReward>
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIFightZodiacReward"; }
    void ButtonDepress(int i_id) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void InitView();

    int m_type = 3; //类型判断  3潘妮  4回忆之旅  5diy
    int all_num = 0;
	int obtain_num = 0;

private:
    void requestReward(int i_index);
};


class FightFireworksData : public INetworkData
{
public:
	RT_CLASS_DEFINE(FightFireworksData, INetworkData, RtClass);

    int FireworksNumber;
    int ZodiacHP;
    std::vector<S2C_BonusInfo> RewardList;
    std::vector<S2C_BonusInfo> FinalList;
};

class FightZodiacData : public INetworkData
{
public:
	RT_CLASS_DEFINE(FightZodiacData, INetworkData, RtClass);

    int FireworksNumber;
    int ZodiacIndex;
    int ZodiacHP;
    std::vector<S2C_BonusInfo> RewardShowList;

    int MonthlyCardReward;
    int FreeReward;
    int PennyReward;
    std::vector<S2C_BonusInfo> FinalReward;
    std::vector<S2C_FightZodiacStateInfo> StateInfo;
    std::vector<int> GachaLimit;
};


class FightZodiacManager : public LazySingleton<FightZodiacManager>
{
public:
    bool shouldShowTips();
};

#define gFightZodiacManager (FightZodiacManager::GetInstancePtr())

#endif

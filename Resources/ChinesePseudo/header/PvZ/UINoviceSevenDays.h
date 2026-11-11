#ifndef UINoviceSevenDays_H
#define UINoviceSevenDays_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "Image.h"


class GeneralTask;
struct NoviceSevenDaysIntegralReward
{
    std::vector<S2C_BonusInfo> BonusList;
};

class NoviceSevenDaysData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysData, INetworkData, RtClass);

    int                                         DiffDay;
    int                                         Integral;
    std::vector<int>                            FinishList;
    std::vector<int>                            BlackList;
    std::vector<int>                            IntegralRewardIndex;
    std::vector<NoviceSevenDaysIntegralReward>  IntegralReward;
};

class NoviceSevenDaysRewardData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysRewardData, INetworkData, RtClass);

    std::vector<S2C_BonusInfo>  BonusList;
};

class NoviceSevenDaysTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RT_CLASS_DEFINE(NoviceSevenDaysTaskWidget, Sexy::Widget, RtClass);

    NoviceSevenDaysTaskWidget();
    virtual ~NoviceSevenDaysTaskWidget();

    //For Cheat
    virtual void TouchBegan(const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch ) override;

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    void SetTask(GeneralTask* i_task);
    void InitView();
    void UpdateButtonState();
    void InitTimer();
    void DrawTimer(Sexy::Graphics* i_g);

    void SetTaskForNewPlayerCollection(GeneralTask* i_task);

protected:
    void RequestReward();

    int32 m_iTouch;
    GeneralTask* m_pTask;
    Sexy::Image* m_iBackground;
    PVZ2UIButton* m_btnButton;
    EffectAnim_UIAnim m_eTimer;
    SexyString m_strName;
    SexyString strProgress;
    Rect m_rName;
    Sexy::PrimeTypeface* m_nameFront;
    Rect m_rBanner;
    Sexy::PrimeTypeface* m_timerFront;
    Rect m_rProgress;
    Sexy::PrimeTypeface* m_progressFront;
    Rect m_rButton;
    bool m_buttonFlag;
};


class NoviceSevenDaysRewardButton : public Widget
{
public:
    NoviceSevenDaysRewardButton();
    virtual ~NoviceSevenDaysRewardButton();
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;
    void SetData(bool i_hasGot, int index);
    void RequestReward();
    void UpdateButtonState(int target);
    int GetIndex(){ return m_index; };
protected:
    int m_index;
    bool m_hasGot;
    int32 m_iTouch;
};

class NoviceSevenDaysRewardDisplay : public Sexy::Widget
{
public:
    NoviceSevenDaysRewardDisplay();
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;
    virtual void Draw(Graphics* i_g) override;
    void SetReawrd(const NoviceSevenDaysIntegralReward& i_reward);
private:
    Sexy::Image*        m_image;
    SexyString          m_des;
    int                 m_bonusId;
    bool                m_isPlantChip;
    std::string         m_bonusName;
    Sexy::Rect          m_iconRect;
    int32               m_iTouch;
    SexyString          m_description;
    class StoneLotteryItemTipUI* m_tipUI;
};

class UINoviceSevenDays : public UISingletonDialog<UINoviceSevenDays>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UINoviceSevenDays();
    virtual ~UINoviceSevenDays();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINoviceSevenDays"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

    int GetCurrentIntegral() { return m_currentIntegral; }
    void AddIntegral(int num);
    void ObtainReward(int index);

private:
    void InitTasks(const NoviceSevenDaysData& noviceSevenDaysData);
    void InitReward(const NoviceSevenDaysData& noviceSevenDaysData);
    void UpdateIntegral();
    void RefreshProgressBar();
private:
    int m_currentIntegral;
    std::vector<NoviceSevenDaysRewardButton*> m_vecRewardButton;
};

//new novice seven days
class UINoviceSevenDaysCollection : public UISingletonDialog<UINoviceSevenDaysCollection>, public Sexy::ScrollWidgetListener
{
public:
    UINoviceSevenDaysCollection();
    virtual ~UINoviceSevenDaysCollection();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINoviceSevenDaysCollection"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

    int GetCurrentIntegral() { return m_currentIntegral; }
    void AddIntegral(int num);
    void ObtainReward(int index);

private:
    void InitTasks(const NoviceSevenDaysData& noviceSevenDaysData);
    void InitReward(const NoviceSevenDaysData& noviceSevenDaysData);
    void UpdateIntegral();
    void RefreshProgressBar();

    void SwitchLabel(int i_index);


private:
    int m_currentIntegral;
    std::vector<NoviceSevenDaysRewardButton*> m_vecRewardButton;
};

#endif
#ifndef PVZ1MODEACHIEVEMENT_H
#define PVZ1MODEACHIEVEMENT_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "Image.h"


class GeneralTask;
struct PVZ1AchievementTaskReward
{
    int m_taskId;
    int m_isGot;
};

class PVZ1ModeAchievementData : public INetworkData
{
public:
	RT_CLASS_DEFINE(PVZ1ModeAchievementData, INetworkData, RtClass);

    int                                         	Integral;
    std::vector<PVZ1AchievementTaskReward>  		TaskReward;
    std::vector<int>                            	IntegralRewardReceiveState;
    std::vector<std::vector<S2C_BonusInfo>>			IntegralReward;
};

class PVZ1ModeAchievementRewardDataMsg : public INetworkData
{
public:
	RT_CLASS_DEFINE(PVZ1ModeAchievementRewardDataMsg, INetworkData, RtClass);

	std::string	strData;
};

class PVZ1ModeAchievementRewardData : public INetworkData
{
public:
	RT_CLASS_DEFINE(PVZ1ModeAchievementRewardData, INetworkData, RtClass);

    std::vector<S2C_BonusInfo>  BonusList;
};

class PVZ1ModeAchievementTaskWidgetCoin : public Sexy::Widget
{
public:
	RT_CLASS_DEFINE(PVZ1ModeAchievementTaskWidgetCoin, Sexy::Widget, RtClass);

	PVZ1ModeAchievementTaskWidgetCoin(){}

	PVZ1ModeAchievementTaskWidgetCoin(int i_count, bool i_hasGot, Rect i_rect)
	{
		m_count = i_count;
		m_hasGot = i_hasGot;
		Resize(i_rect);
		InitView();
	}

	void InitView();

	void SetDate(int i_count, bool i_hasGot)
	{
		m_count = i_count;
		m_hasGot = i_hasGot;
	}

	virtual void Draw(Sexy::Graphics* i_g) override;

private:
	int m_count;
	bool m_hasGot;
};

class PVZ1ModeAchievementTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RT_CLASS_DEFINE(PVZ1ModeAchievementTaskWidget, Sexy::Widget, RtClass);

    PVZ1ModeAchievementTaskWidget();
    virtual ~PVZ1ModeAchievementTaskWidget();

    //For Cheat
    virtual void TouchBegan(const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch ) override;

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void SetTask(GeneralTask* i_task);
    void UpdateButtonState();
    void InitView();

protected:
    void RequestReward();

    int32 m_iTouch;
    GeneralTask* m_pTask;
    Sexy::Image* m_iBackground;
    Sexy::Image* m_iTaskIcon;
    PVZ2UIButton* m_btnButton;
    SexyString m_strName;
    SexyString m_strProgress;
    SexyString m_strDescription;
    SexyString m_strTaskCoinNum;
    Rect m_rName;
    Rect m_rDescription;
    Rect m_rTaskIcon;
    Rect m_rCoin;
    Rect m_rButton;
    Rect m_rTaskCoinNum;
    bool m_buttonFlag;
    int m_index;
};

class PVZ1ModeAchievementRewardButton : public Widget
{
public:
	PVZ1ModeAchievementRewardButton();
    virtual ~PVZ1ModeAchievementRewardButton();
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

class PVZ1ModeAchievementRewardDisplay : public Sexy::Widget
{
public:
	PVZ1ModeAchievementRewardDisplay();
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;
    virtual void Draw(Graphics* i_g) override;
    void SetReawrd(const std::vector<S2C_BonusInfo>& i_reward);
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

class PVZ1ModeAchievement : public UISingletonDialog<PVZ1ModeAchievement>, public Sexy::ScrollWidgetListener
{
public:
	PVZ1ModeAchievement();
    virtual ~PVZ1ModeAchievement();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPVZ1ModeAchievement"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

    int GetCurrentIntegral() { return m_currentIntegral; }
    void AddIntegral(int num);
    void ObtainReward(int index);
    int GetIntegralGrade();

    static bool HasCompletedAllTasks();

private:
    void InitTasks(const PVZ1ModeAchievementData& pvz1ModeAchievementData);
    void InitReward(const PVZ1ModeAchievementData& pvz1ModeAchievementData);
    void UpdateIntegral();
    void RefreshProgressBar();
    void RefreshCoinBank();
private:
    int m_currentIntegral;
    int m_totalIntegral;
    std::vector<PVZ1ModeAchievementRewardButton*> m_vecRewardButton;
};

#endif

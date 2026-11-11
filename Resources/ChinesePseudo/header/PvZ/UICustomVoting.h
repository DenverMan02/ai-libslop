#ifndef UICUSTOMVOTING_H
#define UICUSTOMVOTING_H

#include "UILimitGroupBuy.h"


struct CustomVotingItemData
{
    int ItemID;
    int Quantity;
    //for reward
    int Need;
    bool IsObtained;
};

class CustomVotingData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomVotingData, INetworkData, RtClass);

    std::vector<CustomVotingItemData> VoteList;
    std::vector<CustomVotingItemData> RewardList;
    int RemainTickets;
    int VotedTickets;
};


class VotingRewardGridItem : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(const CustomVotingItemData& i_data, int i_index);
private:
    void ObtainReward();
    int m_index;
    CustomVotingItemData m_data;
    PVZ2UIButton* m_submitButton;
};

class VotingRewardUI : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
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


class CustomVotingGridItem : public LimitGroupBuyGridItem
{
public:
    virtual void ButtonDepress(int i_id) override;

    void Init(const CustomVotingItemData& data);

private:
    void VoteConfirm();
};

class UICustomVoting : public UISingletonDialog<UICustomVoting>, public Sexy::ScrollWidgetListener
{
public:
    UICustomVoting();
	virtual ~UICustomVoting();

	virtual bool	                    OnCreate() override;
    virtual void	                    OnClose() override;
    virtual std::string                 GetLayoutName() override { return "UICustomVoting"; }
	virtual void				        Draw(Sexy::Graphics* i_g) override;
	virtual void					    DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void					    Update() override;
	virtual void					    ButtonDepress(int i_id) override;
    virtual void                        ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void                        ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

	void							    InitView();
    void                                UpdateTimer();
    void                                UpdateTicket();
    void                                SetTickets(int i_tickets);
    int                                 GetTickets();
    void                                VotedTicketsAdd();
    int                                 GetVotedTickets();

    void                                ShowVotingReward();
    void                                CloseVotingReward();

private:
    void                                RealCloseVotingReward();

    int                                 m_tickets;
    int                                 m_votedTickets;
    Widget*                             m_mainPanel;
    VotingRewardUI*                     m_rewardPanel;
    std::vector<CustomVotingGridItem*>  m_itemList;
    
};


#endif
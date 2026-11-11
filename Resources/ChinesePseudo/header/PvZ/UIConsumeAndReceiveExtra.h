#ifndef UICONSUMEANDRECEIVEEXTRA_H
#define UICONSUMEANDRECEIVEEXTRA_H

#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "Image.h"

struct ConsumeAndReceiveRewardData
{
    int PlantId;
    int Amount;
    int Gems;
    int Received;
};

class ConsumeAndReceiveExtraData : public INetworkData
{
RT_CLASS_DEFINE(ConsumeAndReceiveExtraData, INetworkData, RtClass);

    int BannerId;
    std::vector<ConsumeAndReceiveRewardData> List;
};

class ConsumeReceiveExtraRewardWidget : public Widget
{
public:
    ConsumeReceiveExtraRewardWidget();
    virtual ~ConsumeReceiveExtraRewardWidget();
public:
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

	void 					LoadData(int i_pos, int i_id, int i_amount, int i_gems, bool i_canAward);
    void                    SetMask(Widget* i_mask);
	
private:
    int32                   m_touchId;
	int						m_pos;
	int						m_awardId;
    int                     m_amount;
    int                     m_gems;
    bool                    m_canAward;
	ImagePtr				m_image;
    Sexy::Widget*           m_mask;
};

class UIConsumeAndReceiveExtra : public UISingletonDialog<UIConsumeAndReceiveExtra>
{
public:
	UIConsumeAndReceiveExtra();
	virtual ~UIConsumeAndReceiveExtra();
public:
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIConsumeAndReceiveExtra"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void 				Update() override;
    void						UpdateTimer();

	void 						InitView();

    static bool                 HasAnyNotReceivedReward();

protected:
	const int c_chargeLevel = 5;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	std::vector<ConsumeReceiveExtraRewardWidget*> m_widgetVec;
};

#endif
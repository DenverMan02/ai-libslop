/*
 * LoginReward.h
 *
 *  Created on: 2013-10-21
 *      Author: zhaobk
 */

#ifndef LOGINREWARD_H_
#define LOGINREWARD_H_

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"

namespace Message
{
	void TotalLoginRewardReceived(int i_receiveId);
	void ProcessLoginRewardResult(int i_loginId);
	void LoginRewardCollection(int i_loginDay);
}

struct TotalLoginRewardPool
{
	int i_id;	//Reward id
	int i_amount;	//Reward Amount
};

class RewardScrollPanel : public Widget
{
public:
	RewardScrollPanel(Rect &i_rect);
    ~RewardScrollPanel();
    std::vector<class LoginRewardContent*> m_contents;

private:
    void	InitView();
};

enum LoginButtonId
{
    LOGIN_BUTTON_ID_CLOSE = 0,
    LOGIN_BUTTON_ID_SEND_REQUEST,
};

class LoginReward : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
	LoginReward();
    ~LoginReward();

    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

    void getReward(int i_id, int i_amount);
    void onProcessTotalLoginRewardResult(int i_loginId);
    void onProcessTotalLoginRewardException(int i_errorCode);

private:
    void InitView();

	PVZ2UIScrollingWidget* m_scrollingWidget;
    PVZ2UIButton*           m_closeButton;

    int m_loginDays;

};

class LoginRewardContent : public Widget, Sexy::ButtonListener
{
public:
	LoginRewardContent(int i_loginId, bool i_hasGotReward, bool i_canGetReward, bool i_needHighlight);
	~LoginRewardContent();

	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
	virtual void ButtonDepress(int i_id);

	void onTotalLoginRewardReceived(int i_receiveId);

private:
	Image* m_rewardImage;
	Image* m_bgImage;
	Image* m_titleImage;
	Image* m_daysImage;
	Image* m_obtainImage;

	int m_contentWidth;
	int m_loginId;
	bool m_hasGotReward;
	bool m_canGetReward;	//only if m_hasGotReward == false will we need to use this bool
	bool m_needHighlight;

	PVZ2UIButton* m_getButton;

	void InitView();


};


#endif /* LOGINREWARD_H_ */

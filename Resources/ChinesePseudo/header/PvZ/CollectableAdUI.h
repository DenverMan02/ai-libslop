/*
 * CollectableAdUI.h
 *
 *  Created on: 2018-12-1
 *      Author: Administrator
 */

#ifndef COLLECTABLEADUI_H_
#define COLLECTABLEADUI_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

class AdRewardContent : public Sexy::Widget
{
public:
	AdRewardContent(const NDLoginRewardBonus & data);
	virtual ~AdRewardContent();

	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:
	void            setupScreen();
private:
	NDLoginRewardBonus  m_data;
};

class CollectableAdUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	CollectableAdUI();
    ~CollectableAdUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();
	void InitTestData();

	void RefreshActivity(const NDLoginRewardBonus& i_reward);

	static void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	static void onMsgErrorRequest(int erroId, const std::string& i_reqID);
	static void setUnactive();
	static bool isActive(){return s_isActive;}

private:
	void onKillDialog();

	// main board
	Rect m_dialogRect;
	//RecallInfo m_info;
	PVZ2UIButton* m_claimBtn;
	time_t m_endTime;

	// banner
	Image* m_bannerImg;
	Rect m_bannerRect;
	// title
	Image* m_titleImg;
	Rect m_titleRect;
	// title text
	Rect m_titleTextRect;
	static bool s_isActive;

	NDLoginRewardBonus m_reward;
};


#endif /* COLLECTABLEADUI_H_ */

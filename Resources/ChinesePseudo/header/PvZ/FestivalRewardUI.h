/*
 * FestivalRewardUI.h
 *
 *  Created on: 2015-9-8
 *      Author: jianglc
 */

#ifndef FESTIVALREWARDUI_H_
#define FESTIVALREWARDUI_H_

#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "PVZVersion.h"
#include "Effect_PopAnim.h"

enum FestivalRewardButtons
{
    Festival_Get_Reward_Entry,
    Festival_Get_Reward,
    Festvial_Wechat_Share
};

//class UpdateRewardContent : public Widget, Sexy::ButtonListener
//{
//public:
//	UpdateRewardContent(ContentType i_type, UpdateRewardData i_data);
//	~UpdateRewardContent();
//
//	virtual void Draw(Graphics *i_g);
//    virtual void Update();
//
//    void SetReward(UpdateRewardData i_reward) { m_data = i_reward; }
//    void GetReward();
//
//private:
//
//    void InitView();
//    void onAnimDone(const std::string& i_animLabelName);
//
//	Image *     m_rewardImage;
//	Image *     m_bgImage;
//
//    ImagePtr m_amountImage;
//    SexyString m_titleStr;
//    UpdateRewardData m_data;
//    float m_drawScale;
//    ContentType m_type;
//    Effect_PopAnim* m_giftAnim;
//    GiftAnimState m_animState;
//};

class FestivalRewardUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	FestivalRewardUI();
    ~FestivalRewardUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	//bool IsCurrentRewardTimeValid(int iEndDate);

private:

    void InitView();

    //std::vector<UpdateRewardContent*> m_updateRewards;
    int m_contentGap;
    SexyString m_contentStr;
    PVZ2UIButton* m_getRewardEntryBtn;
};


#endif /* FESTIVALREWARDUI_H_ */

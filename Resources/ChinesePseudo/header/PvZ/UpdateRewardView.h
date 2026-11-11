/*
 * UpdateRewardView.h
 *
 *  Created on: 2015-5-27
 *      Author: jianglc
 */

#ifndef UPDATEREWARDVIEW_H_
#define UPDATEREWARDVIEW_H_

#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "PVZVersion.h"
#include "Effect_PopAnim.h"

enum ContentType
{
	CONTENT_UPDATE_REWARD,
	CONTENT_RANDOM_REWARD
};

enum RewardType
{
	FIRST_REWARD = 0,
	SECOND_REWARD,
	THIRD_REWARD
};

enum GiftAnimState
{
	ANIM_NOT_PLAY,
	ANIM_PLAYED
};

enum UpdateRewardButtons
{
    Update_Get_Reward
};

class UpdateRewardContent : public Widget, Sexy::ButtonListener
{
public:
	UpdateRewardContent(ContentType i_type, UpdateRewardData i_data);
	~UpdateRewardContent();

	virtual void Draw(Graphics *i_g);
    virtual void Update();

    void SetReward(UpdateRewardData i_reward) { m_data = i_reward; }
    void GetReward();

private:

    void InitView();
    void onAnimDone(const std::string& i_animLabelName);

	Image *     m_rewardImage;
	Image *     m_bgImage;

    ImagePtr m_amountImage;
    SexyString m_titleStr;
    UpdateRewardData m_data;
    float m_drawScale;
    ContentType m_type;
    Effect_PopAnim* m_giftAnim;
    GiftAnimState m_animState;
};

class UpdateRewardView : public Sexy::Widget, Sexy::ButtonListener
{
public:

	UpdateRewardView();
    ~UpdateRewardView();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	//bool IsCurrentRewardTimeValid(int iEndDate);

private:

    void InitView();
    void InitRewards();
    UpdateRewardData GetRandomReward();

    PVZVersion m_Version;
    TotalRewardData m_TotalReward;
    std::vector<UpdateRewardContent*> m_updateRewards;
    int m_contentGap;
    SexyString m_contentStr;
    PVZ2UIButton* m_getRewardBtn;
};


#endif /* UPDATEREWARDVIEW_H_ */

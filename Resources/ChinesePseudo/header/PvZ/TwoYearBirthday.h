//
//  TwoYearBirthday.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-28.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TwoYearBirthday__
#define __PlantsVersusZombies2__TwoYearBirthday__

//#include "PlatformAutodetect.h"
//#include "RtDb.h"
//#include "RtDelegate.h"
//#include "TimeMgr.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"

enum BirthdayRewardType
{
	BIRTHDAYREWARDTYPE_COINS = 0,
	BIRTHDAYREWARDTYPE_PLANT,
	BIRTHDAYREWARDTYPE_PLANT_PIECE,
	BIRTHDAYREWARDTYPE_COUNT,
};

struct BirthdayRewardData
{
    BirthdayRewardData()
    {
    	Amount = 0;
    	ObjectId = 0;
    }
    
	int Amount;
	int ObjectId;
};

struct WechatRewardData
{
	WechatRewardData()
	{
		ObjectId = 0;
		Quantity = 0;
	}
	int ObjectId;
	int Quantity;
};

class WechatRewardInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(WechatRewardInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<WechatRewardData>     rewardInfos;
};

class BirthdayRewardContent : public Sexy::Widget
{
public:
    
	BirthdayRewardContent(const BirthdayRewardData & data);
	virtual ~BirthdayRewardContent();
    
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
private:
    
    void            setupScreen();
    
private:
    
    BirthdayRewardData  m_data;
};

class TwoYearBirthdayMgr : public LazySingleton <TwoYearBirthdayMgr>
{
public:
	TwoYearBirthdayMgr();
    ~TwoYearBirthdayMgr();

    void requestNetwork();
    void RefreshActivity(bool i_success);
    bool NeedShowChannelActivity();
    std::string GetChannelID();
private:
    //void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class TwoYearBirthday : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	TwoYearBirthday();
	virtual ~TwoYearBirthday();
	
	virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
	void SyncActivityData(const WechatRewardInfo& i_data);
    
private:
    
    void setupScreen();
    void ShareWechatSuccess();
    void ShareWechatFailed();
    
private:
    
    //Effect_PopAnim * m_popAnimEffect;
    
    PVZ2UIButton   * m_getRewardBtn;
    
    int                             m_days;
    int                             m_rewardObjectId;
    std::vector<BirthdayRewardData> m_rewardDatas;
    Rect							m_textRect;
};

class ShareWechatUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:

	ShareWechatUI();
	virtual ~ShareWechatUI();

	virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
private:
	PVZ2UIButton* m_shareToTimeline;
	PVZ2UIButton* m_shareToSession;
	SexyString m_sessionStr;
	SexyString m_timelineStr;

	void ShareToWechat(bool i_timeline);
	void InitView();
};

class ShareRewardView : public Sexy::Widget, Sexy::ButtonListener
{
public:

	ShareRewardView();
    ~ShareRewardView();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView(const std::vector<BirthdayRewardData>& i_rewardList);

private:
    std::vector<BirthdayRewardData> m_rewardList;
    SexyString m_contentStr;
    PVZ2UIButton* m_getRewardBtn;

    void onRewardResult(bool i_success, const S2C_WechatShareResult* pData);
    void onRewardGot();
    void onRewardGotFailed();
};

#endif /* defined(__PlantsVersusZombies2__TwoYearBirthday__) */

/*
 * GemOfferMgr.h
 *
 *  Created on: 2017-8-15
 *      Author: Administrator
 */

#ifndef GEMOFFERMGR_H_
#define GEMOFFERMGR_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

class GemOfferHintUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	GemOfferHintUI();
    ~GemOfferHintUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();

private:
    PVZ2UIButton* m_shopBtn;
};

class GemOfferInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(GemOfferInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<int> hintTimes;
    int timeRange;
};

class GemOfferMgr : public LazySingleton <GemOfferMgr>
{
public:
	GemOfferMgr();
    ~GemOfferMgr();

    void InitTestData();
    void RequestNetwork();
    bool CanShowHint();
    void ShowHint();
    bool NeedShowHint();
    void SetActivatedTips(bool i_activated) { m_activatedTips = i_activated; }
    bool GetActivatedTips() { return m_activatedTips; }
    void ClearDatas();
    void ResetHintTimes();
    void RefreshActivity();

    void Update();
private:
    // these are sever times for hint, eg: 9:00, 12:00, 16:00...
    std::map<int, bool> m_hintTimes;
    // this is the value to control the hint range, from 0-60
    int m_hintRange;
    bool m_activatedTips;

    void SyncActivityData(const GemOfferInfo& i_data);
};


#endif /* GEMOFFERMGR_H_ */

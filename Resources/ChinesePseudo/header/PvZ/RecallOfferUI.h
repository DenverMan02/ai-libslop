/*
 * RecallOfferUI.h
 *
 *  Created on: 2018-10-16
 *      Author: Administrator
 */

#ifndef RECALLOFFERUI_H_
#define RECALLOFFERUI_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

struct RecallItemInfo
{
	RecallItemInfo()
	{
		Id = 0;
		Quantity = 0;
	}
    int Id;
    int Quantity;
};

class RecallInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(RecallInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<RecallItemInfo> itemInfos;
};

class RecallItemWidget : public Sexy::Widget
{
public:
	RecallItemWidget();
    virtual void			Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;

    void                    SetShopData(const RecallItemInfo& shopData);

    RecallItemInfo          m_shopInfo;

    SexyString              m_strName;
    ImagePtr                m_shopImage;

    std::string				m_plantPieceType;
    SexyString              m_strAmount;
};

class RecallOfferUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	RecallOfferUI();
    ~RecallOfferUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();
	void InitTestData();

	void RefreshActivity();
	void SyncActivityData(const RecallInfo& i_info, int i_endDate);

	static void RequestNetwork();
	static void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	static void onMsgErrorRequest(int erroId, const std::string& i_reqID);
	static void setUnactive();
	static bool isActive(){return s_isActive;}

private:
	// main board
	Rect m_dialogRect;
	RecallInfo m_info;
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

	// main bg
	Image* m_mainBg;
	Rect m_mainBgRect;
	static bool s_isActive;
};


#endif /* RECALLOFFERUI_H_ */

/*
 * summary_menu.h
 *
 *  Created on: 2013-8-26
 *      Author: chenyc
 */

#ifndef SUMMARY_MENU_H_
#define SUMMARY_MENU_H_

#include "Precompile.h"
#include <time.h>

class PVZ2UIButton;

enum summaryButtons
{
	SUMMARYBUTTON_CANCEL,
	SUMMARYBUTTON_CLOUD_LEVEL,
	SUMMARYBUTTON_CLOUD_COIN_NUM,
	SUMMARYBUTTON_CLOUD_GEM_NUM,
	SUMMARYBUTTON_CLOUD_PLANT,
	SUMMARYBUTTON_CLOUD_AVATAR,
	SUMMARYBUTTON_USECLOUD,
	SUMMARYBUTTON_LOCAL_LEVEL,
	SUMMARYBUTTON_LOCAL_COIN_NUM,
	SUMMARYBUTTON_LOCAL_GEM_NUM,
	SUMMARYBUTTON_LOCAL_PLANT,
	SUMMARYBUTTON_LOCAL_AVATAR,
	SUMMARYBUTTON_USELOCAL,
	SUMMARYBUTTON_DELEGATE
};

enum summarySelectResult
{
	SSR_USE_LOCAL 	= 0,
	SSR_USE_CLOUD,
	SSR_CANCEL_SYNC,
};

class ProfileSummaryComparer : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	ProfileSummaryComparer(bool isCloudLeft = true);
	virtual ~ProfileSummaryComparer();


	virtual void 	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void 	ButtonDepress(int i_id);

private:
	void initUIPositions(bool isCloudLeft);		//All the UIs are put according to the parameters set in this function.
	void initUIs(bool isCloudLeft);
	void initCloudUIs();
	void initLocalUIs();
	void setSummaryBtn( PVZ2UIButton* i_btn, Image* i_image,  const SexyString& i_leftString, const SexyString& i_rightString );

	void drawLocalSummary(Sexy::Graphics* i_g);
	void drawCloudSummary(Sexy::Graphics* i_g);

	void onConfirmUsingOlderData();
	void onCancelUsingOlderData();

	//arrange in order
	PVZ2UIButton* m_btn_cancel;

	//cloud on the left
	PVZ2UIButton* m_btn_cloud_level;
	PVZ2UIButton* m_btn_cloud_coin_num;
	PVZ2UIButton* m_btn_cloud_gem_num;
	PVZ2UIButton* m_btn_cloud_plant;
	PVZ2UIButton* m_btn_cloud_avatar;
	PVZ2UIButton* m_btn_usecloud;

	//local on the right
	PVZ2UIButton* m_btn_local_level;
	PVZ2UIButton* m_btn_local_coin_num;
	PVZ2UIButton* m_btn_local_gem_num;
	PVZ2UIButton* m_btn_local_plant;
	PVZ2UIButton* m_btn_local_avatar;
	PVZ2UIButton* m_btn_uselocal;

	//parameters to pinpoint UI positions.
	Point m_leftHeaderPosition;
	Rect m_leftProgressPanelBGRect;
	Point m_leftProgressHeaderPosition;
	Point m_leftTimePosition;
	Rect m_leftLevelProgressTableBGRect;
	Rect m_leftStarNumTableBGRect;

	int m_panelToTableGapWidth;
	int m_panelToStarTableGapHeight;
	int m_contentRowHeight;
	int m_contentRowWidth;
	int m_levelToStarGapHeight;
	int m_gapHeightBetween2Rows;

	int m_cloudPanelToLeftDistance;
	int m_localPanelToLeftDistance;
	bool m_isCloudDataOlder;

	time_t m_cloudTime;
	time_t m_localTime;

};

namespace Message
{
	void ProfileSummarySelectResult(int i_result);
}

#endif /* SUMMARY_MENU_H_ */

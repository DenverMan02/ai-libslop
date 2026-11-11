/*
 * notice_board.h
 *
 *  Created on: 2013-9-9
 *      Author: chenyc
 */

#ifndef NOTICE_BOARD_H_
#define NOTICE_BOARD_H_

#include "PVZ2UIButton.h"

enum noticeButtons
{
	NOTICEBUTTON_CANCEL,
	NOTICEBUTTON_CLOSE,
	NOTICEBUTTON_URL,
	NOTICEBUTTON_RECHARGE
};


class PVZ2UIButton;
//class noticeRequest;

class noticeBoard :  public Sexy::Widget,  public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	noticeBoard();
	virtual~noticeBoard();

	virtual void Draw(Sexy::Graphics* g);
	virtual void ButtonPress(int id);
	virtual void ButtonDepress(int id);
	virtual void ScrollTargetReached( ScrollWidget* scrollWidget );
	virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget );

	void setNoticeContent( const std::string& title, const std::string& content );

	void inital();
	void showUrlbtn( bool isshow );

	void onButtonClose();
	void onButtonUrl();
	PVZ2UIButton* createBtn( noticeButtons enbtn, Sexy::Image* btnimg, Sexy::Image* btnimgd );

private:
	//PVZ2UIButton* btn_Recharge_;
	PVZ2UIButton* btn_Close_;

	PVZ2UIButton* btn_URL_;
	//noticeRequest* noticeRequest_;

	class PVZ2UIScrollingWidget*  m_scrollingWidget;
	class staticText* staticTexts_;
	//class staticText* title_;
};


#endif /* NOTICE_BOARD_H_ */

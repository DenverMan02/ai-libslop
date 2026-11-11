/*
 * VersionNoticeBoard.h
 *
 *  Created on: Apr 25, 2014
 *      Author: lijie
 */

#ifndef VERSIONNOTICEBOARD_H_
#define VERSIONNOTICEBOARD_H_

#include "PVZ2UIButton.h"
#include "PVZVersion.h"

enum versionNoticeButtons
{
	VERSION_NOTICEBUTTON_SKIP,
	VERSION_NOTICEBUTTON_UPDATE,
};


class PVZ2UIButton;

class VersionNoticeBoard :  public Sexy::Widget,  public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	VersionNoticeBoard();
	virtual~VersionNoticeBoard();

	virtual void Draw(Sexy::Graphics* g);
	virtual void ButtonPress(int id);
	virtual void ButtonDepress(int id);
	virtual void ScrollTargetReached( ScrollWidget* scrollWidget );
	virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget );

	void inital();
	void showUrlbtn( bool isshow );

	void onButtonSkip();
	void onButtonUpdate();
	PVZ2UIButton* createBtn( versionNoticeButtons enbtn, Sexy::Image* btnimg, Sexy::Image* btnimgd );

private:
    void onWWANDialogCancel();
    void onWWANDialogOK();
    
    void onNotConnectedDialogOK();
    
private:
	PVZ2UIButton* btn_Update;
	PVZ2UIButton* btn_Skip;

	class PVZ2UIScrollingWidget*  m_scrollingWidget;
	class staticText* staticTexts_;
	PVZVersion m_Version;
};



#endif /* VERSIONNOTICEBOARD_H_ */

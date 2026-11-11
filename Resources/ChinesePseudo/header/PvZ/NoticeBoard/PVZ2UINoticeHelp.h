/*
 * PVZ2UINoticeHelp.h
 *
 *  Created on: Jul 24, 2014
 *      Author: lijie
 */

#ifndef PVZ2UINOTICEHELP_H_
#define PVZ2UINOTICEHELP_H_

#include "PVZ2UIButton.h"

class PVZ2UINoticeHelp
{
public:
	static Sexy::Widget* AnalyzeNoticeTxt(SexyString& noticeTxt, int noticeRectWidth);

private:
	enum ALIGN
	{
		E_LEFT,
		E_CENTER,
		E_RIGHT,
	};

private:
	static Sexy::Widget* CreateTxtWidget(SexyString& noticeTxt, int offsetY, int noticeRectWidth);
	static Sexy::Widget* CreateImageWidget(SexyString& imageDefine, int offsetY, int noticeRectWidth);
	static int CalTxtHeight(SexyString& noticeTxt);
};

#endif /* PVZ2UINOTICEHELP_H_ */

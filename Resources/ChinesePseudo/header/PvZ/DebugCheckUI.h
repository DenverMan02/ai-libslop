//
//  DebugCheckUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __DebugCheckUI_h_
#define __DebugCheckUI_h_

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PVZ2UIButton.h"

class DebugCheckUI : public Sexy::Widget, public ButtonListener
{
public:
	DebugCheckUI();
	virtual ~DebugCheckUI();

	virtual void							Update();
	virtual void							DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	virtual void							Draw(Graphics* i_g);
	virtual void							ButtonDepress(int i_id);

	void										Close();
	static DebugCheckUI*		ShowDialog();

protected:
	void										InitView();
	bool										Check();
	bool										CheckPlayerInfo();
	bool										CheckPlants();
	void										SavePlants();
	void										AppendMsg(const SexyString& str, bool bNewLine = false);
	void										ClearMsg();

private:
	Sexy::Rect							m_rectDialog;
	Sexy::Rect							m_rectScroll;
	SexyString							m_strDesc;
	int									m_textHeight;
	bool								m_bTextValid;

	static DebugCheckUI*		s_instance;
};



#endif /* defined(__DebugCheckUI_h_) */

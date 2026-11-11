//
//  ActiveCenter.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ActiveCenterTabRecharge_h_
#define _ActiveCenterTabRecharge_h_

#include "ActiveCenterTab.h"
#include "PlantDisplayBoard.h"
#include "SkillPropertySheet.h"

class SkillLevelBtn : public DisplayLevelButton
{
public:
	SkillLevelBtn(int i_level) : DisplayLevelButton(i_level) {}
	virtual ~SkillLevelBtn() {}
	virtual void DrawAll(ModalFlags* theFlags, Graphics* g);

	void		SetPlant(PlantTypePtr plantType, int iCurLevel);
public:
	SkillPropertySheetPtr	m_skillPtr;
};

class SkillTipsBar : public Sexy::Widget
{
public:
	SkillTipsBar();
	virtual ~SkillTipsBar(){}

	virtual void Draw(Sexy::Graphics* i_g);

	void SetImage(Sexy::Image* pBG, Sexy::Image* pArrow);
	void SetPointAt(const SexyVector2& pointAt);
	void SetTips(const SexyString& strTips, const Color& clr);
private:
	SexyString m_sTips;
	Color			m_color;

	Sexy::Image*		m_pImageBG;
	Sexy::Image*		m_pImageArrow;
	SexyVector2		m_point;
};

//--------------------------------------------------------------------------------------------------------
// ActiveCenterTabRecharge
//--------------------------------------------------------------------------------------------------------
class ActiveCenterTabRecharge : public ActiveCenterTabBase
{
public:
	ActiveCenterTabRecharge(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~ActiveCenterTabRecharge();

	virtual void		OnButtonClicked(int i_id);
	virtual void		SetSelect(bool setting);
	virtual void      DrawForeground(class Sexy::Graphics* i_g);
	virtual void		Update();

    void                Initialse();
	void					RefreshReward();
	void					ShowSkillTips();

	void					OnVerify2015NewTearCharge(bool i_success);
    void                OnGet2015NewTearChargeReward(bool i_success, bool i_neednext);
	void					OnSetDisplayLevel(int i_level);
    
protected:
	class PVZ2UIButton*		m_pBtnGet;
	class UIWidgetAnim*		m_pWidgetPlant;
    class UIWidgetText*     m_pWidgetTime;
	class SkillTipsBar*			m_plantSkillTipsUI;
	std::vector<SkillLevelBtn*> m_vecDisplayLevelButton;
	pvztime_t							m_timerSelectNext;
	Sexy::Widget*					m_pWidgetBar;
	Sexy::Image*						m_plantLevelImage;
    SexyString							m_plantName;
    uint                           m_timeRemain;
};

#endif

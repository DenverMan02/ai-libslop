//
//  DaveClubUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015Äê PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DaveClubUI__
#define __PlantsVersusZombies2__DaveClubUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "PopingWidget.h"
#include "UISingletonDialog.h"

class DaveClubActivityWidget : public Widget, Sexy::ButtonListener
{
public:
	DaveClubActivityWidget(int ActionId, bool isOpen);
	virtual ~DaveClubActivityWidget();

	virtual void Resize(const Rect& theRect) override;
	virtual void Update() override;
	virtual void Draw(Graphics *i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void Init();
	void ClearDaveClubInfo();
	Sexy::Widget* GetStartBtn() { return m_startButton; }
private:
	Sexy::Rect m_dialogRect;
	Sexy::Rect m_contentRect;
	Sexy::Rect m_nameRect;
	PVZ2UIButton* m_startButton;
	ImagePtr m_bgImage;
	SexyString m_content;
	SexyString m_ActivityName;
	bool m_inited;
	int m_nActionId;
	bool m_bIsOpen;
};

class DaveClubActivityScrollPanel : public Widget, public ButtonListener
{
public:
	DaveClubActivityScrollPanel(Sexy::Rect &i_rect, std::vector<DaveClubBonus>& bonus);
	virtual ~DaveClubActivityScrollPanel();

	std::vector<DaveClubActivityWidget *> GetDungeonList() { return m_dungeonList; }
	void RemoveAllDungeonWidget();

private:
	void InitView();

private:
	std::vector<DaveClubActivityWidget *> m_dungeonList;
	std::vector<DaveClubBonus> m_vecBonus;
};

class DaveClubUI : public UISingletonDialog<DaveClubUI>, public Sexy::ScrollWidgetListener
{
public:
	DaveClubUI();
	virtual ~DaveClubUI();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "DaveClubUI"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void loadData();
private:

	PVZ2UIScrollingWidget* m_daveClubScollingWdget;
	DaveClubActivityScrollPanel* m_dungeonScollingPanel;
	Sexy::Rect m_dungeonListScollRect;
	std::vector<DaveClubBonus> m_vecBonus;
};


class DaveClubConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(DaveClubConfig, RtObject, RtClass);
	DaveClubConfig() {}

public:
	std::vector<DaveClubBonus> Bonus;
	
};

#endif /* defined(__PlantsVersusZombies2__DaveClubUI__) */

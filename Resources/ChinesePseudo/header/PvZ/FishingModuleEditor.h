//
//  FishingModuleEditor.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.13
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FishingModuleEditor__
#define __PlantsVersusZombies2__FishingModuleEditor__

#include "UIEditor/UISingletonDialog.h"
#include "FishingModule.h"
#include "PVZ2UIButton.h"


class FishingModuleEditor : public UISingletonDialog < FishingModuleEditor >, public Sexy::ScrollWidgetListener
{
public:
	FishingModuleEditor();
	virtual ~FishingModuleEditor();
	virtual bool							OnCreate();
	virtual std::string				GetLayoutName() { return "fishingeditor.json"; }
	virtual void							Draw(Sexy::Graphics* i_g);
	virtual void							MouseDown(int x, int y, int theBtnNum, int theClickCount);

	// ButtonListener
	virtual void							ButtonDepress(int i_id);
	// implement of Sexy::ScrollWidgetListener
	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

	void										LoadProperty();
	void										SaveProperty();

	class FishingProperties*	GetProps();
	void										LayoutPanel();

	bool										CheckSelectItem(int btnID);

protected:
	class PVZ2UIButton*		InitButton(const std::string& name, int id);
	void										RefreshDrawPoints();
	void										DeletePoint();
	void										NewItem();
	void										Select(Sexy::Widget* pPanel, int iTab);

	void										SetZombieGroup(FishingZombieGroup& group, std::vector<SexyVector2>& points);

protected:
	struct ItemData
	{
		int						m_id;
		std::string			m_name;
		std::vector<SexyVector2> m_Points;
		PVZ2UIButton*	m_pBtn;
		ItemData() : m_pBtn(NULL), m_id(0) {}
	};
	typedef std::map<int, ItemData> MapItemData;
	typedef std::pair<int, ItemData> PairItemData;

	struct ItemPanel
	{
		Sexy::Widget*	m_pPanel;
		PVZ2UIButton*	m_pTab;
		//int						m_iSelect;
		SexyVector2		m_center;
		MapItemData		m_mapItem;
		int						m_IDGenerator;
		std::string			m_strPrefix;

		ItemPanel() : m_IDGenerator(0) {}
		void				InitData(ItemData& data, int baseID);
		void				LayoutPanel();
		void				AddItem(ItemData& data);
		ItemData*	GetItem(int id);
		ItemData*	GetSelectedItem();
		void				RemoveItem(int id, bool bDelete);
		void				SelectItem(int id);
		void				RefreshIDGen(int baseID);
	};
	
	std::map<int, ItemPanel>	m_Tabs;
	int										m_iCurTab;

	std::vector<SexyVector2> m_drawPoints;
	SexyVector2						m_drawCenter;

public:
	ZombieTypePtr					m_DefaultZombieType;
	
};

#endif /* defined(__PlantsVersusZombies2__FishingModuleEditor__) */

//
//  HotUITableView.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 11/18/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUITableView__
#define __PlantsVersusZombies2__HotUITableView__

#include "HotUILayoutList.h"

class HotUITableView : public HotUILayoutList
{
public:
	
	RT_CLASS_DEFINE(HotUITableView, HotUILayoutList, RtClass);
	
	HotUITableView();
	virtual ~HotUITableView();
	
	virtual void						SetDataSource(std::vector<RtId> i_dataSource) { m_dataSource = i_dataSource; };
	virtual void						CreateCells(const RtClass* i_cellAdaptorClass);
	
	virtual void						SetOverrideListenerForCells(ButtonListener* i_overrideListener);
	
protected:
	
	void								onLayoutFinalized() override;
	
private:
	
	void								updateHeightToFitCells();
	void								removeCells();
	
	// Serialized
	
	// Not serialized
	std::vector<RtId>								m_dataSource;
	std::vector<class HotUIAdaptorTableViewCell*>	m_cellAdaptors;
	int												m_originalHeight;
};

class HotUITableViewProperties : public HotUILayoutListProperties
{
public:
	RT_CLASS_DEFINE(HotUITableViewProperties, HotUILayoutListProperties, RtClass);
	
	HotUITableViewProperties()
	{}
	
	RtClass* GetWidgetClass() const override
	{
		return HotUITableView::StaticGetClass();
	}
	
	DynamicSizeData	SpaceBetweenRows;
};

#endif /* defined(__PlantsVersusZombies2__HotUITableView__) */

//
//  HotUIAdaptorTableViewCell.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 11/21/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIAdaptorTableViewCell__
#define __PlantsVersusZombies2__HotUIAdaptorTableViewCell__

#include "HotUIAdaptor.h"

class HotUIAdaptorTableViewCell : public HotUIAdaptor
{
	RT_CLASS_DEFINE(HotUIAdaptorTableViewCell, HotUIAdaptor, RtClass);
	
public:
	
	HotUIAdaptorTableViewCell();
	virtual ~HotUIAdaptorTableViewCell();
	
	virtual void		SetData(RtId i_data) {};
	virtual class HotUITableViewCell*	GetCellWidget();
	
protected:
	class HotUITableViewCell*	m_cellWidget;
};

#endif /* defined(__PlantsVersusZombies2__HotUIAdaptorTableViewCell__) */

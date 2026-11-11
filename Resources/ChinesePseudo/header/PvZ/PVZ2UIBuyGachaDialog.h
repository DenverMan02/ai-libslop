//
//  PVZ2UIBuyGachaDialog.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-5-30.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZ2UIBuyGachaDialog__
#define __PlantsVersusZombies2__PVZ2UIBuyGachaDialog__

#include "PVZ2UIBuyPlantDialog.h"
#include "TodStringFile.h"
#include "UIHelper.h"
#include "ProfileUtils.h"

class PVZ2UIBuyGachaDialog: public PVZ2UIBuyPlantDialog
{
public:
	PVZ2UIBuyGachaDialog(MagentoProductPropsPtr i_props, bool i_quick = true);
	virtual ~PVZ2UIBuyGachaDialog();
    
	virtual void ButtonDepress(int i_id);
    
    
private:
    void OnServerGemCallBack(const bool& i_Success);
    
};

#endif /* defined(__PlantsVersusZombies2__PVZ2UIBuyGachaDialog__) */

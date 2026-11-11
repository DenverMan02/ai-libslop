//
//  BronzeDeadWinCon.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-1-7.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BronzeDeadWinCon__
#define __PlantsVersusZombies2__BronzeDeadWinCon__


#include "LevelModule.h"

class BronzeDeadWinCon : public LevelModule
{
public:
	RT_CLASS_DEFINE(BronzeDeadWinCon, LevelModule, RtClass) {}
	
protected:
	virtual void registerForEvents() override;
	bool    canDamage(const class BoardEntity* i_entity) const;
private:
	bool checkWin();
};

class BronzeDeadWinConProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(BronzeDeadWinConProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return BronzeDeadWinCon::StaticGetClass();
	}
	
	BronzeDeadWinConProperties()
	{
	}
};



#endif /* defined(__PlantsVersusZombies2__BronzeDeadWinCon__) */

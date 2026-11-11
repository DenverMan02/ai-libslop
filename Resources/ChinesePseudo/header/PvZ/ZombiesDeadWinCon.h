//
//  ZombiesDeadWinCon.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiesDeadWinCon_h
#define PlantsVersusZombies2_ZombiesDeadWinCon_h

#include "LevelModule.h"

class ZombiesDeadWinCon : public LevelModule
{
public:
	RT_CLASS_DEFINE(ZombiesDeadWinCon, LevelModule, RtClass) {}
    
    static bool Check();
	
protected:
	virtual void registerForEvents() override;
	
private:
	bool checkWin();
};

class ZombiesDeadWinConProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombiesDeadWinConProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return ZombiesDeadWinCon::StaticGetClass();
	}
	
	ZombiesDeadWinConProperties()
	{
	}
};

// card game zombie dead win
class CardGameZombiesDeadWinCon : public LevelModule
{
public:
	RT_CLASS_DEFINE(CardGameZombiesDeadWinCon, LevelModule, RtClass) {}
    
    static bool Check();
	
protected:
	virtual void registerForEvents() override;
	
private:
	bool checkWin();
};

class CardGameZombiesDeadWinConProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CardGameZombiesDeadWinConProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return CardGameZombiesDeadWinCon::StaticGetClass();
	}
	
	CardGameZombiesDeadWinConProperties()
	{
	}
};


#endif

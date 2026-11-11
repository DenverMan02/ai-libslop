//
//  PerkHandlerModule.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/12/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef PerkHandlerModule_h
#define PerkHandlerModule_h

#include "LevelModule.h"
#include "RtDb.h"

class PerkHandlerModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PerkHandlerModule, LevelModule, RtClass);
	
	~PerkHandlerModule();
	
protected:
	void registerForEvents() override;
	
    
private:
	void initializePerks();
    void onPerkActivated(class PennyPerk* i_perk);

};

class PerkHandlerModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PerkHandlerModuleProperties, LevelModuleProperties, RtClass);
	
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
	RtClass* GetModuleClass() const override
	{
		return PerkHandlerModule::StaticGetClass();
	}
};

#endif /* PerkHandlerModule_h */

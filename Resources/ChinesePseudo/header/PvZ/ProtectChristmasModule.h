//
//  ProtectChristmasModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-22.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ProtectChristmasModule__
#define __PlantsVersusZombies2__ProtectChristmasModule__

#include "LevelModule.h"

class ProtectChristmasModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(ProtectChristmasModule, LevelModule, RtClass);
    
    ProtectChristmasModule();
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
    void        onChristmasProtectDestroy();
    
    void        gameplayStarted();
    void        levelEnded();
	void        winOutroStarted();
    void        onUpdate();
    bool        preventSave();
    
private:
    
    int         m_nProtectDestroyIndex;
    bool        m_bStart;
};


class ProtectChristmasProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ProtectChristmasProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return ProtectChristmasModule::StaticGetClass();
	}
    
    ProtectChristmasProperties()
    {
        
    }
};

#endif /* defined(__PlantsVersusZombies2__ProtectChristmasModule__) */

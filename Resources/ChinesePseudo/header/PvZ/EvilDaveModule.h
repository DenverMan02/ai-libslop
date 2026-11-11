//
//  EvilDaveModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-23.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EvilDaveModule__
#define __PlantsVersusZombies2__EvilDaveModule__

#include "LevelModule.h"
#include "UIWidget.h"

class EvilDaveModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(EvilDaveModule, LevelModule, RtClass);
    
    EvilDaveModule();
	
    float        calcGoalX();
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
    void        levelStarted();
    void        update();
    bool        checkWin();
    
    void        onPlantLost(class Plant * i_plant);
    void        gameplayStarted();
    
    void		addToRenderQueue(class RenderQueue* i_queue);
	void		renderLine(Graphics* i_g);
    
    bool        m_checkCondition;
    
    RtWeakPtr<UIWidget> m_plantCountUI;
};

class EvilDaveProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(EvilDaveProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return EvilDaveModule::StaticGetClass();
	}

    EvilDaveProperties()
    {
        PlantDistance = 6.0f;
    }
    
    float PlantDistance;
};

#endif /* defined(__PlantsVersusZombies2__EvilDaveModule__) */

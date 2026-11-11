//
//  FrontLawnStage.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FrontLawnStage_h__
#define __PlantsVersusZombies2__FrontLawnStage_h__

#include "RtObject.h"
#include "StageModule.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class FrontLawnStage : public StageModule
{
    
public:
    RT_CLASS_DEFINE(FrontLawnStage, StageModule, RtClass);
    
protected:

	void renderBackground(Graphics* i_g) override;
    
    void initializeModule() override;
private:
    bool m_RenderBackGround;
};



class FrontLawnStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(FrontLawnStageProperties, StageModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return FrontLawnStage::StaticGetClass();
	}
};


#endif /* defined(__PlantsVersusZombies2__FrontLawnStage_h__) */

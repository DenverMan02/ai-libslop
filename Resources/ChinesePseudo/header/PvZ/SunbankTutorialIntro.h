//
//  SunbankTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by Leo Wu "Wu Xiangjun" on 13-6-18.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SunbankTutorialIntro__
#define __PlantsVersusZombies2__SunbankTutorialIntro__

#include "StandardLevelIntro.h"
#include "Core.h"

class SunbankTutorialIntro : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(SunbankTutorialIntro, StandardLevelIntro, RtClass);
    
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
    
private:
    void                    onStartIntro();
    void                    onEndLevel();
    void                    onUpdate();
    void                    onNarrationFinished();
    void                    onFakeGemBanked(int i_amount);
    
    void                    showUI(bool i_show);
    
    
    bool                    m_isTutorialEnd;

};

class SunbankTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(SunbankTutorialIntroProperties, StandardLevelIntroProperties, RtClass);
    
	virtual RtClass* GetModuleClass() const override
	{
		return SunbankTutorialIntro::StaticGetClass();
	}
};


#endif /* defined(__PlantsVersusZombies2__SunbankTutorialIntro__) */

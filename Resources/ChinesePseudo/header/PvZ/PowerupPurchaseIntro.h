//
//  PowerupPurchaseIntro.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PowerupPurchaseIntro_h
#define PlantsVersusZombies2_PowerupPurchaseIntro_h

#include "StandardLevelIntro.h"
#include "Core.h"
#include "StandaloneEffect.h"
#include "RenderQueue.h"

class PowerupPurchaseIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(PowerupPurchaseIntro, StandardLevelIntro, RtClass);
	
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;

	virtual bool	suppressReadySetGo() const override;
	
	void			begin();
	void			onTutNarrationFinished();
	virtual void 	onStandardIntroComplete() override;
	void			onHijackedReadySetPlantFinished();
	void 			onLevelEnded();

	void 			addToRenderQueue(class RenderQueue* i_queue);
	void 			onDraw(Graphics* i_g);

private:
	bool 			m_inIntro;
	bool 			m_fadeIn;
	pvztime_t 		m_fadeStart;
};

class PowerupPurchaseIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(PowerupPurchaseIntroProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PowerupPurchaseIntro::StaticGetClass();
	}
	
	std::string Narrative;
};

#endif

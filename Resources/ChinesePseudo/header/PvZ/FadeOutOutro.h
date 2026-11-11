//
//  FadeOutOutro.h
//  PlantsVersusZombies2
//
//  Created by jsola on 7/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FadeOutOutro_h
#define PlantsVersusZombies2_FadeOutOutro_h

#include "LevelModule.h"
#include "OutroModule.h"
#include "TimeLine.h"

class FadeOutOutroModule : public OutroModule
{
public:
	RT_CLASS_DEFINE(FadeOutOutroModule, OutroModule, RtClass) {}
	
	void SetMessage(const SexyString& i_message);
	 
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
	void startLossOutro();
	void onUpdate();
	void addToRenderQueue(class RenderQueue* i_queue);
	void renderMessage(Graphics* i_g);
	
	void outro_notifyComplete(float i_t);

private:
	SexyString m_message;
	TimeLine m_sequence;
};
 
class FadeOutOutroProperties : public OutroModuleProperties
{
public:
	RT_CLASS_DEFINE(FadeOutOutroProperties, OutroModuleProperties, RtClass);
	 
	virtual RtClass* GetModuleClass() const override
	{
		return FadeOutOutroModule::StaticGetClass();
	}
 
	FadeOutOutroProperties()
	{
		DefaultMessage = "";
		PostFadeDelay = 4.f;
		FadeDuration = 2.f;
		FadeColor = Color(0, 0, 0, 255);
	}
	
	std::string DefaultMessage;
	Color FadeColor;
	float FadeDuration;
	float PostFadeDelay;
};

#endif

//
//  Effect_ChallengeFailedMessage.h
//  PlantsVersusZombies2
//
//  Created by jsola on 5/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_ChallengeFailedMessage_h
#define PlantsVersusZombies2_Effect_ChallengeFailedMessage_h

#include "StandaloneEffect.h"

class Effect_ChallengeFailedMessage : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_ChallengeFailedMessage, StandaloneEffect, RtClass);
	
	void SetMessage(const SexyString& i_message);
	
protected:
	virtual void onInitialized() override;
	virtual void onUpdate() override;
	virtual void onDraw(Graphics* i_g) override;

private:
	SexyString m_message;
	pvztime_t m_spawnTime = PVZ_EOT();
};

#endif

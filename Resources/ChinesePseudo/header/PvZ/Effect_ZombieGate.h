//
//  Effect_ZombieGate.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Effect_ZombieGate__
#define __PlantsVersusZombies2__Effect_ZombieGate__

#include "StandaloneEffect.h"
#include "PopAnimRig.h"

class Effect_ZombieGate : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_ZombieGate, StandaloneEffect, RtClass);

	~Effect_ZombieGate();

	void SetRow(const int i_row);
	void SetGateVisible(const bool i_visible);

	void OnAnimDone(const std::string &i_animName);

protected:
	virtual void onInitialized() override;
	virtual void onUpdate() override;
	virtual void onDraw(Sexy::Graphics* i_g) override;

private:

	void playNormalAnim();

	PopAnimRigPtr m_gateRig;
	int m_row = -1;
	bool m_gateVisible = true;
};

#endif /* defined(__PlantsVersusZombies2__Effect_ZombieGate__) */

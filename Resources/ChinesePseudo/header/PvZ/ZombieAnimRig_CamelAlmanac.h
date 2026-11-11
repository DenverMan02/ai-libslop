//
//  ZombieAnimRig_CamelAlmanac.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/15/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_CamelAlmanac__
#define __PlantsVersusZombies2__ZombieAnimRig_CamelAlmanac__

#include "ZombieAnimRig_Camel.h"



class ZombieAnimRig_CamelAlmanac : public ZombieAnimRig_Camel
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_CamelAlmanac, ZombieAnimRig_Camel, RtClass) {}

	ZombieAnimRig_CamelAlmanac();
	~ZombieAnimRig_CamelAlmanac();

	bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	void CalcRigDrawingRect(Sexy::Rect &o_rect) override;

	ZombieAnimRig_Camel* GetMiddleCamel(){ return m_camelMiddle; }
	ZombieAnimRig_Camel* GetEndCamel(){ return m_camelEnd; }
	
protected:
	virtual void onPopAnimInitialized() override;
	virtual void onUpdate() override;
	virtual void onPreDraw(Graphics* i_g) override;

	ZombieAnimRig_Camel* m_camelMiddle;
	ZombieAnimRig_Camel* m_camelEnd;
};



#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_CamelAlmanac__) */

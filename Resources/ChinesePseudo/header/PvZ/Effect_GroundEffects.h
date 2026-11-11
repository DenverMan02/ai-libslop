//
//  Effect_GroundEffects.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/19/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_GroundEffects_h
#define PlantsVersusZombies2_Effect_GroundEffects_h

#include "RtObject.h"
#include "Effect_BeachWaterWave.h"

extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_Tide(class RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_Tide_With_Tail(class RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_Tide_Gargantuar(class RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_RiseFromGround(RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_StuckUnderGround(RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_StuckIntoGround(RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_Surf(class RealObject* i_owner);
extern RtWeakPtr<Effect_PopAnim>	attachGroundEffect_Burrowed(RealObject* i_owner);

class Effect_GroundEffectTide : public Effect_BeachWaterWave
{
public:
	RT_CLASS_DEFINE(Effect_GroundEffectTide, Effect_BeachWaterWave, RtClass) {}
	
protected:
	// Virtual internal dispatches
	void onDraw(Graphics* i_g) override;

private:
	void updateAttachOffset();
	
};

class Effect_GroundEffectSurf : public Effect_BeachWaterWave
{
public:
	RT_CLASS_DEFINE(Effect_GroundEffectSurf, Effect_BeachWaterWave, RtClass);
	Effect_GroundEffectSurf();
	bool IsDone() const;
	
protected:
	// Virtual internal dispatches
	void onUpdate() override;
	void onDraw(Graphics* i_g) override;
	
private:
	float getTargetWakeScale() const;
	void updateAttachOffset();
	
	float m_scale;
};

class Effect_GroundEffectStun : public Effect_BeachWaterWave
{
public:
	RT_CLASS_DEFINE(Effect_GroundEffectStun, Effect_BeachWaterWave, RtClass);
    
    Effect_GroundEffectStun() : m_tEndTime(PVZ_EOT()) {}
    
    void SetEndTime(float iDelay) { m_tEndTime = PVZ_T() + iDelay; }
	
protected:
	// Virtual internal dispatches
	void onUpdate() override;
    
private:
    
    pvztime_t m_tEndTime;
};

#endif

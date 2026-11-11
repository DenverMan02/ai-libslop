//
//  CannonRocket.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-29.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CannonRocket__
#define __PlantsVersusZombies2__CannonRocket__

#include "BoardEntity.h"

class ZombieZombossMech;
class Effect_ZombossRocket;
class Effect_ZombossCrosshair;

class CannonRocket : public BoardEntity
{
public:
	RT_CLASS_DEFINE(CannonRocket, BoardEntity, RtClass);
	
	void InitializeRocketController(const Point& i_boardPixel,
                                    float i_damageAmount);
    
	virtual void OnRocketHitGround();
	
	void StartCrosshairEffect(const std::string& i_crosshairPopAnim, const std::string& i_crosshairAnimation);
	void FadeOutCrosshairEffect();
	void CounterCrosshairEffect();
	void StartRocketEffect(const std::string& i_rocketPopAnim, const std::string& i_rocketAnimation, float i_hitTime, float i_rocketSpeed);
	void CounterRocketEffect();
	void CreateExplosionEffect(const std::string& i_explosionPopAnim, const std::string& i_explosionAnimation);
	
	void CounterRocket();
	bool ShouldDrawShadow() const override { return false; }
	
	bool IsFalling();
    
protected:
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	
private:
    
    float                              m_damageAmount = 0.0f;
	Point                              m_targetBoardPixel;
    RtWeakPtr<Effect_ZombossRocket>    m_rocketEffect;
	RtWeakPtr<Effect_ZombossCrosshair> m_crosshairEffect;
};

#endif /* defined(__PlantsVersusZombies2__CannonRocket__) */

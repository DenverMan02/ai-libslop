//
//  ZombossRocket.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 9/23/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombossRocket_h
#define PlantsVersusZombies2_ZombossRocket_h

#include "BoardEntity.h"

class ZombieZombossMech;
class Effect_ZombossRocket;
class Effect_ZombossCrosshair;

class ZombossRocket : public BoardEntity
{
public:
	RT_CLASS_DEFINE(ZombossRocket, BoardEntity, RtClass);
	
	void InitializeRocketController(const ZombieZombossMech* i_zomboss, const Point& i_gridSquare);

	const Point& GetTargetSquare() const;

	void OnRocketHitGround();
	
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
	bool isInvulnerablePlantInTargetSquare() const;
	
	RtWeakPtr<ZombieZombossMech> m_owningZomboss;
	Point m_targetSquare;
    
    pvztime_t					 m_AutoDestoryTime = PVZ_EOT();
	
	RtWeakPtr<Effect_ZombossRocket>    m_rocketEffect;
	RtWeakPtr<Effect_ZombossCrosshair> m_crosshairEffect;
};


#endif

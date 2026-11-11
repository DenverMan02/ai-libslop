//
//  ZombossCrosshair.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 9/23/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombossCrosshair_h
#define PlantsVersusZombies2_ZombossCrosshair_h

#include "BoardEntity.h"
#include "Effect_PopAnim.h"

class ZombieZombossExplosive;
//class Effect_ZombossCrosshair;
class Effect_ZombossCrosshair;

class ZombossCrosshair : public BoardEntity
{
public:
	RT_CLASS_DEFINE(ZombossCrosshair, BoardEntity, RtClass);
	
	void InitializeRocketController(const ZombieZombossExplosive* i_zomboss, const Point& i_gridSquare);

	const Point& GetTargetSquare() const;

	void OnRocketHitGround();
	
	void StartCrosshairEffect(const std::string& i_crosshairPopAnim, const std::string& i_crosshairAnimation);
	void FadeOutCrosshairEffect();
	void CounterCrosshairEffect();
	void StartRocketEffect(const std::string& i_rocketPopAnim, const std::string& i_rocketAnimation, float i_hitTime, float i_rocketSpeed);
	void CounterRocketEffect();
	void CreateExplosionEffect(const std::string& i_explosionPopAnim, const std::string& i_explosionAnimation);
	
	void CounterRocket();
	
protected:
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	
private:
	bool isInvulnerablePlantInTargetSquare() const;
	
	RtWeakPtr<ZombieZombossExplosive> m_owningZomboss;
	Point m_targetSquare;
	
	//RtWeakPtr<Effect_ZombossCrosshair>  m_rocketEffect;
	RtWeakPtr<Effect_PopAnim>          m_crosshairEffect;
};


#endif

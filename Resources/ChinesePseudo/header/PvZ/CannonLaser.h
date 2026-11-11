//
//  CannonLaser.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.20
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CannonLaser__
#define __PlantsVersusZombies2__CannonLaser__

#include "Projectile.h"


class CannonLaser : public Projectile
{
public:
	RT_CLASS_DEFINE(CannonLaser, Projectile, RtClass);
	CannonLaser();
	virtual ~CannonLaser();
	
	virtual void	Draw(Graphics* i_g) override;
	virtual void	getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
	bool				ShouldDrawShadow() const override { return false; }

	void				Initialise();
	void				SetTarget(const SexyVector3& from, const SexyVector3& to);

	bool				Accept(BoardEntity* i_entity);
protected:
	virtual void	onUpdate(pvztime_t i_dt) override;
	virtual void	onDestroy() override;
	void				onAnimationDone(const std::string& i_animName);

	RtWeakPtr<GameObject> LoadPopanimEffect(std::string i_name, int i_renderLayer);
	float				GetCross(const SexyVector3& p);

protected:
	RtWeakPtr<class Effect_PopAnim> m_laserOriginRig;
	RtWeakPtr<class Effect_PopAnim> m_laserRig;
	SexyVector3		m_laserFrom;
	SexyVector3		m_laserTo;
	pvztime_t			m_timerDestroy;
	pvztime_t			m_timerAttack;
	bool						m_bCanCollision;
	int						m_laserState;
};

class CannonLaserProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(CannonLaserProjectileProps, ProjectilePropertySheet, RtClass);
	CannonLaserProjectileProps();

public:
	std::string		LaserOrginEffect;
	Sexy::Point		LaserStartArtOffset;
	Sexy::Point		LaserEndArtOffset;
	float					AttackTime;
};

#endif /* defined(__PlantsVersusZombies2__CannonLaser__) */

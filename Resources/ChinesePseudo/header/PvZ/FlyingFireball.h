//
//  FlyingFireball.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/16/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FlyingFireball__
#define __PlantsVersusZombies2__FlyingFireball__

#include "BoardEntity.h"
#include "TimeLine.h"

class FlyingFireball : public BoardEntity
{
public:
	RT_CLASS_DEFINE(FlyingFireball, BoardEntity, RtClass);
	
	FlyingFireball();
	
	void StartEffect(Point i_targetLocation, float i_hangTime, float i_apexHeight, float i_burnTime, BoardEntity* i_owner);
	void SetOwner(BoardEntity* i_owner);
	void SetSpawnsDragonImp(bool i_spawnDragonImp);

protected:
	void onUpdate() override;
	void onDestroy() override;
	void onDrawShadow(class Sexy::Graphics* i_g) override;

private:
	void onHitGround();

	RtWeakPtr<class Effect_PopAnim> m_effect;
	BoardEntityPtr m_owner;
	pvztime_t m_burnTime;
	Point m_targetLocation;
	bool m_spawnDragonImp;
	CurveCollection_Float m_movementCurves;
};

#endif /* defined(__PlantsVersusZombies2__FlyingFireball__) */

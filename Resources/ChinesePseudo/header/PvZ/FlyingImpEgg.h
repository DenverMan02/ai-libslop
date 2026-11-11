//
//  FlyingImpEgg.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/20/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FlyingImpEgg__
#define __PlantsVersusZombies2__FlyingImpEgg__

#include "BoardEntity.h"
#include "TimeLine.h"

class FlyingImpEgg : public BoardEntity
{
public:
	RT_CLASS_DEFINE(FlyingImpEgg, BoardEntity, RtClass);
	
	FlyingImpEgg();
	
	void StartEffect(const SexyVector3& i_startingLocation, Point i_targetLocation, float i_hangTime, float i_apexHeight);
    
protected:
	void onUpdate() override;
	void onDestroy() override;
	void onDrawShadow(class Sexy::Graphics* i_g) override;

private:
	void onHitGround();

	RtWeakPtr<class Effect_PopAnim> m_effect;
	Point m_targetLocation;
	CurveCollection_Float m_movementCurves;
};

#endif /* defined(__PlantsVersusZombies2__FlyingImpEgg__) */

//
//  StarLightningCloud.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-8-4.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarLightningCloud__
#define __PlantsVersusZombies2__StarLightningCloud__

#include <iostream>

#include "PopAnimRig.h"
#include "BoardEntity.h"

class StarLightningCloud : public BoardEntity
{
public:
	RT_CLASS_DEFINE(StarLightningCloud, BoardEntity, RtClass);
    
	StarLightningCloud();
    
	void SetOwner(BoardEntityPtr i_owner) { m_owner = i_owner; }
    
protected:
	virtual void onDraw(Graphics* i_g) override;
	virtual void onDrawShadow(Graphics* i_g) override;
	virtual void onInitialized() override;
	virtual void onDestroy() override;
    
private:
	BoardEntityPtr m_owner;
    std::vector<BoardEntityPtr> m_target;
	pvztime_t m_finishTime;
	pvztime_t m_attackTime;
    pvztime_t m_updateTargetTime;
	bool m_canAttack;
    
	PopAnimRigPtr m_animRig;
    
	void onUpdate() override;
    
	void onPlantFinished(const std::string &i_animName);
	void onDieFinished(const std::string &i_animName);
    
	void findTarget();
    
    bool m_isAttacking;
};

#endif /* defined(__PlantsVersusZombies2__StarLightningCloud__) */

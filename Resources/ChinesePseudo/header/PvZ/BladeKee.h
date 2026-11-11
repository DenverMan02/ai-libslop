//
//  GridItemBladeKee.h
//  PlantsVersusZombies2
//
//  Created by hanj on 2/17/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

//PVZ2_CHINESE_BEGIN

#ifndef PlantsVersusZombies2_BladeKee_h
#define PlantsVersusZombies2_BladeKee_h

#include "BoardEntity.h"

class BladeKee : public BoardEntity
{
public:
	RT_CLASS_DEFINE(BladeKee, BoardEntity, RtClass);

	void InitializeBladeKee(float i_velocityByGrid, const SexyVector3& i_initialPosition);

protected:
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onDraw(class Sexy::Graphics* i_g) override;
    
    void onTakePowerEndAnimDone(const std::string& i_label);
    
private:
	void pushPlants();

private:
	float m_velocity = 0;

	RtWeakPtr<class PopAnimRig> 	m_bladeKeeAnim;
    
    bool  m_bIsEnd = false;
};


#endif //PlantsVersusZombies2_BladeKee_h


//PVZ2_CHINESE_END



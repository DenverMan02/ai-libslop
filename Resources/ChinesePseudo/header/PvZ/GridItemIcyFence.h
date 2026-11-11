//
//  GridItemFlame.h
//  PlantsVersusZombies2
//
//  Created by hanj on 12/12/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

//PVZ2_CHINESE_BEGIN

#ifndef PlantsVersusZombies2_GridItemIcyFence_h
#define PlantsVersusZombies2_GridItemIcyFence_h

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"


class GridItemIcyFence : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemIcyFence, GridItemAnimation, RtClass);

	GridItemIcyFence();
	virtual ~GridItemIcyFence(){}

	void Increase();
	void Release();

	void SetDamage(float damage) { m_damage = damage; }

	bool IsDamageable() const override;

	int CalcRenderOrder() const override;

protected:
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void onAnimStopped(const std::string& labelName);
	void playWindAnim(int type);

private:
	float m_damage;
	int m_counter;
	float m_nextAttackTime;
	RtWeakPtr<Effect_PopAnim>   m_windEffect;
};

class GridItemIcyFenceProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemIcyFenceProps, GridItemAnimationProps, RtClass);
	GridItemIcyFenceProps();

	float damageDuration;
	float chillDuration;
};

typedef RtWeakPtr<GridItemIcyFence> IcyFencePtr;


#endif //PlantsVersusZombies2_Flame_h


//PVZ2_CHINESE_END



//
//  GridItemFlame.h
//  PlantsVersusZombies2
//
//  Created by hanj on 12/12/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

//PVZ2_CHINESE_BEGIN

#ifndef PlantsVersusZombies2_Flame_h
#define PlantsVersusZombies2_Flame_h

#include "GridItem.h"
#include "ProjectilePropertySheet.h"

//forward declaration
class BombProperties;
class Projectile;

class GridItemFlame : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemFlame, GridItem, RtClass);

	GridItemFlame(){}
	virtual ~GridItemFlame(){}

	virtual int CalcRenderOrder() const override;

	void Restart();
	void Stop();

	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
	virtual Sexy::Rect calcCollisionRect() override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;

	void attachTo(BoardEntityPtr i_attachedEntity){m_attachedEntity = i_attachedEntity;}
	BoardEntityPtr getAttachedEntity() const {return m_attachedEntity;}

	SexyVector3 CalcProjectileTargetLocation(float i_inTime) const;

protected:
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onDraw(Graphics* i_g) override;
    virtual void onTakeDamage(const DamageInfo& i_damage) override;
	virtual void onGameWon();

	void convertProjectile(Projectile *i_projectile, ProjectilePropertySheetPtr i_newProperties);

private:
	friend class Fuse;

	void GridItemFlameInit(int i_row);
	void reset();

	void spawnExtinctEffect() const;

	void ExtinctFlame();

	RtWeakPtr<class PopAnimRig> 	m_flamePopAnimRig;
	int 							m_row = 0;

	bool							m_doDisappear = false;

	std::vector<RtWeakPtr<Projectile> >		m_affectedProjectiles;

	BoardEntityPtr							m_attachedEntity;
};
typedef RtWeakPtr<GridItemFlame> FlamePtr;


#endif //PlantsVersusZombies2_Flame_h


//PVZ2_CHINESE_END



//

//  GridItemProtectorShieldSegment.h

//  PlantsVersusZombies2

//

//  Created by Michael Fromwiller on 7/24/13.

//  Copyright (c) 2013 PopCap Games. All rights reserved.

//



#ifndef __PlantsVersusZombies2__GridItemProtectorShieldSegment__

#define __PlantsVersusZombies2__GridItemProtectorShieldSegment__



#include "Core.h"

#include "DamageInfo.h"

#include "GridItem.h"

#include "Point.h"

#include "Rect.h"

#include "RtObject.h"

#include "ZombieEnums.h"



namespace Sexy {

class SexyVector3;

}  // namespace Sexy



class GridItemProtectorShieldSegment : public GridItem

{

public:

	

	RT_CLASS_DEFINE(GridItemProtectorShieldSegment, GridItem, RtClass);

	

	virtual void				TakeDamage(const DamageInfo& i_damage) override;

	virtual void				SetPosition(const Sexy::SexyVector3 &i_newPosition) override;

	virtual bool				CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }

    virtual void       SetGridLocation(Sexy::Point i_gridLocation, const bool i_recalculatePosition) override;

	inline void					SetParent(GridItemPtr i_parent);



	inline void					SetGridOffset(const Sexy::Point i_gridOffset);

	inline const Sexy::Point&	GetGridOffset() const;
    bool						NeutralizeSplashDamage() override { return true; }

	virtual void				RecordPreMotion(const Sexy::SexyVector3 &i_position) {}

	void						SetRadius(float i_radius) { m_radius = i_radius; }
	float						GetRadius() { return m_radius; }

protected:



	virtual void				onGridItemInitialize() override;



	virtual Sexy::Rect			calcCollisionRect() override;

	virtual void				onSetPosition(const Sexy::SexyVector3 &i_newPosition) {}

	

private:



	GridItemPtr					m_parent;

	Sexy::Point					m_gridOffset;

	float						m_radius = 0.f;

};



inline void GridItemProtectorShieldSegment::SetParent(GridItemPtr i_parent)

{

	m_parent = i_parent;

}



inline void GridItemProtectorShieldSegment::SetGridOffset(const Sexy::Point i_gridOffset)

{

	m_gridOffset = i_gridOffset;

}



inline const Sexy::Point& GridItemProtectorShieldSegment::GetGridOffset() const

{

	return m_gridOffset;

}

class GridItemProtectorShieldSegmentAlpha : public GridItemProtectorShieldSegment
{
public:

	RT_CLASS_DEFINE(GridItemProtectorShieldSegmentAlpha, GridItemProtectorShieldSegment, RtClass);

	bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return false; }
	bool IsDamageable() const override { return false; }
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override  { return false; }

	void RecordPreMotion(const Sexy::SexyVector3 &i_position) override;
	void onSetPosition(const Sexy::SexyVector3 &i_newPosition) override;

	void onUpdate() override;

protected:
	void onDestroy() override;

private:
	void flickZombie(class Zombie* i_zombie);
	void checkEdge();
	void checkZombies();
	void checkDistancedZombies();
	bool canCheckZombies();
	bool isZombieAlreadyPushed(ZombiePtr i_zombie = nullptr);
	bool OnCollideEntity(BoardEntity* i_entity);
	bool IsValidTarget(ZombiePtr i_zombie) const;

	SexyVector3 m_prePosition;
	std::vector<RtWeakPtr<class Zombie>> m_pushedZombies;
};

namespace Message
{
	void NotifyShieldBlock(int i_type);
}


#endif /* defined(__PlantsVersusZombies2__GridItemProtectorShieldSegment__) */


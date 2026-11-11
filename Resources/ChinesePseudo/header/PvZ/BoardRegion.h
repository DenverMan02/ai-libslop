//
//  BoardRegion.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 8/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BoardRegion__
#define __PlantsVersusZombies2__BoardRegion__

#include "Core.h"
#include "GameObject.h"
#include "BoardEnums.h"
#include "PVZTypes.h"

enum BoardRegionFlags
{
	PVZ_BEGIN_FLAG_ENUM(BOARDREGION_),
	PVZ_FLAG(BOARDREGION_PitOfDoom),
	PVZ_FLAG(BOARDREGION_ShallowWater),
	PVZ_FLAG(BOARDREGION_Sky),
    PVZ_FLAG(BOARDREGION_Gold),
	PVZ_FLAG(BOARDREGION_Roof),
	PVZ_FLAG(BOARDREGION_Concrete),
	PVZ_FLAG(BOARDREGION_OppoentArea),
	PVZ_FLAG(BOARDREGION_DisabledArea),
	PVZ_END_FLAG_ENUM(BOARDREGION_)
};

class BoardRegion : public GameObject
{
public:
	RT_CLASS_DEFINE(BoardRegion, GameObject, RtClass);
	
	BoardRegion();

	// Operations
	void Update();
	
	// Getters and setters
	void SetFlags(BoardRegionFlags i_flags);
	BoardRegionFlags GetFlags() const;
	bool HasFlags(BoardRegionFlags i_flag) const;
	
	void SetRegionFromBoardCoordinates(const FRect& i_region);
	void SetRegionFromGridSquares(const Rect& i_gridRegion);
	FRect GetRegion() const;
	virtual void DrawCollisionInfo(Graphics* g);
	
	bool Contains(const SexyVector3& i_boardLocation) const;
	bool Contains(const Point& i_gridLocation) const;

	void GetContainedEntities(std::vector<class BoardEntity*>& io_ents, BoardEntityTypeFlag i_types, std::function<bool(class BoardEntity*)> i_acceptanceFunc = nullptr);
	
	// Virtual interface (public)
	virtual void DoEntityEnteredEffects(const SexyVector3& i_boardLocation, class BoardEntity* i_enteringEntity) { }
	virtual void GatherPlantingRestrictions(const Sexy::Point& i_atLocation, const class PlantType* i_plantType, std::vector<PlantingReason> * io_plantingErrors) { }
	virtual float GetGroundHeightOffsetFraction(const SexyVector3& i_boardLocation) { return 0.f; }
	
protected:
	// Virtual interface (protected)
	virtual void onUpdate() {}
	
private:
	BoardRegionFlags m_flags;
	FRect m_region;
};

namespace Message
{
	void BoardRegionResized(BoardRegion* i_region);
}

#endif /* defined(__PlantsVersusZombies2__BoardRegion__) */

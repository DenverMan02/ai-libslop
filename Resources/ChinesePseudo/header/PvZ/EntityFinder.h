#ifndef __ENTITYFINDER_H__
#define __ENTITYFINDER_H__

#include <vector>

#include "PVZTypes.h"
#include "PlatformAutodetect.h"
#include "Rect.h"
#include "RtDelegate.h"
#include "BoardEntity.h"

class BoardEntity;
namespace Sexy {
class RtClass;
class SexyVector2;
class SexyVector3;
}  // namespace Sexy

///
/// The EntityFinder namespace contains a variety of methods for finding entities
///
namespace EntityFinder
{
	class BoardEntitySorter;
	typedef Delegate1wRet<bool, BoardEntity*> EntitySearchAcceptDelegateType;
	typedef Event1wRet<EventReturnBehavior::LogicalAnd_ShortCircuit_DefaultTrue, bool, BoardEntity*> EntitySearchAcceptEventType;
	
	// Base Entity Search functions
	void GetEntities(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const EntitySearchAcceptEventType& i_acceptEvent);
	void GetEntities(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes);
    void GetEntitiesOnBoard(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes);
    
	// These functions look only at Entity Position, ignoring bounding boxes and row position entirely
	void GetEntitiesInRectangle(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRect);
	void GetEntitiesInGridSquares(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRectGridSquares);
	void GetEntitiesAtGridSquare(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const int i_x, const int i_y);
	void GetEntitiesWithinCircle(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector3& i_searchLocation, const float i_radius);
	void GetEntitiesWithinCircle2D(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchLocation, const float i_radius);
    void GetEntitiesTouchingRay(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchLocation, const SexyVector2& i_searchDirection, int i_topRow = -1, int i_bottomRow = -1);
	// These functions use Entity bounding boxes, and are restricted to entities within the same
	// logical rows as the search query (or the optional row values passed in)
	void GetEntitiesTouchingRectangle(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRect, int i_topRow = -1, int i_bottomRow = -1);
	void GetEntitiesTouchingPoint(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchPoint, int i_topRow = -1, int i_bottomRow = -1);
	void GetEntitiesTouchingCircle2D(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const SexyVector2& i_searchLocation, float i_radius, int i_topRow = -1, int i_bottomRow = -1);
	void GetEntitiesTouchingRectangleWithoutGrid(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const Sexy::Rect& i_searchRect);
	
	// Type/Class matchers
	void GetEntitiesMatchingClass(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, RtClass* i_acceptedBaseClass);
	void GetEntitiesInRowMatchingClass(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, int32 zombieRow, RtClass*);
	void GetZombiesAtGridSquareWithType(std::vector<BoardEntity*>& o_entityList, const int i_x, const int i_y, ZombieTypePtr zombieType);
	bool HasZombiesAtGridSquareWithType(const int i_x, const int i_y, ZombieTypePtr zombieType);
	void GetEntitiesAtGridSquareMatchingClass(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const int i_x, const int i_y, RtClass* i_matchClass);
	
	
	// Combined entity searching
	// Searches multiple regions, sorting each region by the passed in BoardEntitySorter, and returns the sorted result in order of region.
	// Example: Searching the current row first, then the row above, then the row below, with each row's results sorted by closest to the given X value.
	void EntityFinderGridspace(std::vector<BoardEntity*>& o_entityList, BoardEntityTypeFlag i_acceptedTypes, const std::vector<Sexy::Rect>& i_searchRects, BoardEntitySorter* i_sorter);

	// Entity list pull functions
	// Removes & returns matching entity
	BoardEntity* PullFirstMatchingEntity(std::vector<BoardEntity*>& io_entities, int i_preferredRow, bool i_allowMainPool);

	//
	// std::sort Algorithms
	//
	
	class BoardEntitySorter
	{
	public:
		virtual ~BoardEntitySorter() {}
		
		virtual bool operator()(BoardEntity* i_a, BoardEntity *i_b) const { return true; }
	};

	class BoardEntitySorter_Closest_WeightNewRows : public BoardEntitySorter
	{
	public:
        BoardEntitySorter_Closest_WeightNewRows(Sexy::Point i_gridPosition, const std::vector<RtWeakPtr<BoardEntity> >& i_previousTargets);
		bool operator()(BoardEntity* i_a, BoardEntity *i_b) const override;
		
	private:
		bool findEntityInRow(const std::vector<RtWeakPtr<BoardEntity> >& i_entities, int i_row) const;
		
        Sexy::Point m_gridOrigin;
		std::vector<RtWeakPtr<BoardEntity> > m_previousTargets;
	};

	class BoardEntitySorter_ClosestByColumn : public BoardEntitySorter
    {
    public:
        BoardEntitySorter_ClosestByColumn(Point i_gridPosition);
        bool operator()(BoardEntity* i_a, BoardEntity* i_b) const override;
        
    private:
        Point m_gridOrigin;
    };
	
	class BoardEntitySorter_Closest : public BoardEntitySorter
	{
	public:
		BoardEntitySorter_Closest(Point i_gridPosition);
		bool operator()(BoardEntity* i_a, BoardEntity* i_b) const override;

	private:
		Point m_gridOrigin;
	};

		// Template helper functions
	
	template <typename T>
	T* GetGridItemAt(int i_gridX, int i_gridY)
	{
		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesAtGridSquare(entities, ENTITYTYPE_GRIDITEM, i_gridX, i_gridY);
		
		for (auto entity : entities)
		{
			T* gridItem = entity->CastChecked<T>();
			if (gridItem)
			{
				return gridItem;
			}
		}
		return NULL;
	}

	bool CheckGridValid(Sexy::Point grid);
	std::vector<Sexy::Point> CalcAroundGrids(Sexy::Point grid);
}

#endif

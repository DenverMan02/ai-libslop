//
//  EntitySearch.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 12/16/15.
//  Copyright © 2015 PopCap Games. All rights reserved.
//

#ifndef EntitySearch_h
#define EntitySearch_h

#include "BoardEntity.h"
#include "DebugDraw.h"
#include "LawnApp.h"
#include "Plant_LilyPad.h"
#include "PVZCheats.h"
#include "RealObject.h"
#include "Zombie.h"

class EntitySearch_InGridSquares
{
public:
	EntitySearch_InGridSquares(const Rect& i_searchRect)
	: m_searchRectangle(i_searchRect)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		Rect entityRect = i_entity->CalcGridFootprint();
		return entityRect.Intersects(m_searchRectangle);
	}
	
	Rect m_searchRectangle;
};

class EntitySearch_WithinRadius
{
public:
	EntitySearch_WithinRadius(const SexyVector3& i_searchLoc, float i_searchRadius)
	: m_searchLoc(i_searchLoc), m_radiusSqr(i_searchRadius * i_searchRadius)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		SexyVector3 diff = (i_entity->GetPosition() - m_searchLoc);
		return (diff.MagnitudeSquared() <= m_radiusSqr);
	}
	
	SexyVector3 m_searchLoc;
	float m_radiusSqr;
};

class EntitySearch_WithinRadius2D
{
public:
	EntitySearch_WithinRadius2D(const SexyVector2& i_searchLoc, float i_searchRadius)
	: m_searchLoc(i_searchLoc), m_radiusSqr(i_searchRadius * i_searchRadius)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		SexyVector3 loc = i_entity->GetPosition();
		SexyVector2 boardLoc(loc.x, loc.y);
		SexyVector2 diff = (boardLoc - m_searchLoc);
		return (diff.MagnitudeSquared() <= m_radiusSqr);
	}
	
	SexyVector2 m_searchLoc;
	float m_radiusSqr;
};

class EntitySearch_InRectangle
{
public:
	EntitySearch_InRectangle(const Rect& i_searchRectangle)
	: m_searchRectangle(i_searchRectangle)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		SexyVector3 loc = i_entity->GetPosition();
		return m_searchRectangle.Contains(loc.x, loc.y);
	}
	
	Rect m_searchRectangle;
};

class EntitySearch_InGridRows
{
public:
	EntitySearch_InGridRows(int i_topRow, int i_bottomRow)
	: m_searchRectangle(-100, i_topRow, 200, i_bottomRow - i_topRow + 1)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		Rect entityRect = i_entity->CalcGridFootprint();
		return entityRect.Intersects(m_searchRectangle);
	}
	
	Rect m_searchRectangle;
};

class EntitySearch_TouchingPoint
{
public:
	EntitySearch_TouchingPoint(const SexyVector2& i_searchPoint)
	: m_searchPoint(i_searchPoint.x, i_searchPoint.y)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		Rect entityRect = i_entity->GetCollisionRect();
		return entityRect.Contains(m_searchPoint);
	}
	
private:
	Point m_searchPoint;
};

class EntitySearch_TouchingCircle
{
public:
	EntitySearch_TouchingCircle(const SexyVector2& i_searchLocation, float i_radius)
	: m_searchLocation(i_searchLocation), m_radius(i_radius)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		Rect entityRect = i_entity->GetCollisionRect();
		bool hits = RectCircleIntersection(entityRect, m_searchLocation, m_radius);
		// TODO -- Add 'Debug Collision Tests' cheat
		//DebugDraw_Box(S(entityRect.mX), S(entityRect.mY), S(entityRect.mX + entityRect.mWidth), S(entityRect.mY + entityRect.mHeight), hits ? Color::Green : Color::Red, RectEntry::DRAWMODE_Wireframe, 3.f);
		return hits;
	}
	
private:
	SexyVector2 m_searchLocation;
	float m_radius;
};

class EntitySearch_TouchingRectangle
{
public:
	EntitySearch_TouchingRectangle(const Rect& i_searchRectangle)
	: m_searchRectangle(i_searchRectangle)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		Rect entityRect = i_entity->GetCollisionRect();
		bool hits = entityRect.Intersects(m_searchRectangle);
		// TODO -- Add 'Debug Collision Tests' cheat
		// DebugDraw_Box(S(m_searchRectangle.mX), S(m_searchRectangle.mY), S(m_searchRectangle.mX + m_searchRectangle.mWidth), S(m_searchRectangle.mY + m_searchRectangle.mHeight), Color::Blue, RectEntry::DRAWMODE_Wireframe, 1.f);
		// DebugDraw_Box(S(entityRect.mX), S(entityRect.mY), S(entityRect.mX + entityRect.mWidth), S(entityRect.mY + entityRect.mHeight), hits ? Color::Green : Color::Red, RectEntry::DRAWMODE_Wireframe, 1.f);
		return hits;
	}
	
private:
	Rect m_searchRectangle;
};

class EntitySearch_TouchingRay
{
public:
	EntitySearch_TouchingRay(const SexyVector2& i_searchLocation, const SexyVector2& i_searchDirection)
	: m_searchLocation(i_searchLocation), m_searchDirection(i_searchDirection)
	{}
	
	bool Accept(BoardEntity* i_entity)
	{
		Rect entityRect = i_entity->GetCollisionRect();
		bool hits = RectRayIntersection(entityRect, {m_searchLocation, m_searchDirection});
		// TODO -- Add 'Debug Collision Tests' cheat
		//DebugDraw_Box(S(entityRect.mX), S(entityRect.mY), S(entityRect.mX + entityRect.mWidth), S(entityRect.mY + entityRect.mHeight), hits ? Color::Green : Color::Red, RectEntry::DRAWMODE_Wireframe, 3.f);
#ifndef WANTS_CHEATS_DISABLED
		if ( gLawnApp->m_board && gCheats->GetToggleValue("DrawCollisionInfo") )
		{
			static const float k_DirectionMultiplier = 10000.f;
			DebugDraw_Line(S(m_searchLocation.x), S(m_searchLocation.y), S(m_searchLocation.x + k_DirectionMultiplier * m_searchDirection.x), S(m_searchLocation.y + k_DirectionMultiplier * m_searchDirection.y), Color::Red, 1.f);
		}
#endif
		
		return hits;
	}
	
private:
	SexyVector2 m_searchLocation;
	SexyVector2 m_searchDirection;
	float m_radius;
};

class EntitySearch_MatchesClass
{
public:
	EntitySearch_MatchesClass(RtClass* i_baseClassToMatch)
	{
		m_baseClassToMatch = i_baseClassToMatch;
	}
	
	bool Accept(BoardEntity* i_entity)
	{
		return i_entity->IsA(m_baseClassToMatch);
	}
	
private:
	RtClass* m_baseClassToMatch;
};

class EntitySearch_MatchesZombieType
{
public:
	EntitySearch_MatchesZombieType(ZombieTypePtr i_zombieType)
	{
		m_zombieType = i_zombieType;
	}
	
	bool Accept(BoardEntity* i_entity)
	{
		Zombie* zombie = i_entity->Cast<Zombie>();
		return (zombie && zombie->GetType() == m_zombieType);
	}
	
private:
	ZombieTypePtr m_zombieType;
};

class EntitySearch_IsOnOpposingTeam
{
public:
	EntitySearch_IsOnOpposingTeam(BoardEntityPtr i_comparisonEntity)
	{
		m_comparisonEntity = i_comparisonEntity;
	}
	
	bool Accept(BoardEntity* i_entity)
	{
		return m_comparisonEntity->IsOnOpposingTeam(i_entity);
	}
	
private:
	BoardEntityPtr m_comparisonEntity;
};

class EntitySearch_IsLilyPad
{
public:
	EntitySearch_IsLilyPad(BoardEntityPtr i_comparisonEntity)
	{
		m_comparisonEntity = i_comparisonEntity;
	}
	
	bool Accept(BoardEntity* i_entity)
	{
		return i_entity->IsA<GridItemLilyPad>();
	}
	
	bool Reject(BoardEntity* i_entity)
	{
		return !i_entity->IsA<GridItemLilyPad>();
	}
	
private:
	BoardEntityPtr m_comparisonEntity;
};

class EntitySearch_Lambda
{
public:
	EntitySearch_Lambda(std::function<bool(BoardEntity*)> i_function)
	: m_internalLambda(i_function) {}
	
	bool Accept(BoardEntity* i_entity)
	{
		return m_internalLambda(i_entity);
	}
	
private:
	std::function<bool(BoardEntity*)> m_internalLambda;
};

namespace EntitySearch
{

};

#endif /* EntitySearch_h */

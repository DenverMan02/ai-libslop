/*
 * GridItemTileSubSystem.h
 *
 *  Created on: 2019-8-27
 *      Author: zhousen
 */

#ifndef GRIDITEMTILESUBSYSTEM_H_
#define GRIDITEMTILESUBSYSTEM_H_

#include "RtObject.h"
#include "GameSubSystem.h"

///
/// grid item statistics system
///
class GridItemTileSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(GridItemTileSubSystem, GameSubSystem, RtClass);

	GridItemTileSubSystem();
	virtual ~GridItemTileSubSystem();

	virtual void AddGridItemPosition(std::vector<Sexy::Point> list);
	virtual void AddGridItemPosition(Sexy::Point point);
	virtual void RemoveGridItemPosition(std::vector<Sexy::Point> list);
	virtual void RemoveGridItemPosition(Sexy::Point point);
	virtual bool IsInContainer(Sexy::Point point);

	virtual void ClearContainer();

protected:
	std::vector<Sexy::Point> _gridItemPositionContainer;
};

// Aloes
class WaterMistTileSubSystem : public GridItemTileSubSystem
{
public:
	RT_CLASS_DEFINE(WaterMistTileSubSystem, GridItemTileSubSystem, RtClass);
};

// ZombiePerfumer
class PoisonMistTileSubSystem : public GridItemTileSubSystem
{
public:
	RT_CLASS_DEFINE(PoisonMistTileSubSystem, GridItemTileSubSystem, RtClass);
};

// Icelotus
class DropwaterTileSubSystem : public GridItemTileSubSystem
{
public:
	RT_CLASS_DEFINE(DropwaterTileSubSystem, GridItemTileSubSystem, RtClass);
};

// ZombieHanabi
class HanabiTileSubSystem : public GridItemTileSubSystem
{
public:
	RT_CLASS_DEFINE(HanabiTileSubSystem, GridItemTileSubSystem, RtClass);
};

#endif /* GRIDITEMTILESUBSYSTEM_H_ */

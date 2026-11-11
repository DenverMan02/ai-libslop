//
//  PowerTileSubsystem.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 1/28/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerTileSubsystem__
#define __PlantsVersusZombies2__PowerTileSubsystem__

#include "Core.h"
#include "BoardEnums.h"
#include "GameSubSystem.h"
#include "PopAnimRig.h"
#include "PVZTypes.h"

enum PowerTileClass
{
	PVZ_BEGIN_ENUM(POWERTILE_),
	POWERTILE_ALPHA,
	POWERTILE_BETA,
	POWERTILE_GAMMA,
	POWERTILE_DELTA,
	POWERTILE_EPSILON,		// Pooped out by the Power Plant
	PVZ_END_ENUM(POWERTILE_)
};

struct PowerTilePropagation_ConnectingDotHandler
{
	PowerTilePropagation_ConnectingDotHandler();
	void CreateRig();
	void DestroyRig();

	void FadeIn();
	void FadeOut();

	void Update();
	void Draw(Graphics* i_g);

	RtWeakPtr<class EffectAnimRig_LinkedTileConnect> RigPtr;
	SexyVector2			BoardLocation;
	Color				TintColor;
	bool				Done;
	pvztime_t			FadeInTime;
	pvztime_t			FadeOutTime;
	AnimHandle			FadeOutAnimHandle;
};

struct PowerTilePropagationInfo
{
	PowerTilePropagationInfo()
	{
		Timer = 0.f;
		IsBossPropagation = false;
	}

	void BuildTileGlows(const Color& i_tint);
	void DestroyTileGlows();

	bool IsDone();

	Sexy::Point 		SourceLocation;
	Sexy::Point			TargetLocation;
	PowerTileClass		Group;
	RtWeakPtr<class GridItemPowerTile> TargetTile;
	float				StartTime;
	float				TotalTime;
	float				Timer;
	bool 				IsBossPropagation;

	std::vector<PowerTilePropagation_ConnectingDotHandler> Dots;
};

class GridItemPowerTile;
class Plant;
class PlantType;

class PowerTileSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PowerTileSubsystem, GameSubSystem, RtClass);

	PowerTileSubsystem();
	
	void				ClearPowerTiles();

	GridItemPowerTile*	FindPowerTileAt(const Sexy::Point& i_gridLoc) const;
	// Pass in POWERTILE_Invalid to get a total count of all linked tiles
	int					GetPowerTileCount(PowerTileClass i_class);
	void				FindPowerTilesByClass(PowerTileClass i_class, std::vector<GridItemPowerTile*>& o_powerTiles);

	bool				CanAddPowerTileAt(PowerTileClass i_type, const Sexy::Point& i_gridLoc);
	bool				TryAddPowerTileAt(PowerTileClass i_type, const Sexy::Point& i_gridLoc, int i_special = 0);

	virtual void		DestroyPowerTileAt(const Sexy::Point& i_gridLoc);
	virtual void		DestroyPowerTileAtAndPropagate(const Sexy::Point& i_gridLoc);

	std::vector<RtWeakPtr<GridItemPowerTile> >& GetPowerTiles();
	std::vector<PowerTilePropagationInfo>& GetLinkedTilePropagations();
	const std::vector<RtWeakPtr<GridItemPowerTile> >& GetPowerTiles() const;
	const std::vector<PowerTilePropagationInfo>& GetLinkedTilePropagations() const;

	static PowerTileClass GetPowerTileClassFromToolPacketName(const std::string& i_packetType);
	static GridItemTypePtr GetGridItemType(const PowerTileClass i_tileClass);

	void				Update() override;
	void				AddToRenderQueue(class RenderQueue* i_queue) override;

private:
	void				registerForEvents() override;

	void				renderDots(Sexy::Graphics* i_g);

	void				addPowerTile(const Point& i_gridLocation, PowerTileClass i_tileClass, int i_special = 0);
	void				destroyPowerTile(GridItemPowerTile* i_tile);
	void				destroyPowerTileAtIndex(const int i_index);
	void				propagateFromTile(GridItemPowerTile* i_fromTile, bool i_isBossPropagation);

	void                onPowerTileAdded(class GridItem* i_gridItem);
	void				onToolAppliedPlantFood(class PlantGroup* i_plant);
    void				onToolAppliedPlantFoodToGridItem(class GridItem* i_gridItem);
	void				onGatherPlantedPacketCount(const std::string& i_toolPacketName, int* io_plantedPacketAccumulator);
	void				onPlantPlanted(class Plant* i_plant);
	void				onPlantDied(class Plant* i_plant);
    void				onLilyPadDied(class GridItemLilyPad* i_lilyPad);
	void				onPlantPlantfooded(class Plant* i_plant);
	void				gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	void				onGameWon();
    void				clearEverything();

	std::vector<RtWeakPtr<GridItemPowerTile> > m_powerTiles;
	std::vector<PowerTilePropagationInfo> m_linkedTilePropagations;
	
	int					m_plantsPlantedOnPowerTiles;
};


#endif /* defined(__PlantsVersusZombies2__PowerTileSubsystem__) */

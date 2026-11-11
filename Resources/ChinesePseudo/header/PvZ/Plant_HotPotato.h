//
//  Plant_HotPotato.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 10/31/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_HotPotato__
#define __PlantsVersusZombies2__Plant_HotPotato__

#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantType.h"
#include "RestrictionSet.h"

class GridItemBreakableTarget;

enum HotPotatoState
{
	PVZ_BEGIN_ENUM(HOTPOTATOSTATE_),
	HOTPOTATOSTATE_LANDING,
	HOTPOTATOSTATE_MELTINGBLOCK,
	HOTPOTATOSTATE_FADINGOUT,
	PVZ_END_ENUM(HOTPOTATOSTATE_),
};

class HotPotatoProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HotPotatoProps, PlantPropertySheet, RtClass);
	
	// Time from the moment we start melting (not the moment we're planted!) to the moment
	// we start to fade out.  The potato is in downward motion for this duration.
	float BlockMeltingDuration;
};

class PlantHotPotato : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHotPotato, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animName) override;
	
	int CalcRenderOrder() override;
	
	bool CanBeShoveled()		override	{ return false; }
	bool HasShadow() 		override	{ return false; }
	bool CanBeTargeted()		override	{ return false; }
	bool IsInvincible() const override	{ return true; }
	
private:
	void setState(const HotPotatoState& i_newState);
	void beginCurrentState(const HotPotatoState& i_fromState);
	void updateCurrentState();
	void endCurrentState(const HotPotatoState& i_toState);
	
	void acquireTarget();
    float getIceBlockHeight() const;
	
	void destroyIceBlock() const;
	GridItemBreakableTarget* getTarget() const;
	void spawnSteamCloud();
    
    void updateMeltingBlockState();
    void updatePlantMeltingPosition();
    void updateMeltedIce();
    void spawnPuddle();
	
	HotPotatoState m_state;
	pvztime_t m_blockMeltingDuration;
	pvztime_t m_blockMeltingEndTime;
	SexyVector3 m_startPosition;
	SexyVector3 m_finalPosition;
    bool m_hasSpawnedPuddle;
};

class PlantAnimRig_HotPotato : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HotPotato, PlantAnimRig, RtClass) {}
	
	bool PlayPlantAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayPreviewAnim(bool bHideLayer) override;
};

class PlantTypeHotPotato : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeHotPotato, PlantType, RtClass);
	
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
    bool CanPlantOnConvertedPlant(PlantPtr i_targetPlant) const override;

	GridItemRestrictionSet TargetableGridItemTypes;
};

#endif /* defined(__PlantsVersusZombies2__Plant_HotPotato__) */

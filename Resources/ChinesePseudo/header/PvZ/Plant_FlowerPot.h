#ifndef __PLANT_FLOWERPOT_H__
#define __PLANT_FLOWERPOT_H__

#include "PlantFramework.h"
#include "BoardEnums.h"
#include "GridItemAnimation.h"
#include "PlantAnimRig.h"
#include "PlantType.h"

class PlantFlowerPot : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantFlowerPot, PlantFramework, RtClass);

	void Initialize() override;

    bool IsInvincible() const override { return true; }
	bool CanBeShoveled() override { return false; }
	bool HasShadow() override { return true; }

	void ApplyPlantfood() override;

	GridItem* m_gridItemSpawnPointer = NULL;
};

class GridItemFlowerPot : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemFlowerPot, GridItemAnimation, RtClass);

	int		CalcRenderOrder() const override;

	void	ApplyPlantfood();
	void	Heal();

	bool	CanBeShoveled() override;
	int		Shovel() override;
    
    void    SetIsDuplicatePlant(bool i_duplicate);
	bool	IsDuplicatePlant() { return m_isDuplicate; }
	void	SetRenderOffset(SexyVector2 i_offset) { m_renderOffset = i_offset; }

	bool	CanBeTargetedBy(const BoardEntity* i_entity) const override;
	EntityComponent_GroundEffect GetGroundEffect() { return m_groundEffect; }

protected:
	SexyVector2	getRenderOffset() override;
	void	registerForEvents() override;
	void	GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	void	onGridItemInitialize() override;
	void	onTakeDamage(const DamageInfo& i_damage) override;
	void	onKilled() override;
	void	onDestroy() override;

private:
	void	onPlantSmashed(Plant* i_plant);
    
    bool	m_isDuplicate = false;
    EntityComponent_GroundEffect m_groundEffect;
	SexyVector2 m_renderOffset;
};

class GridItemAnimRig_FlowerPot : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemAnimRig_FlowerPot, PlantAnimRig, RtClass);

	void PlayIdle();
	void PlayPlantEnteredTile();
	void PlayPlantLeftTile();
	void SetPlantIsOnTile(bool i_onTile);

private:
	void onPopAnimInitialized() override;
	void onAnimStopped() override;

	bool m_isOccupied = false;
	bool m_isOnWater = false;
};

class GridItemFlowerPotProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemFlowerPotProps, GridItemAnimationProps, RtClass);
    GridItemFlowerPotProps() {}
    
    PlantRestrictionSet PlantsWhichCannotBePlantedOnFlowerPots;
};

class PlantTypeFlowerPot : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeFlowerPot, PlantType, RtClass);

	void GatherPlantingRestrictions(class Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;	
};

namespace Message
{
	void FlowerPotDied(class GridItemFlowerPot* i_FlowerPot);
}

#endif // __PLANT_LILYPAD_H__

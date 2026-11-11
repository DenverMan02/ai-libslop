/*
 * Plant_MoonFlower.h
 *
 *  Created on: 2017-6-30
 *      Author: Administrator
 */

#ifndef PLANT_MOONFLOWER_H_
#define PLANT_MOONFLOWER_H_

#include <string>

#include "PlantFramework.h"
#include "ComponentConditionRadius.h"
#include "Shield.h"
#include "SunProducer.h"
#include "RestrictionSet.h"
#include "GridItemInfinutShieldSegment.h"
#include "GridItemRailcart.h"
#include "AnimRigLayerSet.h"
#include "GameSubSystem.h"
#include "GridSquareMoonFlowerGlow.h"

enum MoonFlowerFetchType
{
	MOONFLOWER_FETCH_ALL,
	MOONFLOWER_FETCH_ORPHANS
};

class MoonFlowerPoweredTilesSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(MoonFlowerPoweredTilesSubsystem, GameSubSystem, RtClass);

	MoonFlowerPoweredTilesSubsystem();
	virtual ~MoonFlowerPoweredTilesSubsystem();

	void AddGlowEffects(Plant* i_plant);
	void RemoveGlowEffects(Plant* i_plant);
	void UpdateGlowEffects(Plant *i_plant);

	void SetGridSquareWidth(float i_width);
	float getRadiusInGridSquareWidths() const;
private:
	void onPlantKilled(Plant* i_plant);
	void onRailcartMoved(GridItemRailcart* i_railcart);
	void onPlantPlaced(Plant *i_plant);

	int getMoonFlowerGlows(Plant *i_plant, std::vector<GridSquareMoonFlowerGlow*> &io_scratchGlows, MoonFlowerFetchType whatToFetch);

	// helper functions
	void initScratchVector(std::vector<GridSquareMoonFlowerGlow*> &io_scratchGlows, int size);
	bool isOrphanedGlow(GridSquareMoonFlowerGlow *glow, Plant *i_plant);
	Point gridToBoardCentered(Point gridLoc);
	float convertRadiusGridToBoard();

	float	m_radiusInGridSquareWidths;
};

class MoonFlowerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MoonFlowerProps, PlantPropertySheet, RtClass);

	MoonFlowerProps()
	:MaxSunProduction(0)
	,SunPerNeighbor(0)
	{}

	ComponentConditionRadiusProps BoostRadius;
	int SunPerNeighbor;
	int MaxSunProduction;
	float SunProducerRandomPercent;
	PlantRestrictionSet ShadowBoostable;
};

class PlantMoonFlower : public PlantFramework
{
public:
	static const std::string k_boostedLayerSetName;
	static const std::string k_normalLayerSetName;

public:
	RT_CLASS_DEFINE(PlantMoonFlower, PlantFramework, RtClass);
	PlantMoonFlower();
	virtual ~PlantMoonFlower();

	void Initialize() override;
	void ProduceSun(const PlantAction& i_fromAction) override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void avatarSkillAddShield(bool isChangePos = false);
	bool isAvatarShieldAlreadyShow() const;
	void avatarSkillShieldHeal() const;
	bool isAllFullHealth() const;
	void removeShield();
	void UpdateActions() override;
	void OnRelocationBegun() override;
	void OnRelocationComplete() override;

	void onApplyCondition(PlantConditions i_condition) override;
	void onEndCondition(PlantConditions i_condition) override;

protected:
	void onKilled(bool i_instantKill) override;

private:
	PowerPropsSunProducer getSunProduction();
	PowerPropsSunProducer getPerSunProduction();
	PowerPropsSunProducer getPlantFoodSunProduction();
	void skillProduceSun();
	int calcNumBoostedPlants();
	std::string getCurrentLayerSetName();
	void onPlantPlaced(Plant* i_plant);

	RtWeakPtr<ComponentConditionRadius> m_boostRadius;
	RtWeakPtr<MoonFlowerPoweredTilesSubsystem> m_moonflowerSystem;
	std::vector<RtWeakPtr<GridItemInfinutShieldSegment>> m_vecShield;
	bool m_bIsShieldAlreadyShow;
    int m_rowInBoard;
    int m_columInBoard;
    
public:
    int GetRowInBoard() const { return m_rowInBoard; }
    int GetColumInBoard() const { return m_columInBoard; }
};

class PlantAnimRig_MoonFlower : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_MoonFlower, PlantAnimRig, RtClass);

	void onPopAnimInitialized() override;
	void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowLayerSet(std::string setName);
	bool PlayZenGardenIdleAnim() override;
	bool PlayPreviewAnim(bool bHideLayer) override;

private:
	AnimRigLayerSet m_layerSet;
};


#endif /* PLANT_MOONFLOWER_H_ */

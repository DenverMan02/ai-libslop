//
//  TideModule.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TideModule__
#define __PlantsVersusZombies2__TideModule__

#include "LevelModule.h"
#include "Effect_PopAnim.h"
#include "BoardEnums.h"
#include "BoardRegion.h"

#define TIDE_WAVE_TRANSITION_DURATION		4.0

class TideEffectsProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(TideEffectsProps, PropertySheetBase, RtClass);

	TideEffectsProps()
	{}

	std::vector<SexyVector2> Effects;
};

class WaveActionProperties;
class WaveManagerProperties;

class TideModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(TideModule, LevelModule, RtClass);

	TideModule();

	float GetWaveLocation() const;
	float GetMaxWaveLocation() const;
	Sexy::Rect GetTideRectOnBoard() const;
	void SetWaveLocation(float i_newWaveLocation, float i_transitionTime);
	int GetWaveCoveredTiles() const { return m_waveCoveredTiles; }

	void ResetWavePropertiesForLevel(int i_initialWaveLocation, const std::vector<std::vector<RtWeakPtr<WaveActionProperties> > > i_waves);

protected:
	void initializeModule() override;
	void postInitialize() override;
	void registerForEvents() override;

private:
	void onLoadComplete();
	void onUpdate();
	void updateAudio(float i_waveChangeAmount);
	void updateTideRegion();
	float calculateMaxWaveLocation(const float i_initialWaveLocation, const std::vector<std::vector<RtWeakPtr<WaveActionProperties> > > i_waves) const;
	void updateWaveTransition();
	TideEffectsProps* GetEffectProperties();
	void onUpdateEffects();

	RtWeakPtr<WaveManagerProperties> getWaveManagerProps() const;

	// waves are stored off as 1 unit per gridsquare starting from the right of the board
	// if you want half a grid square, use 0.5
	float m_waveLocation;

	float m_waveStart;
	float m_waveDestination;
	pvztime_t m_waveTransitionStart;
	pvztime_t m_waveTransitionEnd;
	bool m_hasWaveTransition;

	int	m_waveCoveredTiles;

	// Fixed wave parameters, cached off early because they are a little complex to calculate all the time.
	float m_maxWaveLocation;

	RtWeakPtr<Effect_PopAnim> m_wetSandEffect;
	std::vector< RtWeakPtr<Effect_PopAnim> > m_lowerWaveEffects;
	RtWeakPtr<Effect_PopAnim> m_upperWaveEffect;
	RtWeakPtr<Effect_PopAnim> m_underWaveEffect;
	RtWeakPtr<class BoardRegion> m_tideRegion;
	RtWeakPtr<class BoardRegion> m_drySandRegion;
};

class TideProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(TideProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return TideModule::StaticGetClass();
	}

	TideProperties()
	{
		StartingWaveLocation = 2.f;
		ShowTideMarker = true;
	}

	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float StartingWaveLocation;
	bool ShowTideMarker;
};

class BoardRegionTideWater : public BoardRegion
{
public:
	RT_CLASS_DEFINE(BoardRegionTideWater, BoardRegion, RtClass) {}

	BoardRegionTideWater();

	void GatherPlantingRestrictions(const Sexy::Point &i_atLocation, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors) override;
	void DoEntityEnteredEffects(const SexyVector3& i_boardLocation, class BoardEntity* i_enteringEntity) override;
	float GetGroundHeightOffsetFraction(const SexyVector3& i_boardLocation) override;

protected:
	void onUpdate() override;
};

class BoardRegionDrySand : public BoardRegion
{
public:
	RT_CLASS_DEFINE(BoardRegionDrySand, BoardRegion, RtClass) {}

	void GatherPlantingRestrictions(const Sexy::Point &i_atLocation, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors) override;
};

namespace Message
{
	void TideChanged(const TideModule* i_tideModule);
}

#endif /* defined(__PlantsVersusZombies2__TideModule__) */

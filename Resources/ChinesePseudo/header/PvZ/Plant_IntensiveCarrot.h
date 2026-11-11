//
//  Plant_IntensiveCarrot.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 8/12/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_IntensiveCarrot__
#define __PlantsVersusZombies2__Plant_IntensiveCarrot__


#include "GameSubSystem.h"
#include "PlantFramework.h"
#include "BaseCursor.h"

class PlantTypeIntensiveCarrot : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeIntensiveCarrot, PlantType, RtClass) {}
	
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
	void AddResourceRequirements(std::set<std::string> &io_resGroupNames) const override;
};

class IntensiveCarrotRevivalSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(IntensiveCarrotRevivalSubsystem, GameSubSystem, RtClass);
	
	IntensiveCarrotRevivalSubsystem();
	virtual ~IntensiveCarrotRevivalSubsystem();
	
	std::pair<RtWeakPtr<PlantType>, int> GetPlantLastPlantedAt(const int i_gridX, const int i_gridY);
	bool HasPlantAt(const int i_gridX, const int i_gridY) const;

private:
	void onPlantPlacedOnBoard(Plant* i_plant);
	bool shouldBeCleared(Plant* i_plant);
	void onPlantKilled(Plant* i_plant);
	void onCursorAdded(BaseCursor* i_cursor);
	void onCursorDestroyed(BaseCursor* i_cursor);

	bool shouldActivatePreview(BaseCursor* i_cursor);

	void			activatePreview();
	void			deactivatePreview();
	void			resetPreview();
	void			addPlantPreviewToGrid(int x, int y);
	bool			canShowPreviewAt(int x, int y);
	void			createPreviewEffect(PlantTypePtr plantType, int x, int y);
	SexyVector3		calcPreviewPos(PlantTypePtr plantType, int x, int y);
	
	void updateSavedPlantTo(Plant* i_plant);
	void deleteSavedPlantUsingLocationFrom(Plant* i_plant);
	
	bool isAllowedBoardPosition(const int i_gridX, const int i_gridY) const;
	int calculateIndex(const int i_gridX, const int i_gridY) const {
		return (i_gridY * BoardConstants::NUMBER_OF_COLUMNS()) + i_gridX;
	}
	
	std::vector<std::pair<RtWeakPtr<PlantType>, int> > m_lastPlantedPlantTypes;
	RtWeakPtr<PlantTypeIntensiveCarrot> m_intensiveCarrotType;
	RtWeakPtr<PlantType> m_imitaterType;

	//Dont need to reflect these because you cannot resume a level with a plant about to be planted
	bool m_previewActive;
	std::vector<RtWeakPtr<Effect_PopAnim>> m_effects;
};

class IntensiveCarrotProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(IntensiveCarrotProps, PlantPropertySheet, RtClass);
    
    IntensiveCarrotProps()
    : InvincibleDuration(5.0f)
    {}
	
	float PercentageOfHealthForRaisedPlant = 1.0f;
	float NewPlantFadeInTime;
    pvztime_t InvincibleDuration;
};

class PlantIntensiveCarrot : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantIntensiveCarrot, PlantFramework, RtClass);
	
	bool CanApplyPlantfood() override { return false; }
	bool CanBeShoveled() override { return false; }
	bool CanBeTargeted() override { return false; }
    bool IsInvincible() const override { return true; }
    void PlayInvincibleEffect();
//	bool IsInvincible() const override { return true; }
//	
//	void TakeSmashAttack(BoardEntity* i_instigator) override {}
	
	void Initialize() override;
	void onAnimStoppedCallback(const std::string& i_anim) override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
private:
	void resurrectPlantAtOurPosition();
	void finalizeResurrection();
	RtWeakPtr<IntensiveCarrotRevivalSubsystem> m_carrotRevivalSubsystem;
	RtWeakPtr<Plant> m_plantBeingRevived;
};

#endif /* defined(__PlantsVersusZombies2__Plant_IntensiveCarrot__) */

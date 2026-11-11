//
//  PlantGroupSubsystem.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/16/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantGroupSubsystem__
#define __PlantsVersusZombies2__PlantGroupSubsystem__

#include <string>
#include <vector>

#include "BoardConstants.h"
#include "Core.h"
#include "GameObject.h"
#include "GameSubSystem.h"
#include "PlantEnums.h"
#include "PlantGroup.h"

class Plant;

class PlantGroupSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PlantGroupSubsystem, GameSubSystem, Sexy::RtClass);

	PlantGroupSubsystem();
    virtual ~PlantGroupSubsystem();
    void InitSubSystem();
    void Update() override;
    
    PlantGroupPtr   GetOrCreatePlantGroup(const Point& i_grid);
    PlantGroupPtr   FindPlantGroup(const Point& i_grid);
    PlantGroupPtr   FindPlantGroup(const PlantPtr i_plant);
    const std::vector<PlantGroupPtr>& GetAllActiveGroups();

    void DebugTestPlantGroupsCorrect();
    
public:
    void ClearData();

protected:
    void onPlantPlaced(Plant* i_plant);
    void onPlantDied(Plant* i_plant);
    void onPlantMoving(Plant* i_plant, Point& i_targetGridLocation);
    void onGatherPlantingRestrictions(const Sexy::Point &i_gridPosition, const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors);
    void onPlantRevertedByCondition(Plant* i_plant, int i_baseCondition, int i_groupCondition);
    void onPlantPlantfooded(Plant* i_plant);
    void onPlantPlantfoodEnd(Plant* i_plant);
    void onClearBoard();

private:
    PlantGroupPtr   createPlantGroup(const Point& i_grid);
    void            removePlantGroup(PlantGroupPtr i_group);
    void            deleteDeferred();
    void            updatePlantfoodRendering(Plant* i_plant);
    
    #ifndef WANTS_CHEATS_DISABLED
    void            validateGroups();
    #endif
    
    std::vector<PlantGroupPtr> m_groups;
    
    std::vector<PlantGroupPtr> m_groupsForDeletion;
};

#endif

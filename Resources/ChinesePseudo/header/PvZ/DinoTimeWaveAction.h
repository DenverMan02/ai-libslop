//
//  DinoTimeWaveAction.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/16/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DinoTimeWaveAction__
#define __PlantsVersusZombies2__DinoTimeWaveAction__

#include "Wave.h"

enum DinoSpawnType
{
    PVZ_BEGIN_ENUM(DINOSPAWNTYPE_),
    DINOSPAWNTYPE_Raptor,
    DINOSPAWNTYPE_Stegosaurus,
    DINOSPAWNTYPE_Pterodactyl,
    DINOSPAWNTYPE_Tyrannosaurus,
    DINOSPAWNTYPE_Ankylosaurus,
    PVZ_END_ENUM(DINOSPAWNTYPE_)
};

class DinoTimeWaveAction : public WaveAction
{
public:
    RT_CLASS_DEFINE(DinoTimeWaveAction, WaveAction, RtClass);
    
    void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
    void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void SpawnDino(const DinoSpawnType& i_dinoType, const int i_row, const int i_duration);
    void GetDinos(std::vector<const CreatureType*> &o_creatures);
    
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
private:
    CreatureTypePtr convertSpawnTypeToCreatureType(const DinoSpawnType& i_dinoType);
    
};

class DinoWaveActionProps : public WaveActionProperties
{
public:
    RT_CLASS_DEFINE(DinoWaveActionProps, WaveActionProperties, RtClass);
    
    DinoWaveActionProps() :
    DinoType(DINOSPAWNTYPE_Invalid),
    DinoRow(0),
    DinoWaveDuration(0)
    {
    }
    RtClass* GetActionClass() const override { return DinoTimeWaveAction::StaticGetClass(); }
    
    DinoSpawnType DinoType;
    int DinoRow;
    int DinoWaveDuration;
};

#endif /* defined(__PlantsVersusZombies2__DinoTimeWaveAction__) */

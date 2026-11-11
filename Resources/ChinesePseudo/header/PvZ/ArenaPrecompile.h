//
//  ArenaPrecompile.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-10-29.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ArenaPrecompile_h
#define PlantsVersusZombies2_ArenaPrecompile_h

#include "PVZTypes.h"

struct ZombieRecord
{
    ZombieTypePtr Type;
    int Num;
    int Level;
    ZombieRecord()
    {
        Num = 0;
        Level = 0;
    }
};

struct PvpPlantLostRecord
{
    std::string Name;
    int Num;
    int Level;
    PvpPlantLostRecord()
    {
        Num = 0;
        Level = 0;
    }
};

enum ArenaResult
{
    Result_Won,
    Result_Lose
};

enum ArenaType
{
    Arena_None = 0,
    Arena_PVP = 1,
    Arena_Special
};

enum ArenaStatus
{
    ArenaStatus_None = 0,
    ArenaStatus_PVP = 1,
    ArenaStatus_Special = 2,
    ArenaStatus_OccupyPrepare = 3,
    ArenaStatus_PVPPrepare = 4,
};

enum RankType
{
    RankType_Garden = 1,
    RankType_League = 2,
};

enum PVPMapType
{
    Map_PVE,
    Map_PVPEntry,
    Map_PVPMap
};

#endif

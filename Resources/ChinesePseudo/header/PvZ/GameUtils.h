//
//  Wave.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/22/13
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GameUtils_h
#define PlantsVersusZombies2_GameUtils_h

// Gets the cumulative health of all alive zombies in a wave.
int GetCumulativeZombieHealthInWave(int i_waveIndex);

std::string GetMaterialNameByPlantRare(int rare);

#endif

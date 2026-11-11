//
//  MiniBoard.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 14-7-24.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MiniBoard__
#define __PlantsVersusZombies2__MiniBoard__

#include "Board.h"


class MiniBoard : public Board
{
public:
    MiniBoard();
    ~MiniBoard();
    
    void InitBoard();
    void CloseBoard();
    void ResetBoard();
    bool CanSaveGameState() override;
    
    Zombie* SpawnZombie(ZombieTypePtr i_zombieType, int i_spawnedFromWave, SpawnZombieParams* pParams = nullptr) override;
    
    void Pause(bool i_pauseGame) override;
    void Update() override;
    void Draw(Graphics* i_g) override;

    bool IsMiniBoard() override;
};

#endif /* defined(__PlantsVersusZombies2__MiniBoard__) */

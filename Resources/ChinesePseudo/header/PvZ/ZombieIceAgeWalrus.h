//
//  ZombieIceAgeWalrus.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 03/12/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieIceAgeWalrus_h
#define PlantsVersusZombies2_ZombieIceAgeWalrus_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"

class ZombieIceAgeWalrusProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeWalrusProps, ZombiePropertySheet, RtClass);
    
    ZombieIceAgeWalrusProps() : AutoStatueCol(1), WalrusEarthTileStayTime(30) {}
    
    int AutoStatueCol;
    int WalrusEarthTileStayTime;
    
};

class ZombieIceAgeWalrus : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeWalrus, Zombie, RtClass);
    
    ZombieIceAgeWalrus() : m_iPreviousCol(BoardConstants::NUMBER_OF_COLUMNS() - 1) { }
    
private:
    
    void onUpdate() override;
    
    bool allowElectrocuteState() const override { return false; }
    
    bool allowAshState() const override { return false; }
    
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_ONEXIT(ZombieState, Die);
    
    void ColumnChangeEffect();
    
    bool IsRecordFoot(Sexy::Point& pt);
    
    void RecordFoot(Sexy::Point& pt);
    
    void GenerateWalrusStatue();
    
    void GenerateWalrusEarthTile(Sexy::Point pt, bool bFragment = false);
    
private:
    
    int m_iPreviousCol;
	
};

class ZombieAnimRig_Walrus : public ZombieAnimRig
{
	RT_CLASS_DEFINE(ZombieAnimRig_Walrus, ZombieAnimRig, RtClass);
    
};

#endif

//
//  ZombieRomanImp.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/29/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieRomanImp_h
#define PlantsVersusZombies2_ZombieRomanImp_h

#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"

class ZombieRomanImp : public ZombieImp
{
public:
	RT_CLASS_DEFINE(ZombieRomanImp, ZombieImp, RtClass);

	ZombieRomanImp();
    
    void LaunchedByGargantuar() override;
	
protected:
    void onPreImpFlight() override;
    void onLandingSuccess() override;

private:
    bool m_hasNet;
};

class ZombieRomanImpProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieRomanImpProps, ZombiePropertySheet, RtClass);
    
    ZombieRomanImpProps()
    {
        NetSuspendSeconds = 10;
    }
    
    int NetSuspendSeconds;
};

class ZombieAnimRig_RomanImp : public ZombieAnimRig_Imp
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_RomanImp, ZombieAnimRig_Imp, RtClass);
    
    const std::vector<std::string>& getHeadLayerNames() override;

    void SetHasNet(bool i_hasNet);
};

#endif

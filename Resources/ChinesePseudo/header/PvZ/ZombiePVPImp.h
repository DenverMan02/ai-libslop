//
//  ZombiePVPImp.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 11/11/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePVPImp_h
#define PlantsVersusZombies2_ZombiePVPImp_h

#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"

class ZombiePVPImp : public ZombieImp
{
public:
	RT_CLASS_DEFINE(ZombiePVPImp, ZombieImp, RtClass);

	ZombiePVPImp();
    
    void ApplyZombieFood() override;
    void ClearPlaybackParams(int i_type) override;
    
    void onUpdate() override;
    
private:
    
    void CreateSmokeEffect(ZombiePtr ptrZombie);
    ZombiePtr CreateShadowImp();
private:
    
    ZombiePtr m_ptrZombie1;
    ZombiePtr m_ptrZombie2;
};


class ZombieAnimRig_PVPImp : public ZombieAnimRig_Imp
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_PVPImp, ZombieAnimRig_Imp, RtClass);
    
    ZombieAnimRig_PVPImp() { }
};


//-----------------------------------zombie shadow imp-----------------------------


class ZombiePVPShadowImpProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePVPShadowImpProps, ZombiePropertySheet, RtClass);
    
    ZombiePVPShadowImpProps() : ShadowTime(20) {}
    
    pvztime_t ShadowTime;
};

class ZombiePVPShadowImp : public ZombiePVPImp
{
public:
    RT_CLASS_DEFINE(ZombiePVPShadowImp, ZombiePVPImp, RtClass);
    
    ZombiePVPShadowImp();
    
    void onZombieInitialize() override;
    
    void onUpdate() override;
    
    void ApplyZombieFood() override;
    
private:
    
    pvztime_t m_iDestoryTime;
};


class ZombieAnimRig_PVPShadowImp : public ZombieAnimRig_PVPImp
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_PVPShadowImp, ZombieAnimRig_PVPImp, RtClass);
    
    ZombieAnimRig_PVPShadowImp() { }
};



#endif

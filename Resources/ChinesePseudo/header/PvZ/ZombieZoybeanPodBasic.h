//
//  ZombieZoybeanPodBasic.hpp
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 11/30/18.
//  Copyright © 2018 PopCap Games. All rights reserved.
//

#ifndef ZombieZoybeanPodBasic_h
#define ZombieZoybeanPodBasic_h

#include <stdio.h>
#include "ZombieBasic.h"
#include "ZombieAnimRig.h"
#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieZoybeanPodBasic : public ZombieBasic
{
public:
    RT_CLASS_DEFINE(ZombieZoybeanPodBasic, ZombieBasic, RtClass);
    
    ZombieZoybeanPodBasic()
    {
        spawnFromPodAnimationName = "born";
        additionalDamage = 0.0f;
    }
    
    bool CanDropArm() const override { return false; }
    bool CanDropHead() const override { return false; }
    bool CanBleedOut() const { return false; }
    
	void SetPlantFamilies(std::vector<std::string> i_families, float i_resistancePiercing) { m_plantFamilies = i_families; m_resistancePiercingOverride = i_resistancePiercing; }
    
	float additionalDamage;
protected:
	virtual BoardEntity *findTarget() override;
    void onTurnedToAsh() override;
    void onElectrocuted() override;
    void onUpdate() override;
	DamageInfo calcEatDamage() override;

	
private:
	std::vector<std::string> m_plantFamilies;
	float m_resistancePiercingOverride;
};


class ZombieAnimRig_ZoybeanPodBasic : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE_ABSTRACT(ZombieAnimRig_ZoybeanPodBasic, ZombieAnimRig_Basic, RtClass);
    
protected:
    ZombieAnimRig_ZoybeanPodBasic();
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    virtual const std::vector<std::string>& getConeLayerNames() override;
    virtual const std::vector<std::string>& getBucketLayerNames() override;

    void onPopAnimInitialized() override;


};

#endif /* ZombieZoybeanPodBasic_h */

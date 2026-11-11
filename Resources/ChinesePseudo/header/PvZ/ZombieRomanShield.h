//
//  ZombieRomanShield.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/6/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEROMANSHIELD_H__
#define __ZOMBIEROMANSHIELD_H__

#include "DamageInfo.h"
#include "ObjectTypeDirectory.h"
#include "PVZTypes.h"
#include "RtDb.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "ZombieEnums.h"
#include "ZombieCamel.h"
#include "ZombieAnimRig_Camel.h"

class ZombieRomanShield : public ZombieCamel
{
public:
	RT_CLASS_DEFINE(ZombieRomanShield, ZombieCamel, RtClass);

    // Typically we would not reach this, but at the moment this is being shared with the TopShield zombie.
    // Ostensibly that should be able to function like the Camel, but we may want to override this class when we get to the art since it may be different enough.
    // bool CanDropArm() const override { return GetCamelType() == CAMELTYPE_BODY; }
    // bool CanDropHead() const override { return GetCamelType() == CAMELTYPE_BODY; }
    
    bool CanDropArm() const override { return HasArm(); }
    bool CanDropHead() const override { return HasHead(); }

protected:
    void onPlaceOnBoard() override;
    bool isFriendInOurLane();

    std::string getNormalZombiePAM() override { return "roman"; }
    void addCamelArmor(ZombieCamelSegmentType i_camelType) override;
    std::string getSegmentTypeName(ZombieCamelSegmentType i_type) override { return i_type == CAMELTYPE_BODY ? "roman_shield_top" : "roman_segment"; }
    std::string getHeadParticlePAMBase() override { return "roman"; }

    Rect calcCollisionRect() override;
    
    DamageInfo onArmorDamageTaken(const DamageInfo& i_incomingDamage, std::string i_armorType) override;
    bool shouldPlayArmorDrop(std::string i_armorType) override;
    bool canBecomeUncamel() override;
    
    bool m_initializedCamel = false;
};

class ZombieAnimRig_RomanShield : public ZombieAnimRig_Camel
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_RomanShield, ZombieAnimRig_Camel, RtClass);
	
	ZombieParticle* CreateProjectileParticle() override;
};

class ZombieRomanTopShield : public ZombieRomanShield
{
public:
    RT_CLASS_DEFINE(ZombieRomanTopShield, ZombieRomanShield, RtClass);

protected:
    bool canBecomeUncamel() override { return false; }
    bool shouldPlayArmorDrop(std::string i_armorType) override { return false; }
    void onArmorDropped(std::string i_armorType) override;
    void onShieldLost(const std::string& i_animName);
};

class ZombieAnimRig_RomanTopShield : public ZombieAnimRig_Camel
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_RomanTopShield, ZombieAnimRig_Camel, RtClass);
    
    const std::string GetHeadParticleName() override { return "particle_head"; }
    const std::string GetArmParticleName() override { return "particle_arm"; }
	
	ZombieParticle* CreateProjectileParticle() override;
    
protected:
    const std::vector<std::string>& getHeadLayerNames() override
    {
        STATIC_VECTOR_INIT(std::string, k_layerArray, "zombie_roman_skull", "zombie_roman_jaw", "zombie_pupil");
        return k_layerArray;
    }
    const std::vector<std::string>& getArmLayerNames() override
    {
        STATIC_VECTOR_INIT(std::string, k_layerArray, "zombie_roman_arm_outer_lower", "zombie_roman_hand_outer", "zombie_roman_hand_outer_01");
        return k_layerArray;
    }
    const std::vector<std::string>& getArmReplacementPairNames() override
    {
        STATIC_VECTOR_INIT(std::string, k_layerArray, "zombie_arm_outer_upper_bone");
        return k_layerArray;
    }

};

#endif

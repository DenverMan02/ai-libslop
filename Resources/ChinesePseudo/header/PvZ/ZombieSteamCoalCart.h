//
//  ZombieModernNewspaper.hpp
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 11/5/15.
//  Copyright © 2015 PopCap Games. All rights reserved.
//

#ifndef ZombieSteamCoalCart_hpp
#define ZombieSteamCoalCart_hpp

#include "DamageInfo.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieEnums.h"

STATE_ENUM_CHILD_BEGIN(SteamCoalCartZombieState, ZombieState)
SCZS_COALCART_SCARED,
SCZS_COALCART_UNLOAD,
STATE_ENUM_END(SteamCoalCartZombieState);

#pragma mark - ZombieSteamCoalCartProps
class ZombieSteamCoalCartProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieSteamCoalCartProps, ZombiePropertySheet, RtClass);
};

#pragma mark - ZombieSteamCoalCart
class ZombieSteamCoalCart : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieSteamCoalCart, Zombie, RtClass);
	
	DECLARE_STATE_FUNCTIONS(SteamCoalCartZombieState, Scared);
	DECLARE_STATE_FUNCTIONS(SteamCoalCartZombieState, Unload);
	
	int CalcProgressMeterHitpoints() const override;
	
protected:
	void onArmorDropped(std::string i_armorType) override;
	void registerForEvents() override;
	void onZombieInitialize() override;
	
private:
	void onUnloadCartComplete(const std::string& i_animName);
	void onScaredComplete(const std::string& i_animName);
	void onCartCrashComplete(const std::string& i_animName);
};



#pragma mark - ZombieAnimRig_CoalCart
class ZombieAnimRig_CoalCart : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_CoalCart, ZombieAnimRig, RtClass);
	
	void UnloadCart(AnimStoppedReflectionDelegate i_animStopDelegate = {});
	void ScaredByCartBurnt(AnimStoppedReflectionDelegate i_animStopDelegate = {});
	void CartCrash(AnimStoppedReflectionDelegate i_animStopDelegate = {});
	
protected:
	void onPopAnimInitialized() override;
	
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	
private:
	bool m_hasCart;
	
};


#endif /* ZombieModernNewspaper_hpp */

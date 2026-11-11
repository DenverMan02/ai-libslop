//
//  ZombieModernNewspaper.hpp
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 11/5/15.
//  Copyright © 2015 PopCap Games. All rights reserved.
//

#ifndef ZombieModernNewspaper_hpp
#define ZombieModernNewspaper_hpp

#include "DamageInfo.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieEnums.h"

STATE_ENUM_CHILD_BEGIN(ModernNewspaperZombieState, ZombieState)
MNZS_NEWSPAPER_BecomeEnraged,
STATE_ENUM_END(ModernNewspaperZombieState);

#pragma mark - ZombieModernNewspaperProps
class ZombieModernNewspaperProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieModernNewspaperProps, ZombiePropertySheet, RtClass);
	
	float EnragedSpeedScale = 4.0f;
	float EnragedDpsScale = 4.0f;
};

#pragma mark - ZombieModernNewspaper
class ZombieModernNewspaper : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieModernNewspaper, Zombie, RtClass);
	
	DECLARE_STATE_FUNCTIONS(ModernNewspaperZombieState, BecomeEnraged);
	
	int CalcProgressMeterHitpoints() const override;
	
protected:
	void onArmorDropped(std::string i_armorType) override;
	void registerForEvents() override;
	void onZombieInitialize() override;
	
private:
	void onDiscardNewspaperComplete(const std::string& i_animName);
};



#pragma mark - ZombieAnimRig_Newspaper
class ZombieAnimRig_Newspaper : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Newspaper, ZombieAnimRig, RtClass);
	
	void DiscardNewspaper(AnimStoppedReflectionDelegate i_animStopDelegate = {});
	
protected:
	void onPopAnimInitialized() override;
	
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	const std::string getEatAnimationName() override;
	
private:
	bool m_hasNewspaper;
	
};


#endif /* ZombieModernNewspaper_hpp */

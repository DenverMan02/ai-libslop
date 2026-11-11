//
//  ZombieAnimRig_Camel.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_CAMEL_H__
#define __ZOMBIEANIMRIG_CAMEL_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

enum ZombieCamelBoardType
{
	CAMELBOARD_BLANK,
	CAMELBOARD_HEAD,
	CAMELBOARD_BODY,
	CAMELBOARD_TAIL,
};

class ZombieAnimRig_Camel : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Camel, ZombieAnimRig, RtClass);
	
	// New stuff
	//helm was deleted, use armor
	// void ShowLayersForCurrentState();
	// void SetBoardType(ZombieCamelBoardType i_boardType);
	// void SetDamageIndex(int i_newDamageIndex);
	
	bool IsWalking();
	int GetWalkAnimFrame();
	void SetWalkAnimFrame(int i_newFrame);
	
	bool IsIdling();
	int GetIdleAnimFrame();
	void SetIdleAnimFrame(int i_newFrame);
	
	// Overrides
	virtual SexyVector2 GetHeadOffset() override;

	void SetAlmanacArmor(std::vector<RtWeakPtr<class ArmorPropertySheet>> armorProps) override;
	class ZombieParticle* CreateProjectileParticle() override;
	
protected:
	virtual void onPopAnimInitialized() override;
	
	// ZombieCamelBoardType m_boardType;
	// int m_damageIndex;
};

#endif // __ZOMBIEANIMRIG_CAMEL_H__

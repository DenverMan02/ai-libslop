//
//  BoardPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/21/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __BOARDPROPERTYSHEET_H__
#define __BOARDPROPERTYSHEET_H__

#include "Precompile.h"
#include "PropertySheetBase.h"
#include "RtObject.h"

class BoardPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(BoardPropertySheet, PropertySheetBase, RtClass);

	BoardPropertySheet()
	{
		MaxSunCurrency = 9900;
		ShowFPSPig = false;
		PlantTargetingXThreshold = 820.f;
		ZombieThreatLowAlert_TriggerPositionX = 0.0f;
		ZombieThreatHighAlert_TriggerPositionX = 0.0f;
		ZombieThreatLowAlert_StarChallengeOffsetX = 0.0f;
		ZombieThreatHighAlert_StarChallengeOffsetX = 0.0f;
		ZombieThreatLowAlert_ProtectPlantOffsetX = 0.0f;
		ZombieThreatHighAlert_ProtectPlantOffsetX = 0.0f;
        CoinAlert_LowBalanceThreshold = 1000;
        
        ZombieTideMaxHeightPct = 0.3f;
        DefaultTideMaxHeightPct = 0.3f;
		MaxTideDropoffDistance = 300.f;
        
        ShrunkenDPSMultiplier = 1.0f;
        BasicTakenDamageMultiplier = 1.0f;
        AdvTakenDamageMultiplier = 1.0f;
        BasicReduceSpeedMultiplier = 0.5f;
        AdvReduceSpeedMultiplier = 0.3f;
	}	
	
	float	PlantTargetingXThreshold;
	uint16	MaxSunCurrency;
	float   ZombieThreatLowAlert_TriggerPositionX;
	float   ZombieThreatHighAlert_TriggerPositionX;
	float   ZombieThreatLowAlert_StarChallengeOffsetX;
	float   ZombieThreatHighAlert_StarChallengeOffsetX;
	float   ZombieThreatLowAlert_ProtectPlantOffsetX;
	float   ZombieThreatHighAlert_ProtectPlantOffsetX;
    bool	ShowFPSPig;
    int     CoinAlert_LowBalanceThreshold;
	std::vector<std::string> RequiredSubsystems;
    
	float	ZombieTideMaxHeightPct;						// Percentage of the zombie's height that will be covered by the tide
	float	DefaultTideMaxHeightPct;					// Percentage of the height that will be covered by the tide
	float	MaxTideDropoffDistance;						// Distance in board units that is the max depth for the tide
    
	std::vector<float> DynamicDifficultyMowerImmunity;
	std::vector<float> DynamicDifficultyMowerCooldown;
    
	float DangerRoomMowerImmunity = 5.0f;
	float DangerRoomMowerCooldown = 45.0f;
    
	std::vector<std::string> PlantFrostBlacklist;
	std::vector<std::string> PlantSmashAttackBlacklist;
    
    float ShrunkenDPSMultiplier;
    float BasicTakenDamageMultiplier;
    float AdvTakenDamageMultiplier;
    float BasicReduceSpeedMultiplier;
    float AdvReduceSpeedMultiplier;
};

#endif // __BOARDPROPERTYSHEET_H__
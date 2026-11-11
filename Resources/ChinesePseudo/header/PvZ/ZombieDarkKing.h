//
//  ZombieDarkKing.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/30/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieDarkKing__
#define __PlantsVersusZombies2__ZombieDarkKing__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"

#include "ZombieAnimRig_DarkWizard.h"

STATE_ENUM_CHILD_BEGIN(ZombieDarkKingState, ZombieState)
	ZS_KING_KingIntro,
	ZS_KING_KingIdle,
	ZS_KING_KingCast,
STATE_ENUM_END(ZombieDarkKingState)

class ZombieDarkKing : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieDarkKing, Zombie, RtClass);

protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, KingIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, KingIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, KingCast);
    bool isImmuneToShrinking() override { return true; }

private:
	virtual void registerForEvents() override;
	virtual void onPlaceOnBoard() override;
	virtual void onIntroCompleted(const std::string&);
	virtual void onKnightingCompleted(const std::string&);
	virtual void chooseDeathState(const DamageInfo& i_deathBlow) override;

	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	void blockGravestoneSpawning(const Sexy::Point& i_gridPosition, bool* o_blocked);

	class Zombie* findKnightingTarget() const;
	bool isValidKnightingTarget(Zombie* i_zombie) const;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	RtWeakPtr<Zombie> m_knightingTarget;
};

class ZombieDarkKingProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieDarkKingProps, ZombiePropertySheet, RtClass);

	ZombieDarkKingProps()
		: DelayBetweenKnightings(3.f), KnightHelm(HELMTYPE_CROWN), KnightHelmHitpoints(2000.f)
		, KnightingAreaX(3), KnightingAreaY(3)
	{}

	float DelayBetweenKnightings;

	int KnightingAreaX, KnightingAreaY;

	HelmType KnightHelm;
	float KnightHelmHitpoints;

	std::vector<std::string> ValidKnightTargets;
	std::vector<std::string> PlantablePlants;
};

class ZombieAnimRig_DarkKing : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DarkKing, ZombieAnimRig, RtClass);

	virtual const std::vector<std::string>& getArmLayerNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieDarkKing__) */

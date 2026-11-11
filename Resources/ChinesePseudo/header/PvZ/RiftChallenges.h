/*
 * RiftChallenges.h
 *
 *  Created on: 2020-10-26
 *      Author: admin
 */

#ifndef RIFTCHALLENGES_H_
#define RIFTCHALLENGES_H_

#include "ChallengeModule.h"
#include "GridItem.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class ZombiePerfumerChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(ZombiePerfumerChallenge, Challenge, RtClass);

	void registerForEvents() override;

	ZombiePerfumerChallenge()
	{
		m_numPoisonCleaned = 0;
	}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifyCleanPoison();

	int m_numPoisonCleaned;
	RtWeakPtr<UIWidget> m_gridItemCounterWidget;
};

class ZombiePerfumerChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombiePerfumerChallengeProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return ZombiePerfumerChallenge::StaticGetClass();
	}

	SexyString GetDescription() const override
	{
		SexyString poisons = StrFormat(_S("%d"), PoisonToClean);
		return TodReplaceString(_S("[CHALLENGE_CLEAN_POISON]"), _S("{NUM_POISON}"), poisons);
	}

	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[CHALLENGE_DESTROY_GRID_ITEMS_OF_TYPE_NAME]"));
	}

	ZombiePerfumerChallengeProps()
	: PoisonToClean(0)
	{}

	int PoisonToClean;
};

class BalletSlipChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(BalletSlipChallenge, Challenge, RtClass);

	void registerForEvents() override;

	BalletSlipChallenge()
	{
		m_numBalletSliped = 0;
	}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifySlip();

	int m_numBalletSliped;
	RtWeakPtr<UIWidget> m_gridItemCounterWidget;
};

class BalletSlipChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(BalletSlipChallengeProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return BalletSlipChallenge::StaticGetClass();
	}

	SexyString GetDescription() const override
	{
		SexyString slips = StrFormat(_S("%d"), BalletToSlip);
		return TodReplaceString(_S("[CHALLENGE_BALLET_SLIP]"), _S("{NUM_SLIP}"), slips);
	}

	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[CHALLENGE_DESTROY_GRID_ITEMS_OF_TYPE_NAME]"));
	}

	BalletSlipChallengeProps()
	: BalletToSlip(0)
	{}

	int BalletToSlip;
};

class SteamManholeChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(SteamManholeChallenge, Challenge, RtClass);

	virtual void registerForEvents() override;

	SteamManholeChallenge()
	: m_manholeEntered(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifyEnterManhole();

	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_manholeEntered;

	RtWeakPtr<UIWidget> m_plantCountUI;
};

class SteamManholeChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SteamManholeChallengeProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return SteamManholeChallenge::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumManholeEntered);
		return TodReplaceString(_S("[CHALLENGE_STEAM_MANHOLE]"), _S("{NUM_ZOMBIE}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_LOST_NAME]"));
	}

	SteamManholeChallengeProps()
	: MaximumManholeEntered(0)
	{}

	int MaximumManholeEntered;
};

class RenaiRollerChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(RenaiRollerChallenge, Challenge, RtClass);

	virtual void registerForEvents() override;

	RenaiRollerChallenge()
	: m_plantsDied(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifyKillPlant();

	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_plantsDied;;

	RtWeakPtr<UIWidget> m_plantCountUI;
};

class RenaiRollerChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RenaiRollerChallengeProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return RenaiRollerChallenge::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumPlantsDied);
		return TodReplaceString(_S("[CHALLENGE_RENAI_ROLLER]"), _S("{NUM_PLANT}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_LOST_NAME]"));
	}

	RenaiRollerChallengeProps()
	: MaximumPlantsDied(0)
	{}

	int MaximumPlantsDied;
};

class ZombiePeaChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(ZombiePeaChallenge, Challenge, RtClass);

	virtual void registerForEvents() override;

	ZombiePeaChallenge()
	: m_plantsHitted(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifyHitPlant();

	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_plantsHitted;

	RtWeakPtr<UIWidget> m_plantCountUI;
};

class ZombiePeaChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombiePeaChallengeProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ZombiePeaChallenge::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumPlantsHitted);
		return TodReplaceString(_S("[CHALLENGE_ZOMBIE_PEA]"), _S("{NUM_HITS}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_LOST_NAME]"));
	}

	ZombiePeaChallengeProps()
	: MaximumPlantsHitted(0)
	{}

	int MaximumPlantsHitted;
};

class ZombieJalapenoChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(ZombieJalapenoChallenge, Challenge, RtClass);

	virtual void registerForEvents() override;

	ZombieJalapenoChallenge()
	: m_zombieExploded(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifySelfExplodeJalapeno();

	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_zombieExploded;

	RtWeakPtr<UIWidget> m_plantCountUI;
};

class ZombieJalapenoChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombieJalapenoChallengeProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ZombieJalapenoChallenge::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumExplode);
		return TodReplaceString(_S("[CHALLENGE_ZOMBIE_JALAPENO]"), _S("{NUM_EXPLODE}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_LOST_NAME]"));
	}

	ZombieJalapenoChallengeProps()
	: MaximumExplode(0)
	{}

	int MaximumExplode;
};

class ZombieExplodenutChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(ZombieExplodenutChallenge, Challenge, RtClass);

	virtual void registerForEvents() override;

	ZombieExplodenutChallenge()
	: m_zombieExploded(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onNotifySelfExplodeExplodenut();

	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_zombieExploded;

	RtWeakPtr<UIWidget> m_plantCountUI;
};

class ZombieExplodenutChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombieExplodenutChallengeProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ZombieExplodenutChallenge::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumExplode);
		return TodReplaceString(_S("[CHALLENGE_ZOMBIE_EXPLODENUT]"), _S("{NUM_EXPLODE}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_LOST_NAME]"));
	}

	ZombieExplodenutChallengeProps()
	: MaximumExplode(0)
	{}

	int MaximumExplode;
};

#endif /* RIFTCHALLENGES_H_ */

/*
 * ZombieModernSolarTruck.h
 *
 *  Created on: 2017-7-12
 *      Author: Administrator
 */

#ifndef ZOMBIEMODERNSOLARTRUCK_H_
#define ZOMBIEMODERNSOLARTRUCK_H_

#include <string>
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"

// These states for zombie transforms each mode
STATE_ENUM_CHILD_BEGIN(ZombieState_SolarTruck, ZombieState)
	ZS_SOLAR_CHARGING,
	ZS_SOLAR_FULL_CHARGED,
    ZS_SOLAR_PUSH,
    ZS_SOLAR_CASTING,
    ZS_SOLAR_EMPEACHSTUN,
STATE_ENUM_END(ZombieState_SolarTruck)

// Inner states
enum SolarState
{
    PVZ_BEGIN_ENUM(SOLARSTATE_),
    SOLARSTATE_UNKNOWN,
    SOLARSTATE_READY_TO_CHARGE,
    SOLARSTATE_CHARGING,
    SOLARSTATE_FULL_CHARGED,
    SOLARSTATE_REDUCE_TO_EMPTY,
    SOLARSTATE_EMPTY,
    PVZ_END_ENUM(SOLARSTATE_)
};

class ZombieModernSolarTruckProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieModernSolarTruckProps, ZombiePropertySheet, RtClass);
	ZombieModernSolarTruckProps()
		: ChargingSpeed(10.0f),
		  EnergyReduceSpeed(3.0f),
		  CastingRange(8),
		  DecayDelay(0.5f),
		  MaxClaimedSunCurrency(250),
		  ExtraDamageTaken(0.5f),
		  SolarBeamDamage(4000.0f),
		  EnergyRatePerSun(0.5f),
		  NumDamageStates(0)
	{}
	float ChargingSpeed;
	float EnergyReduceSpeed;
	int CastingRange;
	float DecayDelay;
	int MaxClaimedSunCurrency;
	float ExtraDamageTaken;
	float SolarBeamDamage;
	float EnergyRatePerSun;
	int NumDamageStates;
};

class ZombieModernSolarTruck : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieModernSolarTruck, Zombie, RtClass);

	ZombieModernSolarTruck();

	void onDestroy() override;
	void setState(SolarState i_state);
	SolarState getState();
	void updateState();
	void TakeDamage(const DamageInfo& i_damage) override;

	void IncrementSunsCollected(const int i_sunCurrency) override;
	void IncrementSunsClaimed(const int i_sunCurrency) override;
	void DecrementSunsClaimed(const int i_sunCurrency) override;
	bool ShouldReleaseSun() override;
	bool CanClaimSun() override;
	SexyVector3 GetSunTarget() { return SexyVector3(-10.0, 0.0, 130.0) * GetConditionTracker().GetDrawScale(); }

	void EMPeachStun(pvztime_t i_time) override;

	bool IsStunned() const override;

	DECLARE_STATE_FUNCTIONS(ZombieState, EMPeachStun);
protected:
	void onUpdate() override;
	void onPlaceOnBoard() override;
	// Some future zombies do not have proper anims electrocute/ash
	bool allowElectrocuteState() const override
	{
		return false;
	}
	bool allowAshState() const override
	{
		return false;
	}
	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onZombieInitialize() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	virtual void onMowedDown() override;
	virtual void onChangeTeams(TeamFlags i_oldTeam, TeamFlags i_newTeam) override;
	void onFlicked(Zombie* i_zombie);
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Charging);
	DECLARE_STATE_FUNCTIONS(ZombieState, FullCharged);
	DECLARE_STATE_FUNCTIONS(ZombieState, Push);
	DECLARE_STATE_FUNCTIONS(ZombieState, Casting);


private:
	bool shouldPush();
	bool canPushPlant(Plant* i_plant);
	void findAndPushPlant();
	void pushRow(int i_gridX, int i_gridY);
	void pushPlant(Plant* i_plant);
	Plant* getValidSpellTarget();
	void releaseCollectedSuns(bool i_autocollect);

	// Transform states
	void onChargingAnimDone(const std::string& i_animLabelName);
	void onFullChargedAnimDone(const std::string& i_animLabelName);
	void onPushAnimDone(const std::string& i_animLabelName);
	void onCastingAnimDone(const std::string& i_animLabelName);

	bool IsInState(uint32 state) const { return m_state == state; }

	bool m_showEnergyBar;
	pvztime_t m_nextFullChargeTime;
	SolarState m_state;
	pvztime_t m_energyEmptyTime;
	int m_sunCurrencyCollected;
	int m_sunCurrencyClaimed;
	pvztime_t m_innerCD;
	int m_damageState;
	int m_energyState;

	pvztime_t m_stunDuration;
	RtWeakPtr<class Effect_PopAnim> m_stunDamageEffect;
};

class ZombieAnimRig_ModernSolarTruck : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ModernSolarTruck, ZombieAnimRig, RtClass) {}

    void PlayCharging(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayFullCharged(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void StartCasting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayPush(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual void SetDamageState(int i_damageState);
	void SetEnergyState(int i_energyState);
protected:
	void onPopAnimInitialized() override;
//	virtual const std::vector<std::string>& getHeadLayerNames() override;
//	virtual const std::vector<std::string>& getArmLayerNames() override;
//	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* ZOMBIEMODERNSOLARTRUCK_H_ */

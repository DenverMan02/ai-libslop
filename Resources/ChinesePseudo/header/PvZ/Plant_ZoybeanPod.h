/*
 * Plant_ZoybeanPod.h
 *
 *  Created on: 2022-8-1
 *      Author: admin
 */

#ifndef PLANT_ZOYBEANPOD_H_
#define PLANT_ZOYBEANPOD_H_




#endif /* PLANT_ZOYBEANPOD_H_ */
#include "Plant.h"
#include "PlantFramework.h"
#include "RtDb.h"
#include "RtObject.h"
#include "ZombieType.h"

class Projectile;
class Zombie;

namespace Sexy {
class SexyVector3;
}  // namespace Sexy

enum ZoybeanPod_State
{
	ZOYBEANPODSTATE_INITIAL = STATE_FRAMEWORK_BEGIN, // initial state before cycle begins
    ZOYBEANPODSTATE_CHARGE_START,                    // idle animation, start of cycle
    ZOYBEANPODSTATE_CHARGING,                        // second idle
    ZOYBEANPODSTATE_FULLY_CHARGED,                   // third idle, must wait for target
    ZOYBEANPODSTATE_TRANSITION,                      // handles transitions between states
	ZOYBEANPODSTATE_ATTACK,                          // zomboid is released (third transition)
	ZOYBEANPODSTATE_RECOVER,                         // fourth idle, then transition back to start
	ZOYBEANPODSTATE_PLANTFOOD,                       // in plantfood state.
};

//Props
class ZoybeanPodProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ZoybeanPodProps, PlantPropertySheet, RtClass);

	ZoybeanPodProps()
    :   ZombieTypeToSpawn("zoybeanpod_basic")
	,	PlantFoodZombieTypeToSpawn("zoybeanpod_gargantuar")
	,	ZombieArmor1ToSpawn("zoybeanpod_armor1")
	,	ZombieArmor2ToSpawn("zoybeanpod_armor2")
	,	ZombieGatlingpeaToSpawn("zombie_zoybeanpodgatlingpea")
	,	AvatarPlantFoodZombieToSpawn("zoybeanpod_gargantuar2")
	,	cone1Posibility(0.5)
	,	cone2Posibility(0.35)
	,	bucketPosibility(0.35)
	,   GatlingpeaPosibility(0.15)
	,	ZombieLevel(1)
	,	PlantFoodZombieLevel(1)
    ,   CycleTime(0)
    {}
	std::string AvatarPlantFoodZombieToSpawn;
	std::string ZombieTypeToSpawn;
	std::string ZombieArmor1ToSpawn;
	std::string ZombieArmor2ToSpawn;
	std::string ZombieGatlingpeaToSpawn;
	std::string PlantFoodZombieTypeToSpawn;
	float cone1Posibility;
	float cone2Posibility;
	float bucketPosibility;
	float GatlingpeaPosibility;
	int ZombieLevel;
	int PlantFoodZombieLevel;
    float CycleTime;
};

class Effect_ZoybeanPodSmoke : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_ZoybeanPodSmoke, Effect_PopAnim, RtClass);

    void StartSmoke(pvztime_t i_preOpenSmokeDuration, pvztime_t i_postOpenSmokeDuration, PlantPtr i_plant);
    void StartSmoke(pvztime_t i_postOpenSmokeDuration, PlantPtr i_plant);

protected:
    void playSmokeEffect(pvztime_t i_preOpenSmokeDuration, pvztime_t i_postOpenSmokeDuration, PlantPtr i_plant, bool i_skipStartup);

    int m_renderDifferenceFromPlant = RENDER_LAYER_PLANT_ABOVE_ZOMBIES - RENDER_LAYER_PLANT;
};

class PlantZoybeanPod : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantZoybeanPod, PlantFramework, RtClass);

	void Initialize() override;
    void UpdatePowerUpStats();

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	void UpdateActions() override;
	virtual void DoSpecial(int i_extraParam = 0) override;

	void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;

protected:
	void	setState(uint i_plantState);
	void	spawnZombieCallback(pvztime_t i_atTime);
    void    initializeAnimationTiming();
    virtual void AutoFire() override;
    int displayN = 0;

    enum displayZombie
    	{
    		basiczombie,
    		zombieArmor1,
    		zombieArmor2,
    		donothing,
    		zombiegatlingpea
    	};

private:
	void spawnZombie(std::string i_zombieType, int i_zombieLevel);
    float m_idleTime;
    float m_animationStartTime;
    bool m_usingDefaultAnimationTimes;
    bool displaySpwan = false;
//    int m_spawnLevel;
};

enum PlantAnimRigState_ZoybeanPod
{
	PLANTANIM_ZOYBEANPOD_CHARGING = PLANTANIM_USERDEFINED,
	PLANTANIM_ZOYBEANPOD_RECOVER,
    PLANTANIM_ZOYBEANPOD_CHARGE_START,
    PLANTANIM_ZOYBEANPOD_TRANSITION,
    PLANTANIM_ZOYBEANPOD_FULLY_CHARGED,
};


class PlantAnimRig_ZoybeanPod : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ZoybeanPod, PlantAnimRig, RtClass);

	bool PlayInitialFrame() override;
	bool PlayRecovery();
	bool PlayCharging();
    bool PlayFullyCharged();
    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
    bool PlayTransition(std::string i_prevIdleAnim);

	bool PlayPreviewAnim(bool bHideLayer = false) override;
    bool PlayZenGardenIdleAnim() override;

    pvztime_t CalcTransitionTime();

    std::string m_prevAnim;
    RtWeakPtr<Plant> m_plant;
    pvztime_t m_basicPreOpenSmokeDuration;
    pvztime_t m_basicPostOpenSmokeDuration;
    RtWeakPtr<Effect_ZoybeanPodSmoke> m_smokeMachine;

protected:
    void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
    void spawnSmokeCloud();
};

//#endif // __PLANT_ZOYBEANPOD_H__

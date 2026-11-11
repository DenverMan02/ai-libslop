/*
 * Plant_HydrocotyleDrummer.h
 *
 *  Created on: 2020-7-24
 *      Author: zhousen
 */

#ifndef PLANT_HYDROCOTYLEDRUMMER_H_
#define PLANT_HYDROCOTYLEDRUMMER_H_

#include "PlantFramework.h"
#include "RtDb.h"
#include "BoardEntity.h"
#include "Projectile.h"
#include "Plant.h"
#include "RtObject.h"
#include "Zombie.h"
#include <string>


enum HydrocotyledrummerState {
    HYDROCOTYLEDRUMMER_IDLE = STATE_FRAMEWORK_BEGIN,
    HYDROCOTYLEDRUMMER_RECOVERY,
    HYDROCOTYLEDRUMMER_BUFF,
    // HYDROCOTYLEDRUMMER_BUFFING,
    HYDROCOTYLEDRUMMER_STOPWATER,
    HYDROCOTYLEDRUMMER_PLANTFOOD,
};

////////////////////////////////////////////////////////////////
/// hydrocotyledrummer anim rig
////////////////////////////////////////////////////////////////
class PlantAnimRig_Hydrocotyledrummer : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Hydrocotyledrummer, PlantAnimRig, RtClass);

    PlantAnimRig_Hydrocotyledrummer();

    pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
};

////////////////////////////////////////////////////////////////
/// hydrocotyledrummer props
////////////////////////////////////////////////////////////////
enum {
    PARAMS_INDEX = -1,
    PARAMS_EFFECT_DURATION,
    PARAMS_ATTACK_RATIO,
    PARAMS_SPEED_RATIO,
    PARAMS_HITPOINT_RATIO,
    PARAMS_MUSIC_ATTACK_RATIO,
    PARAMS_MUSIC_SPEED_RATIO,
    PARAMS_MAX,
};

struct HydrocotyledrummerParams
{
    HydrocotyledrummerParams() {
        EffectDuration = 2.0f;
        AttackPlantAttackRatio = 0.1f;
        AttackPlantSpeedRatio = 0.1f;
        DefendPlantHitpointRatio = 0.1f;
        MusicPlantAttackRatio = 0.15f;
        MusicPlantSpeedRatio = 0.15f;
    }

    pvztime_t EffectDuration;//up duration time 
    float AttackPlantAttackRatio;//attack plants up ratio
    float AttackPlantSpeedRatio;
    float DefendPlantHitpointRatio;//defend plants up ratio
    float MusicPlantAttackRatio;//music plants up ratio
    float MusicPlantSpeedRatio;
};

class PlantHydrocotyledrummerProps : public PlantPropertySheet {
public:
    RT_CLASS_DEFINE(PlantHydrocotyledrummerProps, PlantPropertySheet, RtClass);    

    PlantHydrocotyledrummerProps();

    pvztime_t Recovery_time;// for each attack recovery time
    pvztime_t Zombie_slowdown_time;// normal attack make zombie slowdown
    pvztime_t Zombie_slowdown_time_mid;
    pvztime_t Zombie_slowdown_time_big;
    pvztime_t Zombie_idle_time;// plantfood make zombie idle

    HydrocotyledrummerParams Level1_Params;
    HydrocotyledrummerParams Level2_Params;
    HydrocotyledrummerParams Level3_Params;
    HydrocotyledrummerParams Level4_Params;
    HydrocotyledrummerParams Level5_Params;
    HydrocotyledrummerParams Plantfood_Params;
    HydrocotyledrummerParams Plantfood_Avatar_Params;

    pvztime_t Level5_healRecoveryTime;// level 5 skill heal plants recovery time
    float Level5_healRatio;// level 5 skill heal plants ratio

    std::vector<std::string> Level1MusicPlants;// level1 music plants typenames
    std::vector<std::string> Level1DefendPlants;// level1 defends plants typenames

    std::vector<std::string> MusicPlants;// above level2 music plants typenames
    std::vector<std::string> DefendPlants;// above level2 defends plants typenames

    std::vector<std::string> PlantfoodMusicPlants;// plantfood music plants typename
    std::vector<std::string> PlantfoodDefendPlants;// plantfood defend plants typename

    std::vector<std::string> PlantfoodAvatarMusicPlants;// plantfood avatar music plants typename
    std::vector<std::string> PlantfoodAvatarDefendPlants;// plantfood avatar defend plants typename

    PlantRestrictionSet PlantLevel5HealRestriction;// level5 heal effect blacklist
};

//////////////////////////////////////////////////////////////
/// plant hydrocotyledrummer
//////////////////////////////////////////////////////////////
class PlantHydrocotyledrummer : public PlantFramework {
public:
    RT_CLASS_DEFINE(PlantHydrocotyledrummer, PlantFramework, RtClass);

    PlantHydrocotyledrummer();
    ~PlantHydrocotyledrummer();

    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;

    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void onAnimStoppedCallback(const std::string& i_animCommand) override;

protected:
    void setState(HydrocotyledrummerState state);
    bool FindTarget();

    void DoBuff();
    void DoSpecialBuff();

    // buff attack plants
    void BuffAttackPlant(Plant* plant, bool plantfood = false);
    // buff defend plants
    void BuffDefendPlant(Plant* plant, bool plantfood = false);
    // buff music plants
    void BuffMusicPlant(Plant* plant, bool plantfood = false);

    void Level5Cure(Plant* plant, bool plantfood = false);

    void ApplyEffect(Plant* plant, int x, int y, int type, bool plantfood, bool isStrongAnim);
    void PlayDanceEffect(Plant* plant);
    void StopWaterPlant();

    bool HavePlantfoodSinger();
	std::string GetFireSoundEvent() const override;

private:
    pvztime_t m_recoveryEndTime;
    // some values in buff params

    HydrocotyledrummerParams m_currentRatioParam;
    HydrocotyledrummerParams m_currentPlantfoodRatioParam;
    
    std::vector<std::string> m_currentMusicPlants;
    std::vector<std::string> m_currentDefendPlants;

    std::vector<std::string> m_currentPlantfoodMusicPlants;
    std::vector<std::string> m_currentPlantfoodDefendPlants;

    Effect_PopAnim* m_dancingEffect;
};


////////////////////////////////////////////////////////////////
/// grid item effect proper
////////////////////////////////////////////////////////////////
class GridItemHydrocotyledrummerEffectProps : public GridItemAnimationProps {
public:
    RT_CLASS_DEFINE(GridItemHydrocotyledrummerEffectProps, GridItemAnimationProps, RtClass);

    GridItemHydrocotyledrummerEffectProps();
};


/////////////////////////////////////////////////////////////
/// grid item effect
/////////////////////////////////////////////////////////////

// which effect should grid item play
enum  {
    Effect_Normal,
    Effect_Music_Plantfood,
    Effect_Heal,
};

// grid item state
enum {
    Effect_State_Invalid = -1,
    Effect_State_Idle,
    Effect_State_Update,
    Effect_State_Off,
    Effect_State_AddTime,
    Effect_State_Die,
};

class GridItemHydrocotyledrummerEffect : public GridItemAnimation {
public:
    RT_CLASS_DEFINE(GridItemHydrocotyledrummerEffect, GridItemAnimation, RtClass);

    GridItemHydrocotyledrummerEffect();
    ~GridItemHydrocotyledrummerEffect();

    bool IsDamageable() const override { return false; }
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onGridItemInitialize() override;
    void onUpdate() override;
    void KillGridItem() override;
	int CalcRenderOrder() const override;

    void StartEffect(int type, pvztime_t duration, bool refresh_effect);// this is once effect
    void StartHealEffect(float ratio, pvztime_t duration, bool refresh_effect);// this is duration loop effect 
    void SetLevel(int level) { m_level = level; }
    void SetStrongAnim(bool isStrong) { m_isStrongAnim = isStrong; }

protected:
    void OnAnimStoppedCallback(const std::string& i_animCommand);
    void Level5Cure(Plant* plant, bool plantfood = false);
    void OnPlantDestroyed(Plant* plant);
    Plant* FindPlant(int x, int y);

private:
    int m_state;// grid item state
    pvztime_t m_effectEndTime;// total grid time end time
    pvztime_t m_healDuration;// invegator one heal duration the time
    pvztime_t m_healEndTime;// the heal end time
    float m_healRatio;// heal ratio
    int m_currentType;// the current animation type
    bool m_hasHeal;// if has heal effect
    std::string m_animNamePrefix;// eg.Level1 griditem play lv1_on, lv1_update, lv1_off animation,lv1 is the animation prefix
    int m_level;// plant level
    bool m_isStrongAnim;// chekc if play anim strong ( all music and defend plants are not strong animation )
    bool m_inHealEffectEnd;// the normal effect state when it is in heal status
};

#endif /* PLANT_HYDROCOTYLEDRUMMER_H_ */

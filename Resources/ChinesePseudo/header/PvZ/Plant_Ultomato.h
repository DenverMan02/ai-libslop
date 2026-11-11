//
//  Plant_Ultomato.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/24/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PLANT_ULTOMATO_H__
#define __PLANT_ULTOMATO_H__

#include <string>

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"
#include "PlantAnimRig.h"
#include "PopAnimRig.h"

class Zombie;

enum UltomatoState
{
    ULTOMATO_STATE_EXPLODED = STATE_FRAMEWORK_BEGIN
};

enum UltomatoEffectType
{
	ULTOMATO_EFFECT_LASER,
	ULTOMATO_EFFECT_LASER_START,
	ULTOMATO_EFFECT_HIT
};

class PlantUltomato : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantUltomato, PlantFramework, RtClass);

    ~PlantUltomato();
    
	void Initialize() override;
    void AddToRenderQueue(RenderQueue* i_queue) override;
	bool CanApplyPlantfood() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	float GetRefundSunAmount() override;
	
	bool CanUpgrade(void);
	void Upgrade(void);
    int GetUpgradeLevel() { return m_level; }
    
	void FireSelected(int i_faceId);
    void PlayAttackAnimation() override;

	std::string GetFireSoundEvent() const override;

	int GetGrowthLevel() const { return m_level; }
    int GetMaxHitpoints() override;

    void CancelPlantfood() override;
    void ApplyPlantfood() override;
    void UpdateUnconditionally() override;
    
    float GetReducedLaunchDelay() override;

    void DisplayAvatar() override;
    void TriggerBoost() override;

    void UpgradePlant() override;
    int GetCurrentCost(int i_plantLevel /* = -1 */) const;

    bool HasShadow() override
    {
        return m_plant->m_state != ULTOMATO_STATE_EXPLODED;
    }

    DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override { return i_plantWeapon == WEAPON_SECONDARY ? DAMAGE_FROM_PLANTFOOD_EFFECT | DAMAGE_ELECTRIC : DAMAGE_ELECTRIC; }
    
private:
    enum BeamState
    {
        BEAMSTATE_INACTIVE,
        BEAMSTATE_ACTIVE,
        BEAMSTATE_DISABLING
    };
    
    void onAnimStoppedCallback(const std::string& i_animLabel) override;
    
    void playUpgradeEffect();
    PlantWeapon getBaseWeapon();
    void fireBaseWeapon(RtWeakPtr<BoardEntity> i_target);
    bool fireMahLazer();
    Sexy::RtWeakPtr<Sexy::PopAnim> getMainAttackHitEffect();
    void updateMainBeamTarget();
    void damageMainBeamTarget();
    void damageSubBeamTarget(RtWeakPtr<BoardEntity> i_mainTarget, DamageInfo& i_damage);
    SexyVector2 getPositionForTarget(BoardEntity* i_target);
    void drawMainBeamAndOrigin(Graphics *i_g);
    int getMainBeamDPS();
    float getMainBeamYScale();
    float getMainBeamXOffset();
    float getMainBeamYOffset();
    SexyVector2 getHitEffectOffset();
    float getHitEffectYScale();
    void drawLaserFromTo(Graphics *i_graphics, const Sexy::SexyVector3 &i_from, const Sexy::SexyVector3 &i_to,
                                        const Sexy::Point &i_startArtOffset, const Sexy::Point &i_endArtOffset, Effect_PopAnim* i_beamRig,
                                        float i_beamYScale);
    void drawLaserFromToScreenSpace(Graphics *i_graphics, const Sexy::SexyVector2 &i_from, const Sexy::SexyVector2 &i_to,
                                        const Sexy::SexyVector2 &i_startArtOffset, const Sexy::SexyVector2 &i_endArtOffset, Effect_PopAnim* i_beamRig,
                                        float i_beamYScale);
    
    SexyVector2 getStartEffectOffset();
    void createLaserEffects();
    Sexy::RtWeakPtr<Sexy::PopAnim> getMainAttackStartEffect();
    std::string getLaserAnimationName(UltomatoEffectType i_type);
    int calcLaserRenderLayer();
    bool canSpawnChild();
    void trySpawnChild(PlantTypePtr i_type, int i_col, int i_row);

	int m_level;
    pvztime_t m_destroyAfterPlantfoodTime;
    pvztime_t m_beamEndTime;
    SexyVector2 m_beamTargetPositionBoardSpace;
    BeamState m_beamState;
    RtWeakPtr<BoardEntity> m_beamTarget;
    RtWeakPtr<class Effect_PopAnim> m_beamRig;
    RtWeakPtr<class Effect_PopAnim> m_beamHitFX;
    RtWeakPtr<class Effect_PopAnim> m_beamOriginFX;

};

class PlantTypeUltomato : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeUltomato, PlantType, RtClass) {}
    
    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    int GetExistingLevelCount() const;
    int CalcCostForLevelCount(int i_count, PlantAvatarType i_avatarType) const;

    // void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
    bool CanPlantOnPlant(Plant* plant) const override;
};

// AnimRig

class PlantAnimRig_Ultomato : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Ultomato, PlantAnimRig, RtClass);
    
    PlantAnimRig_Ultomato();
    
    //bool PlayIdleLooped() override;
    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
    bool PlayAttackLoop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayAttackEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

    void SetLevel(int level);
    
    bool PlayPreviewAnim(bool bHideLayer) override;
    bool PlayZenGardenIdleAnim() override;

    void onPostLoad() override;

    std::string getPlantFoodMainAnimName() override;
    bool PlayWatering() override;

private:
    int m_level;
    AnimHandle m_attackHandle;
    PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

class UltomatoProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(UltomatoProps, PlantPropertySheet, RtClass);

    UltomatoProps()
    {
        BeamDPSUpgrade1 = 100;
        BeamDPSUpgrade2 = 100;
        BeamDPSUpgrade3 = 100;
        HitpointsUpgrade2 = 100;
        HitpointsUpgrade3 = 100;
        CostPerExistingPlant = 0;
        ResetLaunchTimeOnUpgrade = 0.5;
        ReducedLaunchDelay = 1.0f;
        ImprovedReducedBonus = 1.0f;
        DamageDecayed = 0.0f;
    }

    int BeamDPSUpgrade1;
    int BeamDPSUpgrade2;
    int BeamDPSUpgrade3;
    int HitpointsUpgrade2;
    int HitpointsUpgrade3;
    
    int CostPerExistingPlant;
    
    float ResetLaunchTimeOnUpgrade;
    
    Sexy::Point BeamStartOffset;
    Sexy::Point BeamStartArtOffset;
    Sexy::Point BeamEndArtOffset;

    float ReducedLaunchDelay;
    float ImprovedReducedBonus;
    float DamageDecayed;
};

#endif

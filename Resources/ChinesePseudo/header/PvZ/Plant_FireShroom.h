//
//  Plant_FireShroom.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-9-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_FireShroom_h
#define PlantsVersusZombies2_Plant_FireShroom_h

#include "Plant_IceShroom.h"
#include "GridItemAnimation.h"

class PlantFireShroom : public PlantIceShroom
{
public:
	RT_CLASS_DEFINE(PlantFireShroom, PlantIceShroom, RtClass);
    
    PlantFireShroom();
    
	virtual ~PlantFireShroom();
    void    Initialize() override;
    void	CancelPlantfood() override;
    void	ApplyPlantfood() override;
    bool	CanApplyPlantfood() override;
    bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    Projectile*	   Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    void onSetDuplicate(bool i_duplicate) override {};
    virtual pvztime_t GetTheLeastAttactDuration() override;
private:
    
    void    NormalApplyPlantFood();    
    void    DoFallingStone(int i_type);

    bool    m_isLevel5Attack;
};

class PlantAnimRig_FireShroom : public PlantAnimRig_IceShroom
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_FireShroom, PlantAnimRig_IceShroom, RtClass);
    
    PlantAnimRig_FireShroom();
    
    bool PlayPreviewAnim(bool bHideLayer = false) override;
    
	virtual ~PlantAnimRig_FireShroom();
    
    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;

    void SetIsLevel5Attack(bool i_flag)
    {
        m_isLevel5Attack = i_flag;
    };

private:
    
    std::string getPlantFoodMainAnimName() override;
    
    std::string getIdleAnimationName() override;

    bool m_isLevel5Attack;
};

class FallingStoneEffectAnim : public Effect_PopAnim
{
public:
    
    RT_CLASS_DEFINE(FallingStoneEffectAnim, Effect_PopAnim, RtClass);
    
    void onAnimStopped(const std::string& i_animLabel) override;
    
    void SetEntity(BoardEntityPtr pSource, BoardEntityPtr pSrc);
    
private:
    
    BoardEntityPtr m_pSourceEntity;
    BoardEntityPtr m_pTargetEntity;
    
};


#pragma mark - FireShroomMagma

enum FireShroomMagmaState{
	PVZ_BEGIN_ENUM(FireShroomMagmaSTATE_),
	FireShroomMagma_STATE_UNKNOWN,
	FireShroomMagma_STATE_SPAWNING,
	FireShroomMagma_STATE_IDLE,
	FireShroomMagma_STATE_DISAPPEAR,
	FireShroomMagma_STATE_DEAD,
    PVZ_END_ENUM(FireShroomMagmaSTATE_)
};

class FireShroomMagma : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(FireShroomMagma, GridItemAnimation, RtClass);

    FireShroomMagma();

    virtual int CalcRenderOrder() const override;

    void InitFire(const DamageInfo& i_damageInfo);

protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

    void setState(FireShroomMagmaState i_state);
    void onAnimationDone(const std::string& i_tabel);
private:
    void takeEffect();
    FireShroomMagmaState m_state;
    float m_duration;
    DamageInfo m_damageInfo;
    pvztime_t m_endTime;
    pvztime_t m_updateTime;
    RtWeakPtr<class Effect_PopAnim> m_effect;
};

#endif

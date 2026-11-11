#ifndef __PLANT_COLDSNAPDRAGON_H__
#define __PLANT_COLDSNAPDRAGON_H__

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ComponentLinearBurst.h"
#include "GameSubSystem.h"
#include "Collectable.h"

class Projectile;
class Zombie;

class SnapdragonProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(SnapdragonProps, PlantPropertySheet, RtClass);
    
    SnapdragonProps()
    {
        ProjectilePAM = "";
    }
    
    std::string ProjectilePAM;
    float                     PlantfoodRate;
    ComponentLinearBurstProps BreathAreaBurst;
    ComponentLinearBurstProps PlantfoodBreathAreaBurst;
    ComponentLinearBurstProps PlantfoodBreathAreaBurstWithAvatars;
    DamageInfoProps PlantfoodSpecialDamagePropsWithAvatars;
};

class PlantColdSnapdragon : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantColdSnapdragon, PlantFramework, RtClass);
    
    void	Initialize() override;
    bool	CanApplyPlantfood() override;
    void	ApplyPlantfood() override;
    void	CancelPlantfood() override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void    OnTakeDamageDoneWithComponent() override;
    
private:
    void	createPlantfoodBuildUpEffect();
    void    freezeAllZombie();
    
    RtWeakPtr<ComponentLinearBurst> m_breathBurst;
};

class ColdSnapdragonFlyDragon:public BoardEntity
{
public:
    
    RT_CLASS_DEFINE(ColdSnapdragonFlyDragon, BoardEntity, RtClass);
    
    ColdSnapdragonFlyDragon();
    virtual ~ColdSnapdragonFlyDragon();
    
    void            initializeRenderEffect(float damage);
    
    void            onUpdate() override ;
    
    void            UpdateMotion();
    
    void            createIce(const Sexy::SexyVector3& pos);
    
    void            SetPosition(const SexyVector3& i_newPosition) override;

    void            SetPlant(PlantPtr i_plantPtr);
protected:
    
    int             m_currentGridPos = -1;
    
    float           m_speed;
    
    float           m_damage;

    PlantPtr        m_plantPtr;
    
    StandaloneEffectPtr m_renderEffect;
};


class PlantAnimRig_ColdSnapdragon : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_ColdSnapdragon, PlantAnimRig, RtClass);
    
    PlantAnimRig_ColdSnapdragon() {};
    
    virtual bool PlayAttackFireDragon(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
public:
    float m_plantfoodRate = 0.5f;
    bool  m_isNewPlantfood = false;
};

#endif //__PLANT_COLDSNAPDRAGON_H__

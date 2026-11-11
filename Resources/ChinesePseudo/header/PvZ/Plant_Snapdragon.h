#ifndef __PLANT_SNAPDRAGON_H__
#define __PLANT_SNAPDRAGON_H__

#include "PlantFramework.h"

/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class PlantSnapdragon : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSnapdragon, PlantFramework, RtClass);

	virtual void	Initialize() override;
	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
	virtual void	UpdatePlantfood() override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual GridItemPtr FindTargetDamageableGridItem(PlantWeapon i_plantWeapon) override;
	virtual DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
    virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	virtual void	onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect) override;
    void Idle() override;
    void onWatered(bool watered) override;
private:
	void			damageEntities(PlantWeapon i_plantWeapon, DamageInfo i_damage);
    void			applyWarming(DamageTypeFlags i_flags, PlantWeapon i_plantWeapon);
	bool			m_hasStartedPlantfoodAttack;
	float			m_plantfoodDamageApplied;
    
    Rect            m_plantfoodAttackRange;
    bool            m_shouldCastBlueFire;
};

class SnapdragonFlyDragon:public BoardEntity
{
public:
    
    RT_CLASS_DEFINE(SnapdragonFlyDragon, BoardEntity, RtClass);
    
    SnapdragonFlyDragon();
    virtual ~SnapdragonFlyDragon();
    
    void            initializeRenderEffect(float damage);
    
    void            onUpdate() override ;
    
    void            UpdateMotion();
    
    void            createIce(const Sexy::SexyVector3& pos);
    
    void            SetPosition(const SexyVector3& i_newPosition) override;
protected:
    
    int             m_currentGridPos = -1;
    
    float           m_speed;
    
    float           m_damage;
    
    StandaloneEffectPtr m_renderEffect;
};

#endif //__PLANT_SNAPDRAGON_H__

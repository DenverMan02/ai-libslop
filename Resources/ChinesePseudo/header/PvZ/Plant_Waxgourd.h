#ifndef PLANT_WAXGOURD_H
#define PLANT_WAXGOURD_H

#include "PlantFramework.h"
#include "Projectile.h"
#include "GameSubSystem.h"

class WaxgourdSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(WaxgourdSubsystem, GameSubSystem, RtClass);

    WaxgourdSubsystem();
    ~WaxgourdSubsystem() override;

    void StunZombies(const Rect& i_searchRect, float i_damage, bool i_beakBack);
private:
    bool shouldStun(Zombie* i_zombie);
};

class WaxgourdProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(WaxgourdProps, PlantPropertySheet, RtClass);

    WaxgourdProps()
    :NormalAttackCD(10.0f)
    ,Level5AttackCD(10.0f)
    ,PlantfoodBaseDamage(10)
    ,Level5BaseDamage(10)
    {
    }

    float NormalAttackCD;
    float Level5AttackCD;
    float PlantfoodBaseDamage;
    float Level5BaseDamage;
};

class PlantWaxgourd : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantWaxgourd, PlantFramework, RtClass);

    PlantWaxgourd();
    virtual ~PlantWaxgourd();

	virtual void			Initialize() override;
    virtual void			UpdateActions() override;

    virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			CancelPlantfood() override;

    virtual void		    DoSpecial(int i_extraParam = 0) override;
    virtual DamageInfo	    TakeDamage(const DamageInfo& i_damage) 	override;
    bool 					HasGravity() override;

protected:
    virtual void onAnimStoppedCallback(const std::string& i_animLabel) override;
    void                    setstate(uint i_state);
private:
    pvztime_t               m_nextNormalAttack;
    pvztime_t               m_nextLevel5Attack;
    pvztime_t               m_plantfoodcountdown;
    pvztime_t               m_idleDown;
};

class PlantAnimRig_Waxgourd : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Waxgourd, PlantAnimRig, RtClass);

    void setPlant(PlantPtr i_plant);

private:
    virtual std::string getIdleAnimationName() override;
    virtual std::string getAttackAnimationName() override;
    virtual std::string getPlantFoodMainAnimName() override;

private:
    PlantPtr m_plant;
};

#endif

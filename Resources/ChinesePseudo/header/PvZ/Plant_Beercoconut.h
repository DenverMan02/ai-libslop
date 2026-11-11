#ifndef PLANT_BEERCOCONUT_H
#define PLANT_BEERCOCONUT_H

#include "PlantFramework.h"
#include "GameSubSystem.h"

class BeercoconutSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(BeercoconutSubsystem, GameSubSystem, RtClass);

    void BeercoconutTossZombies(Plant* i_plant, bool i_isLevel5, bool i_isPlantfood);

    void onIceSkillZombieLanding(class Zombie* i_zombie);
    void onAvatarSkillZombieLanding(class Zombie* i_zombie);
private:
    int m_extraFrozenRate;
};

STATE_ENUM_CHILD_BEGIN(BeercoconutState, PlantState)
    BEERCOCONUT_ACCUMLATION,
    BEERCOCONUT_ATTACKING,
STATE_ENUM_END(BeercoconutState);


class BeercoconutProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BeercoconutProps, PlantPropertySheet, RtClass);

    BeercoconutProps()
    {
        AccumTime = 10;
        Level2AccumTime = 8;
        Level3AccumTime = 6;
        Level5Rate = 0.5f;
    }

    float AccumTime;
    float Level2AccumTime;
    float Level3AccumTime;
    float Level5Rate;
};

class PlantBeercoconut : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantBeercoconut, PlantFramework, RtClass);

	virtual void			Initialize() override;
    virtual void			UpdateActions() override;

    virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void            CancelPlantfood() override;

    virtual DamageInfo	    TakeDamage(const DamageInfo& i_damage) override;

    virtual bool            OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void            onAnimStoppedCallback(const std::string& i_animLabel) override;


    void                    setstate(uint i_state);


private:
    pvztime_t m_lastTokeDamage;
    pvztime_t m_accumTime;
    pvztime_t m_maxAccumTime;
    bool m_isLevel5;
};

class PlantAnimRig_Beercoconut : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Beercoconut, PlantAnimRig, RtClass);

    PlantAnimRig_Beercoconut();

    bool PlayStartAccumlation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayAccumlation();
    void setIsLevel5(bool i_flag);

private:
	virtual std::string getAttackAnimationName() override;
    virtual	std::string getPlantFoodMainAnimName() override;

    bool m_isLevel5;
};

#endif
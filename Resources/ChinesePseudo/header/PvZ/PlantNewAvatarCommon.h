#ifndef __PlantsVersusZombies2__PlantNewAvatarCommon__
#define __PlantsVersusZombies2__PlantNewAvatarCommon__

#include "PlantNewAvatar.h"

class NewAvatarGeneralSkillBoost : public PlantNewAvatar
{
public:
	RT_CLASS_DEFINE(NewAvatarGeneralSkillBoost, PlantNewAvatar, RtClass);
    NewAvatarGeneralSkillBoost()
    :BoostRate(0.0f)
    {}
    float BoostRate;
};

class WinterMelonBoostFreeze : public PlantNewAvatar
{
public:
	RT_CLASS_DEFINE(WinterMelonBoostFreeze, PlantNewAvatar, RtClass);
    WinterMelonBoostFreeze()
    :BoostExtraFreezeRate(0.07)
    {}
    float BoostExtraFreezeRate;
};

class ChardGuardBoostRecover : public PlantNewAvatar
{
public:
	RT_CLASS_DEFINE(ChardGuardBoostRecover, PlantNewAvatar, RtClass);
    ChardGuardBoostRecover()
    :BoostRecoverTime(10)
    {}
    float BoostRecoverTime;
};

class DusklobberBoostRate : public PlantNewAvatar
{
public:
	RT_CLASS_DEFINE(DusklobberBoostRate, PlantNewAvatar, RtClass);
    DusklobberBoostRate()
    :BoostRate(0.2)
    {}
    float BoostRate;
};

class WitchhazelBoostMagicCD : public PlantNewAvatar
{
public:
	RT_CLASS_DEFINE(WitchhazelBoostMagicCD, PlantNewAvatar, RtClass);
    WitchhazelBoostMagicCD()
    :MagicCD(0.2)
    {}
    float MagicCD;
};

class PrimalpeashooterBoostKnockbackChance : PlantNewAvatar
{
public:
	RT_CLASS_DEFINE(PrimalpeashooterBoostKnockbackChance, PlantNewAvatar, RtClass);
    PrimalpeashooterBoostKnockbackChance()
    :BoostRate(0.05)
    {}
    float BoostRate;
};

class PeashooterBoostReShoot : public PlantNewAvatar
{
public:
    RT_CLASS_DEFINE(PeashooterBoostReShoot, PlantNewAvatar, RtClass);
    PeashooterBoostReShoot()
    :BoostRate(0.1)
    {}
    float BoostRate;
};

class cactusBoostReShoot : public PlantNewAvatar
{
public:
    RT_CLASS_DEFINE(cactusBoostReShoot, PlantNewAvatar, RtClass);
    cactusBoostReShoot()
    :BoostRate(0.1)
    {}
    float BoostRate;
};

#endif
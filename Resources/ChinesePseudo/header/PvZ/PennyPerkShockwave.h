//
// Created by Starkey, Andrew on 2020-01-23.
//

#ifndef PVZ2_PENNYPERKSHOCKWAVE_H
#define PVZ2_PENNYPERKSHOCKWAVE_H

#include "BasicPerks.h"
#include "Projectile.h"

class PennyPerkShockwaveProperties : public PennyPerkProperties
{
public:
    RT_CLASS_DEFINE(PennyPerkShockwaveProperties, PennyPerkProperties, RtClass);

    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

    std::vector<float> TimesBetweenApplications;
    std::vector<float> PushBackDistance;

    SexyString GetDescriptionForLevel(int i_level) override;
    SexyString TranslatePerkName() override;
};

class PennyPerkShockwave : public PennyPerkTimedEffect
{
public:
    RT_CLASS_DEFINE(PennyPerkShockwave, PennyPerkTimedEffect, RtClass);

protected:
    void onUpdate() override;

private:
    pvztime_t calcNextUpdateTime() override;
    void createShockWave();
};

class PennyPerkShockwaveProjectileProperties : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PennyPerkShockwaveProjectileProperties, ProjectilePropertySheet, RtClass);
};

class PennyPerkShockwaveProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PennyPerkShockwaveProjectile, Projectile, RtClass);

    void SetKnockbackDistance(float i_knockbackDistance) { m_knockbackDistance = i_knockbackDistance; }

protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override {return true;}
    void knockbackZombie(BoardEntity* i_impactedEntity, float i_distance, float i_time, float i_height);

private:
    float m_knockbackDistance = 0;
};


#endif //PVZ2_PENNYPERKSHOCKWAVE_H

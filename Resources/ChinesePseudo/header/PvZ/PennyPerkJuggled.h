/*
 * PennyPerkJuggled.h
 *
 *  Created on: 2020-10-28
 *      Author: admin
 */

#ifndef PENNYPERKJUGGLED_H_
#define PENNYPERKJUGGLED_H_

#include "BasicPerks.h"
#include "Utils.h"

typedef struct RiftProjectileTimer RProjectileTimer;

class PennyPerkJuggledProperties : public PennyPerkProperties
{
public:
	RT_CLASS_DEFINE(PennyPerkJuggledProperties, PennyPerkProperties, RtClass);

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<float> TimesBetweenApplications;
	std::vector<float> Duration;

	SexyVector3 LaunchVelocity;
	SexyVector3 LaunchAcceleration;
	ValueRange LaunchHeight;

	int MaxProjectilesToJuggle;
	float JuggleLaunchDelay;
	float MoveSpeedMultiplierWhileJuggling;
	float CatchArcDegrees;

	std::vector<std::string> JuggleableProjectiles;
	std::vector<std::string> UnthrowableProjectiles;
	std::vector<std::string> AngleAgnosticProjectiles;

	SexyString GetDescriptionForLevel(int i_level) override;
};

struct PerkJuggledData
{
	PerkJuggledData()
	{
		m_accumulatedTime = 0;
	}

	std::vector<RProjectileTimer> m_juggledProjectiles;
	pvztime_t 						  m_accumulatedTime;
	RtWeakPtr<class Plant> m_plant;
};

class PennyPerkJuggled : public PennyPerkTimedEffect
{
	RT_CLASS_DEFINE(PennyPerkJuggled, PennyPerkTimedEffect, RtClass);

public:
	void Activate() override;

	bool addProjectile(class Projectile* i_projectile, class Plant* i_plant);

protected:
	void onUpdate() override;
	void updateOthers() override;

private:
	pvztime_t calcNextUpdateTime() override;
	void enableJuggled();
	void disableJuggled();
	void updateJunggle();

	void buildProjectileSets();
	void clearAllProjectiles();
	bool canJuggleProjectile(class Projectile* i_projectile);
	bool isProjectileArrivingAtCatchableAngle(class Projectile *i_projectile);
	bool storeProjectileInJuggleLimbo(class Projectile *i_projectile, class Plant* i_plant);
	void launchProjectile(class Projectile *i_projectile, RtWeakPtr<class Plant> i_plant);

	bool m_enabled;
	std::set<const class ProjectilePropertySheet*> m_juggleableProjectiles;
	std::set<const class ProjectilePropertySheet*> m_unthrowableProjectiles;
	std::set<const class ProjectilePropertySheet*> m_angleAgnosticProjectiles;
	std::vector<PerkJuggledData> m_datas;
	pvztime_t m_endTime;
};


#endif /* PENNYPERKJUGGLED_H_ */

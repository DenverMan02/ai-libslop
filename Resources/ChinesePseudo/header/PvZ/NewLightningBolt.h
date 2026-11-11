/*
 * NewLightningBolt.h
 *
 *  Created on: 2019-10-10
 *      Author: Administrator
 */

#ifndef NEWLIGHTNINGBOLT_H_
#define NEWLIGHTNINGBOLT_H_

#include <vector>

#include "BoardEntity.h"
#include "PopAnimRig.h"
#include "NewRayEntity.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TimeMgr.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class NewLightningBolt : public NewRayEntity
{
public:
	RT_CLASS_DEFINE(NewLightningBolt, NewRayEntity, RtClass);

	NewLightningBolt();

	void InitializeBounceInfo(const int i_maxBounces, const pvztime_t i_bounceDelay, const std::string& i_bouncePopAnimName, const std::string& i_typeName);
	void InitializeDamageInfo(const float i_damage, const float i_bounceDamagePercent, const float i_damageMasteryPiercing) { m_damage = i_damage; m_bounceDamagePercent = i_bounceDamagePercent; m_damageMasteryPiercing = i_damageMasteryPiercing;}

	void SetHitTargets(const std::vector<BoardEntityPtr> i_hitTargets) { m_hitTargets = i_hitTargets; }


protected:
	void onInitialized() override;
	void onUpdate() override;

	void createPopAnimsToTarget(const BoardEntityPtr i_target) override;

private:
	void causeDamage(BoardEntityPtr i_target);
	void createBounce();
	void setBounceCount(const int i_count) { m_bounceCount = i_count; }

	int m_bounceCount;
	int m_maxBounces;

	float m_damage;
	float m_bounceDamagePercent;
    float m_damageMasteryPiercing;

	std::vector<BoardEntityPtr> m_hitTargets;

	pvztime_t m_bounceTime;
	pvztime_t m_bounceDelay;

	std::string m_bouncePopAnimName;
	std::string m_plantTypeName;
};


#endif /* NEWLIGHTNINGBOLT_H_ */

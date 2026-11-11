//
//  LightningCloud.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LightningCloud_h
#define PlantsVersusZombies2_LightningCloud_h

#include <string>

#include "BoardEntity.h"
#include "PlatformAutodetect.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "TimeMgr.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class CloudBase : public BoardEntity
{
public:
	enum LightningCloud_State
	{
		STATE_LIGHTNINGCLOUD_UNINITIALIZED,
		STATE_LIGHTNINGCLOUD_IDLE,
		STATE_LIGHTNINGCLOUD_MOVING,
		STATE_LIGHTNINGCLOUD_ATTACKING,
		
		STATE_LIGHTNINGCLOUD_SPAWNING,
	};

public:
	RT_CLASS_DEFINE(CloudBase, BoardEntity, RtClass);

	CloudBase();

	void SetAttackCooldown(float i_time) { m_attackCooldown = i_time; }
	void SetCloudSpeed(float i_speed) { m_cloudSpeed = i_speed; }
	void SetOwner(BoardEntityPtr i_owner) { m_owner = i_owner; }
	void SetDamage(float i_damage) { m_damage = i_damage; }
	bool ShouldDrawShadow() const override { return false; }
	void SetMaxTargets(int i_targets) { m_remainingTargets = i_targets; }
    void SetMaxAttackCount(int count) { m_attackCount = count; }
    void SetAttackRect(const Rect& rect) { m_attackRect = rect; }
    void SetBossDamageRate(float rate) { m_bossDamageRate = rate; }
    float GetDamage() { return m_damage; }
protected:
	void setTargetTypes(BoardEntityTypeFlag i_typesToTarget) { m_typesToTarget = i_typesToTarget; }
    bool findNextTarget();
    virtual bool WillTarget(BoardEntity* entity);
	virtual BoardEntity* pickPreferredTarget(std::vector<BoardEntity*> i_zombies, std::vector<BoardEntity*> i_gridItems);
	
	void onDraw(Graphics* i_g) override;
	void onUpdate() override;
	void onDestroy() override;

	void setState(uint i_plantState);
	
	PopAnimRigPtr m_animRig;
	
	// Interface
protected:
	virtual DamageInfo createDamage();
	virtual void onUpdateCloud();
	virtual void onStateChanged(uint i_state) {};
	virtual void onAttack(BoardEntity* target) {};
	virtual DamageTypeFlags getDamageTypeFlags() { return DAMAGE_NONE; }
	virtual void onNoTargetRemaining() {};
	
private:
	BoardEntityTypeFlag m_typesToTarget;
	BoardEntityPtr m_owner;
	BoardEntityPtr m_target;
	pvztime_t m_nextAttackTime;
	
	float m_attackCooldown;
	float m_cloudSpeed;
	float m_damage;
    float m_bossDamageRate;
	uint m_state;
	int m_remainingTargets;
    int m_attackCount;
    Sexy::Rect	m_attackRect;
};

class LightningCloud : public CloudBase
{
public:
	RT_CLASS_DEFINE(LightningCloud, CloudBase, RtClass);

	LightningCloud();

protected:
	void onInitialized() override;
	void onUpdateCloud() override;
	void onStateChanged(uint i_state) override;
	void onAttack(BoardEntity* target) override;
	DamageTypeFlags getDamageTypeFlags() override { return DAMAGE_LIGHTNING | DAMAGE_FROM_PLANTFOOD_EFFECT; }

private:
	pvztime_t m_finishTime;
	bool m_canMove;

	void onPlantFinished(const std::string &i_animName);
	void onDieFinished(const std::string &i_animName);
};




#endif

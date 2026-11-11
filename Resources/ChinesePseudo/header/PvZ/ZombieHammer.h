//
//  ZombieProspector.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIESHAMMER_H__
#define __ZOMBIESHAMMER_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieHammerState, ZombieState)
	ZS_Hammer_Block,
    ZS_Hammer_Rest,
    ZS_Hammer_ChargeAttack,
STATE_ENUM_END(ZombieHammerState);

class ZombieHammer : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieHammer, Zombie, RtClass);

	ZombieHammer();
	virtual ~ZombieHammer(){}
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;
    void startBlockAnimation();
    void ApplyZombieFood() override;
    void CancelZombieFood() override;
    bool    isCdAvailable;
    bool    willBeStun;
protected:
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    virtual ZombieParticle* DropArm() override;
    bool CanShiftProjectile(Projectile* projectile);
    void ShiftProjectile(Projectile *projectile);
    Effect_PopAnim* CreateChargeAttackEffect(RenderLayer baselayer);
    
	DECLARE_STATE_FUNCTIONS(ZombieState, Block);
    DECLARE_STATE_FUNCTIONS(ZombieState, Rest);
    DECLARE_STATE_FUNCTIONS(ZombieState, ChargeAttack);
    
	void onBlockEnd(Zombie* z);
    void onRestEnd(Zombie* z);

	bool m_dynamiteActive;
	bool m_countdownStarted;
	
	pvztime_t m_countdown;
    pvztime_t hasRestTime;
    pvztime_t hasBlockTime;
    pvztime_t blockSoundStartTime;
private:
    void onAnimStopped(const std::string& i_animLabel);
    void PlayChargeAttackEffect();
    void DamageTarget(const Rect& rect, float baseDamage);
    void DamageTarget(BoardEntity* target, float baseDamage);
    bool CanTarget(BoardEntity* entity);
    bool AdvanceSpin();
    void UpdateSpinPosition();
    Rect CalcAttackRect( const Rect& src);
    std::vector<BoardEntity*> GetSpinAttackTarget();
};

#endif

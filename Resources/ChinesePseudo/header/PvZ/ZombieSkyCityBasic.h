//
//  ZombieSkyCityBasic.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/16
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSkyCityBasic_h
#define PlantsVersusZombies2_ZombieSkyCityBasic_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieBasic.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"
#include "Projectile.h"
#include "Effect_Barrage.h"
#include "ZombieAnimRig_SkyCityBasic.h"

class ZombieSkyCityBasic : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieSkyCityBasic, Zombie, RtClass);
    ZombieSkyCityBasic();

    virtual BoardEntity *findTarget() override;
	virtual std::vector<BoardEntityPtr> findAttackTargets() override;
    
    void GetPooyanPrepared();
    Effect_Barrage * GetBarragePtr();

	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onEndCondition(ZombieConditions i_condition) override;

protected:
	virtual void onUpdate() override;
    virtual void onZombieInitialize() override;
	virtual void onAttackAnimStopped(const std::string& i_animLabel) override;

    std::string getAshPAMName() const override; 
    
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Glide);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Attack);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	OVERRIDE_STATE_ONENTER(ZombieState, Die);
private:
	SexyVector3 GetAttackEffectPosition();
    void PlayAttackEffect(bool bNeedPrepare);
	void PlayAttackEndEffect();
	void onAttackEffectEnd(class StandaloneEffect* pEffect);
    void onAttackPrepareStopped(const std::string&);
    void preShoot();
    void takeShoot();
    // void stopShoot();
private:
    pvztime_t		m_lastShootTime;
    bool					m_glide;
    bool					m_prepared;
    float					m_interval;
	bool					m_bFirePaused;
    Effect_Barrage  m_barrage;
};

#endif

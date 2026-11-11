//
//  SecurityGourdModule.h
//  PlantsVersusZombies2
//
//  Created by rknapp on 7/6/17
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SecurityGourdModule_h
#define PlantsVersusZombies2_SecurityGourdModule_h

#include <string>

#include "LevelModule.h"
#include "RtObject.h"
#include "Zombie.h"
#include "MacroStateMachine.h"
#include "Zombie.h"

namespace Sexy
{
	class PopAnim;
}
class BoardEntity;
class AdaptorSecurityGourdDialog;
class StandaloneEffect;

STATE_ENUM_BASE_BEGIN(SecurityGourdState)
	Idle,
	AnimVineDown,
	AnimWrap,
	AnimVineUp,
	AnimGourdDown,
	AnimGourdUp,
STATE_ENUM_END(SecurityGourdState);

class SecurityGourdModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(SecurityGourdModule, LevelModule, RtClass);
	SecurityGourdModule();
	virtual ~SecurityGourdModule();

	void TriggerEffect();

protected:
	void initializeModule() override;
	void registerForEvents() override;

private:
	void getWinningZombie();
	void destroyZombies();
	bool shouldDestroyZombie(Zombie* i_zombie) const;
	void destroyZombie(Zombie* i_zombie, DamageTypeFlags additionalCustomFlags = (DamageTypeFlags)0);
    void doExtraActionsToAllZombies();
    void knockbackZombies();
	bool shouldKnockbackZombie(Zombie* i_zombie) const;
	void knockbackZombie(Zombie* i_zombie);
	void resetPlantCooldowns();
	void doGameplayEffect();
	std::string GetLayerToShow(ZombieSizeType size);
	void ShowAnimationLayerForZombieSize(ZombieSizeType size);
	SexyVector3 GetVineDownOffsetForSize(ZombieSizeType size);
	SexyVector3 GetVineWrapOffsetForSize(ZombieSizeType size);

	void initializeStateMachine();
	void update();
	void updateEffect(RtWeakPtr<Effect_PopAnim> i_effect);
	void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);

	void onVineDownEffectComplete(StandaloneEffect* i_effect);
	void onVinesEffectComplete(StandaloneEffect* i_effect);
	void onVineUpEffectComplete(StandaloneEffect* i_effect);
	void onGourdDropEffectComplete(StandaloneEffect* i_effect);

	ZombiePtr m_targetZombie;
	Sexy::MTRand m_rand;
	RtWeakPtr<Effect_PopAnim> m_vinesLineEffect;
	RtWeakPtr<Effect_PopAnim> m_vinesTopEffect;
	RtWeakPtr<Effect_PopAnim> m_vinesBottomEffect;
	RtWeakPtr<Effect_PopAnim> m_vinesEffect;
	RtWeakPtr<Effect_PopAnim> m_gourdDropEffect;

protected:
	DECLARE_FSM_HANDLER_BASE(SecurityGourdState);
private:
	DECLARE_FSM_STATE_VALUE(SecurityGourdState);

	float m_grabStartTime;
	float m_grabEndTime;
	SexyVector3 m_grabStartPosition;
	SexyVector3 m_grabEndPosition;
	bool m_currentAnimationComplete;
};

class SecurityGourdModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SecurityGourdModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return SecurityGourdModule::StaticGetClass();
	}

	SecurityGourdModuleProperties()
	{
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	int DestroyZombiesAffectedColumns;
	float DestroyZombiesUnderHealthPercent;

	int KnockbackAffectedColumns;
	float KnockbackDistance;
	float KnockbackTime;
	float KnockbackHeight;

	bool ResetPlantCooldowns;
    
    std::vector<std::string> ZombieClassKillWhitelist;
};

namespace Message
{
	void SecurityGourdsPurchased(int i_gemCost);
}

#endif

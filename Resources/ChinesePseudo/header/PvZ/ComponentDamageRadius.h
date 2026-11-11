#ifndef __PlantsVersusZombies2__ComponentDamageRadius__
#define __PlantsVersusZombies2__ComponentDamageRadius__

#include "ComponentRadiusBurst.h"
#include "DamageInfoProps.h"

class ComponentDamageRadiusProps : public ComponentRadiusBurstProps
{
public:
	ComponentDamageRadiusProps()
	:ComponentRadiusBurstProps() {}
	
	std::string		ImpactSound = "";
    Sexy::Point		ShakeBoard = { 0, 0 };
	std::string		PopAnimHitEffectName = "";
	DamageInfoProps	DamageProps;
};

class ComponentDamageRadius : public ComponentRadiusBurst
{
public:
	RT_CLASS_DEFINE(ComponentDamageRadius, ComponentRadiusBurst, RtClass);

	void StartPulse();
	void StartApply();

	void SetRadiusProps(const ComponentDamageRadiusProps& i_props);
	bool HasPopanim();
	
protected:
	void beginApply() override;
	void beginCoolDown() override;
	void onAnimationTriggered() override;
	
	virtual void	damageZombies();
	void			applyDamageTo(std::vector<BoardEntity*> i_touchedEntities);

private:
	float			calculateDamageBasedOnDistance(BoardEntity* i_entity);
	DamageInfo		calculateDamageInfo();
	
	void			damageGridItems();
	void			playDamageSound();
	void			createDamageEffect(BoardEntity* target);
	
	void			reportNumberOfZombiesDamagedToOwner(int i_numDamagedZombies);
    void            NotifyDamagedZombie(BoardEntity *entity);
    void			reportToOwnerWhenApplyingDamage();
	
	ComponentDamageRadiusProps m_damage_props;
};

class ComponentDamageTossRadiusProps : public ComponentDamageRadiusProps
{
public:
	ComponentDamageTossRadiusProps()
	:ComponentDamageRadiusProps() {}

	float TossDistance = 0.0f;
	float TossTime = 0.0f;
	float TossHeight = 0.0f;
};

class ComponentDamageTossRadius : public ComponentDamageRadius
{
public:
	RT_CLASS_DEFINE(ComponentDamageTossRadius, ComponentDamageRadius, RtClass);

	void SetOwner(RtWeakPtr<class Plant> i_ower) { m_owner = i_ower; }
	void SetRadiusProps(const ComponentDamageTossRadiusProps& i_props);

protected:
	void damageZombies() override;

private:
	void tossZombies(const std::vector<class BoardEntity*>& i_entities);

	ComponentDamageTossRadiusProps m_toss_props;
	RtWeakPtr<class Plant> m_owner;
};

#endif /* defined(__PlantsVersusZombies2__ComponentDamageRadius__) */

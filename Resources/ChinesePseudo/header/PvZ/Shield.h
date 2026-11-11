#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "GameObject.h"
#include "DamageInfo.h"
#include "PlantAnimRig_Shielded.h"

class ShieldProps
{
public:
	ShieldProps():
	Hitpoints{0.f}
	{}
	ShieldProps(int i_health) :
		Hitpoints(i_health)
	{}
	float	Hitpoints;
};

class Zombie;
class Shield : public GameObject
{
	RT_CLASS_DEFINE(Shield, GameObject, RtClass);
public:
	Shield();
	void		SetProps(const ShieldProps& i_props);
	const ShieldProps& GetProps();
	void		SetAnimRig(RtWeakPtr<PlantAnimRig_Shielded> animRig);
	DamageInfo	ReduceDamage(const DamageInfo& i_damage);
	bool		TakeSmashAttack(BoardEntity* i_instigator);
	bool		TryBlockZombossRush(Zombie *i_zombie);
	bool		CanDeployShield();
	void		DeployShield();
    
    bool        Undamaged() { return hasShield(); }
    SexyString  GetShieldInfo();
    SexyString  GetShieldPercent();
	
    bool	hasShield();

	int		getCurrentHitPoint();
	void	setCurrentHitPoint(int i_hitpoint);

protected:
	bool	isExcessiveDamage(const DamageInfo& i_damage);
	int		getDamageIndex(int i_numDamageStates);
	void	updateLayers();

	RtWeakPtr<PlantAnimRig_Shielded>	m_animRig;
	float			m_hitpoints;
	ShieldProps		m_props;
	int				m_damageIndex;
};

#endif //__SHIELD_H__

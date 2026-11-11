#pragma once

#include "PlantFramework.h"
#include "EffectAnimRig_SpikeweedSaw.h"

class PlantSpikeweed : public PlantFramework
{
public:
    
    PlantSpikeweed();
	virtual ~PlantSpikeweed();
    
	RT_CLASS_DEFINE(PlantSpikeweed, PlantFramework, RtClass);

public:
	virtual void		Initialize() override;
	virtual void		Draw(Graphics * i_g) override;
	virtual void		UpdateActions() override;
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	virtual SexyVector2		GetShadowOffset() override;
	virtual bool		CanApplyPlantfood() override;
	virtual void		ApplyPlantfood() override;
	virtual void		CancelPlantfood() override;
	virtual bool		HasShadow() override
	{
		return false;
	}
	virtual int			CalcRenderOrder() override;
	virtual void 		OnKillZombie(Zombie* i_zombie);

	virtual void		TakeGridItemSmashAttack(Sexy::RtWeakPtr<GridItem> i_srcGridItem) override;

	// Is unique to plant...
	void				SetPlantfoodFocus(const bool i_hasFocus);		// Only one spikeweed can have its plantfood effect working per row

protected:
	virtual PopAnimRig*		createPlantfoodSawEffect();
    bool                    canAttackZombie(ZombiePtr& i_zombie);
    DamageTypeFlags 	GetDamageFlags(PlantWeapon i_plantWeapon) override { return DAMAGE_FROM_MELEE; }
    
    enum State
	{
		STATE_ATTACKING = STATE_FRAMEWORK_BEGIN,
		STATE_ATTACKED,
		STATE_PF_ATTACKING,
		STATE_PF_ATTACKED,
	};

private:
	
	virtual void		playAttackSound();
	virtual void 		stopAttackSound();

	void				setState(const uint i_state);
	const bool			isValidSpikeLocation(const int i_gridX, const int i_gridY);
	void				findZombiesInRowAndApplyStun();
    
    void                ApplyStab(class Zombie * i_zombie);

	virtual void		onDestroy() override;

	void 				onZombieDamageTaken(Zombie* i_zombie, const DamageInfo& i_damage);

	void				NotifyZombieKilled();

	void				TransformSelf();

	std::vector<PopAnimRigPtr> m_plantfoodSpikes;		// 9 columns total, but only 8 are spawned (the 9th column is the spikeweed, whereever it lies).
	bool				m_plantfoodSpikesActive;
	int					m_killedZombieCount;
	bool				m_isTransformed;
};


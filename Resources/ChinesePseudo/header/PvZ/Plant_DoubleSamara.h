//
//  Plant_DoubleSamara.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.6.30
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantDoubleSamara_H__
#define __PlantDoubleSamara_H__

#include "PlantFramework.h"
#include "Zombie.h"

class PlantDoubleSamara : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantDoubleSamara, PlantFramework, RtClass);
	PlantDoubleSamara();

	virtual void		Initialize() override;
	virtual void 		registerForEvents() override;
	virtual void 		unregisterForEvents() override;

	virtual void		DoSpecial(int i_extraParam = 0) override;
	virtual void		UpdateActions() override;
	virtual bool		OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
		
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;

	virtual bool		CanBeShoveled() override { return false; }
	virtual bool		CanBeTargeted() override { return false; }
	virtual bool		IsInvincible() const override { return true; }

	void					onZombieTossEnd(Zombie* i_zombie);

protected:
	void					CollectZombies();
    
public:
	class CollectedZombie
	{
	public:
		CollectedZombie();
		inline bool operator == (const CollectedZombie& inOther) const { return m_zombiePtr == inOther.m_zombiePtr; }
		inline bool operator != (const CollectedZombie& inOther) const { return !operator==(inOther); }
		inline bool operator < (const CollectedZombie& inOther) const { return m_zombiePtr < inOther.m_zombiePtr; }

		bool				CanBeControlled();
	public:
		ZombiePtr			m_zombiePtr;
		SexyVector3		m_posOrgin;
		pvztime_t			m_timerBack;
	};
protected:
	std::vector<CollectedZombie>		m_collectedZombies;
	bool														m_bTrigger;
    
};

#endif //__PLANT_CHERRYBOMB_H__

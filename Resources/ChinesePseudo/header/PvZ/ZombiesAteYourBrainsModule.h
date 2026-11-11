//
//  ZombiesAteYourBrainsModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/24/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiesAteYourBrainsModule_h
#define PlantsVersusZombies2_ZombiesAteYourBrainsModule_h

#include "LevelModule.h"
#include "Zombie.h"
#include "TimeLine.h"

class ZombiesAteYourBrainsModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(ZombiesAteYourBrainsModule, LevelModule, RtClass);
	
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
     
private:
	void startTestingForZombieWin();
	void stopTestingForZombieWin();
	void onUpdate();
	
	bool checkDoesZombieWin(ZombiePtr i_zombie);
	
	bool m_testingForZombieWin = false;
};
 
class ZombiesAteYourBrainsProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(ZombiesAteYourBrainsProperties, LevelModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return ZombiesAteYourBrainsModule::StaticGetClass();
    }
 
    ZombiesAteYourBrainsProperties()
    {
		ZombieWinPositionX = -80.f;
    }
	
	float ZombieWinPositionX;
};


// card game zombie ate base
class CardGameZombiesAteYourBaseModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(CardGameZombiesAteYourBaseModule, LevelModule, RtClass);

    virtual ~CardGameZombiesAteYourBaseModule();

    float GetMaxHitpoints() const;
    float GetHitpoints() const;
    void TakeDamage(float i_hitPoints);
	
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
     
private:
	void startTestingForZombieWin();
	void stopTestingForZombieWin();
	void onUpdate();
    void addToRenderQueue(RenderQueue* i_queue);
	
	bool checkDoesZombieWin(ZombiePtr i_zombie);
	bool checkDoesProjectileHit(ProjectilePtr i_proj);
	void CheckDestroyZombie(ZombiePtr i_zombie);
	void CheckDestroyProject(ProjectilePtr i_proj);
	
	void onAirshipTakeDamage(float i_amount);
    void AddMessage(ZombiePtr zombie, int hitpoint, Color color, pvztime_t duration = 0.4f);

	bool m_testingForZombieWin = false;

	float m_hitpoints;
	float m_hitpointsMax;
	float m_biteHitpoints;

	std::vector<ZombiePtr> m_winZombieList;
	std::vector<ProjectilePtr> m_hitProjectileList;
    AnimationMgrWkPtr       m_animationMgr;
};
 
class CardGameZombiesAteYourBaseProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(CardGameZombiesAteYourBaseProperties, LevelModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return CardGameZombiesAteYourBaseModule::StaticGetClass();
    }
 
    CardGameZombiesAteYourBaseProperties()
    {
		ZombieWinPositionX = -80.f;
		BaseMaxHitpoints = 1000.0f;
		DeltaBiteHitpoints = 50.0f;
    }
	
	float ZombieWinPositionX;
	float BaseMaxHitpoints;
	float DeltaBiteHitpoints;
};

#endif

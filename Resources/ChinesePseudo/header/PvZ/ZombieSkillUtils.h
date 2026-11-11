//
//  ZombieSkillUtils.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 14-1-17.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//


#ifndef __PlantsVersusZombies2__ZombieSkillUtils__
#define __PlantsVersusZombies2__ZombieSkillUtils__

#include "Precompile.h"
#include "ZombieEnums.h"

struct ZombieSummonPoolItem
{
	ZombieSummonPoolItem() :
		m_zombieWeight(100),
		m_summonRange(0, 0, 9, 5),
		m_zombieTypeName("")
	{

	}

	int					m_zombieWeight;
	Sexy::Rect 			m_summonRange;
	std::string			m_zombieTypeName;
};

struct CZombieSummonDataPool
{
	CZombieSummonDataPool() :
		m_summonType(ZOMBIE_SUMMON_NONE),
		m_summonNumMin(0),
		m_summonNumMax(0)
	{

	}

	ZombieSummonType 		m_summonType;
	int     				m_summonNumMin;
	int     				m_summonNumMax;
	std::vector<ZombieSummonPoolItem> m_zombieSummonPool;
};

struct ZombieSkillData
{
	ZombieSkillData()
	{
        m_skillCD     = 15.0f;
        m_skillWeight = 300;

        m_skillType   = ZOMBIE_SKILL_NONE;
	}

    pvztime_t               m_skillCD;
    int 					m_skillWeight;

    ZombieSkillType         m_skillType;
};

struct ZombieSkill
{
public:
    ZombieSkill();
	ZombieSkill(const ZombieSkillData& i_data);
    
    void ResetSkillTime();
    void UpdateSkillTime();
    
    ZombieSkillType GetSkillType()   const;
    bool            GetSkillReady()  const;
    int             GetSkillWeight() const;
    
    
    ZombieSkillData         m_data;
    pvztime_t               m_skillCDEndTime;
    bool                    m_skillReady;
};

class ZombieSkillUtils
{
public:

	static void SummonZombies(const CZombieSummonDataPool& i_zombieSummonDataPool, class Zombie* i_zombie);
	static void LoadSummonZombiesResources(const CZombieSummonDataPool& i_zombieSummonDataPool);
	static void UnloadSummonZombiesResources(const CZombieSummonDataPool& i_zombieSummonDataPool);
};



#endif /* defined(__PlantsVersusZombies2__ZombieSkillUtils__) */

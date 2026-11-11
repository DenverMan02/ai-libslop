//
//  Zombie_Camel_Subsystem.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_CAMEL_SUBSYSTEM_H__
#define __ZOMBIE_CAMEL_SUBSYSTEM_H__

#include "ZombieCamel.h"
#include "GameSubSystem.h"
#include "GameEventMgr.h"



class ZombieCamel;

typedef RtWeakPtr<ZombieCamel> ZombieCamelPtr;

class ZombieCamelCollection
{
public:
	ZombieCamelCollection()
	{
		m_newSegmentSignHealth = 0;
		m_spawnNewHumps = false;
	}
	
	ZombieCamelCollection(ZombieTypePtr i_type)
	{
		m_newSegmentSignHealth = 0;
		m_spawnNewHumps = false;
		m_camelType = i_type;
	}
	
	bool ContainsZombie(RtWeakPtr<ZombieCamel> i_testZombie)
	{
		return (GetIndexForZombie(i_testZombie) != -1);
	}
	
	int GetSize()
	{
		return static_cast<int>(m_segments.size());
	}
	
	ZombieCamelPtr GetHeadZombie()
	{
		if (m_segments.size() == 0)
			return ZombieCamelPtr();
		return m_segments[0];
	}
	ZombieCamelPtr GetPreviousZombie(ZombieCamelPtr i_testZombie)
	{
		int zombieIndex = GetIndexForZombie(i_testZombie);
		if (zombieIndex == -1)
			return ZombieCamelPtr();
		if (zombieIndex == 0)
			return ZombieCamelPtr();
		return m_segments[zombieIndex - 1];
	}
	ZombieCamelPtr GetNextZombie(ZombieCamelPtr i_testZombie)
	{
		int zombieIndex = GetIndexForZombie(i_testZombie);
		if (zombieIndex == -1)
			return ZombieCamelPtr();
		if (zombieIndex == m_segments.size() - 1)
			return ZombieCamelPtr();
		return m_segments[zombieIndex + 1];
	}
	ZombieCamelPtr GetTailZombie(ZombieCamelPtr i_testZombie)
	{
		if (m_segments.size() == 0)
			return ZombieCamelPtr();
		return m_segments.back();
	}
	
	void AddZombie(ZombieCamelPtr i_addZombie)
	{
		DBG_ASSERT_MSG(!ContainsZombie(i_addZombie), "Adding a Camel Segment to a Camel that already contains it!");
		m_segments.push_back(i_addZombie);
	}
	
	bool RemoveAndSplit(ZombieCamelPtr i_removeZombie, ZombieCamelCollection& o_newCollection)
	{
		int splitIndex = GetIndexForZombie(i_removeZombie);
		if (splitIndex == -1)
		{
			return false;
		}
		
		// If we break anywhere other than the tail...
		bool valid = false;
		if (splitIndex < (int) m_segments.size() - 1)
		{
			// Create a new ZombieCamelCollection for the remainder
			valid = true;
			for (int i = splitIndex + 1; i < (int) m_segments.size(); ++i)
			{
				o_newCollection.AddZombie(m_segments[i]);
			}
		}
		
		// Finally, remove all entries in our list including and beyond the split index
		m_segments.erase(m_segments.begin() + splitIndex, m_segments.end());
		
		return valid;
	}
	
	bool RemoveZombie(ZombieCamelPtr i_removeZombie)
	{
		int zombieIndex = GetIndexForZombie(i_removeZombie);
		if (zombieIndex == -1)
		{
			return false;
		}
		m_segments.erase(m_segments.begin() + zombieIndex);
		return true;
	}
	
	void SetNewSegmentSignHealth(int i_newHealth)
	{
		m_newSegmentSignHealth = i_newHealth;
	}
	int GetNewSegmentSignHealth()
	{
		return m_newSegmentSignHealth;
	}
	
	void SetShouldSpawnHumps(bool i_spawn)
	{
		m_spawnNewHumps = i_spawn;
	}
	bool GetShouldSpawnHumps()
	{
		return m_spawnNewHumps;
	}
	
	ZombieTypePtr GetCamelType()
	{
		return m_camelType;
	}
	
	int GetIndexForZombie(ZombieCamelPtr i_testZombie)
	{
		for (int i = 0; i < (int) m_segments.size(); ++i)
		{
			if (m_segments[i] == i_testZombie)
				return i;
		}
		return -1;
	}
	
	// This is a list of all of our component segments.
	// This list should always remain ordered, with the head zombie first and the tail zombie last
	std::vector<ZombieCamelPtr> m_segments;
	
	// This is the sign health that should be propagated to new Zombies joining our Camel
	int m_newSegmentSignHealth;
	
	// Whether additional humps should be spawned from this camel
	bool m_spawnNewHumps;
	
	// The ZombieType of our Camel
	ZombieTypePtr m_camelType;
};

class ZombieCamelSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombieCamelSubSystem, GameSubSystem, RtClass);
	
	virtual void Update() override;

	virtual void OnZombieRemoved(Zombie* i_zombie);
	
	void OnCamelSegmentCreated(RtWeakPtr<ZombieCamel> i_headZombie, RtWeakPtr<ZombieCamel> i_segmentZombie);
	
	RtWeakPtr<ZombieCamel> GetHeadZombie(RtWeakPtr<ZombieCamel> i_camelZombie);
	RtWeakPtr<ZombieCamel> GetPreviousZombie(RtWeakPtr<ZombieCamel> i_camelZombie);
	RtWeakPtr<ZombieCamel> GetNextZombie(RtWeakPtr<ZombieCamel> i_camelZombie);
	RtWeakPtr<ZombieCamel> GetTailZombie(RtWeakPtr<ZombieCamel> i_camelZombie);
	ZombieCamelCollection* GetZombieCollectoin(RtWeakPtr<ZombieCamel> i_camelZombie) { return GetCamelForZombie(i_camelZombie); }
	
	int GetNewSegmentSignHealth(RtWeakPtr<ZombieCamel> i_camelZombie);
	bool GetAnimationOffset(RtWeakPtr<ZombieCamel> i_camelZombie, int i_walkCycleOffset, int& o_frameOverride);
	void NotifyZombieLeftCamel(RtWeakPtr<ZombieCamel> i_camelZombie);
	std::vector<ZombieCamelCollection>& GetCamels() { return m_camels; }
	
protected:
	virtual void registerForEvents() override;
	
private:
	
	ZombieCamelCollection* GetCamelForZombie(RtWeakPtr<ZombieCamel> i_testZombie)
	{
		for (int i = 0; i < (int) m_camels.size(); ++i)
		{
			ZombieCamelCollection& currCollection = m_camels[i];
			
			if (currCollection.ContainsZombie(i_testZombie))
			{
				return &currCollection;
			}
		}
		return NULL;
	}
	
	std::vector<ZombieCamelCollection> m_camels;
};



#endif // __ZOMBIE_CAMEL_SUBSYSTEM_H__

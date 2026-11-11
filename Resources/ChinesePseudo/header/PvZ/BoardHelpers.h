//
//  BoardHelpers.h
//  PlantsVersusZombies2
//
//  Reduces includes in Board.h
//
//  Created by Emery, Jason on 7/12/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef __BOARD_HELPERS_H__
#define __BOARD_HELPERS_H__

#include "Board.h"
//#include "FamilyResistanceSubSystem.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "OutroModule.h"
#include "RiftUtils.h"

class SunDropperProperties;

namespace BoardHelpers
{
	template<typename T>
	T* GetLevelModuleByClass()
	{
        return gLawnApp->m_board->GetLevelModuleManager() ? gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<T>() : NULL;
	}

	template<typename T>
	T* GetOutroModule()
	{
		OutroModule* outro = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<OutroModule>();
		if (outro)
		{
			return outro->Cast<T>();
		}
		return NULL;
	}

	template<class T> bool HasGameModuleInLevelDefinition()
	{
		if (gLawnApp->m_board == nullptr)
		{
			return false;
		}

        if(gLawnApp->m_board->GetLevelDefinition() == nullptr)
        {
            return false;
        }
		
		return gLawnApp->m_board->GetLevelDefinition()->HasLevelModule<T>();
	}
	
	template<class T> T* GetGameModuleInLevelDefinition()
	{
		if (gLawnApp->m_board == nullptr)
		{
			return nullptr;
		}

        if(gLawnApp->m_board->GetLevelDefinition() == nullptr)
        {
            return nullptr;
        }
		
		return gLawnApp->m_board->GetLevelDefinition()->GetLevelModule<T>();
	}

    RtWeakPtr<GameObject> LoadPopanimEffect(const std::string& i_name, int i_renderLayer, const std::string& i_initialAnimation = "idle");
    
    template<typename T> T* GetPerkByClass()
    {
        for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PERKS); (iter); ++(iter))
        {
            RtWeakPtr<RtObject> object = *iter;
            if (object.Get()->IsA(T::StaticGetClass()))
            {
                return object->Cast<T>();
            }
        }

        return nullptr;
    }

    template<typename T> T* GetPerkByClassInRift()
	{
    	if(!RiftUtils::IsPlayingRiftLevel())
    	{
    		return nullptr;
    	}

		for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PERKS); (iter); ++(iter))
		{
			RtWeakPtr<RtObject> object = *iter;
			if (object.Get()->IsA(T::StaticGetClass()))
			{
				return object->Cast<T>();
			}
		}

		return nullptr;
	}
	
    bool HasExtraChallenges();
	bool IsOptionalChallenge(Challenge* i_challenge);
	bool IsLastStandLevel();
    
    // Misc Utils

	template<typename T>
	std::vector<T> PickRandom(MTRand& i_rand, const std::vector<T>& i_source, size_t i_maxPicks);

    // Level Status
    
    float GetLevelProgressPct();
    int GetCumulativeZombieHealthInWave(int i_waveIndex);
    //std::map<std::string, std::vector<PlantFamilyResistance> > GetFamilyResistances();
    
	// Level Override Values
    bool CanProduceSun();
    int GetLevelBasedZombieTypeIndexByType(ZombieTypePtr i_zombieType);
    void ApplyLevelOverride_RiftTimedSunBlackList(std::vector<std::string>& i_list);
    int ApplyLevelOverride_SunDrop(int i_originalValue, bool i_dropByZombie);
    std::string ApplyLevelOverride_SunDropType(std::string i_originalValue);
    std::string ApplyLevelOverride_SunDropSmallType(std::string i_originalValue);
    std::string ApplyLevelOverride_SunDropTinyType(std::string i_originalValue);

    int ApplyLevelOverride_RiftTimedToolSize();
    void ApplyLevelOverride_RiftTimedToolList(std::vector<std::string>& i_list);

    int ApplyLevelOverride_PlantfoodStart(int i_originalValue);
    float ApplyLevelOverride_PlantCooldownTime(float i_originalValue, PlantTypePtr plantType);
    int ApplyLevelOverride_SeedSlotCount(int i_originalValue);
    std::string ApplyLevelOverride_PowerupSet(std::string& i_originalValue);
    int ApplyLevelOverride_MaxSun(int i_originalValue);
    MowerSpawnOverride GetLevelOverride_MowerSpawn();
    int ApplyLevelOverride_ZombieCountdownFirstWaveSecs(int i_originalValue);
    int ApplyLevelOverride_ZombieBaseLevel(int i_originalValue);
    int ApplyLevelOverride_ZombieGeneralBaseLevel(int i_originalValue);
    SunDropperProperties* ApplyLevelOverride_SunDropperProperties(SunDropperProperties* i_levelModuleProps);
    int ApplyLevelModifier_StartingSun(int i_originalValue);
    ZombieTypePtr ApplyLevelOverride_ZombieSpawnType(ZombieTypePtr i_zombieType);
    int ApplyLevelOverride_ZombossRiftStages(int i_originalValue);
    
    float ApplyLevelBasedModifierValue(float i_originalValue, int i_type, int i_subType = -1, int i_index = 0);
    void ApplyLevelBasedModifierZombieConditions(std::vector<ZombieConditions>& i_conditions);
}

template<typename T>
std::vector<T> BoardHelpers::PickRandom(MTRand& i_rand, const std::vector<T>& i_source, size_t i_maxPicks)
{
    // If size is less than expected pick count, return all of source
    if (i_source.size() <= i_maxPicks)
    {
        return i_source;
    }
    
    std::vector<T> selected;
    // Make a scratch copy of source
    std::vector<T> scratch = i_source;
    size_t effectiveCount = scratch.size();
    // Until we've picked i_maxPicks values...
    while (selected.size() < i_maxPicks)
    {
        // Pick a new one, copy it to the selected list
        int idx = i_rand.Next((int)effectiveCount);
        selected.push_back(scratch[idx]);
        // Swap the picked value with the last valid one in scratch,
        // and pretend scratch is now one element shorter
        effectiveCount--;
        std::swap(scratch[idx], scratch[effectiveCount]);
    }
    
    return selected;
}
#endif

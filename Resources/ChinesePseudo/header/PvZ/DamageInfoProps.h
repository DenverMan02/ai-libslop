#ifndef __DAMAGE_INFO_PROPS_H__
#define __DAMAGE_INFO_PROPS_H__

#include <string>
#include <vector>

#include "Core.h"
#include "DamageInfo.h"
#include "ZombieEnums.h"
#include "PlantEnums.h"
#include "Utils.h"
#include "PropertySheetBase.h"

class Plant;

struct StarLevelConditionEntry
{
    StarLevelConditionEntry()
    {
        Condition = ZCONDITION_Invalid;
        Duration = 0;
        chance = 0;
    }
    
    ZombieConditions Condition;
    float Duration;
    float chance;
    std::vector<std::string> BlackList;
};

struct ZombieConditionEntry
{
	ZombieConditionEntry()
	{
		Condition = ZCONDITION_Invalid;
	}
	
	ZombieConditions Condition;
	ValueRange Duration;
};

class ZombieConditionProps
{
public:
	ZombieConditionProps(const std::vector<ZombieConditionEntry>& zombieConditions)
	:m_zombieConditions(zombieConditions)
	{}
	
	void ApplyZombieConditionsTo(DamageInfo& damageInfo);

private:
	const std::vector<ZombieConditionEntry>& m_zombieConditions;
};

struct PlantConditionEntry
{
	PlantConditionEntry()
	{
		Condition = PCONDITION_Invalid;
	}
	
	PlantConditions Condition;
	ValueRange Duration;
};

class PlantConditionProps
{
public:
	PlantConditionProps(const std::vector<PlantConditionEntry>& plantConditions)
	:m_plantConditions(plantConditions)
	{}
	
	void ApplyPlantConditionsTo(Plant& plant);
	
private:
	const std::vector<PlantConditionEntry>& m_plantConditions;
};

class DamageFlagProps
{
public:
	DamageFlagProps(std::vector<DamageTypeFlags>& jsonDamageFlags)
	:m_damageFlagIndexes(jsonDamageFlags)
	{}
	
	void ApplyDamageFlagsTo(DamageInfo& damageInfo);
	
private:
	std::vector<DamageTypeFlags>& m_damageFlagIndexes;
};

class BoardEntity;
class DamageInfoProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(DamageInfoProps, PropertySheetBase, RtClass);
	
	DamageInfoProps()
	:BaseDamage(0.0f) {}
	
	DamageInfo BuildDamageInfo();
	DamageInfo BuildDamageInfo(RtWeakPtr<BoardEntity> entity);
    void SetBaseDamage(float damage);
    float GetBaseDamage() const;
private:
	float BaseDamage;
	std::vector<ZombieConditionEntry> Conditions;
	std::vector<DamageTypeFlags> DamageFlags;
};
#endif // __DAMAGE_INFO_PROPS_H__

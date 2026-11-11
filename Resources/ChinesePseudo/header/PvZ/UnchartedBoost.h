/*
 * UnchartedBoost.h
 *
 *  Created on: 2024-1-5
 *      Author: admin
 */

#ifndef UNCHARTEDBOOST_H_
#define UNCHARTEDBOOST_H_

#include "PropertySheetBase.h"
#include "RtObject.h"
#include "LevelModule.h"

typedef RtWeakPtr<class UnchartedBoostPropertySheet> UnchartedBoostPropertiesPtr;

//Do not delete or reorder these.  You will break live saved player datas
enum UnchartedBoostType
{
	U_Boost_None,
	U_Boost_Sun_Reduced,
	U_Boost_Plant_CD_Reduced,
	U_Boost_HP,
	U_Boost_ATK_Speed,
	U_Boost_Damage,
	U_Boost_Sun_Add,
	U_Boost_Hero_Plant_Material,
	U_Boost_Bonus_Damage,
	U_Boost_Die_Explode,
	U_Boost_Global_Damage,
	U_Boost_Die_Reset_CD,
	U_Boost_Damage_By_Sun,
	U_Boost_Plantfood_ATK_Speed,
	U_Boost_Damage_Multiplier,
	U_Boost_Take_Damage_Plantfood,
	U_Boost_Multiplier_Sun,
	U_Boost_Hero_Plant,
	U_Boost_Hero_Plant_Execute,
	U_Boost_Hero_Plant_Energy,
	U_Boost_Hero_Plant_Kill_Explode
};

enum ValidBoostType
{
	ValidBoostType_InstantKill,
	ValidBoostType_Physical,
	ValidBoostType_Poison,
	ValidBoostType_Lightning,
	ValidBoostType_Magic,
	ValidBoostType_Frost,
	ValidBoostType_Flame,
	ValidBoostType_All
};

class UnchartedBoostPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(UnchartedBoostPropertySheet, PropertySheetBase, RtClass);

	UnchartedBoostPropertySheet()
	: TypeName("")
	, Description("")
	, Name("")
	, Type(U_Boost_None)
	, ValidType(ValidBoostType_All)
	, UseCount(-1)
	{

	}

	std::string TypeName;

	std::string Description;
	std::string Name;

	SexyString GetDescription();
	SexyString GetName();

	std::vector<float> Values;
	UnchartedBoostType Type;
	ValidBoostType ValidType;
	int UseCount;
};

struct BoostValue
{
	BoostValue()
	: ValidType(ValidBoostType_All)
	, Type(U_Boost_None)
	, UseCount(-1)
	{

	}

	BoostValue(UnchartedBoostType i_type, ValidBoostType i_BoostType, const std::vector<float>& i_values, int i_useCount)
	: Type(i_type)
	, ValidType(i_BoostType)
	, Values(i_values)
	, UseCount(i_useCount)
	{

	}

	ValidBoostType ValidType;
	std::vector<float> Values;
	UnchartedBoostType Type;
	int UseCount;
};

class UnchartedBoostModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(UnchartedBoostModule, LevelModule, RtClass);

    UnchartedBoostModule();
    ~UnchartedBoostModule();

    void registerForEvents() override;

private:
    void onLoadComplete();
    void onGameplayStarted();
    void onPlantFoodEnd(class Plant* i_plant);
    void onPlantAdded(class Plant* i_plant);
    void onSunCurrencyChanged(int32 i_upcomingAmount);
	void onZombieDied(class Zombie* zombie, const class DamageInfo* i_deathBlow);
};

class UnchartedBoostModuleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(UnchartedBoostModuleProperties, LevelModuleProperties, RtClass);

    RtClass* GetModuleClass() const override
    {
        return UnchartedBoostModule::StaticGetClass();
    }

	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

typedef RtWeakPtr<const UnchartedBoostModuleProperties> UnchartedBoostModulePropertiesPtr;

class UnchartedBoostMgr : public LazySingleton<UnchartedBoostMgr>
{
public:
	UnchartedBoostMgr();
	virtual ~UnchartedBoostMgr();

	// Sync from network
	void Sync(const std::vector<int>& i_ids);
	float GetBoostValue(const class PlantType* i_plantType, UnchartedBoostType i_type, int i_index);

	UnchartedBoostPropertiesPtr GetUnchartedBoostPropertiesById(int i_id);
	UnchartedBoostType GetUnchartedBoostType(int i_id);
	void GetUnchartedBoostValues(int i_id, std::vector<float>& i_values);
	float GetBoostValueBySlot(UnchartedBoostType i_type, int i_slot, int i_index);
	ValidBoostType GetUnchartedBoostValidBoostType(int i_id);
	bool HasAnyValidBoostType(UnchartedBoostType i_type, const PlantType* i_plantType);
	// Values and type
	void GetUnchartedBoostInfo(int i_id, BoostValue& i_value);

	std::string GetUnchartedBoostName(int i_id);
	std::string GetUnchartedBoostDescription(int i_id);

	bool IsValidLevel();
	ImagePtr GetBoostImage(int i_id);


private:
	bool isValidBoostType(const class PlantType* i_plantType, ValidBoostType i_boostType);
	int getValidTypeCount(ValidBoostType i_validType);
	float getSpecialBoostValue(const std::vector<float>& i_values, ValidBoostType i_validType, UnchartedBoostType i_type, int i_index);
	bool isSpecialBoostValue(UnchartedBoostType i_type);

	std::vector<BoostValue> m_values;
};

#define GetUBoostValue(p_type, type, index) UnchartedBoostMgr::GetInstancePtr()->GetBoostValue(p_type, type, index)
#define GetUBoostValueSlot(type, slot, index) UnchartedBoostMgr::GetInstancePtr()->GetBoostValueBySlot(type, slot, index)
#define GetUBoostImage(id) UnchartedBoostMgr::GetInstancePtr()->GetBoostImage(id)
#define IsHeroPlantUnlocked() (GetUBoostValue(NULL, U_Boost_Hero_Plant, 0) > 0.0f)
#define IsHeroPlantSkillImproved(index) (GetUBoostValue(NULL, UnchartedBoostType(index + U_Boost_Hero_Plant_Execute), 0) > 0.0f)

#endif /* UNCHARTEDBOOST_H_ */

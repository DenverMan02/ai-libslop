//
//  CrazyOlafTest.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/7/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CrazyIvanTest_h
#define PlantsVersusZombies2_CrazyIvanTest_h

#include "Core.h"
#include "LevelModule.h"
#include "PVZTypes.h"
#include "DamageInfo.h"
#include "PlantEnums.h"

class CrazyOlafTest : public LevelModule
{
	RT_CLASS_DEFINE(CrazyOlafTest, LevelModule, RtClass);

protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;

	void onUpdate();

private:
	void pickAndPerformAction();

	void loadPlantType(PlantTypePtr);
	void unloadPlantType(PlantTypePtr);

	PlantTypePtr popFreeQueue();
	void pushFreeQueue(PlantTypePtr);

	std::vector<Point> destroyAllPlantsOfType(PlantTypePtr);
	void plantAt(const std::vector<Point>& i_squares, PlantTypePtr i_type);
	void plantAt(const Point& i_square, PlantTypePtr i_type);

	int getPlantedCount(PlantTypePtr i_type);
	PlantTypePtr pickValidPlantType();
	Point pickRandomGridSquare(PlantTypePtr i_canPlantAt = PlantTypePtr());
	class Plant* pickRandomPlant(PlantTypePtr i_type = PlantTypePtr());
	PlantGroupPtr pickRandomPlantGroup();

	void onPlantDied(class Plant* i_plant)
	{	m_deadPlantCount++; }
	void onZombieAddedToBoard(class Zombie* i_zombie)
	{	m_zombieCount++; }
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow)
	{	m_deadZombieCount++; }

	void refreshDisplayText();

private:
	pvztime_t m_actionTimer;

	std::vector<PlantTypePtr> m_freePlantTypes;
	std::vector<PlantTypePtr> m_loadedPlantTypes;

	int m_plantCount;
	RtWeakPtr<class Effect_FloatingText> m_textPlantCount;
	int m_zombieCount;
	RtWeakPtr<class Effect_FloatingText> m_textZombieCount;
	int m_deadPlantCount;
	RtWeakPtr<class Effect_FloatingText> m_textKilledPlants;
	int m_deadZombieCount;
	RtWeakPtr<class Effect_FloatingText> m_textKilledZombies;
};

class CrazyOlafTestProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CrazyOlafTestProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return CrazyOlafTest::StaticGetClass();
	}

	enum TestActionsCrazyOlafStyle
	{
		TACOS_Shovel,
		TACOS_PlantSingle,
		TACOS_PlantColumn,
		TACOS_PlantfoodSingle
	};

	struct ActionWeights
	{
		TestActionsCrazyOlafStyle 	Action;
		int32 						Weight;
	};

	CrazyOlafTestProperties()
	: ActionTimer(1.f)
	, MaxPlantTypes(8)
	, MaxPerType(15)
	, PlantBeforeColumn(0)
	{}

	std::vector<std::string> PlantWhitelist;
	std::vector<std::string> PlantBlacklist;

	std::vector<ActionWeights> Actions;

	float ActionTimer;

	int PlantBeforeColumn;
	int MaxPlantTypes;
	int MaxPerType;
};

typedef CrazyOlafTestProperties::TestActionsCrazyOlafStyle TACOS;

#endif

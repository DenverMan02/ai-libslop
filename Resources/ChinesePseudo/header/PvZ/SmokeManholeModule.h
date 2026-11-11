#ifndef SMOKE_MANHOLE_MODULE_H
#define SMOKE_MANHOLE_MODULE_H

#include "LevelModule.h"
#include "MTRand.h"
#include "Precompile.h"
#include <vector>
#include "SmokeManhole.h"

class GridItemSmokeManhole;
class PlantFlattenedshroom;
class PlantLotusshooter;

namespace Message
{
	void BlockSmokeManhole(PlantFlattenedshroom* mushroom);
	void UnblockSmokeManhole(PlantFlattenedshroom* mushroom);
	void AbsorbSmoke(PlantLotusshooter* lotusshooter);
	void SmokeDiffusion(class GridItemSmokeManhole* smokeManhole);
}

class SmokeManholeModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(SmokeManholeModule, LevelModule, RtClass);

	SmokeManholeModule();

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	virtual void initializeModule();

	void onBlockSmokeManhole(PlantFlattenedshroom* mushroom);
	void onUnblockSmokeManhole(PlantFlattenedshroom* mushroom);
	void onHurrikaleBlow(int row);
	void onBloverBlow();
	void onAbsorbSmoke(PlantLotusshooter* lotusshooter);
	void onPlantDie(Plant* plant);

	void onGameStart();
	void onLoadComplete();

	void CheckGridPlants(int i_gridX, int i_gridY);

protected:
	std::vector<GridItemSmokeManhole*> m_smokeManholeList;
};

class SmokePollutionModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SmokePollutionModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return SmokeManholeModule::StaticGetClass();
	}

    struct SmokeManholeInfo
    {
        int GridColumn;
        int GridRow;
        float StartTime;
    };

    std::string GridItem;
    std::vector<SmokeManholeInfo> SmokeManholeList;
    float Damage = 0.0f;
};

#endif

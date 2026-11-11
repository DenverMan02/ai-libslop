#ifndef PIPLELINE_MODULE_H
#define PIPLELINE_MODULE_H

#include "LevelModule.h"
#include "MTRand.h"
#include "Precompile.h"
#include <vector>

class PlantFlattenedshroom;
class ManholePipeline;
class Plant;

namespace Message
{
	void BlockPipleline(PlantFlattenedshroom* mushroom);
	void UnblockPipleline(PlantFlattenedshroom* mushroom);
}

class ManholePipelineModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(ManholePipelineModule, LevelModule, RtClass);

	virtual ~ManholePipelineModule();

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	virtual void initializeModule();

	void onBlockPipleline(PlantFlattenedshroom* mushroom);
	void onUnblockPipleline(PlantFlattenedshroom* mushroom);
	void onPlantDie(Plant* plant);
	void onZombieDestroyed(class Zombie* i_zombie);

	void onGamePlayUpdate();
	void onLoadComplete();

	bool CanPlantFlatMushroom(PlantFlattenedshroom* mushroom);
	void CheckGridPlants(int i_gridX, int i_gridY);
	void onGameStart();

protected:
	std::vector<ManholePipeline*> m_piplelineList;
};

class ManholePipelineModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ManholePipelineModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ManholePipelineModule::StaticGetClass();
	}

    struct ManholePipelineInfo
    {
        int StartX;
        int StartY;
        int EndX;
        int EndY;
    };

    float OperationTimePerGrid;
    std::vector<ManholePipelineInfo> PipelineList;
    float DamagePerSecond;
};

#endif

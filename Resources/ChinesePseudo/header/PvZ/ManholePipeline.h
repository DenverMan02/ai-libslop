#ifndef GRIDITME_PIPLELINE_H
#define GRIDITME_PIPLELINE_H

#include "Precompile.h"
#include "GridItemAnimation.h"
#include "Zombie.h"

namespace Message
{
	void NotifyEnterManhole();
}

enum ManholePipelineState
{
    PVZ_BEGIN_ENUM(MANHOLE_PIPELINE_),
    	MANHOLE_PIPELINE_READY,
    	MANHOLE_PIPELINE_WORK,
    	MANHOLE_PIPELINE_BLOCK,
    PVZ_END_ENUM(MANHOLE_PIPELINE_)
};

class PlantFlattenedshroom;

class GridItemManholePipeline: public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemManholePipeline, GridItem, RtClass);

	int CalcRenderOrder() const override;

	void SetupPipelineImage();

	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
	void onDraw(class Graphics* i_g) override;

	ImagePtr	  m_PipelineImageFront;
	ImagePtr	  m_PipelineImageBack;
};

class ManholePipelineProps : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(ManholePipelineProps, GridItemPropertySheet, RtClass);

	std::string ImageRes;
	SexyVector2 ArtCenter;
};

class ManholePipeline
{
public:
	ManholePipeline();
	virtual ~ManholePipeline();

	void SetupPipelineImage();

	void InitPipleline(int startX, int startY, int EndX, int EndY, float operationTimePerGrid, float riseTime, float stuckTime);
	void AddZombieToPipleline(ZombiePtr zombie);
	bool RemoveZombieToPipleline(ZombiePtr zombie);
	void BlockPipeline(PlantFlattenedshroom* mushroom);
	void UnBlockPipeline(PlantFlattenedshroom* mushroom);

	bool CanPlantFlatMushroom(PlantFlattenedshroom* mushroom);

	void onUpdate(float damage);

	void onZombieDie(Zombie* i_zombie);

protected:
	ManholePipelineState m_state;
	float m_operationTime;
	float m_stuckTime;
	float m_riseTime;

	GridItemManholePipeline* m_piplelineStart;
	GridItemManholePipeline* m_piplelineEnd;
	std::vector<ZombiePtr> m_zombieQueue;

	std::vector<PlantFlattenedshroom*> m_mushroom;
};

#endif

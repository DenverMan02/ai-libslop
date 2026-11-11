//
//  GridItemProtectorShieldSegmentWaveGenerator.h
//  PlantsVersusZombies2
//	12-14-21
//
#ifndef _GridItemProtectorShieldSegmentWaveGenerator_H_
#define _GridItemProtectorShieldSegmentWaveGenerator_H_


class GridItemProtectorShieldSegmentWaveGenerator : public GridItemProtectorShieldSegment
{
public:

	RT_CLASS_DEFINE(GridItemProtectorShieldSegmentWaveGenerator, GridItemProtectorShieldSegment, RtClass);

	bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }
	bool IsDamageable() const override { return false; }
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override  { return false; }

	void RecordPreMotion(const Sexy::SexyVector3 &i_position) override;
	void onSetPosition(const Sexy::SexyVector3 &i_newPosition) override;

	void onUpdate() override;

	void CheckGridPlants(int i_gridX, int i_gridY);

	virtual void TakeDamage(const DamageInfo& i_damage) override {}

protected:
	void onDestroy() override;

private:
	void flickPlant(class Plant* i_plant);
	void checkEdge();
	void checkPlants();
	void checkDistancedPlants();
	bool canCheckPlants();
	bool isPlantAlreadyPushed(PlantPtr i_plant = nullptr);
	bool OnCollideEntity(BoardEntity* i_entity);
	bool IsValidTarget(PlantPtr i_plant) const;

	SexyVector3 m_prePosition;
	std::vector<RtWeakPtr<class Plant>> m_pushedPlant;
};

#endif
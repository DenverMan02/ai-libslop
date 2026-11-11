/*
 * GridItemRenaiTile.h
 *
 *  Created on: 2019-7-30
 *      Author: Administrator
 */

#ifndef GRIDITEMRENAITILE_H_
#define GRIDITEMRENAITILE_H_

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

namespace Message
{
    void NotifyRenaiTileState(bool i_pushed);
}

enum RenaiTileDirection
{
	PVZ_BEGIN_ENUM(TILE_DIRECTION_),
	TILE_DIRECTION_LEFT,
	TILE_DIRECTION_RIGHT,
	PVZ_END_ENUM(TILE_DIRECTION_)
};

enum RenaiTileState
{
	PVZ_BEGIN_ENUM(TILESTATE_),
	TILESTATE_PREPARE,
	TILESTATE_IDLE,
	TILESTATE_PUSHING,
	TILESTATE_PULLING,
	TILESTATE_PUSHED,
	PVZ_END_ENUM(TILESTATE_)
};

class GridItemRenaiTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemRenaiTile, GridItemAnimation, RtClass);

	GridItemRenaiTile();

	int CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	bool IsOccupied();
	bool IsLeftTile();
	void setState(RenaiTileState i_state);
	void SetBindingEntity(PlantPtr i_entity) { m_bindingEntity = i_entity;}
	void registerForEvents() override;
	void SetStopFindingTargets(bool i_stop) { m_stopFindingTargets = i_stop; }

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	bool findTargets();
	void onAnimDone(const std::string &i_animLabel);

private:
	RenaiTileDirection getRenaiTileDirection() const;
	void updateState();
	void onNotifyPlantfoodRelease(Plant* i_entity);
	bool ContainPushableEntity(BoardEntity* i_entity);

	RenaiTileState m_state;
	pvztime_t m_lastPushedTime;
	PlantPtr m_bindingEntity;
	bool m_stopFindingTargets;
};


class GridItemRenaiTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemRenaiTileProps, GridItemAnimationProps, RtClass);

	GridItemRenaiTileProps()
	{
		Direction = TILE_DIRECTION_Invalid;
		CheckTime = 1.0f;
	}

	RenaiTileDirection Direction;
	Sexy::Rect TargetRect;
	float CheckTime;
};

class GridItemRenaiTileAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemRenaiTileAnimRig, PopAnimRig, RtClass);

	void PlayTileIdle();
	void PlayTilePushStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayTilePushed();
	void PlayTilePullStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};


#endif /* GRIDITEMRENAITILE_H_ */

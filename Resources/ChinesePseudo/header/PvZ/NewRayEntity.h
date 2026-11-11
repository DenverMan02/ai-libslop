/*
 * NewRayEntity.h
 *
 *  Created on: 2019-10-10
 *      Author: Administrator
 */

#ifndef NEWRAYENTITY_H_
#define NEWRAYENTITY_H_

#include <vector>

#include "BoardEntity.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TimeMgr.h"

namespace Sexy {
	class Graphics;
}  // namespace Sexy

struct RayEntityData
{
	RayEntityData()
	{
		PopAnimName = "";
		HitPopAnimName = "";
		HitAnimLabel = "idle";
		InitialAnimLayerName = "lightningreed_bolt_start";
		MainAnimLayerName = "lightningreed_bolt_middle";
		InitialBoltXOffset = 10.0f;
		MiddleBoltXOffset = 10.0f;
	}

	std::string PopAnimName;
	std::string HitPopAnimName;
	std::string HitAnimLabel;
	std::string InitialAnimLayerName;
	std::string MainAnimLayerName;

	float InitialBoltXOffset;
	float MiddleBoltXOffset;
};

class NewRayEntity : public BoardEntity
{
	RT_CLASS_DEFINE(NewRayEntity, BoardEntity, RtClass);

	NewRayEntity();

	void Initialize(const RayEntityData& i_rayData, const BoardEntityPtr i_owner, const float i_decayDelay);

	void InitiateWithTarget(const BoardEntityPtr i_target) { createPopAnimsToTarget(i_target); }

	int CalcRenderOrder() const override;
	bool ShouldDrawShadow() const override { return false; }

	void SetHitOffset(Point i_offset) { m_hitOffset = i_offset; }

	void SpawnHitEffect();

protected:
	void onInitialized() override {};
	void onDestroy() override;
	void onUpdate() override;
	void onDraw(Graphics* i_g) override;

	void updateTiles();

	virtual void createPopAnimsToTarget(const BoardEntityPtr i_target);

	const virtual std::string getPopAnimName() { return m_data.PopAnimName; }

	RayEntityData m_data;
	BoardEntityPtr m_owner;

	pvztime_t m_destroyTime;
	float m_decayDelay;
	SexyVector3 m_endPos;
	Point m_hitOffset;

private:

	void setRenderTransformForRig(PopAnimRig* i_rig, const float i_xOffset);

	std::vector<PopAnimRigPtr> m_tiledRigs;
};


#endif /* NEWRAYENTITY_H_ */

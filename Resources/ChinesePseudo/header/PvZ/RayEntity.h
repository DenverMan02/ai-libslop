//
//  RayEntity.h
//  PlantsVersusZombies2
//
//  Created by Kobylarek, Alexander on 8/17/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef RayEntity_h
#define RayEntity_h

#include <vector>

#include "BoardEntity.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TimeMgr.h"

namespace Sexy {
	class Graphics;
}  // namespace Sexy

class RayEntity : public BoardEntity
{
	RT_CLASS_DEFINE(RayEntity, BoardEntity, RtClass);
	
	RayEntity();
	
	void Initialize(const std::string& i_popAnimName, const std::string& i_hitPopAnimName, const std::string& i_hitAnimLabel, const BoardEntityPtr i_owner, const float i_decayDelay, bool i_single = false, bool i_hitSigle = true);
	
	void InitiateWithTarget(const BoardEntityPtr i_target) { createPopAnimsToTarget(i_target); }
	
	int CalcRenderOrder() const override;
	bool ShouldDrawShadow() const override { return false; }
	
	void SetHitOffset(Point i_offset) { m_hitOffset = i_offset; }
	void SetPlaySingle(bool i_single) { m_playSingle = i_single; }
	void SetTopLayer(bool i_topLayer) { m_topLayer = i_topLayer; }
	void SetHitPosition(bool i_setHitPos, const SexyVector3& i_pos) { m_setHitPos = i_setHitPos; m_endPos = i_pos; }

	void SetOffsetHeight(float i_offset) { m_offsetHeight = i_offset; }
	
protected:
	void onInitialized() override {};
	void onDestroy() override;
	void onUpdate() override;
	void onDraw(Graphics* i_g) override;
	
	void updateTiles();
	
	virtual void createPopAnimsToTarget(const BoardEntityPtr i_target);
	
	const virtual std::string getPopAnimName() { return m_popAnimName; }
	
	pvztime_t m_destroyTime;
	pvztime_t m_decayDelay;
	
	std::string m_popAnimName;
	std::string m_hitPopAnimName;
	
	std::string m_hitAnimLabel;
	
	BoardEntityPtr m_owner;
	SexyVector3 m_endPos;
	
	Point m_hitOffset;

	bool m_setHitPos;
private:
	void spawnHitEffect();
	void setRenderTransformForRig(PopAnimRig* i_rig, const float i_xOffset);
	void onAnimationDone(const std::string& i_animName);
	
	std::vector<PopAnimRigPtr> m_tiledRigs;
	bool m_playSingle;
	bool m_hitSingle;
	bool m_topLayer;
	float m_offsetHeight;
	RtWeakPtr<Effect_PopAnim> m_effect;
};

#endif /* RayEntity_hpp */

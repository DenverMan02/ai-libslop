/*
 * RichManSquash.h
 *
 *  Created on: 2019-12-24
 *      Author: Administrator
 */

#ifndef RICHMANSQUASH_H_
#define RICHMANSQUASH_H_

#include "Core.h"
#include "PVZTypes.h"
#include "AnimationMgr.h"
#include "RealObject.h"

namespace Message
{
    void NotifyMovingFinish(bool i_handleEvent);
}

typedef RtWeakPtr<class Effect_PopAnim> PopAnimPtr;

enum SquashState
{
	PVZ_BEGIN_ENUM(SQUASH_),
	SQUASH_IDLE,
	SQUASH_LOOKING_LEFT,
	SQUASH_LOOKING_RIGHT,
	SQUASH_JUMPING_LEFT,
	SQUASH_JUMPING_RIGHT,
	SQUASH_IN_AIR_LEFT,
	SQUASH_IN_AIR_RIGHT,
	SQUASH_LANDING_LEFT,
	SQUASH_LANDING_RIGHT,
	PVZ_END_ENUM(SQUASH_)
};

class RichManSquash : public RealObject
{
public:
    RT_CLASS_DEFINE(RichManSquash, RealObject, RtClass);

    RichManSquash();
    virtual ~RichManSquash();

    void            InitView();

    void            onDraw(Graphics* i_g) override;
    void            onUpdate();
    void            UpdateMotion();

    void initializeRenderEffect();
    void SetIsHidden(bool i_hidden);

    // state
	void setState(SquashState i_state);
	SquashState getState();

	void TryJump(const std::vector<SexyVector3>& i_positions);
	void SetTurnRightPoint(const SexyVector3& i_pos) { m_turnRightPt = i_pos; }
	void SetTurnLeftPoint(const SexyVector3& i_pos) { m_turnLeftPt = i_pos; }

	void SetPiecePosition(const SexyVector3& i_pos);
	void SetLeftIdle(bool i_left) { m_leftIdle = i_left; }

private:
    Effect_PopAnim* CreateSelfRenderEffect();
    void OnEffectDone(const std::string& label);
    bool IsInState(uint32 state) const { return m_state == state; }

    void PlayIdle();
    void JumpRight();
    void DealAir();
    void LandingRight();
    void Look(bool i_left);

    void JumpLeft();
    void DealAirLeft();
    void LandingLeft();

    void travelToJumpUpDestination();
    void travelToLandingDestination();

    void CheckTurnLeftOrRight();
    void DoJump();

    class Effect_PopAnim* m_renderEffect;
    SquashState m_state;
    pvztime_t m_stateEndTime;

    SexyVector3	m_startPos;
    SexyVector3	m_endPos;

    SexyVector3 m_turnRightPt;
    SexyVector3 m_turnLeftPt;

    std::vector<SexyVector3> m_positions;
    bool m_leftIdle;
};


#endif /* RICHMANSQUASH_H_ */

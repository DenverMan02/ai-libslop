//
//  Effect_PlayFrame.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.23
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Effect_PlayFrame__
#define __PlantsVersusZombies2__Effect_PlayFrame__

#include "StandaloneEffect.h"
#include "TimeLine.h"

class Effect_PopAnim;

class Effect_PlayFrame : public Effect_PopAnim
{
public:
	/*	if m_frameStart < 0 then begin with current frame;
		m_frameEnd must be equal or greater than 0;
	*/
	struct FrameRange
	{
		std::string m_animLabel;
		int	m_frameStart;		// if m_frameStart < 0 then begin with current frame;
		int	m_frameEnd;			// m_frameEnd must be equal or greater than 0;
		FrameRange() : m_frameStart(-1), m_frameEnd(-1) {}
		bool IsForward() const { return m_frameStart <= m_frameEnd; }
		bool IsValid() const { return m_frameEnd >= 0 && m_frameStart != m_frameEnd; }
	};
public:
	RT_CLASS_DEFINE(Effect_PlayFrame, Effect_PopAnim, RtClass);
	Effect_PlayFrame();	

	void				PlayFrame(const std::string& i_animLabel, int frameFrom, int frameTo);
	void				PlayFrames(std::vector<FrameRange>& frames);
	int				GetLabelFrameNum(const std::string& i_animLabel);
	void				SetFrameStopDelegate(PopAnimRig::AnimStoppedReflectionDelegate i_frameStopDelegate) { m_animPlayFrameStopped = i_frameStopDelegate; }
	void				SetPlayFrameSpeed(float val) { m_fSpeed = val; }

protected:
	PopAnim*	GetPAM();
	void				PreparePlay();
	void				UpdatePopAnim();
	void				UpdateSpriteInstMainFrame(float i_increment);
	void				UpdateSpriteInstSubFrame(PASpriteInst* i_spriteInst, float i_increment, bool bForward);

protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;

protected:
	std::vector<FrameRange>		m_vecFrames;
	PopAnimRig::AnimStoppedReflectionDelegate m_animPlayFrameStopped;
	bool												m_bFinished;
	float												m_fSpeed;
};

#endif /* defined(__PlantsVersusZombies2__Effect_PlayFrame__) */

/*
 * GridSquareMoonFlowerGlow.h
 *
 *  Created on: 2017-6-30
 *      Author: Administrator
 */

#ifndef GRIDSQUAREMOONFLOWERGLOW_H_
#define GRIDSQUAREMOONFLOWERGLOW_H_

#include <stdio.h>
#include "BoardEntity.h"
#include "Effect_PopAnim.h"

class MoonFlowerGlowAnimEffect : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(MoonFlowerGlowAnimEffect, Effect_PopAnim, RtClass);
	bool IsIntroFinished() { return m_introFinished; }

protected:
	void onInitialized() override;
	void onAnimStopped(const std::string& i_animLabel) override;
	bool m_introFinished;
};

class GridSquareMoonFlowerGlow : public BoardEntity
{
public:
	RT_CLASS_DEFINE(GridSquareMoonFlowerGlow, BoardEntity, RtClass);

	GridSquareMoonFlowerGlow() { m_glowEffect = RtWeakPtr<class MoonFlowerGlowAnimEffect>(); }

	void StartEffect(Point i_gridLocation);
	const char* getPamName();
	Point GetGridLocation() { return m_gridLocation; }
	void DoExit();

protected:
	void onDestroy() override;
	void addStartingAnimationSequence(Effect_PopAnim* popAnim);
	RtWeakPtr<class Effect_PopAnim> createSpawnAndLoopEffect(SexyVector3 i_vecPos);
	void createExitEffect(SexyVector3 i_vecPos);;

private:

	Point m_gridLocation;
	RtWeakPtr<class MoonFlowerGlowAnimEffect> m_glowEffect;
};


#endif /* GRIDSQUAREMOONFLOWERGLOW_H_ */

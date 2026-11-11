//
//  CollectableSun.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableSunBomb_h
#define PlantsVersusZombies2_CollectableSunBomb_h

#include "CollectableSun.h"
#include "RtDb.h"
#include "RtObject.h"

class StandaloneEffect;

/// Parameters

class CollectableSunBombType : public CollectableSunType
{
public:
	RT_CLASS_DEFINE(CollectableSunBombType, CollectableSunType, RtClass);
};

/// Implementation

class CollectableSunBomb : public CollectableSun
{
public:
	RT_CLASS_DEFINE(CollectableSunBomb, CollectableSun, RtClass);

    bool ShouldExplode() const;
	void ExplodeMe();
	~CollectableSunBomb();

protected:
	virtual void onCollectableInitialize() override;
	virtual void onFinishMotion() override;
	virtual void onUpdate() override;

private:
	void startSunBomb();
	void switchToNormalSun();
	void onAnimDone_Explode(StandaloneEffect* i_effect);
	void beamCreate();
	void beamUpdate();
	void beamDestroy();
	void onBeamAnimDone_Destroy(StandaloneEffect* i_effect);

	class AnimationSequence animationSequenceIdle();
	class AnimationSequence animationSequenceTransitionToNormal();
	class Effect_PopAnim* getAnim();

	RtWeakPtr<class Effect_PopAnim> m_beamEffect;
    bool m_isExploding;
};

#endif


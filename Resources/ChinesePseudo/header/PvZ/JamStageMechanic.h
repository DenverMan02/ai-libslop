//
//  JamDispensor.h
//  PlantsVersusZombies2
//
//  Created by Mina, Elliott on 7/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JamKeeper__
#define __PlantsVersusZombies2__JamKeeper__

#include <stdio.h>
#include "GameObject.h"
#include "GridItemJammable.h"
#include "ZombieEnums.h"

class Zombie;
class JamStageMechanic : public GameObject
{
public:
	RT_CLASS_DEFINE(JamStageMechanic, GameObject, RtClass);

    JamStageMechanic();
    virtual ~JamStageMechanic();
	
private:
	void registerForEvents() override;
	void unregisterForEvents() override;
	
	void onPostLoad() override;
	
	void onLoadComplete();
	void onWaveNotificationEvent(const std::vector<std::string>& i_events);
	void applyNewJam(const std::string& i_jam);
	void onZombieAddedToBoard(Zombie* i_zombie);
	void onJammableGridItemAddedToBoard(GridItemJammable *item);
	void onZombieHypnotized(Zombie* i_zombie);
	void doEffectTransition(const std::string& i_fromJam, const std::string& i_toJam) const;
	void onTransitionStopped(const std::string&);

	const std::string& getJamForEvents(const std::vector<std::string>& i_events) const;
	
	void onOverrideJamsWith(const std::string& i_owningJam);
	void applyOverridingJam(const std::string& i_jam);
	void onRestoreOriginalJam();

	std::string m_overridingJam;
	std::string m_lastJamPlayed;
	int m_numberOfJamOverrides;
	RtWeakPtr<class Effect_PopAnim> m_jamEffectsTop;
	RtWeakPtr<class Effect_PopAnim> m_jamEffectsBottom;
};

namespace Message
{
	void OverrideJamsWith(const std::string& i_owningJam);
	void RestoreOriginalJam();
}

#endif /* defined(__PlantsVersusZombies2__JamKeeper__) */

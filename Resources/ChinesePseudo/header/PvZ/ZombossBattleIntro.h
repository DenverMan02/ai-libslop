//
//  ZombossBattleIntro.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombossBattleIntro__
#define __PlantsVersusZombies2__ZombossBattleIntro__

#include "StandardLevelIntro.h"

class ZombossBattleIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(ZombossBattleIntro, StandardLevelIntro, RtClass);
	
	ZombossBattleIntro();
	
	void AddReadySetPlantToAnimMgr(AnimationMgr* i_animMgr, float& io_endTime, Delegate0 i_delgateNameToCall, bool i_finishAfterSet = false) override;
	void OnZombossIntroDone();
	
    void OnLuaNotify(const std::string& rLuaEvent);
    void PlayIntro(void);
protected:
	void initializeModule() override;
	void registerForEvents() override;
	void onLoadComplete() override;

private:
	void showZomboss();
	void startHealthMeterFill();
	void continueReadySetPlant();
	void onUpdate();
	
	/// Transient
	Delegate0 m_callOnReadySetPlantDone;
	pvztime_t m_startHealthFillTime;
	pvztime_t m_endHealthFillTime;
	bool m_startedFill;
};

class ZombossBattleIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(ZombossBattleIntroProperties, StandardLevelIntroProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return ZombossBattleIntro::StaticGetClass();
	}
	
	ZombossBattleIntroProperties()
	{
		ZombossPhaseCount = 3;
		SkipShowingStreetBossBattle = false;
	}
	
	int ZombossPhaseCount;
	bool SkipShowingStreetBossBattle;
};

#endif /* defined(__PlantsVersusZombies2__ZombossBattleIntro__) */

//
//  ChallengeModule.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 9/4/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengeModule_h
#define PlantsVersusZombies2_ChallengeModule_h

#include <vector>

#include "LevelModule.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyString.h"
#include "TimeMgr.h"

class ChallengeUI;

class ChallengeModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ChallengeModule, LevelModule, RtClass);

	void	GatherDependentModulePropertySheets(std::vector<LevelModulePropertiesPtr>& io_dependent) override;
	
	virtual bool	IsChallengeActive() { return true; }
	
	void			FailAllChallenges();
	virtual void	SetActiveChallengesCompleted(){ setActiveChallengesCompletedAtIndex(0); }
	bool			GetChallengesWereCompleted() const { return m_challengesWereCompleted; }
	float			GetHighThreatPosition();
	float			GetLowThreatPosition();
	float			GetThreatTargetPosition();
	virtual void 	getActiveChallenges(std::vector<class Challenge*>& o_challenges);
	virtual void 	getChallenges(std::vector<class Challenge*>& o_challenges);
	void			GetActiveChallengeDescriptions(std::vector<SexyString>& o_challengeDescriptions);
	
protected:
	void			initializeModule() override;
	void			registerForEvents() override;
	
	void			setActiveChallengesCompletedAtIndex(int i_index);
	
	virtual void	onChallengeFailed(class Challenge* i_challenge);

	bool			m_challengesWereCompleted;

private:
	void 			saveChallengeStateToProfile();
};

class ChallengeModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ChallengeModuleProperties, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return ChallengeModule::StaticGetClass();
	}
	
	std::vector<std::vector<RtWeakPtr<const LevelModuleProperties> > > Challenges;
	std::vector<int> Difficulties;
};

class Challenge : public LevelModule
{
public:
	RT_CLASS_DEFINE_ABSTRACT(Challenge, LevelModule, RtClass);
	
	Challenge()
	{
		m_failTime = PVZ_EOT();
		m_state = CS_InProgress;
	}

	enum ChallengeState
	{
		CS_Unknown,
		CS_InProgress,
		CS_Completed,
		CS_Failed,
	};
	
	void registerForEvents() override;
	
	void HideUI();
	
	bool InProgress() { return m_state == CS_InProgress; }

	void Fail();
	bool Failed() { return m_state == CS_Failed; }
	pvztime_t FailTime() { return m_failTime; }

	void Complete();
	bool Completed() { return m_state == CS_Completed; }
	
	virtual float	GetLowThreatPosition() { return 0.0f; }
	virtual float	GetHighThreatPosition() { return 0.0f; }
	virtual float	GetThreatTargetPosition() { return 0.0f; }
	
	virtual SexyString GetDescription() const
	{
		const LevelModuleProperties* props = getProps();
		return props->GetDescription();
	}
	
	virtual SexyString GetDescriptiveName() const
	{
		const LevelModuleProperties* props = getProps();
		return props->GetDescriptiveName();
	}

	virtual SexyString GetProgressDescription() const
	{
		const LevelModuleProperties* props = getProps();
		return props->GetDescription();
	}
	
protected:
	virtual void onAnyChallengeFailed(Challenge* i_challenge);
	virtual void onFail() {}
	virtual void onCompleted() {}
	
	virtual ChallengeUI* getChallengeUI();
	
	pvztime_t m_failTime;
	ChallengeState m_state;
};

namespace Message
{
	void ObjectiveFailed(Challenge* i_objectiveFailed); //Used to signal module of failure before informing everything else in the game
	void ChallengeFailed(Challenge* i_challengeFailed);
	void ChallengeModuleGameplayEnded();
};

#endif

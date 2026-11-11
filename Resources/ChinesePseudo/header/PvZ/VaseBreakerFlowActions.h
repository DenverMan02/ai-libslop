//
//  VaseBreakerFlowActions.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__VaseBreakerFlowActions__
#define __PlantsVersusZombies2__VaseBreakerFlowActions__

#include "VaseBreakerFlowModule.h"
#include "TimeMgr.h"

class VaseBreakerFlowActionWait : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionWait, VaseBreakerFlowAction, RtClass);

	VaseBreakerFlowActionWait()
		: m_startingTime(0)
		, m_waitTime(0)
	{}

	void SetWaitTime(pvztime_t i_time);

protected:
	void onBegin() override;
	void onUpdate() override;

private:
	pvztime_t m_startingTime;
	pvztime_t m_waitTime;
};

class VaseBreakerFlowActionStartGame : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionStartGame, VaseBreakerFlowAction, RtClass) {}

protected:
	void onBegin() override;
};

class VaseBreakerFlowActionReadySetBreak : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionReadySetBreak, VaseBreakerFlowAction, RtClass);

protected:
	void onBegin() override;

private:
	void onShowReady();
	void onShowSet();
	void onShowBreak();
	void onFinishReadySetBreak();
};

class VaseBreakerFlowActionFirstTimeAdvice : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionFirstTimeAdvice, VaseBreakerFlowAction, RtClass) {}
	
protected:
	void registerForEvents() override;
	
	void onBegin() override;
	
private:
	void onVaseBroken(class GridItemVase* i_vase);
};

class VaseBreakerFlowActionPlaceholderMessage : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionPlaceholderMessage, VaseBreakerFlowAction, RtClass);

	void SetPlaceholderMessage(const std::string& i_message, pvztime_t i_duration);

protected:
	void onBegin() override;
	void onUpdate() override;
	void onEnd() override;

private:
	std::string m_message;
	pvztime_t m_endTime;
};

class VaseBreakerFlowActionCreateAndShowVases : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionCreateAndShowVases, VaseBreakerFlowAction, RtClass) {}

protected:
	void onBegin() override;
	void onUpdate() override;

	std::vector<RtWeakPtr<class GridItemVase> > m_vases;
	std::vector<pvztime_t> m_vaseSpawnTimes;
	int m_nextVaseToSpawn = 0;
};

class VaseBreakerFlowActionShowNarrative : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionShowNarrative, VaseBreakerFlowAction, RtClass);

	void SetNarrative(const std::string& i_narrativeID);

protected:
	void onBegin() override;
	void onUpdate() override;
    
    void onNarrationFinished();

private:
	std::string m_narrativeID;
};

enum VaseBreakerFanfareSequenceType
{
	FST_WaveCompleted,
	FST_NewRecord,
	FST_NewRecordBackdrop,
	FST_VasesIncoming
};

struct VaseBreakerFanfareSequence
{
	VaseBreakerFanfareSequenceType Type;
	pvztime_t StartTime;
	pvztime_t EndTime;
	int YOffset;
	int YMotionOffset;
	
	bool IsActive() const;
};

class VaseBreakerFlowActionShowEndlessFanfare : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionShowEndlessFanfare, VaseBreakerFlowAction, RtClass);

	void SetParameters(int i_completedWave, bool i_newRecord);

protected:
	void onBegin() override;
	void onUpdate() override;
	void onAddToRenderQueue(class RenderQueue* i_queue) override;

private:
	bool isAnySequenceActive() const;
	bool isSequenceActive(const VaseBreakerFanfareSequence& i_sequence) const;
	void draw(class Graphics* i_g);
	void playRewardSound(bool i_newRecord);

	int m_completedWave;
	bool m_newRecord;
	std::vector<VaseBreakerFanfareSequence> m_sequences;
};

class VaseBreakerFlowActionClearBoard : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionClearBoard, VaseBreakerFlowAction, RtClass) {}

protected:
	void onBegin() override;
};

class VaseBreakerFlowActionLevelOfDayReward : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionLevelOfDayReward, VaseBreakerFlowAction, RtClass);

	VaseBreakerFlowActionLevelOfDayReward();

protected:
	void registerForEvents() override;
	void onBegin() override;
private:
	void onRewardSequenceFinished();
	void OnLeveloftheDayReward(bool i_success);
	void onGotChristmasProtect(bool i_success);
	void onNetworkError(int erroId);
};

class VaseBreakerFlowActionDropPowerUpReward : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionDropPowerUpReward, VaseBreakerFlowAction, RtClass);
	
	VaseBreakerFlowActionDropPowerUpReward()
		: m_showDialogTime(0.f)
	{}
	
	void SetPowerupType(const std::string& i_powerupTypeName);
	
protected:
	void registerForEvents() override;
	void onBegin() override;
	void onUpdate() override;
	
private:
	void onCollectableTryToCollect(class Collectable* i_collectable);
	void onAwardScreenDismissed();
	
	void showAwardScreen();
	void startCollectableCollection(float i_collectTime);

	std::string m_powerupTypeName;
	pvztime_t m_showDialogTime;
	RtWeakPtr<class Collectable> m_droppedCollectable;
};

class VaseBreakerFlowActionSetUIVisibility : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionSetUIVisibility, VaseBreakerFlowAction, RtClass);
	void SetVisibility(bool i_visible);
protected:
	void onBegin() override;
private:
	bool m_desiredVisibility;
};

#endif /* defined(__PlantsVersusZombies2__VaseBreakerFlowActions__) */

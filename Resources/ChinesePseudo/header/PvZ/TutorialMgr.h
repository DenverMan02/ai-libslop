/*
 * TutorialMgr.h
 *
 *  Created on: 2021-4-15
 *      Author: admin
 */

#ifndef TUTORIALMGR_H_
#define TUTORIALMGR_H_

#include "Singleton.h"
#include "Core.h"
#include "MapEventItem.h"
#include "NetworkData.h"
#include "UISingletonDialog.h"

namespace Message
{
	void NotifyTutorialCheck(bool i_result);
}

class UITutorialSkipDialog : public UISingletonDialog<UITutorialSkipDialog>
{
public:
	typedef Sexy::Delegate2<UITutorialSkipDialog*, int> MessageCallbackEvent;

	UITutorialSkipDialog();
	virtual ~UITutorialSkipDialog();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UITutorialSkipDialog"; }

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	void                        SetCallback(MessageCallbackEvent iEvent) {m_confirmCallbackEvent = iEvent;}
	void                        SetCancelCallback(MessageCallbackEvent iEvent) {m_cancelCallbackEvent = iEvent;}

private:
	void onAgreeBtn();
	void onDisagreeBtn();

	MessageCallbackEvent               m_confirmCallbackEvent;
	MessageCallbackEvent               m_cancelCallbackEvent;
};

class NetworkTutorialCheckInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkTutorialCheckInfo, INetworkData, RtClass);

public:
	bool needTutorial;
};

class NetworkTutorialRewards : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkTutorialRewards, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> billList;
};

class TutorialMgr : public LazySingleton <TutorialMgr>
{
public:
	TutorialMgr();
    ~TutorialMgr();

    void StartTutorial(MapTutorialState i_state);
    bool HasTutorial(MapTutorialState i_state);
    void SetQueuedTutorial(MapTutorialState i_state) { m_queuedTutorial = i_state; }
    MapTutorialState GetQueuedTutorial() { return m_queuedTutorial; }
    void TryClearQueuedTutorial(MapTutorialState i_state);
    void CheckTutorial();
    void StartRequest(bool i_needTutorial);
    int GetTotalCompletedStars();
    void SkipTutorials();
    void CompleteAllTutorials();
    bool IsExtraTutorial(MapTutorialState i_state);
    bool HasRunningIconEffect();
    void TryProfileReset();
    void ResetProfile();
    bool GetNeedTutorial();
    void RequestSkipReward();
    void SetHasSkippedTutorial(bool i_skipped) { m_skippedTutorial = i_skipped; }
    bool HasSkippedTutorial() { return m_skippedTutorial; }

private:
    void onNotifyTutorialEffectEnd(int i_type);
    void onNarrationFinished();
    void onQueuedNarrationFinished();

    bool m_needTutorial;
    int m_currentType;
    MapTutorialState m_queuedTutorial;
    bool m_skippedTutorial;
};


#endif /* TUTORIALMGR_H_ */

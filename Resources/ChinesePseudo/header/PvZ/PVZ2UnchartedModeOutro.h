/*
 * PVZ2UnchartedModeOutro.h
 *
 *  Created on: 2022-3-17
 *      Author: zhousen
 */

#ifndef PVZ2UNCHARTEDMODEOUTRO_H_
#define PVZ2UNCHARTEDMODEOUTRO_H_

#include <vector>
#include "OutroModule.h"
#include "RtObject.h"
#include "PVZ2UnchartedModeResultScreen.h"

class PVZ2UnchartedModeOutro : public OutroModule
{
public:
	enum PVZ2UnchartedModeOutroState
	{
		PVZ2_UNCHARTED_OUTRO_NOT_READY = 0,
		PVZ2_UNCHARTED_OUTRO_UPDATE,
		PVZ2_UNCHARTED_OUTRO_RESULT_INIT,
        PVZ2_UNCHARTED_OUTRO_SHOW_RESULTS,
        PVZ2_UNCHARTED_OUTRO_YOU_WON_SUCCESS,
        PVZ2_UNCHARTED_OUTRO_LOSE,
        PVZ2_UNCHARTED_OUTRO_FIRST_CLEAR_SCREEN,
		PVZ2_UNCHARTED_OUTRO_FADING_OUT,
        PVZ2_UNCHARTED_OUTRO_FIRST_REWARD,
        PVZ2_UNCHARTED_OUTRO
	};

	RT_CLASS_DEFINE(PVZ2UnchartedModeOutro, OutroModule, RtClass);

	PVZ2UnchartedModeOutro();
	virtual ~PVZ2UnchartedModeOutro();

	void registerForEvents() override;

	pvztime_t GetElapseTime();
	std::vector<std::string> GetModes();

	void SetChooseCardsCallback(std::function<void()> i_onCallback) { m_onChooseCardsCallback = i_onCallback; }

protected:
	void postInitialize() override;
	void gameStart();
	void onUpdate();

	void startBoardFade();
	void onBoardFadeDone();

	void startWinOutro();
	void startLossOutro();

    void showResultsScreen(PVZ2UnchartedModeResultType type);
    void onResultsScreenDismissed();
    void onPlayAgain();
    void onPlayNextLevel();

    void onRealExitToMap();
    void onRealContinueToPlay();
    void OnLuaNotify(const std::string& rLuaEvent);

    void sendPostEndPlay(bool i_won);
    void sendPostEndPlayLoss();

	void onPVZ2UnchartedModeNetworkResponse(int i_context, int i_status);

	void onSuccessResponse();
	void onChallengeFailedResponse();
	void onFailedResponse();

protected:
	PVZ2UnchartedModeOutroState m_state;// outro state
	class PVZ2UnchartedModeResultScreen* m_resultScreen;// result screen ptr

	pvztime_t m_startTime;
	pvztime_t m_endTime;
	int m_challengeWinNum;
	std::function<void()> m_onChooseCardsCallback;
};

class PVZ2UnchartedModeOutroProperties : OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(PVZ2UnchartedModeOutroProperties, OutroModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return PVZ2UnchartedModeOutro::StaticGetClass();
	}

	PVZ2UnchartedModeOutroProperties()
    {
		Modes.clear();
    }

	std::vector<std::string> Modes;
};

namespace Message
{
	void NotifyUnchartedBirthdayFinished(bool i_won);
}


#endif /* PVZ2UNCHARTEDMODEOUTRO_H_ */

/*
 * PVZ1ModeOutro.h
 *
 *  Created on: 2021-7-30
 *      Author: zhousen
 */

#ifndef PVZ1MODEOUTRO_H_
#define PVZ1MODEOUTRO_H_

#include <vector>
#include "OutroModule.h"
#include "RtObject.h"
#include "PVZ1ModePropertySheet.h"
#include "UISpacetimeEnergy.h"

class PVZ1ModeOutro : public OutroModule
{
public:
	enum PVZ1ModeOutroState
	{
        PVZ1_OUTRO_NOT_READY = 0,
        PVZ1_OUTRO_UPDATE,
        PVZ1_OUTRO_RESULT_INIT,
        PVZ1_OUTRO_SHOW_RESULTS,
        PVZ1_OUTRO_YOU_WON_SCREEN,
        PVZ1_OUTRO_CHALLENGE_LOSE_SCREEN,
        PVZ1_OUTRO_TIME_ENERGY_LOSE_SCREEN,
		PVZ1_OUTRO_FIRST_CLEAR_SCREEN,
        PVZ1_OUTRO_FADING_OUT,
        PVZ1_OUTRO_FIRST_REWARD,
        PVZ1_OUTRO_DONE
	};


	RT_CLASS_DEFINE(PVZ1ModeOutro, OutroModule, RtClass);

	PVZ1ModeOutro();
	virtual ~PVZ1ModeOutro();

	void registerForEvents() override;

	pvztime_t GetElapseTime();

protected:
	void postInitialize() override;
	void gameStart();
	void onUpdate();

	void startBoardFade();
	void onBoardFadeDone();

	void startWinOutro();
	void startLossOutro();

    void showResultsScreen(PVZ1ModeResultType type);
    void onResultsScreenDismissed();
    void onPlayAgain();

    void sendPostEndPlay();
    void sendPostEndPlayLoss();

	void onPVZ1ModeNetworkResponse(int i_context, int i_status);

	void onSuccessResponse();
	void onChallengeFailedResponse();
	void onFailedResponse();

protected:
	PVZ1ModeOutroState m_state;// outro state
	class UIPVZ1ModeResultScreen* m_resultScreen;// result screen ptr

	pvztime_t m_startTime;
	pvztime_t m_endTime;
};

class PVZ1ModeOutroProperties : OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(PVZ1ModeOutroProperties, OutroModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return PVZ1ModeOutro::StaticGetClass();
	}
};

#endif /* PVZ1MODEOUTRO_H_ */

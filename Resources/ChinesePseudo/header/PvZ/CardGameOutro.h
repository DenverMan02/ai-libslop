/*
 * CardGameOutro.h
 *
 *  Created on: 2022-6-01
 *      Author: zhousen
 */

#ifndef CARDGAMEOUTRO_H_
#define CARDGAMEOUTRO_H_

#include <vector>
#include "OutroModule.h"
#include "RtObject.h"
#include "PropertySheetBase.h"

enum CardGameResultType
{
	CardGameResult_Invalid = -1,
	CardGameResult_Win,
	CardGameResult_Loss,
	CardGameResult_Max,
};

namespace Message
{
	void CardGameNetworkResponseReceived(int , int);
}

class CardGameOutro : public OutroModule
{
public:
	RT_CLASS_DEFINE(CardGameOutro, OutroModule, RtClass);

	CardGameOutro();
	virtual ~CardGameOutro();

	void registerForEvents() override;

protected:
	void postInitialize() override;
	void gameStart();
	void onUpdate();

	void startBoardFade();
	void onBoardFadeDone();

	void startWinOutro();
	void startLossOutro();

    void showResultsScreen(CardGameResultType type);
    void onResultsScreenDismissed(int i_type);
    void onPlayAgain();

    void sendPostEndPlay();
    void sendPostEndPlayLoss();

	void onCardGameNetworkResponse(int i_context, int i_status);

	void onSuccessResponse();
	void onFailedResponse();
	void onNotifyCardSelectDone();

	void OnNarrativeTutorialEndCompleted();

protected:
	class CardGameResultScreen* m_resultScreen;// result screen ptr
	int m_challengeWinNum;
};

class CardGameOutroProperties : OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(CardGameOutroProperties, OutroModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return CardGameOutro::StaticGetClass();
	}

	CardGameOutroProperties()
    {
		Modes.clear();
    }

	std::vector<std::string> Modes;
};



#endif /* CARDGAMEOUTRO_H_ */

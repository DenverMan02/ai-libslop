/*
 * CardGameResultScreen.h
 *
 *  Created on: 2022-6-02
 *      Author: zhousen
 */

#ifndef CARDGAMERESULTSCREEN_H_
#define CARDGAMERESULTSCREEN_H_

#include "PVZDB.h"
#include "Singleton.h"
#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PVZTypes.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "UISingletonDialog.h"
#include "UIUtil.h"
#include "UIRewardFrame.h"
#include "UIUtil.h"
#include "CardGameOutro.h"

enum {
	CardGame_Result_Screen_Button = 1000,
	CardGame_Result_Screen_BackToMap,
	CardGame_Result_Screen_PlayAgain,
};

///
/// Card Game Result Screen
///
class CardGameResultScreen : public UISingletonDialog<CardGameResultScreen>
{
public:
    typedef Delegate0 CardGameResultScreenCabllBack;
    typedef Delegate1<int> CardGameResultScreenCabllBackSelect;

    CardGameResultScreen();
	~CardGameResultScreen();

	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;
	virtual std::string GetLayoutName() override { return "UICardGameResultScreen"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView(CardGameResultType type);
	void SetChallengeWinNum(int winNum) { _challengeWinNum  = winNum; }
	void SetCallback(CardGameResultScreenCabllBackSelect func, CardGameResultScreenCabllBack playAgain);


private:
	CardGameResultType _screenType;// win / loss
	CardGameResultScreenCabllBackSelect _buttonCallback;
	CardGameResultScreenCabllBack _buttonCallbackPlayAgain;
	SexyString _winDesc;// win desc str
	Rect _winDescRect;
	SexyString _elapseStr;// time elapse str
	Rect _elapseStrRect;
	SexyString _challengeFailStr;// challenge fail str
	std::vector<SexyString> _challengeDescStrList;// challenge desc when lose
	std::vector<bool> _challengeFailList;// challenge states
	Rect _timeEnergyLoseRect;
	std::string _bonusPlantName;
	int _challengeWinNum;
};



#endif /* CARDGAMERESULTSCREEN_H_ */

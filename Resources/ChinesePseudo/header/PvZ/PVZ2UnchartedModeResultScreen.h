/*
 * PVZ2UnchartedModeResultScreen.h
 *
 *  Created on: 2022-3-17
 *      Author: zhousen
 */

#ifndef PVZ2UNCHARTEDMODERESULTSCREEN_H_
#define PVZ2UNCHARTEDMODERESULTSCREEN_H_

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

enum {
	PVZ2UnchartedMode_Result_Screen_Button = 1000,
	PVZ2UnchartedMode_Result_Screen_BackToMap,
	PVZ2UnchartedMode_Result_Screen_PlayAgain,
};

enum PVZ2UnchartedModeResultType
{
	PVZ2UnchartedMode_Result_Win,
	PVZ2UnchartedMode_Result_Lose,
};

///
/// PVZ1 Mode Result Screen
///
class PVZ2UnchartedModeResultScreen : public UISingletonDialog<PVZ2UnchartedModeResultScreen>
{
public:
    typedef Delegate0 PVZ2UnchartedModeResultScreenCabllBack;

    PVZ2UnchartedModeResultScreen();
	~PVZ2UnchartedModeResultScreen();

	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;
	virtual std::string GetLayoutName() override { return "UIPVZ2UnchartedModeResultScreen"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView(PVZ2UnchartedModeResultType type);
	void SetChallengeWinNum(int winNum) { _challengeWinNum  = winNum; }
	void SetCallback(PVZ2UnchartedModeResultScreenCabllBack func, PVZ2UnchartedModeResultScreenCabllBack playAgain);

private:
	void getObjectiveData(std::vector<SexyString>& o_objectiveText, std::vector<bool>& o_objectiveFailed);
	void ShowUnlockPlantScreen();

private:
	PVZ2UnchartedModeResultType _screenType;// win / loss
	PVZ2UnchartedModeResultScreenCabllBack _buttonCallback;
	PVZ2UnchartedModeResultScreenCabllBack _buttonCallbackPlayAgain;
	SexyString _winDesc;// win desc str
	Rect _winDescRect;
	SexyString _elapseStr;// time elapse str
	Rect _elapseStrRect;
	SexyString _challengeFailStr;// challenge fail str
	std::vector<SexyString> _challengeDescStrList;// challenge desc when lose
	std::vector<bool> _challengeFailList;// challenge states
	Rect _timeEnergyLoseRect;
	std::string _bonusPlantName;
	UnchartedModeEndOfPlayData _endData;
	int _challengeWinNum;
};



#endif /* PVZ2UNCHARTEDMODERESULTSCREEN_H_ */

/*
 * UIPVZ1ModeResultScreen.h
 *
 *  Created on: 2021-7-30
 *      Author: zhousen
 */

#ifndef UIPVZ1MODERESULTSCREEN_H_
#define UIPVZ1MODERESULTSCREEN_H_

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
#include "PVZ1ModeDataPacket.h"


enum {
	PVZ1Mode_Result_Screen_Button = 1000,
	PVZ1Mode_Result_Screen_BackToMap,
	PVZ1Mode_Result_Screen_PlayAgain,
};

///
/// Bonus Widget
///
class PVZ1ModeResultBonusWidget : public UIRewardFrame
{
public:
	PVZ1ModeResultBonusWidget(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual ~PVZ1ModeResultBonusWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	static PVZ1ModeResultBonusWidget* CreateUIRewardFrame(int objectId, int num, bool hasFrame);
};

///
/// PVZ1 Mode Result Screen
///
class UIPVZ1ModeResultScreen : public UISingletonDialog<UIPVZ1ModeResultScreen>
{
public:
    typedef Delegate0 PVZ1ModeResultScreenCallback;

	UIPVZ1ModeResultScreen();
	~UIPVZ1ModeResultScreen();

	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;
	virtual std::string GetLayoutName() override { return "UIPVZ1ModeResultScreen"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView(PVZ1ModeResultType type);
	void SetCallback(PVZ1ModeResultScreenCallback func, PVZ1ModeResultScreenCallback playAgain);

private:
	void getObjectiveData(std::vector<SexyString>& o_objectiveText, std::vector<bool>& o_objectiveFailed);

private:
	PVZ1ModeResultType _screenType;// win / challenge loss / time energy loss
	PVZ1ModeResultScreenCallback _buttonCallback;
	PVZ1ModeResultScreenCallback _buttonCallbackPlayAgain;
	SexyString _winDesc;// win desc str
	Rect _winDescRect;
	SexyString _elapseStr;// time elapse str
	Rect _elapseStrRect;
	SexyString _challengeFailStr;// challenge fail str
	std::vector<SexyString> _challengeDescStrList;// challenge desc when lose
	std::vector<bool> _challengeFailList;// challenge states
	Rect _timeEnergyLoseRect;
};

#endif /* UIPVZ1MODERESULTSCREEN_H_ */

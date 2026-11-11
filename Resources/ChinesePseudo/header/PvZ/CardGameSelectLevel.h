/*
 * CardGameSelectLevel.h
 *
 *  Created on: 2022-6-24
 *      Author: zhousen
 */

#ifndef CARDGAMESELECTLEVEL_H_
#define CARDGAMESELECTLEVEL_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "PVZ2UnchartedModeSelectLevel.h"
#include "CardGameNetworkMgr.h"

///////////////////////////////
/// Button ID Enum
///////////////////////////////
enum {
	CARD_GAME_SELECT_LEVEL_BTN_CLOSE = 1000,
	CARD_GAME_SELECT_LEVEL_BTN_TIPS,
	CARD_GAME_SELECT_LEVEL_BTN_START,
};

//////////////////////////////////////
/// CardGameSelectLevel
//////////////////////////////////////
class CardGameSelectLevel : public UISingletonDialog<CardGameSelectLevel>
{
public:
	CardGameSelectLevel();
	~CardGameSelectLevel();

	virtual bool	     OnCreate() override;
    virtual std::string  GetLayoutName() override {
//    	return "UICardGameSelectLevel";
    	return "UICardGameSelectLevelNew";
    }
	virtual void		 ButtonDepress(int i_id) override;

	void SetEventNode(MapEventItem* event);
	void SetPlayLevelCallback(Sexy::Delegate1<const std::string&> callback);

private:
	void InitView();
	void InitBonusWidgets();
	void InitZombies();

	void InitChallengeWidgets();
	void InitModes();

	void InitStartButton();

	void PressStartButton();
	void showDescriptionWidget();

private:
	std::vector<bool> _challengeSelectList;
	UIScrollControl* _bonusScrollView;
	std::vector<CardGameLevelBonusData> _finalBonusDataList;
	std::vector<PVZ2UnchartedModeBonusWidget*> _finalBonusWidgetList;
	Widget* _bonusScrollViewContainer;
	MapEventItem* _eventNodeToPlay;
    Sexy::Delegate1<const std::string&> _playLevelCallback;
    std::vector<int> _challengeStatusList;// the challenge status list 0 = not complete 1 = complete
};

#endif /* CARDGAMESELECTLEVEL_H_ */

/*
 * PennyPerkBattleStatementChoose.h
 *
 *  Created on: 2020-5-29
 *      Author: zhousen
 */

#ifndef PENNYPERKBATTLESTATEMENTCHOOSE_H_
#define PENNYPERKBATTLESTATEMENTCHOOSE_H_

#include "PVZDB.h"
#include "Singleton.h"
#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "PopingWidget.h"
#include "UISingletonDialog.h"
#include "EASquared.h"
#include "UIUtil.h"
#include "UIRewardFrame.h"
//#include "ActivityManager.h"
#include "UIUtil.h"
#include "BasicPerks.h"
#include "PennyPerkMgr.h"

enum {
	BTN_PENNY_PERK_BATTLESTATEMENT_CHOOSE = 1000,
	BTN_PENNY_PERK_LEVELUP_CLOSE = 1001,
};

class PennyPerkProperties;
class PennyPerkBattleStatementChooseUI;
class RiftOutro;

///
/// Perk Choose Item
///
class PerkChooseWidget : public Widget
{
public:
	PerkChooseWidget(int index, PerkData data, PennyPerkBattleStatementChooseUI* parent);
	// PerkChooseWidget(int index, PennyPerkProperties data, PennyPerkBattleStatementChooseUI* parent);
	virtual ~PerkChooseWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

	void InitView();
	void SetFrameEnable(bool enable) { _frameEnable = enable; }

protected:

protected:
	SexyString _itemName;// perk item name
	SexyString _itemDescription;//perk item description

	Sexy::Image* _itemBgBig;
	Sexy::Image* _itemBg;// perk bg
	Sexy::Image* _itemIcon;// perk icon
	// Sexy::Image* _itemLevel;// perk level
	SexyString _itemLevelStr;
	Sexy::Image* _itemFrame;// outline frame

	Sexy::Widget* _itemNameWidget;
	Sexy::Widget* _itemDescriptionWidget;
	Sexy::Widget* _itemBgWidget;

	int _touchID;// item touch id

	// PennyPerkProperties _data;// penny perk data
	PerkData _data;

	PennyPerkBattleStatementChooseUI* _parentUI;// main ui

	int _index;// the index of widgets

	bool _frameEnable;// if draw the frame
    
    Color _fontColor;
};

/// 
/// level up ui
///
class PennyPerkLevelUpUI : public Widget, ButtonListener
{
public:
	PennyPerkLevelUpUI(PerkData data, PennyPerkBattleStatementChooseUI* parent, int originalLevel);
	// PennyPerkLevelUpUI(PennyPerkProperties data, PennyPerkBattleStatementChooseUI* parent, int originalLevel);
	~PennyPerkLevelUpUI();

	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void InitView();

private:
	// PennyPerkProperties _data;// perk data
	PerkData _data;
	Sexy::Image* _itemIcon;// perk icon
	SexyString _originalLvStr;

	int _originalLevel;// perk lv
	PVZ2UIButton* _closeButton;// close button
	PennyPerkBattleStatementChooseUI* _parentUI;

	Sexy::Rect _originalItemRect;
	Sexy::Rect _levelUpItemRect;
	Sexy::Rect _arrowRect;
};

///
/// Main UI
///
class PennyPerkBattleStatementChooseUI : public UISingletonDialog<PennyPerkBattleStatementChooseUI>
{
public:
	PennyPerkBattleStatementChooseUI();
	~PennyPerkBattleStatementChooseUI();

	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual std::string GetLayoutName() override { return "UIPennyPerkBattleStatementChoose"; }
	virtual void ButtonDepress(int i_id) override;

	void Init(ActiveItem item);// init data
	void InitView();// init ui
	void SetRiftOutro(RiftOutro* outro) { _outro = outro; }
	RiftOutro* GetRiftOutro() { return _outro; }
	void SetChooseIndex(int index);

protected:
	std::vector<PennyPerkProperties> CreateTestData();
	void RequestChoosePerk(int world_level, int perk_index);

private:
	std::vector<PerkChooseWidget*> _perkChooseList;// a list of all three perk items.
	// std::vector<PennyPerkProperties> _perkDataList;// perk item properties
	std::vector<PerkData> _perkDataList;
	
	PVZ2UIButton* _chooseBtn;

	PennyPerkLevelUpUI* _levelUpUI;

	int _chooseIndex;// the index of the choosen item
	RiftOutro* _outro;// get parent ptr
};

#endif /* PENNYPERKBATTLESTATEMENTCHOOSE_H_ */

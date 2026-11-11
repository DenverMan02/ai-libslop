/*
 * WorldMap_CardGameBottomBar.h
 *
 *  Created on: 2022-6-28
 *      Author: admin
 */

#ifndef WORLDMAP_CARDGAMEBOTTOMBAR_H_
#define WORLDMAP_CARDGAMEBOTTOMBAR_H_

#include "RtObject.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "UIEasyButtonWidget.h"
#include "DNode/DNodeWidget.h"
#include "DNode/DButton.h"
#include "DNode/DMenu.h"

namespace Sexy
{
	class Graphics;
}

class CardPickButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(CardPickButton, UIEasyButtonWidget, RtClass);

    CardPickButton();
    virtual ~CardPickButton();

    virtual void onUpdate() override;
    virtual void Draw(Graphics* i_g) override;

    virtual void OnClick();

};

class WorldMap_CardPickBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_CardPickBank, UIWidget, RtClass);

	WorldMap_CardPickBank()
	{
		m_maxNum = 21;
		m_num = 0;
		m_button = nullptr;
		m_isAddNotice = false;
	}

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

	virtual void onUpdate()	override;

//	void setNum(int i_num) { m_num = i_num; }
	int getNum() { return m_num; }

//	void setMaxNum(int i_maxNum) { m_maxNum = i_maxNum; }
	int getMaxNum() { return m_maxNum; }

//	void setIsAddNotice(bool i_isAddNotice) { m_isAddNotice = i_isAddNotice; }
	bool isAddNotice() { return m_isAddNotice; }

private:
	void checkHasAvailableRewards();

	class CardPickButton* m_button;
	int m_maxNum;
	int m_num;

	bool m_isAddNotice;
};

class WorldMap_CardGameSwitchWidget : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_CardGameSwitchWidget, UIWidget, RtClass);

	WorldMap_CardGameSwitchWidget()
	{
		m_resetButton = nullptr;
		m_previewButton = nullptr;
		m_isHardModeUnlocked = true;
		m_isOnHardMode = false;
	}

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

	virtual void onUpdate()	override;

//	void setIsHardModeUnlocked(bool i_isHardModeUnlocked) { m_isHardModeUnlocked = i_isHardModeUnlocked; }
	bool isHardModeUnlocked() { return m_isHardModeUnlocked; }

	bool isOnHardMode() { return m_isOnHardMode; }
	void setIsOnHardMode(bool i_isOnHardMode);

private:
	class CardGameResetButton* m_resetButton;
	class CardGamePreviewButton* m_previewButton;

	bool m_isHardModeUnlocked;
	bool m_isOnHardMode;
};


// CardGameResetButton

class CardGameResetButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(CardGameResetButton, UIEasyButtonWidget, RtClass);

    CardGameResetButton();
    virtual ~CardGameResetButton();

    virtual void Draw(Graphics* i_g) override;
    virtual void onUpdate() override;

//    virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

    virtual void OnClick();

    void ConfirmReset(class UIMessageBox* box, int buttonID);
};

struct CardPreviewInfo
{
	CardPreviewInfo()
	: CardID(0)
	, CardCount(0)
	{

	}

	CardPreviewInfo(int i_id, int i_count)
	: CardID(i_id)
	, CardCount(i_count)
	{

	}

	int CardID;
	int CardCount;
};

class CardPreview:public DNodeWidget
{
public:
    static CardPreview* create(const std::vector<CardPreviewInfo>& i_cards);
    static CardPreview* get();

    virtual ~CardPreview();

    virtual void Initialize() override;

    virtual void UserInit() override;

    DArray<class Card*> CreateCard(int i_id, int i_count);

public:
    static CardPreview* s_pWidgetHandler;
    std::vector<CardPreviewInfo> m_cards;
};

// CardGamePreviewButton

class CardGamePreviewButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(CardGamePreviewButton, UIEasyButtonWidget, RtClass);

    CardGamePreviewButton();
    virtual ~CardGamePreviewButton();

    virtual void Draw(Graphics* i_g) override;
    virtual void onUpdate() override;

//    virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

    virtual void OnClick();
};

class WorldMap_CardGameBottomBar : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_CardGameBottomBar, UIWidget, RtClass);

	WorldMap_CardGameBottomBar()
	{
		m_cardPickBank = nullptr;
		m_modeSwitchWidget = nullptr;
	}

	virtual void onUpdate()	override;

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;


private:
	WorldMap_CardPickBank* m_cardPickBank;
	WorldMap_CardGameSwitchWidget* m_modeSwitchWidget;

};

class CardGameCountDownWidget : public UIWidget
{
public:
	RT_CLASS_DEFINE(CardGameCountDownWidget, UIWidget, RtClass);

	CardGameCountDownWidget();
	virtual ~CardGameCountDownWidget();

	virtual void Draw(Graphics* i_g) override;

protected:
    // Protected Interface (Inheritable)

    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

    SexyString m_timeLabel;
};


#endif /* WORLDMAP_CARDGAMEBOTTOMBAR_H_ */

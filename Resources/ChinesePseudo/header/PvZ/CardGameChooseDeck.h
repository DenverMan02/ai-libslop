/*
 * CardGameChooseDeck.h
 *
 *  Created on: 2022-6-24
 *      Author: zhousen
 */

#ifndef CARDGAMECHOOSEDECK_H_
#define CARDGAMECHOOSEDECK_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"

enum {
	CardGame_Btn_Close = 1000,
	CardGame_Btn_Confirm,
	CardGame_Btn_Deck1,
	CardGame_Btn_Deck2,
};

enum {
	Select_Deck1 = 0,
	Select_Deck2,
};

// CardGameChooseDeck
class CardGameChooseDeck : public UISingletonDialog<CardGameChooseDeck>
{
public:
	CardGameChooseDeck();
	virtual ~CardGameChooseDeck();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICardGameChooseDeck"; }
	virtual void ButtonDepress(int i_id) override;

protected:
	void InitView();
	void ChooseButton(int index);
	class CardGameDeckButton* CreateDeckButton(int index, std::string name);

protected:
	int m_selectionIndex;// select button.
	class CardGameDeckButton* m_deckButton1;
	class CardGameDeckButton* m_deckButton2;
};

// CardGameDeckButton
class CardGameDeckButton : public PVZ2UIButton
{
public:
	CardGameDeckButton(int id, ButtonListener* listener);
	virtual ~CardGameDeckButton();

    virtual void Draw(Sexy::Graphics* i_g) override;

	void SetSelect(bool select);
	bool IsSelected() const;
	void SetIndex(int index);

	void InitView();

protected:
	int m_Index;// button index
	bool m_Selected;// button is selected
	Image* m_Image;// button bg
	Image* m_SpeechBg;// speech pop background image
	Rect m_SpeechRect;// speech pop background rect
	SexyString m_Desc;// button desc
};

#endif /* CARDGAMECHOOSEDECK_H_ */

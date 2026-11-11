/*
 * ComboBox.h
 *
 *  Created on: 2021-12-23
 *      Author: zhousen
 */

#ifndef COMBOBOX_H_
#define COMBOBOX_H_

////////////////////////////////////
/// Combo Box Widget
////////////////////////////////////
typedef Sexy::Delegate1<int> BoxClickEvent;

class ComboBoxItem : public PVZ2UIButton, public Sexy::ButtonListener
{
public:
	ComboBoxItem(int id);
	virtual ~ComboBoxItem();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ButtonDepress(int i_id);
	virtual SexyString GetWidgetName() { return m_buttonName; }
	virtual int GetWidgetID() { return m_id; }
	virtual void SetArrowImage(Image* image) { m_arrowImage = image; }
	virtual void SetBgImage(Image* image) { m_bgImage = image; }
	virtual void SetWidgetName(SexyString name) { m_buttonName = name; }
	virtual void SetClickFunc(BoxClickEvent func) { m_func = func; }
	virtual void SetMainClickFunc(BoxClickEvent func) { m_mainFunc = func; }
	virtual void SetCustomClickFunc(BoxClickEvent func) { m_customFunc = func; }

protected:
	SexyString m_buttonName;// widget name
	int m_id;// widget id
	Image* m_arrowImage;// arrow image
	Image* m_bgImage;// bg image
	BoxClickEvent m_func;// click func
	BoxClickEvent m_mainFunc;// combobox main func
	BoxClickEvent m_customFunc;// custom func
};

////////////////////////////////////
/// Combo Box
////////////////////////////////////

class ComboBox : public Sexy::Widget, public Sexy::ButtonListener
{
public:
public:
	ComboBox(BoxClickEvent func);
	virtual ~ComboBox();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_w, int i_h);
	virtual void SetDisabled(bool isDisabled);
	virtual void ButtonDepress(int i_id);		// menu clicked
	virtual void OnCreate(int i_id, const SexyString& text);
	virtual void ShowMenu();
	virtual void HideMenu();
	ComboBoxItem* AddSubMenu(int i_id, const SexyString& text);
	ComboBoxItem* GetSubMenu(int i_id);
	Sexy::Widget* GetPanel() { return m_pPanel; }
	int GetMenuID() { return m_pMenu ? m_pMenu->mId : -1; }
//	void						SetClickFunc(BoxClickEvent func) {}
	int GetCurrentWidgetID() { return m_currentWidgetID; }
	void SetCallBack(BoxClickEvent func) { m_menuClickedCallback = func; }

protected:
	void ClickComboBox(int id);
	void ClickComboBoxMain(int id);

protected:
	ComboBoxItem*				m_pMenu;
	Sexy::Widget*				m_pPanel;
	BoxClickEvent				m_menuClickedCallback;
	int							m_currentWidgetID;// current id
	SexyString					m_currentWidgetName;// current name
	int							m_subMenuCount;
};



#endif /* COMBOBOX_H_ */

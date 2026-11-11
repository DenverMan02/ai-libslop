//
//  UIEditor.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/10.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIEditor_h_
#define _UIEditor_h_

#include "UISingletonDialog.h"
#include "UISelection.h"

class UIEditor;
class UIEditorMenu;
class UILayoutDefinition;
class UIProperty;
class UIPropertySheet;

class UIEditorCanvas : public Sexy::Widget
{
public:
	UIEditorCanvas(UIEditor* pEditor);
	~UIEditorCanvas();
	virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseDrag(int x, int y);
public:
	UIEditor*			m_pEditor;
};

class UIEditor : public UISingletonDialog<UIEditor>, public Sexy::EditListener
{
public:
	enum {
		State_None,
		State_Pressed,
		State_Area,
	};
public:
	UIEditor();
	~UIEditor();
	virtual std::string				GetLayoutName() { return "uieditor"; }
	virtual bool							OnCreate();
	virtual void							OnClose();

	virtual void							DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
	virtual void							MouseDown(int x, int y, int theBtnNum, int theClickCount);
	virtual void							MouseUp(int x, int y, int theBtnNum, int theClickCount);
	virtual void							MouseDrag(int x, int y);
	//virtual void							ButtonDepress(int i_id);

	void										OnMenuClicked(int menuID);

	UIEditorMenu*								AddMenu(int i_id, const SexyString& text);
	void										LayoutMenus(bool bVertical);
	void										HidePopupMenu(int menuID);

protected:
	void										checkMouseType(int x, int y);
	void										setMouseType(int type);
	Sexy::Widget*								getTargetWindow(int x, int y);
	Sexy::Widget*								createWindow();
	void										selectWindow(Widget* pWnd, bool bAppend = false);
	std::string									getUniqueName(const std::string& strType);
	std::string									getBestName(const std::string& i_origenName);
	void										saveFile();
    void										openFile(const std::string& strFile);
    void										createMenuFiles(UIEditorMenu* pMenu);

	void										initPropertySheet();
	void										refreshPropertySheet(Sexy::Widget* pWidget);
	void										OnPropertyChanged(UIProperty* pProperty);

	void										initDialogSheet();
	void										refreshDialogSheet();
	void										OnDialogPropertyChanged(UIProperty* pProperty);

	void										OnMenuSelectOperator(int menuID);
    void										OnMenuAddExOperator(int menuID);
	void										OnMenuToolOperator(int menuID);
    void										OnInputDialogCallback(class UIInputDialog* pDlg, int btn_id);
    
    void UnloadUIEditorGroups();
    void AddUIEditorResGroup(const std::string& group_name);

private:
	void										toWidgetRecursively(Sexy::Widget* pRoot, VecUIWidgetType& vecWidgetType);


	UIEditorCanvas*				m_pCanvas;		// add to gLawnApp
	UIPropertySheet*				m_pPropertySheet;
	UIPropertySheet*				m_pDialogSheet;
	Sexy::Point							m_mousePos;
	std::vector<UIEditorMenu*> m_menuList;
	UI::Selection						m_selection;
	int										m_state;
	int										m_mouseType;
	std::string							m_createType;
	std::map<int, std::string>	m_mapCreateTypes;
    std::map<int, std::string>	m_mapFileList;
    std::set<std::string> m_editorResGroups;
};


#endif

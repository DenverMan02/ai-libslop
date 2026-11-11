//
//  RechargeGiftUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __UIDialog_h_
#define __UIDialog_h_

#include "Widget.h"
#include "RtObject.h"
#include "UILayoutDefinition.h"
#include "ButtonListener.h"

namespace UI 
{

// extension NonCopyable, Singleton
class Dialog : public Sexy::Widget, public Sexy::ButtonListener
{

public:
	Dialog();
	virtual ~Dialog();

	// inherit from Sexy::Widget
	//virtual void							Update();
	virtual void							DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;
	virtual void							Draw(Sexy::Graphics* i_g) override;
	//virtual void							Resize(int theX, int theY, int theWidth, int theHeight);
	//virtual void							ButtonDepress(int i_id);

	//-------------------------------------------------------------------------
	virtual bool							OnCreate();
	virtual void							OnClose();
    virtual std::string				GetLayoutName() {return "";}
	virtual void							UnloadGroups();
	void										AddResGroup(const std::string& group_name);

	//-------------------------------------------------------------------------
	class Sexy::Widget*			GetWidget(const std::string& name);
	template <typename T>
	T*						GetWidget(const std::string& name)
	{
		class Sexy::Widget* pFind = GetWidget(name);
		return pFind ? WidgetFactory<T*>::GetWidget(pFind) : NULL;
	}
	static class Sexy::Widget*			GetChildWidget(Sexy::Widget* pWidget, const std::string& name);
    template <typename T>
    static T*						GetChildWidget(Sexy::Widget* pWidget, const std::string& name)
    {
        class Sexy::Widget* pFind = GetChildWidget(pWidget, name);
        return pFind ? WidgetFactory<T*>::GetWidget(pFind) : NULL;
    }
    
    class Sexy::Widget*         CloneWidget(class Sexy::Widget* pSrcWidget, bool bRecursive = true);
    void                        SetWidgetVisible(const std::string& name, bool bVisible);
    void                        SetCenter(Sexy::Widget* pWidget, bool ignoreY = false);
    void                        setWindowCenter(Sexy::Widget* pWidget);

	//-------------------------------------------------------------------------
	// tools
	void									SetButtonListener(class PVZ2UIButton* pButton, int buttonID, class Sexy::ButtonListener* pListener);
	// ButtonListener
    virtual void                            ButtonPress(int i_id) override;
	virtual void							ButtonDepress(int i_id) override;
    void SetDarkBgAlpha(float alpha);
protected:
    bool										CreateFromLayout();
	void										AttachLawnApp();
	void										DetachLawnApp();
	
	void										InstantiateWidget_Recursively(Sexy::Widget* pRoot, VecUIWidgetType& vecWidgetType);
	
	void										AddCustomWidget(Sexy::Widget* pWidget);
protected:
	std::set<std::string>			m_resGroups;
	std::vector<Sexy::Widget*> m_CustomWidgets;
    bool                                    m_bDeleted;
    bool                                    m_bNeedDarkenBG;
    float                                   m_darkenBgAlpha = 0.5f;
    bool									m_bNeedAttachLawnApp;
};

}

#endif /* defined(__UIDialog_h_) */

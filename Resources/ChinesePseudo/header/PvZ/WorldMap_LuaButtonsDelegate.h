//
//  WorldMap_LuaButtonsDelegate.h
//  PlantsVersusZombies2
//
//  Created by Ruoqian, Chen on 06/03/2016.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef __WorldMap_LuaButtonsDelegate_h__
#define __WorldMap_LuaButtonsDelegate_h__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

// worldamp btn logic delegete
class WorldMap_LuaButtonsDelegate : public UIWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_LuaButtonsDelegate, UIWidget, RtClass);
    
    WorldMap_LuaButtonsDelegate();
    virtual ~WorldMap_LuaButtonsDelegate();
	
	void CheckActivated();
	virtual void Draw(Graphics* i_g) override;
    virtual void onUpdate() override;
    
    static WidgetContainer* GetBtnContainer(void);
    
    virtual bool IsMouseOver(const int i_mouseX, const int i_mouseY) override;
    virtual void OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    virtual void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    
    static void TouchBegan(const Sexy::Touch& i_touch, int x, int y);
    static void TouchMoved(const Sexy::Touch& i_touch, int x, int y);
    static void TouchEnded(const Sexy::Touch& i_touch, int x, int y);
    static void TouchesCanceled();
protected:
    virtual void onClickableStateChanged(void) override;
    virtual void onVisibleStateChange(bool i_visible) override;
private:
    void onWorldLoaded();
    
    static WidgetContainer* s_pBtnContainer;
};

// lua impl instance interface
class WorldMap_LuaButtonsImpl
{
public:
	WorldMap_LuaButtonsImpl();
	virtual ~WorldMap_LuaButtonsImpl();
    void RegisterHandler(int nHandler);
	void NotifyLua(const char *pszEvent, int nData);
private:
	int m_luaHandler;
};

#endif /* __WorldMap_LuaButtonsDelegate_h__ */

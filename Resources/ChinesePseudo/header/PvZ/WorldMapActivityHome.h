//
//  WorldMapActivityHome.hpp
//  PlantsVersusZombies2
//
//  Created by popcap on 7/27/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef WorldMapActivityHome_hpp
#define WorldMapActivityHome_hpp

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "WorldMapChooseDialog.h"
#include "WorldMapDefine.h"

class LevelofTheDayActivityInfo: public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(LevelofTheDayActivityInfo, Sexy::RtObject, RtClass);

	LevelofTheDayActivityInfo();

	int currentDay;
	int currentChance;
	int remainDays;
};

class WorldMapActivityHome : public Widget, Sexy::ButtonListener
{
public:
    WorldMapActivityHome(int activityIndex);
    ~WorldMapActivityHome();
    
    virtual void    ButtonPress(int i_id);
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(ModalFlags* theFlags, Graphics* i_g);
public:
    void InitDangerRoomTutotrial();
    void InitJoustTutotrial();
    virtual void InitView();
    virtual float GetItemLeftMargin();
    virtual float GetItemHInterval();
    virtual float GetItemRightMargin();
    virtual int GetBaseHeight();
    virtual int GetPanelHeight();
    virtual int GetItemCount();
    virtual UIWidget * GetAssociatedMainWidget();
    void    OnOK();
protected:
    virtual void PrepareActivityConfig();
    virtual void FillState();
    virtual int LayoutItems();
private:
    void KillMyChildren();
    void onCloseDialog();

private:
    std::unordered_map<int, PVZ2UIButton *> m_btnMap;
    std::unordered_map<int, std::string> m_resNameMap;
    std::unordered_map<int, uint8_t> m_openStateMap;
    std::unordered_map<int, uint8_t> m_attachStateMap;
    std::vector<int> m_activityOrderList;
    int             m_iBgWidth;
    int             m_iBgHeight;
};

// interface for worldmap choose dialog class
class InterfaceChooseDialog
{
public:
    virtual ~InterfaceChooseDialog() {}
    virtual bool GetHomeActivityPos(HomeActityType id, SexyVector2& pos) = 0;
    virtual std::string GetHomeActivityRes(HomeActityType id);
    virtual Widget* GetButtonById(HomeActityType id);
    virtual void ShowWidgetVisible(HomeActityType id, bool i_visible);
    virtual bool AllowInput();

protected:
    std::map<HomeActityType, SexyVector2> m_positionMap;
    std::unordered_map<int, std::string> m_resNameMap;
    std::unordered_map<int, PVZ2UIButton *> m_btnMap;
};

#endif /* WorldMapActivityHome_hpp */

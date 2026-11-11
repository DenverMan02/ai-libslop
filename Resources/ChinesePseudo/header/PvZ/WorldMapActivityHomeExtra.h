//
//  WorldMapActivityHome.hpp
//  PlantsVersusZombies2
//
//  Created by popcap on 7/27/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef WorldMapActivityHomeExtra_hpp
#define WorldMapActivityHomeExtra_hpp

#include "WorldMapActivityHome.h"


class WorldMapActivityHomeExtra : public Widget, Sexy::ButtonListener
{
public:
    WorldMapActivityHomeExtra(int activityIndex);
    ~WorldMapActivityHomeExtra();
    
    virtual void    ButtonPress(int i_id);
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(ModalFlags* theFlags, Graphics* i_g);
public:
    void InitDangerRoomTutotrial();
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
    bool            m_isRechargeBundle;
    bool			m_isDangerRoomBundle;
};

class AnniversaryGeneralConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(AnniversaryGeneralConfig, RtObject, RtClass);

    int gpi;
    std::vector<int> rb;
};

#endif /* WorldMapActivityHome_hpp */

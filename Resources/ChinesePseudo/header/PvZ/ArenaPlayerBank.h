//
//  ArenaPlayerBank.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-12.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaPlayerBank__
#define __PlantsVersusZombies2__ArenaPlayerBank__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "ArenaPrecompile.h"

class ArenaPlayerBank : public UIWidget
{
public:
    RT_CLASS_DEFINE(ArenaPlayerBank, UIWidget, RtClass);
    
    ArenaPlayerBank();
    virtual ~ArenaPlayerBank();
    
    // Public Interface (Inheritable)
    virtual void				Draw(Graphics* i_g) override;
    virtual void                onUpdate() override;
    
    void                        SetWinCup(int i_num) { m_winCup = i_num; }
    void                        SetLostCup(int i_num) { m_lostCup = i_num; }
    void                        SetWinCurrency(int i_num) { m_winCurrency = i_num; }
    void                        SetPlayerName(SexyString i_name) { m_playerName = i_name; }
    
protected:
    // Protected Interface (Inheritable)
    //OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
    OVERRIDE_STATE_UPDATE(WidgetState, Ready);
    
    virtual void				initLoadingResourcesGroupList() override;
    virtual void				registerForEvents() override;
    virtual void				unregisterForEvents() override;
private:
    bool    m_bEvilDavid;
    int     m_winMetal;
    int     m_winCup;
    int     m_lostCup;
    int     m_winCurrency;
    SexyString m_playerName;
    SexyString m_winCupTxt;
    SexyString m_lostCupTxt;
    SexyString m_winCurrencyTxt;
    SexyString m_winDisplayTxt;
    SexyString m_loseDisplayTxt;
    ArenaType  m_type;
    // Occupy
    SexyString m_levelTxt;
    SexyString m_occupyDisplayTxt;
    SexyString m_occupyCurrencyTxt;
    SexyString m_occupyMedalTxt;
    SexyString m_getCurrencyDisplayTxt;
    SexyString m_occupyName;
    SexyString m_getCurrencyTxt;
};

#endif /* defined(__PlantsVersusZombies2__ArenaPlayerBank__) */

//
//  BossChallenge.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.8.31
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _BossChallenge_h_
#define _BossChallenge_h_

#include "Widget.h"

namespace Lua {
    class CUIDialog;
}

class BossChallenge
{
public:
    static void                         RequestDatas();
    static bool                         IsHaveNewTips();
    static bool                         IsInBossBattle();
    static bool                         IsOpened();
    static Lua::CUIDialog*              ShowDialog();
    static void                         CloseDialog();
    static Lua::CUIDialog*              GetSingletonPtr();
    static void                         InitDialog(Lua::CUIDialog* pDlg);
    static void                         RequestBuyChallenge();
    static void                         ResponseRankList(const std::string& i_json);
    static void                         SetButtonsDisabled(bool i_bDisabled);
    static void							ShowTab(int i_id);
    static void							CloseActivityCollection();
    
    BossChallenge();
    ~BossChallenge();
    void OnBuyItemFinish(class MsgResultInfo* io_result, const class S2C_ICloud_GetConsumeGemInfo* item, const class S2C_PlayerInfo* pGemChanged);
    void OnActiveItemRefresh(class ActiveItem* item);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

#endif

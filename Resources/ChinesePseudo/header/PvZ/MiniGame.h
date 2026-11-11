//
//  MiniGame.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.8.31
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _MiniGame_h_
#define _MiniGame_h_

#include "Widget.h"

namespace Lua {
    class CUIDialog;
}

class MiniGame
{
public:
    static void                         RequestDatas();
    static bool                         IsHaveNewTips();
    static bool                         IsOpened();
    static Lua::CUIDialog*              ShowDialog();
    static void                         CloseDialog();
    static Lua::CUIDialog*              GetSingletonPtr();
    static void                         InitDialog(Lua::CUIDialog* pDlg);
    static void                         ResponseRankList(const std::string& i_json);
    static void                         SetButtonsDisabled(bool i_bDisabled);
    static void							ShowTab(int i_id);
    
    MiniGame();
    ~MiniGame();
    void OnActiveItemRefresh(class ActiveItem* item);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

#endif

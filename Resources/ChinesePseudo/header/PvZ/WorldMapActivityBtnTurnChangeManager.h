//
//  WorldMapActivityBtnTurnChangeManager.hpp
//  PlantsVersusZombies2
//
//  Created by popcap on 7/27/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef WorldMapActivityBtnTurnChangeManager_hpp
#define WorldMapActivityBtnTurnChangeManager_hpp

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "WorldMapChooseDialog.h"
#include "CUIDialog.h"

struct stActivity_iconInfo
{
    int m_nActivityId = 0;
    int m_nPriority = 0;
    int m_nlineNum = 1;
    bool m_open = false; // check activity is open
};

enum Btn_State
{
    Btn_static,
    Btn_moving,
};

class ActivityTurnChangeConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(ActivityTurnChangeConfig, RtObject, RtClass);
	ActivityTurnChangeConfig() : m_fSpaseTimeConfig(0) {}

public:
	std::vector<stActivity_iconInfo> m_vecOriginalAcOrList;
    float m_fSpaseTimeConfig;
};

class WorldMapActivityBtnTurnChangeManager: public LazySingleton<WorldMapActivityBtnTurnChangeManager>
{
public:
    WorldMapActivityBtnTurnChangeManager();
    virtual ~WorldMapActivityBtnTurnChangeManager();
    void loadData(const ActivityTurnChangeConfig& activityTurnChangeConfig);
    
    void update();
    void setIsPause(bool isPause);
    bool getIsPause() const;
    
    void setIsInit(bool isInit);
    bool getIsInit() const { return m_bIsInit; };

    void setVecLine1(const SexyVector2& p1);
    void setVecLine2(const SexyVector2& p1);

    bool isAllLiaded();
    void setIsLoaded(int id, bool isLoaded);

    bool isActivityOpened(int id);
    bool isActivityOpened(int id, bool op);
    void        onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void        onNotifyPurchasedSpecialOffer();
    void updateData();
    void clear();
     void OnLuaNotify(const std::string& rLuaEvent);
     void setFirstInit(bool bIsFirstInit);
     void initButtonTurn();

private:
    void doFirstLineBtnTurn();
    void doSecondLineBtnTurn();
    void doCurBtnWidget(int lineNum, int activityId);
   
    void doNextFirstLineBtnTurn();
    void doNextSecondLineBtnTurn();
    void doNextBtnWidget(int lineNum, int activityId);

    void toNextBtnWidget(int lineNum);

    void initButtonFirstIcon(int lineNum, int activityId);
    
    // zhousen for new icon
    void InitNewIcon_Btn(int activityId);
    void Update_NewIcon();
    void NewIconBtnChange(int activityId);
    std::string GetWidgetSheetName(int activityId);
    bool CheckUniverseMap();
    bool CheckGame();

    // new icon
    void HideAllWidgets();
    
private:
    std::vector<stActivity_iconInfo> m_firstLineActivityOrderList;
    std::vector<stActivity_iconInfo> m_secondLineActivityOrderList;
    int m_nFirstLineCurAcIndex;
    int m_m_nSecondLineCurAcIndex;
    pvztime_t m_stateFirstTime;
    pvztime_t m_stateSecondTime;
    Btn_State m_curFirstBtnState;
    Btn_State m_nextFirstBtnState;
    Btn_State m_curSecondBtnState;
    Btn_State m_nextSecondBtnState;
    float m_fSpaseTime;
    pvztime_t m_stateChangeTime;
public:
    bool m_bIsPause;
    bool m_bIsInit;
    SexyVector2 m_vecLine1;
    SexyVector2 m_vecLine2;
    std::map<int, bool> m_mapIsLoaded;
    bool m_bIsFirstInit;
    bool m_bIsAlreadyLoadData;
    bool m_bShowWorldPackBtn;
    UIWidget* m_curBtnWidget;// new icon
    Lua::CUIDialog* m_curLuaWidget;
};

#endif /* WorldMapActivityBtnTurnChangeManager_hpp */

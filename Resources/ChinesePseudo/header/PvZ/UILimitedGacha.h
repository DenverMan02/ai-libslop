
#ifndef _UI_LIMITED_GACHA_H_
#define _UI_LIMITED_GACHA_H_

#include "DNode/DNodeWidget.h"

class UILimitedGacha:public DNodeWidget
{
public:
    static bool createWithNetwork();
    
    static UILimitedGacha* create(bool focus = true);
    
    static void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    static void onMsgErrorRequest(int erroId, const std::string& i_reqID);
    
    static bool isActive(){return s_isActive;}
    static void setUnactive();
    static std::string GetGachaMainPlantName();
    
    virtual ~UILimitedGacha();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    void loadWithNetMessage();
    
    void updatePlantShowFromNetwork(const std::vector<int>& plantInfos,bool isFirstGacha1,bool isFirstGacha10);
    
    void CancelBuy();
    
    bool gachaAgain();
    
    bool isFirstGacha1() const {return m_isFirstGacha1;}
    bool isFirstGacha10() const {return m_isFirstGacha10;}
    
    void showGacha1Flag(bool isFirstGacha1);
    void showGacha10Flag(bool isFirstGacha10);
    
    void DoConfirmDialog(float i_cost);
    void ConfirmBuyGacha();

    void UpdateButtons();

    float GetTempCost() { return m_tempCost; }

public:
    static UILimitedGacha* s_pWidgetHandler;
    static bool s_isActive;
private:
    float  m_leftTime = 0;
    float  m_cost = 0;
    int    m_actId = 0;
    bool   m_isFirstGacha1 = false;
    bool   m_isFirstGacha10 = false;
    float m_tempCost = 0;
    int m_tempActId = 0;
};

#endif

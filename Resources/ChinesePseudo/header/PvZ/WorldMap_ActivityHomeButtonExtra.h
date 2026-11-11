#ifndef WorldMap_ActivityHomeButtonExtra_h
#define WorldMap_ActivityHomeButtonExtra_h

#include "UIEasyButtonWidget.h"
#include "ActivityManager.h"

class WorldMap_ActivityHomeButtonExtra :public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_ActivityHomeButtonExtra, UIEasyButtonWidget, RtClass);
    
    WorldMap_ActivityHomeButtonExtra();
    virtual ~WorldMap_ActivityHomeButtonExtra();
    
    void WaitForTutorialClick()
    {
        m_clicked = false;
    }
    bool WasClickedForTutorial()
    {
        return m_clicked;
    }
    void RequestData(ActivityTypeID i_typeId);
public:
    static bool CheckVisibility(bool i_init = false);
    static bool CheckDrawDollActivityTips();
    static bool CheckFirstRechargeActivityTips();
    
protected:
    bool CheckActivityTips();
    
    void Draw(Sexy::Graphics* i_g) override;
    void SetNotice(bool notice);
    
protected:
    void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void                onMsgErrorRequest(int erroId, const std::string& i_reqID);
    void                onNotifyStaticConfig(int result, const class S2C_StaticConfig* data);
    
private:
    void                OnKillChooseDialog(UIWidget* pButton);
    void                KillChooseDialog();
    void                CheckTutorialAndCancel();
    
    bool	            m_clicked;
    bool		    	m_bRequested = false;
};

#endif

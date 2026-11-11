/*
 * WorldMap_DailyActivityButton.h
 *
 *  Created on: 2021-3-22
 *      Author: zhousen
 */

#ifndef WORLDMAP_DAILYACTIVITYBUTTON_H_
#define WORLDMAP_DAILYACTIVITYBUTTON_H_


#include "UIEasyButtonWidget.h"
#include "ActivityManager.h"


class WorldMap_DailyActivityButton : public UIEasyButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_DailyActivityButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_DailyActivityButton();
    virtual ~WorldMap_DailyActivityButton();
    
    void WaitForTutorialClick() { m_clicked = false; }
    bool WasClickedForTutorial() { return m_clicked; }
    void RequestData(ActivityTypeID i_typeId);
    void OnTouch();

public:
    static bool CheckVisibility(bool i_init = false);
    
public:
    bool CheckActivityTips();
    void Draw(Sexy::Graphics* i_g) override;
    void SetNotice(bool notice);

protected:
    virtual void onLoadComplete() override;
    
protected:
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void onMsgErrorRequest(int erroId, const std::string& i_reqID);
    
private:
    void OnKillChooseDialog(UIWidget* pButton);
    void KillChooseDialog();
    void CheckTutorialAndCancel();
    
    bool m_clicked;
    bool m_bRequested = false;
};


#endif /* WORLDMAP_DAILYACTIVITYBUTTON_H_ */

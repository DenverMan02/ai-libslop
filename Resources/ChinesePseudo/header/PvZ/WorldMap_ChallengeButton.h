/*
 * WorldMap_ChallengeButton.h
 *
 *  Created on: 2021-3-22
 *      Author: zhousen
 */

#ifndef WORLDMAP_CHALLENGEBUTTON_H_
#define WORLDMAP_CHALLENGEBUTTON_H_

#include "UIEasyButtonWidget.h"

class WorldMap_ChallengeButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_ChallengeButton, UIEasyButtonWidget, RtClass);

    WorldMap_ChallengeButton();
    virtual ~WorldMap_ChallengeButton();

    void WaitForTutorialClick() { m_clicked = false; }
    bool WasClickedForTutorial() { return m_clicked; }
//    void RequestData(ActivityTypeID i_typeId);
    void RequestData(int i_typeId);
    void OnTouch();

public:
    static bool CheckVisibility(bool i_init = false);

protected:
    bool CheckActivityTips();
    void Draw(Sexy::Graphics* i_g) override;
    void SetNotice(bool notice);

protected:
    virtual void onLoadComplete() override;

protected:
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void onMsgErrorRequest(int erroId, const std::string& i_reqID);
    void onNotifyStaticConfig(int result, const class S2C_StaticConfig* data);

private:
    void OnKillChooseDialog(UIWidget* pButton);
    void KillChooseDialog();
    void CheckTutorialAndCancel();

    bool m_clicked;
    bool m_bRequested = false;
};

#endif /* WORLDMAP_CHALLENGEBUTTON_H_ */

//
//  TimeChallengeEndLevelUI.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/8/24.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef TimeChallengeEndLevelUI_h
#define TimeChallengeEndLevelUI_h

#include "Widget.h"

class TimeChallengeEndLevelUI : public Widget, public ButtonListener
{
public:
    typedef Sexy::Delegate1<TimeChallengeEndLevelUI*> Callback;
public:
    TimeChallengeEndLevelUI();
    virtual ~TimeChallengeEndLevelUI();
    virtual void Draw(Graphics* i_g) override;
    virtual void Update() override;
    virtual void Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void	ButtonDepress(int theId) override;
    bool IsFinished();
    void SetScore(int score);
    void SetContinueCallBack(const Callback& callback);
private:
    void OnAnimationFinish(const std::string& label);
    void DrawScore(Graphics* i_g);
private:
    class PopAnimRig* m_endLevelRig = nullptr;
    class PVZ2UIButton* m_continueBtn = nullptr;
    int  m_score = 0;
    bool m_finished = false;
    SexyVector2 m_posOffset;
    Callback m_callback;
    
};

#endif /* TimeChallengeEndLevelUI_h*/

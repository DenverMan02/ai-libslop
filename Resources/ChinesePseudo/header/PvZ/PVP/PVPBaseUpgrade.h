//
//  PVPBaseUpgrade.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/1/4.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PVPBaseUpgrade_h
#define PVPBaseUpgrade_h

#include "Widget.h"
#include "MagentoService.h"
#include "PVZ2UIButton.h"
#include "PVPDatas.h"
#include "PVPFinishButton.h"

class PVPBaseUpgrade : public Sexy::Widget, public ButtonListener
{
public:
    PVPBaseUpgrade(PVPLabItemType type);
    ~PVPBaseUpgrade();
protected:
    void Draw(Graphics* i_g) override;
    void ButtonDepress(int i_id) override;
private:
    void DrawTimeLeft(Graphics* i_g, int time);
    void DrawCompleteButton(Graphics* i_g, int price);
    void DrawUpgradeButton(Graphics* i_g, int price);
    void DrawCurrentBox(Graphics* i_g, int left, int top, int current, Sexy::Image* icon);
    void DrawNextLevel(Graphics* i_g, int left, int top, int current, int next, Sexy::Image* icon, bool showText);
    void DrawInstruction(Graphics* i_g);
    void DrawRewardPerHour(Graphics* i_g, int left, int top, int count);
    void DrawProcessBar(Graphics* i_g, int left, int top, int current, int max);
    void DrawUpagradeReady(Graphics* i_g, int level);
    void DrawLevel(Graphics* i_g, int left, int top, int level);
    void DrawNeedBaseLevel(Graphics* i_g, int level);
    void DrawCurrentAndNextState(Graphics* i_g, int currentLevel);
    void DrawMaxState(Graphics* i_g, int maxLevel);
    void DrawUnlockZombie(Graphics* i_g, const std::vector<std::string>& unlockZombie);
    void BeginPVPUpgradeSuccess();
    void ConfirmCompletePVPUpgrade(int buttonID);
    void GetPVPCompleteUpgradeGemSuccess(int gem);
    void GetPVPCompletePVPUpgrade(class S2C_PVPCompleteUpgradeData* pData);
    int GetMaxLevel();
    int GetTimeLeft();
    int GetUpgradeCost(int level);
    Rect GetUpgradeButtonRect();
    Sexy::Image* GetTitle();
    Sexy::Image* GetBackImage();
    Sexy::Image* GetIconInBox1();
private:
    int m_dialogLeft;
    int m_dialogTop;
    PVPLabItemType m_type;
    PVZ2UIButton* m_upgradeButton;
    PVPFinishButton* m_completeButton;
    class PVPCancelUpgradeBtn*  m_pCancelButton = nullptr;
};


#endif /* PVPBaseUpgrade_h */

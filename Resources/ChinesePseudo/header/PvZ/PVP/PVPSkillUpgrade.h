//
//  PVPSkillUpgrade.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/3/10.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PVPSkillUpgrade_h
#define PVPSkillUpgrade_h
#include "PVZ2UIButton.h"
#include "Widget.h"
#include "ZombiePVPSkill.h"
#include "PVPFinishButton.h"

class PVPSkillUpgrade : public Sexy::Widget, public ButtonListener
{
public:
    class SkillButton : public PVZ2UIButton
    {
    public:
        void Draw(Sexy::Graphics* i_g) override;
        void Draw(Sexy::Graphics* i_g, const Rect& rect, bool select);
        void SetLevel(int level);
        void SetSelect(bool select);
        void SetSkill(const std::string& name);
        const std::string& GetSkill();
        SkillButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
        ~SkillButton();
    private:
        void DrawSkillIcon(Sexy::Graphics* i_g, const Rect& rect);
        void DrawLock(Graphics* i_g, const Rect& rect);
        void DrawLevel(Sexy::Graphics* i_g, int level, const Rect& rect);
    private:
        bool m_select;
        int m_level;
        std::string m_skillName;
    };
public:
    PVPSkillUpgrade();
    ~PVPSkillUpgrade();
protected:
    void Draw(Graphics* i_g) override;
    void ButtonDepress(int i_id) override;
private:
    int GetCurrentSkillCompleteTime();
    void SetCurrentSkill(int index);
    void DrawTimeLeft(Graphics* i_g, float time);
    void RefreshSkillButton();
    void RefreshUpgradeButton();
    void DrawUpgradeTip(Graphics* i_g, const Rect& rect);
    void DrawLeftTopSection(Graphics* i_g);
    void DrawRightTopSection(Graphics* i_g);
    void BeginPVPUpgradeSuccess();
    void ConfirmCompletePVPUpgrade(int buttonID);
    void GetPVPCompleteUpgradeGemSuccess(int gem);
    void GetPVPCompletePVPUpgrade(class S2C_PVPCompleteUpgradeData* pData);
    void onPVPLabRefresh();
    Rect GetBottomSectionRect();
    Rect GetLeftTopSectionRect();
private:
    int m_dialogLeft;
    int m_dialogTop;
    PVZ2UIButton* m_pControlButton;
    PVPFinishButton* m_finishButton;
    std::vector<SkillButton*> m_skillButtons;
    int m_currentSkillIndex;
    PVPZombieData* m_currentSkillData;
    ZombieTypePtr     m_currentSkillType;
    ZombiePVPSkillProps* m_currentSkillProps;
    class PVPCancelUpgradeBtn*  m_pCancelButton = nullptr;
};


#endif /* PVPSkillUpgrade_h */

//
//  PVPZombieLevelUpDlg.hpp
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 16/1/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVPZombieLevelUpDlg_hpp
#define PlantsVersusZombies2_PVPZombieLevelUpDlg_hpp

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PrimeTextWidget.h"
#include "ZombieAnimRig.h"
#include "AlmanacWidget.h"
#include "SeedPacketUtils.h"
#include "NetworkMgr.h"
#include "PVPFinishButton.h"

class PVPZombieItemButton : public Sexy::ButtonWidget
{
    
public:
    
    PVPZombieItemButton(int i_id, ButtonListener* i_listener, ObjectTypeDescriptorPtr i_objectType);
    
    void Draw(Sexy::Graphics* i_g) override;
    
    bool GetSelectStatue() { return m_bSelected; }
    
    void SetSelectStatue(bool bSelect) { m_bSelected = bSelect; }
    
    ObjectTypeDescriptorPtr m_objectType;
    
private:
    
    void DrawItemComponse(Sexy::Graphics* i_g, Sexy::Rect srcRect, Sexy::Point srcOffset, Sexy::Point desOffset = {0, 0});
    
    void drawZombie(Graphics* i_g);
    
private:
    
    const PacketRenderData* m_pRenderData;
    
    bool m_bSelected;
};


class PVPZombieChooser : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    PVPZombieChooser(const std::string& strCurrentName);
    virtual ~PVPZombieChooser();
    
    virtual void Initialize(int i_x, int i_y, int i_width, int i_height);
    virtual void ButtonDepress(int i_id);
    
    int GetScrollOffset() const;
    
    std::string& GetCurrentZombieName() { return m_strCurrentZombieName; }
    
private:
    
    std::string m_strCurrentZombieName;
    std::vector<PVPZombieItemButton*> m_vZombieButtons;
};


class PVPZombieLevelUpContent
: public Widget
{
    
public:
    
    PVPZombieLevelUpContent(const std::string& strName);
    
    ~PVPZombieLevelUpContent();
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
private:
    
    void InitView();
    
    void AddZombieBaseInfo();
    
    void DrawWord(Sexy::Graphics* i_g);
    
private:
    
    std::string m_strZombieName;
};

class PVPZombieLevelUpTitle
: public Widget
, public Sexy::ButtonListener
{
    
public:
    
    PVPZombieLevelUpTitle(const std::string& strName);
    
    ~PVPZombieLevelUpTitle();
    
    void Update() override;
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    void ButtonPress(int i_id) override;
    
    void ButtonDepress(int i_id) override;
    
    void SetLevelUpStatue(bool bLevelUping) { m_bLevelUping = bLevelUping; }
    
    bool GetLevelUpStatue() { return m_bLevelUping; }
    
    void BeginPVPUpgradeSuccess();
    PVPFinishButton* GetFinishButton() { return m_finishButton; }
private:
    
    void InitView();
    
    void CreateZombieAnimation();
    
    void ReleaseZombieAnimation();
    
    void DrawZombieAnimation(Sexy::Graphics* i_g);
    
    void DrawZombieRank(Sexy::Graphics* i_g);
    
    void DrawZombieCNName(Sexy::Graphics* i_g);
    
    void DrawCDTime(Sexy::Graphics* i_g);
    
    void RefreshLevelUpButton();
    
    bool IsPVPTopicIn();
    
private:
    
    ZombieAnimRig* m_pZombieAnimation;
    
    std::string m_strZombieName;
    
    Sexy::Rect m_ZombieRigRect;
    
    bool m_bLevelUping;
    
    PVZ2UIButton* m_pControlButton;
    PVPFinishButton* m_finishButton;
    class PVPCancelUpgradeBtn*  m_pCancelButton = nullptr;
};

class PVPZombieLevelUpMain
: public Widget
, public Sexy::ScrollWidgetListener
{
    
public:
    
    PVPZombieLevelUpMain(const std::string& strZombieName);
    
    ~PVPZombieLevelUpMain();
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override { }
    
    void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override { }
    
    void RefreshMainView(const std::string& strZombieName);
    
private:
    
    void InitView(const std::string& strZombieName);
    
    void AddZombiesSeedScroll();
    
    void onPVPLabRefresh();
    
    void GetDoPVPCompleteUpgradeGemSuccess(int gem);
    
    void ConfirmCompletePVPUpgrade(int buttonID);
    
    void OnGetPVPCompletePVPUpgrade(S2C_PVPCompleteUpgradeData* pData);
    
    void RecvBeginPVPUpgradeSuccess();
    
private:
    
    PVPZombieLevelUpTitle* m_pPVPZombieLevelUpTitle;
    
    PVPZombieLevelUpContent* m_pPVPZombieLevelUpContent;
    
    std::string m_strZombieName;
};

class PVPZombieLevelUpDlg
: public Widget
, public Sexy::ButtonListener
{
    
public:
    
    PVPZombieLevelUpDlg();
    
    ~PVPZombieLevelUpDlg();
    
    void Update() override;
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    void ButtonPress(int i_id) override;
    
    void ButtonDepress(int i_id) override;
    
private:
    
    void InitView();
    
    void AddCloseButton();

};

#endif /* PlantsVersusZombies2_PVPZombieLevelUpDlg_hpp */

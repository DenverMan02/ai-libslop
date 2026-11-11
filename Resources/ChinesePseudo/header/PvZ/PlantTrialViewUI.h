//
//  PlantTrialViewUI.h
//  PlantsVersusZombies2
//
//  Created by Eric Nan on 15-4-03.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantTrialViewUI_h
#define PlantsVersusZombies2_PlantTrialViewUI_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"
#include "MagentoService.h"
#include "PVZ2UIPlantCard.h"
#include "SettingsDialog.h"
#include "FestivalManager.h"
#include "PlantType.h"
#include "PVZ2UIPlantCard.h"
#include "PlantLevelUpListView.h"
#include "Effect_PopAnim.h"

class PlantTrialViewUI : public Sexy::Widget, Sexy::ButtonListener
{
public:
    PlantTrialViewUI(const std::string & sPlantName);
    ~PlantTrialViewUI();
    
    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(ModalFlags* theFlags, Graphics* g) override;
    void onCloseDialogWithSuccess();
    void onCloseDialog();
    void OnPaidWithMoney();
    void Update() override;
private:
    
    void ButtonPress(int i_id) override;
    
    void ButtonDepress(int i_id) override;
    
    void InitView();
    
    void DrawTimeLeft(Sexy::Graphics* i_g);
    
    void AddBuyButton();
    
    void DrawPlantDesc(Sexy::Graphics* i_g);
    
    void BuyWithGem(int iGem);
    
    void BuyWithGem(int i_plantid, int i_gems, int i_toLevel);
    void BuyWithMoney(const std::string& strSKU);
    void OnPlantTrialPaid(bool i_success);
    
    void OnBuySuccess();
    
    int GetNeedTotalPiece(const std::string& strPlantName, int iDesLevel);
    
    void AddBuyDialog();
    
    void CancelBuy();
    
    void ConfirmBuy();
    void ShowOwnPlantTip();
    void DrawDiscount(Sexy::Graphics* pGraphics);
    void DrawRewardValue(Sexy::Graphics* pGraphics);
    void DrawLimitTimeBuy(Sexy::Graphics *i_g);
    void SetCurrentPlant(int index);
    void UpdateView();
    void UpdateDot();
    void UpdateBuyText();
    void DrawDot(Sexy::Graphics* i_g);
    int GetPlantCount();
    int GetPlantIndex(const std::string& plant);
    void OnPlantedNarrationFinished();
    void DrawTimeLimitNumber(Sexy::Graphics* i_g, int number, int x, int y);
    void RemoveCurrentPlant();
    void EnableInput(bool enable);
    void AddSwitchButton();
    void CreateCurtain();
    Effect_PopAnim* CreatePageTearEffect();
    void OnAnimationFinish(const std::string& label);
    void OnPopAnimCommand(const std::string& i_animName,
                          pvztime_t i_time,
                          const std::string& i_command,
                          const std::string& i_params);
private:
    int m_iBaseX;
    int m_iBaseY;

    int m_currentIndex;
    int m_nextIndex;
    class TrialData* m_currentPlant;
    class PlantTrialCD* m_currentCD;
    std::vector<std::string> m_SkuPosted;
    
    PopAnimRig* m_curtain;
    Effect_PopAnim* m_pageTear;
    
    PVZ2UIButton* m_buy;
    PVZ2UIButton* m_left;
    PVZ2UIButton* m_right;
    class UIWidgetAnim* m_curtainContainer;
    RtWeakPtr<Image> m_discount;
    RtWeakPtr<Image> m_plantNameImage;
    PlantLevelUpListView* m_pPlantLevelUpListView;
};

class PlantTrialShowDialog : public Sexy::Widget
{
public:
    
    PlantTrialShowDialog();
    ~PlantTrialShowDialog();
    
    void Draw(Sexy::Graphics* i_g) override;
    
private:
    
    void DrawShowDialog(Sexy::Graphics* i_g);
    
private:
    
    bool m_bShowDialogScaling;
    pvztime_t m_iStartDialogTime;
    Sexy::PrimeTextWidget* m_pDialogTextWidget;
    
};

//------------------------------------------------------------------------------------------

#endif

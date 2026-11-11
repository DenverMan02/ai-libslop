//
//  TrainingCampZombieDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.29
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVPItemWidgets_h_
#define __PlantsVersusZombies2__PVPItemWidgets_h_

#include "Widget.h"
#include "ButtonListener.h"
#include "UIListener.h"
#include "UIDialog.h"
#include "PVZ2UIButton.h"

class TrainingCampZombieDlg;
//---------------------------------------------------------
// TrainingItemWidget
// Need resource group: UI_PVP_Training, UIImages,
//---------------------------------------------------------
class TrainingItemWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    enum ShowMode
    {
        ShowMode_InTraining,
        ShowMode_InSelling,
        ShowMode_InMap,
        ShowMode_JustShow,
    };
public:
    TrainingItemWidget(ShowMode i_mode);
    ~TrainingItemWidget();
    virtual void		Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void        Draw(Sexy::Graphics* i_g) override;
    virtual void        Update() override;
    void                TouchBegan(const Sexy::Touch& i_touch) override;
    
    void                SetTypeName(const std::string& i_type);
    const std::string&  GetTypeName() const { return m_typeName; }
    
    // ButtonListener
    virtual void		ButtonDepress(int i_id) override;
    
    void                SetSellNum(int iVal);
    int                 GetSellNum() { return m_sellNum; }
    int                 GetNum() { return m_num; }
    
    void                SetTrainingCampZombieDlg(TrainingCampZombieDlg* trainingCampZombieDlg);
    void                SetShowNum(int val) {m_showNum = val;}
    void                PlayFinishedEffect();
    
protected:
    class PVZ2UIButton* m_btnReduce;
    std::string         m_typeName;
    int                 m_num;
    int                 m_sellNum;
    float               m_endTime;
    float               m_totalSeconds;
    const class PacketRenderData* m_pRenderData;
    ShowMode            m_showMode;
    int                 m_showNum;
    class Effect_PopAnim*     m_pEffectFinised = NULL;
    
    TrainingCampZombieDlg* m_pTrainingCampZombieDlg;
};

//---------------------------------------------------------
// ZombieItemWidget
// Need resource group: UI_PVP_Training, UIImages,
//---------------------------------------------------------
class ZombieItemWidget : public Sexy::Widget
{
public:
    ZombieItemWidget(const std::string& strType);
    ~ZombieItemWidget();
    virtual void		Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void        Draw(Sexy::Graphics* i_g) override;
    virtual void        Update() override;
    void                TouchBegan( const Sexy::Touch& i_touch ) override;
    
    void                SetType(const std::string& strType);
    void                SetTrainingCampZombieDlg(TrainingCampZombieDlg* trainingCampZombieDlg);
    
    void                SetTips(const SexyString& str) { m_strTips = str; }
    void                SetLocked(bool setting) { m_bLocked = setting; }
    
protected:
    Sexy::Rect          m_btnInfoRect;
    std::string         m_typeName;
    int                 m_num;
    int                 m_trainCost;
    int                 m_buyCost;
    bool                m_bLocked;
    SexyString          m_strTips;
    const class PacketRenderData* m_pRenderData;
    
    TrainingCampZombieDlg* m_pTrainingCampZombieDlg;
};

//---------------------------------------------------------
// PVPCurrencyBar
//---------------------------------------------------------
class PVPCurrencyBar : public UI::Dialog
{
public:
    PVPCurrencyBar();
    virtual ~PVPCurrencyBar();
    virtual std::string         GetLayoutName() {return "currencyBar";}
    // ButtonListener
    virtual void                ButtonDepress(int i_id);
    virtual void                Update();
    
    void                        InitView();
    void                        RefreshCurrency();
    
protected:
    void                        onPVPCurrencyChanged();
    void                        onGemCurrencyChanged(int i_amount);
    
protected:
    class UIWidgetText*         m_pTextMedal;
    class UIWidgetText*         m_pTextCoin;
    class UIWidgetText*         m_pTextGem;
};

//---------------------------------------------------------
// PVPCancelUpgradeBtn
//---------------------------------------------------------
class PVPCancelUpgradeBtn : public PVZ2UIButton
{
public:
    PVPCancelUpgradeBtn(int i_id, Sexy::ButtonListener* i_listener);
    
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    void OnMessageCallback(class UIMessageBox* box, int buttonID);
};

//---------------------------------------------------------
namespace Message
{
    void TrainingItemReduceClicked(class TrainingItemWidget* pItem);
}

#endif /* defined(__PlantsVersusZombies2__PVPItemWidgets_h_) */

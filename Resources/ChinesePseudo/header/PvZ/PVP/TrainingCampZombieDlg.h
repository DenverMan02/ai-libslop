//
//  TrainingCampZombieDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.29
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TrainingCampZombieDlg__
#define __PlantsVersusZombies2__TrainingCampZombieDlg__

#include "UISingletonDialog.h"
#include "UIListener.h"
#include "UIWidgetAnim.h"

//---------------------------------------------------------
class TrainingCampZombieDlg : public UISingletonDialog<TrainingCampZombieDlg>, public UI::PageListener
{
public:
    TrainingCampZombieDlg();
    virtual ~TrainingCampZombieDlg();
    virtual bool							OnCreate();
    virtual std::string                 GetLayoutName() { return "TrainingCampZombie"; }
    virtual void							Draw(Sexy::Graphics* i_g);
    virtual void							DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void                        Update();
    
    // ButtonListener
    virtual void							ButtonDepress(int i_id);
    virtual void                        PageChanged();
    
    void                                RefreshAll();
    void                                RefreshDesc();
    void                                RefreshTraining();
    void                                RefreshSell();
    void                                RefreshTotalSeconds();
    
    void                                SetSelling(bool setting);
    
    void                                onTutorialTrainZombieClick();
    int                                 getTutorialTrainZombieCount() {return m_iTutorialTrainCount;}
    void                                onPVPTutorialTrainingFinished();
    
protected:
    void                                checkPageBtns();
    void                                initTrainedEffect();
    void                                playTrainedEffect();
    void                                onTrainedEffectStopped();
    
    void                                onTrainingItemReduceClicked(class TrainingItemWidget* pItem);
    void                                onSellConfirmCallback(int iResult);
    void                                onPVPTrainingSellResult(bool i_success);
    void                                onPVPTrainingZombieChanged(bool bPlayEffect);
    void                                onPVPTrainingFinishGems(int i_gems);
    void                                onFinishAtOnceCallback(int iResult);
    
private:
    class UIScrollControl*               m_pScrollTraining;
    class UITabControl*                 m_pTabControl;
    std::vector<class TrainingItemWidget*>  m_trainingItems;
    std::vector<class TrainingItemWidget*>  m_sellItems;
    Sexy::Widget*                       m_pPanelZombie;
    Sexy::Widget*                       m_pPanelSell;
    class UIWidgetImage*                m_pProgress;
    class UIPage*                       m_pPageWidget;
    class PVZ2UIButton*                 m_pBtnLeft;
    class PVZ2UIButton*                 m_pBtnRight;
    class PVZ2UIButton*                 m_pBtnFinishAtOnce;
    class PVPFinishButton*              m_pBtnFinishAtOnce2;
    bool                                m_bSelling;
    float                               m_timerLast;
    int                                 m_iConfirmGems;
    bool                                m_bOutSpace;
    
    int                                 m_iTutorialTrainCount;
    bool                                m_bHighlightClose;
    
    class TrainedEffectWidget*          m_pTrainedEffect = NULL;
    
};

class TrainedEffectWidget : public UIWidgetAnim
{
public:
    TrainedEffectWidget();
    virtual ~TrainedEffectWidget();
    virtual void        Draw(Sexy::Graphics* i_g) override;
    virtual void        Update() override;
    
    class DeviceImage*  GetDeviceImage() { return m_pDeviceImage; }
    void                SetStopCallback(const Sexy::Delegate0& listener) { m_stopCallback = listener; }
    void                PlayEffect(const SexyVector2& from, const SexyVector2& to);
protected:
    void                onAnimStopped(const std::string &i_animName);
protected:
    class DeviceImage*      m_pDeviceImage = NULL;
    Sexy::Delegate0         m_stopCallback;
    SexyVector2             m_moveTo;
    SexyVector2             m_moveCurrent;
    SexyVector2             m_moveStep;
    int                     m_status = 0;
    float                   m_imageScale = 1.0f;
    float                   m_imageAlpha = 1.0f;
};


#endif /* defined(__PlantsVersusZombies2__TrainingCampZombieDlg__) */

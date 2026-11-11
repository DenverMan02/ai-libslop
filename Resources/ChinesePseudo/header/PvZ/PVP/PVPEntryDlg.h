//
//  PVPEntryDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.1.15
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _PVPEntryDlg_h_
#define _PVPEntryDlg_h_

#include "UISingletonDialog.h"

class PVPEntryDlg : public UISingletonDialog<PVPEntryDlg>
{
public:
	PVPEntryDlg();
	virtual ~PVPEntryDlg();
	virtual bool                OnCreate();
	virtual std::string         GetLayoutName() { return "PVPEntry"; }
    virtual void                Draw(Sexy::Graphics* i_g);
    virtual void                DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void                Update();

	// ButtonListener
	virtual void                ButtonDepress(int i_id);
    
    void                        RefreshData();
    void                        ShowRankMonthRewardMessage();
    void                        OnRankMonthRewardCallback(class UIMessageBox* box, int buttonID);

    
    void                        onTutorialAnimDone(const std::string &i_animName);
    void                        onTutorialAnim1Done(const std::string &i_animName);
    void                        onPVPNarrationFinished();
protected:
    void                        onPVPLogin(bool i_success);
    
    void                        setTimer(const std::string& prefix, float endTime);

private:
    class PVPCurrencyBar*       m_pCurrencyBar;
    class UIWidgetText*         m_pCupText;
    class PVZ2UIButton*        m_pRankImage;
    bool                        m_bNeedUpdate;
    int                         m_clickedBtn;
    
    RtWeakPtr<class PopAnimRig> 	m_tutorialAnim;
    bool                            m_tutorialAnimFinish;
    RtWeakPtr<class PopAnimRig> 	m_tutorialAnim1;
    bool                            m_tutorialAnim1Finish;
    bool                            m_deletedAnim;
    bool                            m_depressDisable = false;
    
};


#endif

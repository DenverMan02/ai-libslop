//
//  PlaybackDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.11.20.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _PlaybackDlg_h_
#define _PlaybackDlg_h_

#include "UISingletonDialog.h"
#include "PlaybackData.h"

class PlaybackDlg : public UISingletonDialog<PlaybackDlg>
{
public:
	PlaybackDlg();
	virtual ~PlaybackDlg();
	virtual bool            OnCreate();
	virtual std::string     GetLayoutName() { return "PlaybackUI"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);

	// ButtonListener
	virtual void            ButtonDepress(int i_id);
    
protected:
    void                    onPlaybackDownloadResult(BattleID battle_id, bool i_success);
    void                    onPlaybackListRefresh(const std::vector<BattleID>& idList);

private:
    class UIScrollControl*  m_pScrollBar = nullptr;
};


//-------------------------------------------------------------
class RecordWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RecordWidget(BattleID i_id);
    virtual void        Draw(Sexy::Graphics* i_g);
    virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
    
    // ButtonListener
    virtual void			ButtonDepress(int i_id);
    
protected:
    void                refresh();
    
protected:
    BattleID            m_recordID;
    class PVZ2UIButton* m_btnPlay = NULL;
    class PVZ2UIButton* m_btnRevenge = NULL;
    bool                m_bWin;
    int                 m_numStar;
    SexyString          m_strTime;
    SexyString          m_strResult;
    int                 m_pvpCoin;
    int                 m_pvpCup;
    int                 m_pvpMedal;
};



#endif

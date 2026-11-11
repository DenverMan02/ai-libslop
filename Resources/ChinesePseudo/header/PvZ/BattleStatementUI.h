//
//  BattleStatementUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-2-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BattleStatementUI__
#define __PlantsVersusZombies2__BattleStatementUI__

#include "Widget.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "EASquared.h"

namespace Message
{
    void BattleStatementUIMouseDown();
}

struct StatementData
{
    Image*          img;
    int             count;
    bool            isCoin;
    std::string		PlantPieceType;
    
    StatementData()
    {
        img     = NULL;
        count   = 0;
        isCoin  = false;
        PlantPieceType = "";
    }
};

class StatementContent : public Widget
{
public:
	StatementContent(StatementData data);
	virtual ~StatementContent();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
private:
    
    SexyString  m_labelDes;
    Image*      m_img;
    bool        m_isCoin;
    std::string m_plantPieceType;
};

//////

class BattleStatementUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
    enum AccountUIType
    {
        AccountUIType_Normal,
        AccountUIType_DangerRoom
    };
    
	BattleStatementUI(AccountUIType eType = AccountUIType_Normal);
	virtual ~BattleStatementUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    virtual void	MouseDown(const int i_mouseX, const int i_mouseY, const int i_clickCount);
    
private:
    
    void SetupDatas();
    
    void SetupDangerRoomDatas();
    
    void setupNormalDatas();
    
    void CreateButton();
    
    void NormalDraw(Sexy::Graphics* pGraphics);
    
    void DangerRoomDraw(Sexy::Graphics* pGraphics);
    
    // for advertisement
    void SetupAdvertisement();
    bool IsAdvertisementEnable();
    void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    void RemoveAdvertisement();

    void doublePieceRewards();
    void onADFinished(int i_type);
    void onRewardAdded(int i_mode, int count);

    enum Statement_Level_Result
    {
        Statement_Level_Result_SSS = 0,
        Statement_Level_Result_SS,
        Statement_Level_Result_S,
        Statement_Level_Result_A,
        Statement_Level_Result_B,
        Statement_Level_Result_Count
    };
    
private:
    Sexy::Rect      m_rectDialog;
    
    SexyString      m_labelScore;
    
    SexyString      m_labelPower;
    SexyString      m_labelTime;
    SexyString      m_labelBeatNum;
    
    int             m_nTotalScore;
    int             m_nRollingScore;
    
    bool            m_bRollingEnd;
    
    pvztime_t       m_markStartTime;
    
    bool            m_bIsBest;
    
    Statement_Level_Result m_level_result;
    
    AccountUIType   m_eAccountUIType;
};

#endif /* defined(__PlantsVersusZombies2__BattleStatementUI__) */

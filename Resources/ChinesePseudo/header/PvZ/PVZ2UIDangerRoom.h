//
//  PVZ2UIDangerRoom.h
//  PlantsVersusZombies2
//
//  Created by ZYM on 14-12-8.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZ2UIDangerRoom__
#define __PlantsVersusZombies2__PVZ2UIDangerRoom__

#include "Core.h"
#include "ResourceHelpers.h"
#include "MagentoService.h"
#include "Effect_PopAnim.h"
#include "PVZDangerRoomNetwork.h"
#include "PVZ2UIButton.h"

class MapEventItem;
class PVZ2UIButton;

enum DrLevelNodeType
{
    LEVEL_LOCKED,
    LEVEL_UNLOCKED,
    LEVEL_COMPLETED,    
};

enum PickingStatus
{
    NOT_PICKING,
    PICKING_REQUESTING,
    PICKING_REQUEST_DONE,
};

enum ruleButtonId{
    ENUM_RULE_CONFIRM=0,
};

class PVZ2UIDangerRoomRule : public Sexy::Widget,  public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UIDangerRoomRule();
	virtual ~PVZ2UIDangerRoomRule();
	void Init(ruleButtonId buttonID, const char* noticeTxt);
	virtual void Draw(Sexy::Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget );
	virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget );
	
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);	
	
private:
	
    PVZ2UIButton* createBtn( ruleButtonId enbtn, Sexy::Image* btnimg, Sexy::Image* btnimgd );
	std::string			m_compenNoticeName;
	
	class staticText* staticTexts_;
    class PVZ2UIScrollingWidget*  m_scrollingWidget;
    
	PVZ2UIButton*		m_ConfirmButton;
	
};



class DangerRoomTipsUI : public Sexy::Widget
{
public:
    DangerRoomTipsUI(DangerRoomLevelType i_type);
    DangerRoomTipsUI(DangerRoomLevelType i_type, int i_w, int i_h);
    virtual ~DangerRoomTipsUI(){}
    
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void DrawOverlay(Sexy::Graphics* i_g);
    
    void ModifyType(DangerRoomLevelType i_type);
private:
    DangerRoomLevelType m_type;
    int m_currentLevel;
    int m_maxLevel;
    int m_screenWidth;
    int m_screenHeight;
    SexyString m_titleText;
    SexyString m_contentText;
};

class DangerRoomLevelNode : public Sexy::Widget
{
public:
    DangerRoomLevelNode(int i_positionX, int i_positionY, DrLevelNodeType i_type, DangerRoomLevelType i_levelType);
    virtual ~DangerRoomLevelNode();
    
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void DrawOverlay(Sexy::Graphics* i_g);
    
    virtual void Update();
    
    virtual void MouseDown(int x, int y, int theClickCount);
    
    void SetIsSelected(bool i_selected);
    
    bool CanBeSelected();
    
    bool IsSelected();
    
    std::string GetAnimLabel(DrLevelNodeType i_type);
    
    DangerRoomLevelType GetLevelType();
    
    void         LinkLevelNodes(const std::vector<DangerRoomLevelNode*> i_nodes);
    
    void ShowTips();
    
private:
    Effect_PopAnim* m_levelNodeAnim;
    DrLevelNodeType m_type;
    bool            m_isSelected;
    DangerRoomLevelType m_levelType;
    std::vector<DangerRoomLevelNode*> m_levelNodes;
};

namespace Message
{
    void NoticeOtherNodes(int i_type);
}

class PVZ2UIDangerRoom : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	PVZ2UIDangerRoom(DangerRoomType i_type);
	virtual ~PVZ2UIDangerRoom();
    
	virtual void Draw(Sexy::Graphics* i_g);	
	virtual void Update();
    
    virtual void DrawPlayerRankInfo(Sexy::Graphics *i_g, int startX, int startY, int index, SexyString titleText, SexyString valueText, bool devider);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
    
    void         CreateLevelNodes();    
    
    void  OnCloseDialog();
    void  OnStartDangerRoomPlay(bool i_success);
    void  ResetRankAndLife();
    
//    static void  AcceptStart();
private:
    void    OnNodesNoticed(int i_type);
    void    ChooseLevelAndStart();
    DrLevelNodeType GetLevelNodeType(DangerRoomLevelType i_levelType);
    void LinkLevelNodes(const std::vector<DangerRoomLevelNode*> i_nodes);
	void OnRequestRankFinished(bool i_success);
    
    void SyncAllTexts();
    
    void PickReward();
    void PickReward(int i_lastrank);
    void TryPickReward();
    
    void BuyLife();
    void OnBuyDangerRoomLife(const bool& isSuccess);
    void OnLifeBought();
    void OnAcceptStart();
    void OnConfirmReward(bool i_success, int i_lastRank, bool i_setToFalse = false);
    
    void InitAllButtons();
    
    void OnConfirmProgress();
    
    void OnConfirmBuyLife();
    
    Image* GetRewardImage();

    void HandleTutorialInputs();
    void OnTutorialFinished();

	PVZ2UIButton*		m_closeButton;
    PVZ2UIButton*		m_ruleButton;
    PVZ2UIButton*		m_rewardButton;
    PVZ2UIButton*		m_exchangeButton;
    PVZ2UIButton*		m_startButton;
    PVZ2UIButton*		m_lifeButton;    

    std::vector<DangerRoomLevelNode*> m_levelNodes;
    
    RewardInfo          m_rewardInfo;
    
    SexyString          m_titleTextValue;
    SexyString          m_highestScoreTextValue;
    SexyString          m_currentRewardTextValue;
    SexyString          m_rewardLeftTextValue;
    
    SexyString          m_lifeTextValue;
    SexyString          m_stoneTextValue;
    
    DangerRoomType      m_type;
    
    PickingStatus       m_pickingStatus;
    
    class BouncingArrow* m_tutorialArrow;

};

#endif /* defined(__PlantsVersusZombies2__PVZ2UIDangerRoom__) */

//
//  WhackAMoleUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-10-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WhackAMoleUI__
#define __PlantsVersusZombies2__WhackAMoleUI__

#include "UIWidget.h"
#include "WhackAMoleModule.h"

class WhackAMoleUI : public UIWidget
{
public:
    RT_CLASS_DEFINE(WhackAMoleUI, UIWidget, RtClass);
	
	WhackAMoleUI();
	virtual ~WhackAMoleUI();
    
	virtual void Draw(Graphics* i_g) override;
	virtual bool OnTouch(const Sexy::Touch& i_touch) override;
    
    void         SetWhackAMoleType(prop_type i_type);
    int          GetArrowType() const;
    
    void         SetArrowCount(int i_count);
    int          GetArrowCount() const;
    
    void         SetCanCoolDown(bool i_canCoolDown);
    
    bool         IsInCoolDown() const;
    
    void         SetArrowSelect(bool i_select);
    bool         IsArrowSelect() const;
    void         SetDisable(bool isDisabled);
protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    
    void         onOakArrowHitted(const int i_target_type, const int i_count);
    
private:
    
    int         m_arrow_type;
    int         m_arrow_count;
    
    bool        m_IsSelected;
    
    ImagePtr    m_arrowImage;
	ImagePtr	m_arrowDownImage;
    
    bool        m_canCoolDown;
    bool        m_isInCoolDown;
	float       m_timeRemaining;

    bool m_disable;
};


//-----------------------------------------------------------------
// UISteamMiniGameScore
//-----------------------------------------------------------------
class UISteamMiniGameScore : public UIWidget
{
public:
	RT_CLASS_DEFINE(UISteamMiniGameScore, UIWidget, RtClass);
    UISteamMiniGameScore();
	void setScores(uint32 *score);
	virtual ~UISteamMiniGameScore();

	virtual void					Draw(Graphics* i_g) override;

    void setMinWinScore(uint32 minWinScore);
    void setTargetScore(uint32 targetScore);

    void updateScoreboard();
private:
	uint32 *m_Score;
    uint32 m_displayScore;
    uint32 m_nTargetScore;
    uint32 m_nMinWinScore;
    SexyString m_scoreLabel;
    Sexy::Rect m_scoreLebelRect;
    Color m_scoreColor;

    Sexy::Rect m_goalLebelRect;
    SexyString m_goalLabel;


};

#endif /* defined(__PlantsVersusZombies2__WhackAMoleUI__) */

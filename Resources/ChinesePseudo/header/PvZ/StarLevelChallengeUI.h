//
//  StarLevelChallengeUI.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-5-15.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarLevelChallengeUI__
#define __PlantsVersusZombies2__StarLevelChallengeUI__

#include <iostream>

#include "Widget.h"
#include "RtObject.h"
#include "TimeMgr.h"

namespace Message
{
	void StarLevelChallengeStart();
    void StarLevelChallengeCancel();
}


class StarLevelChallengeUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	StarLevelChallengeUI(int worldIndex,int levelIndex);
	virtual ~StarLevelChallengeUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
public:
    
private:
    int GetMaxZombieLevel(const class LevelDefinition* level);
    SexyString		m_headerLabel;
    
    Sexy::Rect      m_rectDialog;
    bool            m_bExit;
    bool            m_bShowNotice;
    
    Sexy::Rect      m_rectImgBg;
    
    SexyString      m_strDesc;
    Sexy::Rect      m_rectDesc;
    
    int             m_challengeIndex;
    
    Image *         m_pNumImage;
};


class StarLevelChallengeHelper
{
public:
    static bool canShowStarLevelChallengeUI(const std::string& levelName);
};

#endif /* defined(__PlantsVersusZombies2__StarLevelChallengeUI__) */

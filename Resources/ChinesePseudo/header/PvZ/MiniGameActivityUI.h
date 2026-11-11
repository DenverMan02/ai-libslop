//
//  StoreUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MiniGameActivityUI__
#define __PlantsVersusZombies2__MiniGameActivityUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "MagentoService.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"



class CMiniGameActivityUI : public Widget, public ButtonListener
{
public:
	CMiniGameActivityUI();
	virtual ~CMiniGameActivityUI();

	virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g);
    virtual void Draw(Graphics* i_g);
	virtual void Update();
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
    
    static int s_iRewardMultiply;
private:
    void    GenerateReward();
    Image* m_imgbkgddecorate;
    Rect  m_bksizeRect;
    Rect  m_rewardpools;    
    class PVZ2UIButton* m_startButton;
    class PVZ2UIButton* m_refreshButton;
    class PVZ2UIButton* m_levelerButton;
    class PVZ2UIButton* m_leafgetButton;
    class PVZ2UIButton* m_lookupbonusButton;
    
    struct MiniGame*    m_pCurMiniGame;
    struct MiniGameRewardList*  m_pRewardList[3];
};

#endif

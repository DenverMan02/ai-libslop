//
//  PVZ2UICompenNotice.h
//  PlantsVersusZombies2
//
//  Created by Rain Chen on 05/21/14
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UICompenNotice_h
#define PlantsVersusZombies2_PVZ2UICompenNotice_h

#include "Core.h"
#include "PVZ2UIButton.h"
#include "ResourceHelpers.h"
#include "MagentoService.h"

class MapEventItem;
class PVZ2UIButton;

enum FakeCountVersion
{
	FakeCountVersion_PVP_FOR_WANDOUJIA = 10
};

enum compenButtonId
{
    ENUM_COMPEN_CONFIRM              = 0,
    ENUM_COMPEN_GACHA_CONFIRM        = 1,
    ENUM_COMPEN_DAILY_REWARD_CONFIRM = 2,
    ENUM_COMPEN_IOS_BUG_CONFIRM      = 3,
    ENUM_COMPEN_PVP_FOR_WANDOUJIA    = 4
};

class PVZ2UICompenNotice : public Sexy::Widget,  public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UICompenNotice();
	virtual ~PVZ2UICompenNotice();
	void Init(compenButtonId buttonID, const char* noticeTxt);
	virtual void Draw(Sexy::Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget );
	virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget );
	
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	
	
private:
	
    PVZ2UIButton* createBtn( compenButtonId enbtn, Sexy::Image* btnimg, Sexy::Image* btnimgd );
	std::string			m_compenNoticeName;
	
	class staticText* staticTexts_;
    class PVZ2UIScrollingWidget*  m_scrollingWidget;

	PVZ2UIButton*		m_ConfirmButton;
	
};

#endif

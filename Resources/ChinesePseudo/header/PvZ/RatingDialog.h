//
//  RatingDialog.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-5-4.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RatingDialog__
#define __PlantsVersusZombies2__RatingDialog__

#include "Widget.h"
#include "RtObject.h"
#include "Precompile.h"
#include "ButtonWidget.h"

class RatingDialog : public Sexy::Widget, public Sexy::ButtonListener
{
    enum
    {
        Rating_btn_rate = 0,
        Rating_btn_later,
        Rating_btn_never,
    };
    
public:
	RatingDialog();
	virtual ~RatingDialog();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    class PVZ2UIButton* m_ratingButton;
    class PVZ2UIButton* m_laterButton;
    class PVZ2UIButton* m_neverButton;
    
    void gotoRatingStore();
    
};

#endif /* defined(__PlantsVersusZombies2__RatingDialog__) */

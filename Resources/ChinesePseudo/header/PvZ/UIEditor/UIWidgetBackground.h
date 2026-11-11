//
//  UIWidgetBackground.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIWidgetBackground_h_
#define _UIWidgetBackground_h_
#include "Widget.h"

class UIWidgetBackground : public Sexy::Widget
{
public:
	enum {
		Type_Grass = 0,
        Type_Frame = 1,
        Type_Inner = 2,
        Type_Grass_Leaves = 3,
        Type_Outer = 4,
        Type_Green = 5,
        Type_Red = 6,
        Type_Orange = 7,
        Type_Round_Green = 8,
        Type_Anniversary = 9,
        
        Type_None = 0xFF,       // 255
	};
public:
	UIWidgetBackground(int iType = Type_Grass);
	virtual ~UIWidgetBackground();

    virtual void						DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
	virtual void                     Draw(Sexy::Graphics* i_g);

	void								SetType(int iType);
	int								GetType() const { return m_type; }

protected:
	void								DrawTypeGrass(Sexy::Graphics* i_g);
    void								DrawTypeFrame(Sexy::Graphics* i_g);
    void								DrawTypeInner(Sexy::Graphics* i_g);
    void								DrawTypeLeaves(Sexy::Graphics* i_g);
    void								DrawTypeOuter(Sexy::Graphics* i_g);
    void								DrawTypeGreen(Sexy::Graphics* i_g);
    void								DrawTypeRed(Sexy::Graphics* i_g);
    void								DrawTypeOrange(Sexy::Graphics* i_g);
    void								DrawTypeRoundGreen(Sexy::Graphics* i_g);
    void								DrawTypeAnniversary(Sexy::Graphics* i_g);

protected:
	int								m_type;
};



#endif

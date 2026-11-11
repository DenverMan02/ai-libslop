//
//  PowerupChooser.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupChooser__
#define __PlantsVersusZombies2__PowerupChooser__

#include "LawnDialog.h"

class PowerupChooser : public LawnDialog
{
public:
	PowerupChooser(int i_id, bool i_isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode);

	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void ButtonDepress(int i_id);

private:
	StretchableNewLawnButton*	m_wizardFinger;
	StretchableNewLawnButton*	m_pinch;
	StretchableNewLawnButton*	m_flick;

};

#endif /* defined(__PlantsVersusZombies2__PowerupChooser__) */

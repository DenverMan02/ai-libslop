//
//  HotUIHelpers.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/18/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__File__
#define __PlantsVersusZombies2__File__

#include <string>

#include "HotUIWidget.h"
#include "Image.h"
#include "Insets.h"

namespace HotUIHelpers
{
	Insets		GetInsetsFromDynamicPadding(const DynamicPadding& i_padding);
	bool		DoLayoutPassOnWidget(HotUIWidget* i_widget);
	void		LayoutAndPositionWidget(HotUIWidgetPtr i_widget);
	ImagePtr	GetImageFromStringId(const std::string& i_imageName);
}


#endif /* defined(__PlantsVersusZombies2__HotUIHelpers__) */

//
//  PopAnimWidgetRig.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 10/10/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PopAnimWidgetRig__
#define __PlantsVersusZombies2__PopAnimWidgetRig__

#include <vector>

#include "Rect.h"
#include "Widget.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class PopAnimRigWidget : public Sexy::Widget
{
public:
	PopAnimRigWidget(const Sexy::Rect& i_rect, class PopAnimRig* i_rig=nullptr);
	virtual ~PopAnimRigWidget();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);

	void AddRig(class PopAnimRig* i_rig);
	
	PopAnimRig* GetAnimRig(int i_index = 0);

private:

	std::vector<class PopAnimRig*> m_animRigs;
};

#endif /* defined(__PlantsVersusZombies2__PopAnimWidgetRig__) */

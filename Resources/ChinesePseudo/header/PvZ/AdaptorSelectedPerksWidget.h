//
//  AdaptorSelectedPerksWidget.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 7/25/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorSelectedPerksWidget_h
#define AdaptorSelectedPerksWidget_h

#include "BasicPerks.h"
#include "Curve.h"
#include "HotUIAdaptor.h"
#include "HotUIButton.h"

class AdaptorSelectedPerksWidget : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorSelectedPerksWidget, HotUIAdaptor, RtClass);
	
public:
	AdaptorSelectedPerksWidget();
	void ButtonDepress(int i_buttonID) override;
	void Update() override;
	void OnLayoutFinalized();
	
protected:
	void onLinkToUIViewCreated() override;
	void onSelectedPerksChanged(std::string& i_perkName, bool i_needsAnimation, Point i_startPoint);
	void onPerkSelected(std::string& i_perkName, bool i_needsAnimation, Point& i_startPoint);
	void onPerkDeselected(std::string& i_perkName);
	
private:
	
	std::vector<HotUIButton*> m_selectedPerksButtons;
	std::vector<std::string> m_selectedPerks;
	
	bool m_isAnimating;
	std::vector<Curve<Point>> m_selectedPerkCurves;
	std::vector<int> m_animatingButtonIndices;

	bool m_isInitializeTop;
	int m_top;
};


#endif /* AdaptorSelectedPerksWidget_h */

//
//  AdaptorDifficultyModifierFullScrollWidget.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 9/18/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorDifficultyModifierFullScrollWidget_h
#define AdaptorDifficultyModifierFullScrollWidget_h

#include "AdaptorRiftDifficultyInfoWidget.h"
#include "HotUIAdaptor.h"
#include "RtDb.h"

class AdaptorDifficultyModifierFullScrollWidget : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorDifficultyModifierFullScrollWidget, HotUIAdaptor, RtClass);
	
public:
	AdaptorDifficultyModifierFullScrollWidget();
	~AdaptorDifficultyModifierFullScrollWidget();
	
	void ButtonDepress(int i_buttonID) override;
    void SetLevel(const std::string& i_levelToShow) { m_levelToShow = i_levelToShow; }
    bool OnBackButtonPressed() override { onClose(); return true; }

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void createScrollList();
	void onClose();
	
private:
	std::vector<AdaptorRiftDifficultyInfoWidget*> m_difficultyModifierWidgets;
    
    std::string m_levelToShow;
};

#endif /* AdaptorDifficultyModifierFullScrollWidget_h */

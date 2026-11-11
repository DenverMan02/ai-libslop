//
//  AdaptorPerkSelectionDialog.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 5/20/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorPerkSelectionDialog_h
#define AdaptorPerkSelectionDialog_h

#include "AdaptorPerkInfoWidget.h"
#include "HotUIAdaptor.h"
#include "RtDb.h"

class AdaptorRiftDifficultyList;

class AdaptorPerkSelectionDialog : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorPerkSelectionDialog, HotUIAdaptor, RtClass);
public:
    AdaptorPerkSelectionDialog();
	~AdaptorPerkSelectionDialog();
	
	void ButtonDepress(int i_buttonID) override;
	void SetOnCloseAction(std::function<void()> i_onClose);
	void SetOnBackAction(std::function<void()> i_onBack);
	void Close();
	
protected:
	void onPerkSelected(std::string i_perkName, bool i_needsAnimation, Point& i_startPoint);
	void onPerkSelectionChanged(std::string i_perkName);
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	void onRepickButtonPressed();
	void onPlayButtonPressed();
    bool OnBackButtonPressed() override;
	void refresh();
	
	void createPerkScrollList();
	void verifySelectedPerksAndContinue();
	void finalizePerks();

	bool CanEitherPerkInfoWidgetSelectable();// zhousen check if either one item can be selected
	void OnServerGemCallBack(const bool& i_Success);
	
private:
    void showGemBank(bool i_visible);
    
	std::function<void()> m_onCloseCallback;
	std::function<void()> m_onBackCallback;
	
	std::vector<AdaptorPerkInfoWidget*> m_perkWidgets;
	AdaptorRiftDifficultyList* m_difficultyList;
};

#endif /* AdaptorPerkSelectionDialog_h */

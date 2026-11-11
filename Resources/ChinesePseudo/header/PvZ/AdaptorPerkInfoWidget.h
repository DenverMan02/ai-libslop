//
//  AdaptorPerkInfoWidget.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 7/23/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorPerkInfoWidget_h
#define AdaptorPerkInfoWidget_h

#include "HotUIAdaptor.h"
#include "HotUIButton.h"
#include "PennyPerkMgr.h"

enum PerkInfoType
{
	PerkInfo_Gameplay,
	PerkInfo_Library
};

class AdaptorPerkInfoWidget : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorPerkInfoWidget, HotUIAdaptor, RtClass);
public:
	AdaptorPerkInfoWidget();
	void SetInfoType(PerkInfoType i_type);
	
	void ButtonDepress(int i_buttonID) override;
	void SetPerk(PerkData i_perk);

	bool IsSelectable() const { return m_selectable; }
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onPerkSelected(std::string& i_perkName, bool i_needsAnimation, Point& i_startPoint);
	void onPerkDeselected(std::string& i_perkName);
	void onRepickButtonPressed();
	
	void setPerkLocked();
	void setPerkDisabled();
	void setPerkSelected();
	void resetPerkStatus();
	
	void setDefaultLevelText();
	void setIncrementedLevelText();
	void setLevelText(int i_level, bool i_greenText);
	
private:
	
	PerkData m_perk;
	ImagePtr m_perkIcon;
	PerkInfoType m_infoType;
	
	//Gameplay only
	HotUIButton* m_activationButton;
	bool m_selectable;
	
	//Library only
	HotUIButton* m_checkbox;
	bool m_checkboxSelected;
};

#endif /* AdaptorPerkInfoWidget_h */

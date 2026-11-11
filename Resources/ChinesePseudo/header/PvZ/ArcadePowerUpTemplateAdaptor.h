//
//  ArcadePowerUpTemplateAdaptor.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/5/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadePowerUpTemplateAdaptor__
#define __PlantsVersusZombies2__ArcadePowerUpTemplateAdaptor__

#include "HotUIAdaptor.h"

class HotUIAnim;
class PowerUpUIButton;

class ArcadePowerUpTemplateAdaptor : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(ArcadePowerUpTemplateAdaptor, HotUIAdaptor, Sexy::RtClass);
	ArcadePowerUpTemplateAdaptor() {}
	virtual ~ArcadePowerUpTemplateAdaptor() {}
	
	void Configure(WidgetContainer* i_parent, const std::string& i_collectionID, const std::string& i_powerUpID);
	
	void RefreshUnlockStatus();
	
	bool IsConfiguredForPowerUp(const std::string& i_collectionID, const std::string& i_powerUpID) const;
	HotUIAnim* GetLockAnimation() const;
	PowerUpUIButton* GetPowerUpUIButton() const;
	
protected:
	std::string getUIFileName();
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	std::string getProgressText() const;
	void getProgressTowardPowerUp(int& o_currentValue, int& o_goalValue) const;
	
	std::string m_collectionID;
	std::string m_powerUpID;
	WidgetContainer* m_parent;
};

#endif /* defined(__PlantsVersusZombies2__ArcadePowerUpTemplateAdaptor__) */

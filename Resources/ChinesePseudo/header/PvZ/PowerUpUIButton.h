//
//  PowerUpUIButton.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/22/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerUpUIButton__
#define __PlantsVersusZombies2__PowerUpUIButton__

#include "PVZ2UIButton.h"
#include "RunnableAction.h"

namespace ArcadePropertySheetHelpers
{
	class PowerUpMetaData;
}

class PowerUpUIButton : public PVZ2UIButton, public ButtonListener
{
public:
	class AnimateSaturation : public RunnableAction
	{
	public:
		AnimateSaturation(PowerUpUIButton* i_button, const float i_startingSaturation, const float i_finalSaturation, const float i_duration);
		
	protected:
		void onBegin() override;
		void onUpdate() override;
		
	private:
		PowerUpUIButton* m_button;
		float m_startingSaturation;
		float m_finalSaturation;
		float m_duration;
		float m_startTime;
	};
	
public:
	PowerUpUIButton(int i_buttonID, const std::string& i_collectionID, const std::string& i_powerUpID);
	virtual ~PowerUpUIButton() {}
	
	void SetType(const std::string& i_collectionID, const std::string& i_powerUpID);
	void SetSaturation(float i_colorSaturation);
	
	void RefreshUnlockState();
	void Draw(Graphics* i_g) override;
	
	void ButtonDepress(int theId) override;
	
private:
	SexyString doSubstitutions(SexyString i_sourceText) const;
	
	std::string m_collectionID;
	std::string m_powerUpID;
	bool m_isUnlocked;
	float m_saturation;
};

#endif /* defined(__PlantsVersusZombies2__PowerUpUIButton__) */

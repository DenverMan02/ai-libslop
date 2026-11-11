//
//  SeedPacket_Powerup.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SeedPacket_Powerup__
#define __PlantsVersusZombies2__SeedPacket_Powerup__

#include "SeedPacket.h"

class SeedPacket_Powerup : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_Powerup, SeedPacket, RtClass);
	
	virtual void Draw(Graphics* i_g) override;
	
	void SetPowerupType(const std::string& i_tool);
	bool OnTouch(const Sexy::Touch& i_touch) override;

	bool IsActivated() const { return m_activated; }

private:

	bool m_activated;
};

#endif /* defined(__PlantsVersusZombies2__SeedPacket_Powerup__) */

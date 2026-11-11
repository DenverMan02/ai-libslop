//
//  Whitelistable.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 1/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Whitelistable__
#define __PlantsVersusZombies2__Whitelistable__

#include <string>

class Whitelistable
{
public:
	virtual ~Whitelistable() {}
	void RegisterForWhitelistEvents();
	void UnregisterForWhitelistEvents();
	
	void SetWhitelistID(const std::string& i_whitelistID);
	
protected:
	bool isDisabledByWhitelisting();
	
	virtual void onWhitelistingChanged() {};
	
private:
	std::string m_whitelistID;
};

#endif /* defined(__PlantsVersusZombies2__Whitelistable__) */

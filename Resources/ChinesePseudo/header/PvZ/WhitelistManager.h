//
//  WhitelistManager.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 1/22/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WhitelistManager__
#define __PlantsVersusZombies2__WhitelistManager__

#include "Singleton.h"

namespace Message
{
	void WhitelistingChanged();
}

class WhitelistManager : public LazySingleton<WhitelistManager>
{
public:
	void DisableAllInput();
	void EnableWhitelisting(const std::string& i_allowedID);
	void EnableWhitelisting(const std::vector<std::string>& i_allowedIDs);
	void DisableWhitelisting();
	
	bool IsDisabledByWhitelisting(const std::string& i_whitelistID);
	
private:
	bool m_whitelistingEnabled;
	std::vector<std::string> m_allowedWhitelistIDs;
};

#endif /* defined(__PlantsVersusZombies2__WhitelistManager__) */

//
//  NetworkStatusDecider.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 12/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NetworkStatusDecider__
#define __PlantsVersusZombies2__NetworkStatusDecider__

#include <iostream>

class NetworkStatusDecider
{
public:
	NetworkStatusDecider(std::ostream& os = std::cerr);
    virtual const bool ShouldSendNetworkRequest() const;
	
protected:
    virtual const bool networkReachable() const;
	virtual const bool areMetricsEnabled() const;
	
private:
	std::ostream& m_os;
};
#endif /* defined(__PlantsVersusZombies2__NetworkStatusDecider__) */

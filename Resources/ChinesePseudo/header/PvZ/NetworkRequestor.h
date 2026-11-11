//
//  NetworkRequestor.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen, Matt Westhoff on 3/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NetworkRequestor__
#define __PlantsVersusZombies2__NetworkRequestor__

#include "Precompile.h"

class ServerConfigGetter;
class PvZ2NetworkServiceListener;
class FakeHttpDriver;

namespace Sexy
{
	class StructuredData;
}

class NetworkRequestor
{
public:
	virtual ~NetworkRequestor() {}
	
protected:
	NetworkRequestor(ServerConfigGetter& serverConfigGetter, const std::string& requestType);
	virtual bool isWaitingForResponse() = 0;
	virtual void addArguments(Sexy::StructuredData& request) = 0;
	void makeRequest(PvZ2NetworkServiceListener& listener);
	void sendRequest(Sexy::StructuredData* request, PvZ2NetworkServiceListener* listener);
	
	// DATA ACCESSIBLE FOR TEST
	FakeHttpDriver* m_HttpDriverForTest;	
private:
	ServerConfigGetter& m_serverConfigGetter;
	const std::string m_requestType;
};

#endif /* defined(__PlantsVersusZombies2__NetworkRequestor__) */

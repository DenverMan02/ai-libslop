//
//  PvZ2NetworkServiceListener.h
//  PlantsVersusZombies2
//
//  Created by Ross Baker on 3/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PvZ2NetworkServiceListener__
#define __PlantsVersusZombies2__PvZ2NetworkServiceListener__

#include "NetworkServiceManager.h"

namespace Sexy
{
	class StructuredData;
}

class PvZ2NetworkServiceListener : public Sexy::NetworkServiceListener
{
public:
	void SetBlocked();
	bool IsBlocked();
protected:
	PvZ2NetworkServiceListener();
	float m_lastSet;
	
	inline bool isMyRequest(const void* context) { return context == this; }
	virtual void logFailMessage(const std::string& requestType, const Sexy::StructuredData* response);
	virtual void logSuccessMessage(const std::string& requestType, const Sexy::StructuredData* response);
private:
	bool m_blocked;
};

#endif /* defined(__PlantsVersusZombies2__PvZ2NetworkServiceListener__) */

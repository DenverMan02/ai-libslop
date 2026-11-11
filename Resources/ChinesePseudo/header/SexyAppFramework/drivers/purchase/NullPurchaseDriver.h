
#pragma once
#include "IPurchaseDriver.h"
using namespace Sexy;

namespace Sexy
{
	class NullPurchaseDriver : public IPurchaseDriver
	{
	public:
		
		NullPurchaseDriver();
		~NullPurchaseDriver();
    };		
}

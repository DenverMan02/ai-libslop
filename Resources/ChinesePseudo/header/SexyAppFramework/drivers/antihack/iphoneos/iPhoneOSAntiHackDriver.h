#pragma once
#ifndef ANDROIDANTI_HACK_H_INCLUDED
#define ANDROIDANTI_HACK_H_INCLUDED

#include <drivers/antihack/BaseAntiHackDriver.h>

#include "IAntiHackDriver.h"
namespace Sexy 
{
	class iPhoneOSAntiHackDriver: public BaseAntiHackDriver
	{
	public:
		iPhoneOSAntiHackDriver();
		virtual~ iPhoneOSAntiHackDriver();
	};

}


#endif


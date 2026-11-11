#pragma once
#ifndef ANDROIDANTI_HACK_H_INCLUDED
#define ANDROIDANTI_HACK_H_INCLUDED

#include <drivers/antihack/BaseAntiHackDriver.h>
#include "IAntiHackDriver.h"

namespace Sexy 
{
	class AndroidAntiHackDriver: public BaseAntiHackDriver
	{
	public:
		AndroidAntiHackDriver();
		virtual~ AndroidAntiHackDriver();

		//is some one hacked the game package
		virtual bool IsPackageHacked();

	private:
		long GetDigitalSignature();

	};

}


#endif


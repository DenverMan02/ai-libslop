//
//  MacAntiHackDriver.h
//  SexyAppFramework Prime
//
//  Created by Yujia Rao "Rao Yujia" on 13-7-12.
//
//

#ifndef __SexyAppFramework_Prime__MacAntiHackDriver__
#define __SexyAppFramework_Prime__MacAntiHackDriver__

#include <iostream>
#include <drivers/antihack/BaseAntiHackDriver.h>

#include "IAntiHackDriver.h"
namespace Sexy
{
	class MacAntiHackDriver: public BaseAntiHackDriver
	{
	public:
		MacAntiHackDriver();
		virtual~ MacAntiHackDriver();
	};
    
}

#endif

//
//  WindowsAntiHackDriver.h
//  SexyAppFramework Prime
//
//  Created by Yujia Rao "Rao Yujia" on 13-7-12.
//
//

#ifndef __SexyAppFramework_Prime__WindowsAntiHackDriver__
#define __SexyAppFramework_Prime__WindowsAntiHackDriver__

#include <iostream>
#include <drivers/antihack/BaseAntiHackDriver.h>

#include "IAntiHackDriver.h"
namespace Sexy
{
	class WindowsAntiHackDriver: public BaseAntiHackDriver
	{
	public:
		WindowsAntiHackDriver();
		virtual~ WindowsAntiHackDriver();
	};
    
}

#endif

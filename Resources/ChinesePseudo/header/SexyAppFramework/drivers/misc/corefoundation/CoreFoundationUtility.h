
#pragma once
#include <string>
#include <CoreFoundation/CFString.h>

namespace Sexy
{
	std::string CFStringGetStdString( CFStringRef cfs, CFStringEncoding encoding );
}


#pragma once
#include "PopCapSharing.h"
#include <CoreFoundation/CFString.h>

namespace Sexy
{
	class PopCapSharingImpl
		: public PopCapSharing
	{
	public:

		PopCapSharingImpl();
		~PopCapSharingImpl();
		
		bool SavePassword( const std::string& service, const std::string& account, const Data& generic, const Data& value );
		bool SavePassword( const std::string& service, const std::string& account, const std::string& genericString, const Data& value );
		
		bool RetrievePassword( const std::string& service, const std::string& account, Data& generic, Data& value );
		bool RetrievePassword( const std::string& service, const std::string& account, std::string& generic, Data& value );
		
	protected:

		CFStringRef mAccessGroup;
		
	};
}

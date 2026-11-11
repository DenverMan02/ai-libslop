//
//  IMessagingDriver.h
//  SexyAppFramework Prime
//
//  Created by Guy Stables on 3/13/13.
//
//

#pragma once
#include <string>
#include <vector>
#include "Common.h"

namespace Sexy
{
	class IMessagingDriver;
	class StructuredData;
	
	class IMessagingDriver
	{
	public:
		
		static IMessagingDriver* CreateMessagingDriver();
		virtual ~IMessagingDriver() {}
		
        virtual bool CanSendEmail() = 0;
		virtual bool SendEmail(const std::string& title, const std::string& body, const std::string& to, const std::string& mimeType) = 0;
        virtual bool CanSendTextMessage() = 0;
        virtual bool SendTextMessage(const std::string& body) = 0;
	};

}

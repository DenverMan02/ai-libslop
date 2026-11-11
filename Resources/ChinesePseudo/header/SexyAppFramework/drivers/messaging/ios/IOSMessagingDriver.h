//
//  IOSMessagingDriver.h
//  SexyAppFramework Prime
//
//  Created by Guy Stables on 3/13/13.
//
//

#pragma once

#include "IMessagingDriver.h"

using namespace Sexy;


namespace Sexy
{
	class IOSMessagingDriver;
}


namespace Sexy
{
	
	class IOSMessagingDriver : public IMessagingDriver
	{
		typedef IMessagingDriver super;
		
	public:
		
        bool CanSendEmail();
        bool SendEmail(const std::string& title, const std::string& body, const std::string &to, const std::string &mimeType);
        bool CanSendTextMessage();
        bool SendTextMessage(const std::string& body);

    protected:
    };
}


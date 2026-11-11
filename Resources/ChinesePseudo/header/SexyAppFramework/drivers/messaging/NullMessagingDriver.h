//
//  NullMessagingDriver.h
//  SexyAppFramework Prime
//
#pragma once

#include "IMessagingDriver.h"

#include <string>
#include <vector>
#include "Common.h"

namespace Sexy
{
    class NullMessagingDriver : public IMessagingDriver
    {
    public:
        bool CanSendEmail();
		bool SendEmail(const std::string& title, const std::string& body, const std::string &to);
        bool CanSendTextMessage();
        bool SendTextMessage(const std::string& body);
    };
}

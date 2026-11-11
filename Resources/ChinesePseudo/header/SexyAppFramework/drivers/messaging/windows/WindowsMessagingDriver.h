#pragma once
#ifndef WINDOWS_EMAILDRIVER_H_INCLUDED
#define WINDOWS_EMAILDRIVER_H_INCLUDED

#include "IMessagingDriver.h"
//#include "drivers/app/android/JavaInterface.h"
//#include "drivers/app/android/JavaBound.h"
//#include "drivers/app/android/AndroidAppDriver.h"

namespace Sexy
{
    class WindowsMessagingDriver : public IMessagingDriver
    {
    public:
		WindowsMessagingDriver();
        
        bool CanSendEmail();
		bool SendEmail( const std::string& title, const std::string& body, const std::string &to, const std::string &mimeType );
        bool CanSendTextMessage();
        bool SendTextMessage( const std::string& body );
    };
}

#endif

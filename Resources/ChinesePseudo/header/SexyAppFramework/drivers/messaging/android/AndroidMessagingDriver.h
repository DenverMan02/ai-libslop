#pragma once
#ifndef ANDROIDEMAILDRIVER_H_INCLUDED
#define ANDROIDEMAILDRIVER_H_INCLUDED

#include "IMessagingDriver.h"
#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"
#include "drivers/app/android/AndroidAppDriver.h"

namespace Sexy
{
    class AndroidMessagingDriver : public IMessagingDriver,
                                   public JavaBound< AndroidMessagingDriver >
    {
    public:
        static JavaMethod<jboolean>     JavaComposeTextMessage;
        static JavaMethod<jboolean>     JavaComposeEmailMessage;

        AndroidMessagingDriver();
        void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
        
        bool CanSendEmail();
		bool SendEmail( const std::string& title, const std::string& body, const std::string &to, const std::string &mimeType );
        bool CanSendTextMessage();
        bool SendTextMessage( const std::string& body );
    };
}

#endif

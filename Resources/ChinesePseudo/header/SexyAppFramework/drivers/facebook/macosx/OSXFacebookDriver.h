
#pragma once
#include "NullFacebookDriver.h"
#import "WebDialog.h"
using namespace Sexy;

extern NSString* kGraphBaseURL;
extern NSString* kDialogBaseURL;
extern NSString* kDialogRedirectURL;

namespace Sexy
{
	
	class OSXFacebookDriver : public NullFacebookDriver
	{
		typedef NullFacebookDriver super;
		
	public:
		
		OSXFacebookDriver() {}
		~OSXFacebookDriver() {}
        
        void DialogDidComplete( WebDialog* dialog, NSURL* url ) {}
		void DialogWasClosed( WebDialog* dialog ) {}
		void DialogDidFail( WebDialog* dialog, NSError* error ) {}
		BOOL DialogShouldOpenURLInExternalBrowser( WebDialog* dialog, NSURL* url ) { return false; }
    };

}

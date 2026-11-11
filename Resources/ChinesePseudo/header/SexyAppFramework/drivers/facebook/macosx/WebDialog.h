
#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

namespace Sexy
{
	class OSXFacebookDriver;
	class IFBDialogListener;
}
using namespace Sexy;

// ---------------------------------------------------------------------------
// class WebDialogSheet declaration
// ---------------------------------------------------------------------------

@interface WebDialogWindow : NSWindow
{
}
@end

// ---------------------------------------------------------------------------
// class WebDialog declaration
// ---------------------------------------------------------------------------

@interface WebDialog : NSView
{
	OSXFacebookDriver* mDriver;
	NSURL* mURL;

	WebView* mWebView;
	NSButton* mCloseButton;
	NSProgressIndicator* mSpinner;

	WebDialogWindow* mWindow;
}

- (id)initWithName:(NSString*)name params:(NSDictionary*)params driver:(OSXFacebookDriver*)driver;
- (void)show;
- (void)close;

@end

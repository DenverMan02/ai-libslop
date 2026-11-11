#import <Cocoa/Cocoa.h>

namespace Sexy 
{
	class MacosxAppDriver;
	class SexyAppBase;
}

@interface SexyApplicationDelegate : NSObject< NSApplicationDelegate, NSWindowDelegate >
{
@public
	Sexy::MacosxAppDriver* mAppDriver;
	Sexy::SexyAppBase* mAppBase;

@private
	NSWindow* mWindow;
}
@property (nonatomic,assign) Sexy::MacosxAppDriver* appDriver;
@property (nonatomic,assign) Sexy::SexyAppBase* appBase;

- (void)alertDidEnd:(NSAlert *)alert returnCode:(NSInteger)returnCode
		contextInfo:(void *)contextInfo;

@end

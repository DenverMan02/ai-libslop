//most cobbled together from Apple examples. needs to be cleaner
/* Required Includes */
#import <Cocoa/Cocoa.h>
#import <OpenGL/CGLRenderers.h>
#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#import <OpenGL/OpenGL.h>
class GasMacosWindowManager;

namespace Sexy 
{
	class SexyAppBase;
}

/* The OpenGL View */
@interface SexyOpenGLView : NSOpenGLView
{
@public
	//this is a hack to make sure that this delegate stays linked in
	int nop;
	
	Sexy::SexyAppBase* mApp;
	BOOL mInitialized;
	int	mYFlip;
}
@property (nonatomic,assign) Sexy::SexyAppBase* sexyAppBase;

- (id) initWithFrame: (NSRect) theFrame;
- (void) drawRect: (NSRect) theRect;

@end

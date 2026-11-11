
#import <Foundation/Foundation.h>

@interface SexyWindow : NSWindow
{
	bool mResizing;
	NSPoint mResizingMinCorner;
	NSPoint mResizingMaxCorner;
	NSPoint mResizingAnchorOffset;
}
+ (NSRect)contentRectForContent:(NSSize)naturalSize preferred:(NSRect)prefRect safe:(NSRect)safeRect min:(NSSize)minSize max:(NSSize)maxSize;
- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)windowStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)deferCreation screen:(NSScreen*)screen;

@end


#import "EAGLView.h"

@interface GameView : EAGLView
{
@private
    id  mEventDelegate;
}

- (void)setEventDelegate:(id)target;
- (UIImage*) takeSnapshot:(NSInteger) maxWidth maxHeight:(NSInteger) maxHeight;
@end

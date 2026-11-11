//
//  EAGLView.h
//  test ipad app
//
//  Created by Jacob Van Wingen on 1/28/10.
//  Copyright Apple Inc 2010. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import "ESRenderer.h"

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView
{
@private
    id <ESRenderer> renderer;
}


- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
- (unsigned int) getSysFBO;
- (void) setCurrentContext;
- (void) setLoadingContext;
- (BOOL) isCurrentContext;
- (void) clearCurrentContext;
- (void) swapBuffers; //This also checks the current OpenGL error and logs an error if needed
- (void) forceResizeFromLayer;

- (void)drawView:(id)sender;

@end

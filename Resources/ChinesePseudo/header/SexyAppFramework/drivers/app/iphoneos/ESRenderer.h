//
//  ESRenderer.h
//  test ipad app
//
//  Created by Jacob Van Wingen on 1/28/10.
//  Copyright Apple Inc 2010. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

@protocol ESRenderer <NSObject>

- (void)render;
- (void)setCurrentContext;
- (void)setLoadingContext;
- (void)swapBuffers;
- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer;
- (BOOL)forceResizeFromLayer:(CAEAGLLayer *)layer;
- (unsigned int) getSysFBO;

@end

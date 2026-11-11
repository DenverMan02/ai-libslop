//
//  ES1Renderer.h
//  test ipad app
//
//  Created by Jacob Van Wingen on 1/28/10.
//  Copyright Apple Inc 2010. All rights reserved.
//

#import "ESRenderer.h"

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@interface ES1Renderer : NSObject <ESRenderer>
{
@private
	EAGLSharegroup* shareGroup;
    EAGLContext *context;
	EAGLContext *loadingContext;

    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth;
    GLint backingHeight;

    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint defaultFramebuffer, colorRenderbuffer;
}

- (void)render;
- (void)setCurrentContext;
- (void)setLoadingContext;
- (void)swapBuffers;
- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer;
- (BOOL)forceResizeFromLayer:(CAEAGLLayer *)layer;
- (GLuint) getSysFBO;

- (void) createGLResources;
- (void) releaseGLResources;

@end

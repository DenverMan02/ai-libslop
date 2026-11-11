#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "Deviceimage.h"

@class AVCamRecorder;
@protocol AVCamCaptureManagerDelegate;

@interface AVCamCaptureManager : NSObject {
}

@property (nonatomic,retain) AVCaptureSession *session;
@property (nonatomic,assign) AVCaptureVideoOrientation orientation;
@property (nonatomic,retain) AVCaptureDeviceInput *videoInput;
@property (nonatomic,retain) AVCaptureStillImageOutput *stillImageOutput;
@property (nonatomic,assign) id deviceConnectedObserver;
@property (nonatomic,assign) id deviceDisconnectedObserver;
@property (nonatomic,assign) id <AVCamCaptureManagerDelegate> delegate;
@property (nonatomic,assign) Sexy::MemoryImage *lastImage;
@property (nonatomic,assign) double previewAspectRatio;

- (BOOL) setupSession;
- (void) addObservers;
- (void) removeObservers;
- (void) captureStillImage;
- (unsigned int) getNumCameras:(AVCaptureDevicePosition)position;
- (char const*) getCameraInfo:(unsigned int) cameraIdx;
- (AVCaptureDevice *) cameraWithPosition:(AVCaptureDevicePosition)position;
- (AVCaptureDevice *) frontFacingCamera;
@end

@interface AVCamCaptureManager (InternalUtilityMethods)
- (AVCaptureVideoOrientation)getCurrentAVOrientation;
- (AVCaptureVideoOrientation)convertAppOrientationToAVOrientation:(UIInterfaceOrientation) interfaceOrientation;
@end

// These delegate methods can be called on any arbitrary thread. If the delegate does something with the UI when called, make sure to send it to the main thread.
@protocol AVCamCaptureManagerDelegate <NSObject>
@optional
- (void) captureManager:(AVCamCaptureManager *)captureManager didFailWithError:(NSError *)error;
- (void) captureManagerStillImageCaptured:(AVCamCaptureManager *)captureManager;
- (void) captureManagerStillImageCaptureFailed:(AVCamCaptureManager *)captureManager;
- (void) captureManagerDeviceConfigurationChanged:(AVCamCaptureManager *)captureManager;
- (void) NotifyNewOrientation:(NSInteger)newOrientation;
@end

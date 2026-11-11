#import <UIKit/UIKit.h>
#import "SexyApplicationDelegate.h"
#import "drivers/app/iphoneos/iPhoneOSAppDriver.h"
#import "DeviceImage.h"

@class AVCamCaptureManager, AVCamPreviewView, AVCaptureVideoPreviewLayer;

@interface AVCamViewController : UIViewController <UIImagePickerControllerDelegate,UINavigationControllerDelegate>
{
}

@property (nonatomic,retain) AVCamCaptureManager *captureManager;
@property (nonatomic,retain) IBOutlet UIView *videoPreviewView;
@property (nonatomic,retain) AVCaptureVideoPreviewLayer *captureVideoPreviewLayer;
@property (nonatomic) CGRect viewBounds;
@property (nonatomic) Sexy::ImageReceivedDelegate imageReceivedRTDelegate;

- (IBAction)captureStillImage:(id)sender delegate: (Sexy::ImageReceivedDelegate)inImageReceivedRTDelegate;
- (void)NotifyNewOrientation:(NSInteger)newOrientation;
- (void)ResizeAbs: (CGRect)newBounds;
@end


#include "Interpolator.h"

namespace Sexy 
{
	class iPhoneOSAppDriver;
	class SexyAppBase;
	class NotificationManagerImpl;
}
@class GameViewController;
@class GameView;

@interface SexyApplicationDelegate : UIResponder <UIApplicationDelegate, UITextFieldDelegate>
{
@public
	bool mKeepThisClassLinked;
@private
	Sexy::iPhoneOSAppDriver* mAppDriver;
	Sexy::SexyAppBase* mAppBase;
	UIWindow* mWindow;
	GameViewController* mViewController;
    GameView* mView;
    UIImageView *mSplashView;
	UITextField* mTextField;
	UIImagePickerController* mImagePickerController;
	NSTimer* mTimer;
	NSTimeInterval mIdleInterval;
	BOOL mIsRotating;
    BOOL mRotatedHalfWay;
    BOOL mIsAppInitialized;

    UIInterfaceOrientation mNewOrientation;
    NSUInteger mStartRotTick;
    NSUInteger mRotTickTime;
    BOOL mStopTimerAfterRotation;
    CADisplayLink* mDisplayLink;
	NSMutableSet* mSlaveDelegates;
    int mKeyboardChangeCount;
}
@property (nonatomic,readwrite,retain) UIWindow* window;
@property (nonatomic,readonly,retain) GameViewController* viewController;
@property (nonatomic,readonly,retain) GameView* view;
@property (nonatomic,assign) Sexy::iPhoneOSAppDriver* appDriver;
@property (nonatomic,assign) Sexy::SexyAppBase* appBase;

+ (SexyApplicationDelegate*)sharedAppDelegate;
-(void) addDelegate:(id<UIApplicationDelegate>)delegate;
-(void) removeDelegate:(id<UIApplicationDelegate>)delegate;
-(void) showTextField;
-(void) activateTextField;
-(void) activatePhoneNumTextField;
-(void) activateEmailTextField;
-(void) deactivateTextField;
- (UITextField*)sharedUITextField;
- (BOOL)isTextFieldActive;
- (void) setDisplayLinkPaused:(BOOL)i_paused;
- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)w;

// keyboard functions
- (void) keyboardWillShow;
- (void) keyboardDidShow;
- (void) keyboardWillHide;
- (void) keyboardDidHide;
- (void) keyboardWillChangeFrame;
- (void) keyboardDidChangeFrame;

// status bar functions
- (void) willChangeStatusBarFrame;
- (void) didChangeStatusBarFrame;

//PVZ2_CHINESE_BEGIN
- (void) detectCall;
- (void) onResumeAudio;
- (void) onStopAudio;
- (void) autoSwitchMusic;
//PVZ2_CHINESE_END

- (IBAction)handleSwipeGesture:(UISwipeGestureRecognizer *)sender;
- (IBAction)handleLongPressGesture:(UILongPressGestureRecognizer *)sender;

// iPod player state changes
- (void)onPlaybackStateDidChangeNotification:(NSNotification*)notification;

- (BOOL)appliaction:(UIApplication *)application handleOpenURL:(NSURL*)url;
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

@end

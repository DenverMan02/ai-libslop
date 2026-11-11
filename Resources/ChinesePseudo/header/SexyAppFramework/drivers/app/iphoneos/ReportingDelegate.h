#ifndef REPORTING_DELEGATE_H_INCLUDED
#define REPORTING_DELEGATE_H_INCLUDED

namespace Sexy
{
	class iPhoneOSAppDriver;
	class SexyAppBase;
    
    enum AlertLabelType
    {
        AlertLabelType_Title = 1001,
        AlertLabelType_Text  = 1002
    };
}

@interface ReportingDelegate : NSObject <UIApplicationDelegate, UIAlertViewDelegate>
{
@public
    int mDialogReturnValue;
}
- (int) waitForAlertReturnValue;
@end

#endif
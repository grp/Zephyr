
#import <UIKit/UIKit.h>
#import "iPhonePrivate.h"

@interface SwipeDetectorWindow : UIWindow
+ (BOOL)shouldActivate;
@end

@interface SBUIController (SwipeDetectorWindow)
- (void)updateSwipeDetectorWindows;
@end


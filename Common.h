
#import "iPhonePrivate.h"

CGFloat ZephyrHeightForOrientation(UIInterfaceOrientation orientation);
CGFloat ZephyrHeightFromScreenPercentage(CGFloat percentage, UIInterfaceOrientation orientation);

void ZephyrRotateViewFromOrientationToOrientation(UIView *view, UIInterfaceOrientation fromOrientation, UIInterfaceOrientation toOrientation, BOOL inPlace);
UIView *ZephyrViewWithScreenshotOfView(UIView *view);

UIInterfaceOrientation ZephyrOrientationFlip(UIInterfaceOrientation orientation);
NSString *ZephyrDescriptionForOrientation(UIInterfaceOrientation orientation);

UIInterfaceOrientation ZephyrHomeInterfaceOrientation();
UIInterfaceOrientation ZephyrDeviceInterfaceOrientation();
UIInterfaceOrientation ZephyrCurrentInterfaceOrientation();


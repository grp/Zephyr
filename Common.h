
#import "iPhonePrivate.h"

CGFloat ZephyrHeightForOrientation(UIInterfaceOrientation orientation);
CGFloat ZephyrHeightFromScreenPercentage(CGFloat percentage, UIInterfaceOrientation orientation);
CGFloat ZephyrWidthForOrientation(UIInterfaceOrientation orientation);

void ZephyrRotateViewFromOrientationToOrientation(UIView *view, UIInterfaceOrientation fromOrientation, UIInterfaceOrientation toOrientation, BOOL inPlace);

CGFloat ZephyrScreenRounded(CGFloat value);

UIView *ZephyrViewForApplication(SBApplication *app);
UIView *ZephyrViewWithScreenshotOfHomeScreen();
UIView *ZephyrViewWithScreenshotOfView(UIView *view);

UIInterfaceOrientation ZephyrOrientationFlip(UIInterfaceOrientation orientation);
NSString *ZephyrDescriptionForOrientation(UIInterfaceOrientation orientation);

UIInterfaceOrientation ZephyrHomeInterfaceOrientation();
UIInterfaceOrientation ZephyrDeviceInterfaceOrientation();
UIInterfaceOrientation ZephyrCurrentInterfaceOrientation();

BOOL ZephyrShouldForceSwitchAppStatusBar();

// Compatibility
BOOL ZephyrAssistantIsVisible();
BOOL ZephyrMultitaskingSupported();



#import "BaseGesture.h"
#import "OffscreenGesture.h"

typedef enum {
    kSwipeUpActionDisabled,
    kSwipeUpActionCloseApp,
    kSwipeUpActionSwitcher
} SwipeUpAction;

typedef enum {
    kSwipeUpKeyboardActionEnabled,
    kSwipeUpKeyboardActionDisabled,
    kSwipeUpKeyboardActionGrabber
} SwipeUpKeyboardAction;

@interface ZephyrSwitcherGesture : ZephyrBaseGesture {
    UIView *wrapperView;

    UIView *appView;
    UIView *switcherView;
    UIImageView *shadowView;

    NSMutableSet *pendingSwitcherActivations;
}

@end


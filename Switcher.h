
#import "OffscreenGesture.h"

typedef enum {
    kSwipeUpActionDisabled,
    kSwipeUpActionCloseApp,
    kSwipeUpActionSwitcher
} SwipeUpAction;

@interface SwitcherGesture : OffscreenGesture {
    UIView *appView;
    UIView *wrapperView;
    UIView *switcherView;
    UIImageView *shadowView;
    NSMutableSet *pendingSwitcherActivations;
}

@end


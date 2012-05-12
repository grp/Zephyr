
#import "BaseGesture.h"
#import "OffscreenGesture.h"

typedef enum {
    kSwipeUpActionDisabled,
    kSwipeUpActionCloseApp,
    kSwipeUpActionSwitcher
} SwipeUpAction;

@interface SwitcherGesture : BaseGesture {
    UIView *wrapperView;

    UIView *appView;
    UIView *switcherView;
    UIImageView *shadowView;

    NSMutableSet *pendingSwitcherActivations;
}

@end


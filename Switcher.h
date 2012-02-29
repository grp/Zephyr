
#import "BaseGesture.h"
#import "OffscreenGesture.h"

typedef enum {
    kSwipeUpActionDisabled,
    kSwipeUpActionCloseApp,
    kSwipeUpActionSwitcher
} SwipeUpAction;

@interface SwitcherGesture : BaseGesture {
    UIView *appView;
    UIView *wrapperView;
    UIView *switcherView;
    UIView *linenView;
    UIImageView *shadowView;
    NSMutableSet *pendingSwitcherActivations;
}

@end


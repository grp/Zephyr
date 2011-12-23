
#import "OffscreenGesture.h"

typedef enum {
    kSwipeUpActionDisabled,
    kSwipeUpActionSwitcher
} SwipeUpAction;

@interface SwitcherGesture : OffscreenGesture {
    UIView *appView;
    UIView *wrapperView;
    UIView *switcherView;
    UIImageView *shadowView;
}

@end


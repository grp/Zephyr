
#import "iPhonePrivate.h"

@interface GrabberController : NSObject {
    NSMutableDictionary *_grabberViews;
    NSMutableDictionary *_grabberWindows;
}

+ (id)sharedInstance;

- (BOOL)visibleAtAnyEdge;
- (BOOL)visibleAtEdge:(SBOffscreenEdge)edge;
- (void)showAtEdge:(SBOffscreenEdge)edge animated:(BOOL)animated;
- (void)hideAtEdge:(SBOffscreenEdge)edge animated:(BOOL)animated;

@end


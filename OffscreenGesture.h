
#import "iPhonePrivate.h"

@interface OffscreenGesture : NSObject {
    NSMutableArray *gestureRecognizers;
    BOOL isActive;
}

@property (nonatomic, readonly) BOOL isActive;

- (void)addOffscreenEdge:(SBOffscreenEdge)edge;
- (BOOL)shouldActivate;

- (void)handleGestureBeganWithLocation:(CGFloat)location;
- (void)handleGestureChangedWithLocation:(CGFloat)location velocity:(CGPoint)velocity;
- (void)handleGestureEndedWithLocation:(CGFloat)location velocity:(CGPoint)velocity completionType:(int)type;
- (void)handleGestureCanceled;

@end



#import "iPhonePrivate.h"

@interface OffscreenGesture : NSObject {
    NSMutableArray *gestureRecognizers;
    BOOL isActive;
}

@property (nonatomic, readonly) BOOL isActive;
@property (nonatomic, readonly) NSMutableArray *gestureRecognizers;

- (void)addOffscreenEdge:(SBOffscreenEdge)edge minimumTouchCount:(int)count;
- (BOOL)shouldActivate;

- (void)handleGestureBeganWithLocation:(CGFloat)location;
- (void)handleGestureChangedWithLocation:(CGFloat)location velocity:(CGPoint)velocity;
- (void)handleGestureEndedWithLocation:(CGFloat)location velocity:(CGPoint)velocity completionType:(int)type;
- (void)handleGestureCanceled;

@end


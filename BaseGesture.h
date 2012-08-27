
#import "iPhonePrivate.h"

@interface BaseGesture : NSObject {
    NSMutableArray *gestureRecognizers;
    BOOL isActive;
}

@property (nonatomic, readonly) BOOL isActive;
@property (nonatomic, readonly) NSMutableArray *gestureRecognizers;

- (void)addOffscreenEdge:(SBOffscreenEdge)edge minimumTouchCount:(int)count edgeMargin:(CGFloat)edgeMargin;
- (BOOL)currentOrientationIsSupported;

- (BOOL)shouldActivateAtEdge:(SBOffscreenEdge)edge;
- (BOOL)shouldUseGrabberAtEdge:(SBOffscreenEdge)edge;

- (void)handleGestureBeganWithLocation:(CGFloat)location;
- (void)handleGestureChangedWithLocation:(CGFloat)location velocity:(CGPoint)velocity;
- (void)handleGestureEndedWithLocation:(CGFloat)location velocity:(CGPoint)velocity completionType:(int)type;
- (void)handleGestureCanceled;
- (void)cancelGesture;

@end


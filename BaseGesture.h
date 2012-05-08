
#import "iPhonePrivate.h"

UIInterfaceOrientation CurrentInterfaceOrientation();
UIInterfaceOrientation HomeInterfaceOrientation();

@interface BaseGesture : NSObject {
    NSMutableArray *gestureRecognizers;
    BOOL isActive;
}

@property (nonatomic, readonly) BOOL isActive;
@property (nonatomic, readonly) NSMutableArray *gestureRecognizers;

- (void)addOffscreenEdge:(SBOffscreenEdge)edge minimumTouchCount:(int)count edgeMargin:(CGFloat)edgeMargin;
- (BOOL)currentOrientationIsSupported;
- (BOOL)shouldActivate;

- (void)handleGestureBeganWithLocation:(CGFloat)location;
- (void)handleGestureChangedWithLocation:(CGFloat)location velocity:(CGPoint)velocity;
- (void)handleGestureEndedWithLocation:(CGFloat)location velocity:(CGPoint)velocity completionType:(int)type;
- (void)handleGestureCanceled;
- (void)cancelGesture;

@end


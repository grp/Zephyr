
#import "iPhonePrivate.h"

@interface ZephyrBaseGesture : NSObject {
    NSMutableArray *gestureRecognizers;
    BOOL isActive;
}

@property (nonatomic, readonly) BOOL isActive;
@property (nonatomic, readonly) NSMutableArray *gestureRecognizers;

- (void)addOffscreenEdge:(SBOffscreenEdge)edge minimumTouchCount:(int)count edgeMargin:(CGFloat)edgeMargin;
- (BOOL)currentOrientationIsSupported;

- (BOOL)shouldActivateAtEdge:(SBOffscreenEdge)edge;
- (BOOL)shouldActivateAtEdge:(SBOffscreenEdge)edge atPoint:(CGPoint)point; // only if shouldActivateAtEdge: too.
- (BOOL)shouldUseGrabberAtEdge:(SBOffscreenEdge)edge;

- (void)handleGestureBegan:(SBGestureRecognizer *)recognizer withLocation:(CGFloat)location;
- (void)handleGestureChanged:(SBGestureRecognizer *)recognizer withLocation:(CGFloat)location velocity:(CGPoint)velocity;
- (void)handleGestureEnded:(SBGestureRecognizer *)recognizer withLocation:(CGFloat)location velocity:(CGPoint)velocity completionType:(int)type;
- (void)handleGestureCanceled:(SBGestureRecognizer *)recognizer;
- (void)cancelGesture;

@end


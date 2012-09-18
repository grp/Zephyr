
#import "BaseGesture.h"
#import "OffscreenGesture.h"

extern "C" BOOL ZephyrSwitchAppGestureIsActive();
extern "C" BOOL ZephyrSwitchAppGestureIsAnimatingCompletion();

@interface ZephyrSwitchAppGesture : ZephyrBaseGesture
@end


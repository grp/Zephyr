#import "NSTimer+Blocks.h"

@implementation NSTimer (Blocks)

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats {
    NSTimerBlock heapBlock = [block copy];
    NSTimer *timer = [self timerWithTimeInterval:seconds target:self selector:@selector(fireBlockTimer:) userInfo:heapBlock repeats:repeats];
    [heapBlock release];
    return timer;
}

+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats {
    NSTimerBlock heapBlock = [block copy];
    NSTimer *timer = [self scheduledTimerWithTimeInterval:seconds target:self selector:@selector(fireBlockTimer:) userInfo:heapBlock repeats:repeats];
    [heapBlock release];
    return timer;
}

+ (void)fireBlockTimer:(NSTimer *)timer {
    NSTimerBlock block = (NSTimerBlock) [timer userInfo];

    block(timer);
}

@end


#import "NSTimer+Blocks.h"

@implementation NSTimer (Blocks)

+ (NSTimer *)zephyrTimerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats {
    NSTimerBlock heapBlock = [block copy];
    NSTimer *timer = [self timerWithTimeInterval:seconds target:self selector:@selector(zephyrFireBlockTimer:) userInfo:heapBlock repeats:repeats];
    [heapBlock release];
    return timer;
}

+ (NSTimer *)zephyrScheduledTimerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats {
    NSTimerBlock heapBlock = [block copy];
    NSTimer *timer = [self scheduledTimerWithTimeInterval:seconds target:self selector:@selector(zephyrFireBlockTimer:) userInfo:heapBlock repeats:repeats];
    [heapBlock release];
    return timer;
}

+ (void)zephyrFireBlockTimer:(NSTimer *)timer {
    NSTimerBlock block = (NSTimerBlock) [timer userInfo];

    block(timer);
}

@end



typedef void (^NSTimerBlock)(NSTimer *timer);

@interface NSTimer (Blocks)

+ (NSTimer *)zephyrTimerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats;
+ (NSTimer *)zephyrScheduledTimerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats;

@end


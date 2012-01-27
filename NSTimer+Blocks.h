
typedef void (^NSTimerBlock)(NSTimer *timer);

@interface NSTimer (Blocks)

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats;
+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)seconds block:(NSTimerBlock)block repeats:(BOOL)repeats;

@end


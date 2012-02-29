#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface CALayer (Snapshot)
- (UIImage *)renderSnapshotWithScale:(CGFloat)scale;
@end

@interface UIView (Snapshot)
- (UIImage *)renderSnapshot;
@end

@interface UIImage (Saving)
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)atomically;
@end

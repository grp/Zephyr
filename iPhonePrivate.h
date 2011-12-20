
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <objc/runtime.h>
#import <substrate.h>

%config(generator=internal);

@class SBApplication;
@interface SpringBoard : UIApplication
- (UIInterfaceOrientation)activeInterfaceOrientation;
- (SBApplication *)_accessibilityFrontMostApplication;
- (void)noteInterfaceOrientationChanged:(UIInterfaceOrientation)orientation;
@end

static SpringBoard *SBApp = nil;

@interface UIDevice (Private)
- (void)setOrientation:(int)orientation animated:(BOOL)animated; // not sure if UIInterfaceOrientation or UIDeviceOrientation
@end

@interface SBDisplay : NSObject
- (BOOL)displayFlag:(unsigned)flag;
@end

@interface SBDisplayStack : NSObject
- (void)pushDisplay:(SBDisplay *)display;
- (void)popDisplay:(SBDisplay *)display;
- (BOOL)containsDisplay:(SBDisplay *)display;
@end

@interface SBAlert : SBDisplay
@end

@interface SBProcess : NSObject
- (void)killWithSignal:(int)signal;
@end

@interface SBApplication : SBDisplay
- (NSString *)displayIdentifier;
- (SBProcess *)process;
- (void)disableContextHostingForRequester:(CFStringRef)requester;
- (void)setActivationSetting:(unsigned)setting flag:(BOOL)flag;
- (void)setActivationSetting:(unsigned)setting value:(id)value;
- (void)setDeactivationSetting:(unsigned)setting flag:(BOOL)flag;
- (void)setDeactivationSetting:(unsigned)setting value:(id)value;
- (void)setDisplaySetting:(unsigned)setting flag:(BOOL)flag;
- (void)setDisplaySetting:(unsigned)setting value:(id)value;
- (int)suspensionType;
- (UIInterfaceOrientation)statusBarOrientation;
- (void)clearDeactivationSettings;
@end

@interface SBApplicationController : NSObject
+ (id)sharedInstance;
- (SBApplication *)applicationWithDisplayIdentifier:(NSString *)displayIdentifier;
@end

@interface SBAppSwitcherController : NSObject
+ (id)sharedInstance;
- (void)setupForApp:(id)app orientation:(UIInterfaceOrientation)orientation;
@end

@interface SBShowcaseContext : NSObject
@property(assign, nonatomic) int showcaseOrientation;
@end

@interface SBBulletinListController : NSObject
+ (id)sharedInstanceIfExists;
- (BOOL)listViewIsActive;
- (void)hideListViewAnimated:(BOOL)animated;
@end

@interface SBSwitchAppGestureView : UIView
@property(assign, nonatomic) float percentage;
@property(retain, nonatomic) SBApplication *endingApp;
@property(retain, nonatomic) SBApplication *leftwardApp;
@property(retain, nonatomic) SBApplication *rightwardApp;
@property(retain, nonatomic) SBApplication *startingApp;
- (id)initWithInterfaceOrientation:(int)interfaceOrientation startingApp:(SBApplication *)app leftwardApp:(SBApplication *)app3 rightwardApp:(SBApplication *)app4;
- (void)beginPaging;
- (void)finishBackwardToStartWithCompletion:(id)completion;
- (void)finishForwardToEndWithPercentage:(float)percentage completion:(id)completion;
- (void)moveToApp:(id)app;
- (void)moveToApp:(id)app animated:(BOOL)animated;
- (float)percentageForApp:(id)app;
- (void)updatePaging:(float)paging;
@end

typedef enum {
    kSBGestureTypeNone,
    kSBGestureTypeLaunchSuspend,
    kSBGestureTypeUnknown1,
    kSBGestureTypeUnknown2,
    kSBGestureTypeSwitchApp
} SBGestureType;

@interface SBGestureViewVendor : NSObject
+ (id)sharedInstance;
- (id)viewForApp:(SBApplication *)app gestureType:(SBGestureType)type includeStatusBar:(BOOL)include;
@end

@interface SBUIController : NSObject
+ (id)sharedInstance;
- (void)_switchAppGestureBegan;
- (void)_switchAppGestureCancelled;
- (void)_switchAppGestureChanged:(float)changed;
- (void)_switchAppGestureEndedWithCompletionType:(int)completionType cumulativePercentage:(float)percentage;
- (void)_switchAppGestureViewAnimationComplete;
- (void)_dismissShowcase:(double)unk unhost:(BOOL)unhost;
- (int)_dismissSheetsAndDetermineAlertStateForMenuClickOrSystemGesture;
- (BOOL)_activateSwitcherFrom:(id)from to:(id)to duration:(double)duration;
- (id)_calculateSwitchAppList;
- (void)_resumeEventsIfNecessary;
- (void)_lockOrientationForSystemGesture;
- (void)_releaseSystemGestureOrientationLock;
- (id)_makeSwitchAppFilteredList:(id)list initialApp:(SBApplication *)app;
- (void)_releaseSystemGestureOrientationLock;
- (void)_installSwitchAppGesturePlaceholderViewForEndingApp:(SBApplication *)endingApp;
- (id)_showcaseContextForOffset:(CGFloat)offset;
- (CGFloat)bottomBarHeight;
- (UIView *)rootView;
- (void)clearPendingAppActivatedByGesture;
- (BOOL)isSwitcherShowing;
- (void)clearZoomLayer;
- (void)setRootViewHiddenForScatter:(BOOL)scatter duration:(double)duration startTime:(double)time;
- (void)cleanupSwitchAppGestureStatusBar;
- (void)cleanupSwitchAppGestureViews;
- (void)notifyAppResignActive:(SBApplication *)application;
- (void)notifyAppResumeActive:(SBApplication *)application;
- (void)showSystemGestureBackdrop;
- (void)hideSystemGestureBackdrop;
- (void)prepareSwitchAppGestureStatusBar;
- (void)programmaticSwitchAppGestureApplyWithPercentage:(float)percentage;
- (void)programmaticSwitchAppGestureMoveToLeft;
- (void)programmaticSwitchAppGestureMoveToRight;
- (void)updateSwitchAppGestureStatusBar;
- (void)scheduleApplicationForLaunchByGesture:(SBApplication *)application;
@end

@interface SBAwayController : SBAlert
+ (id)sharedAwayController;
- (BOOL)isLocked;
@end

static NSMutableArray *displayStacks = nil;

#define SBWPreActivateDisplayStack        [displayStacks objectAtIndex:0]
#define SBWActiveDisplayStack             [displayStacks objectAtIndex:1]
#define SBWSuspendingDisplayStack         [displayStacks objectAtIndex:2]
#define SBWSuspendedEventOnlyDisplayStack [displayStacks objectAtIndex:3]

%group Shared

%hook SBDisplayStack

- (id)init {
    id stack = %orig;
    [displayStacks addObject:stack];
    return stack;
}

- (void)dealloc {
    [displayStacks removeObject:self];
    %orig;
}

%end

%hook SBUIController

- (void)finishLaunching {
    SBApp = (SpringBoard *) [objc_getClass("SpringBoard") sharedApplication];
    %orig;
}

%end

%end

%ctor {
    displayStacks = [[NSMutableArray alloc] init];
    %init(Shared);
}



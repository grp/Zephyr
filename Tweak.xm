
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <objc/runtime.h>
#import <substrate.h>

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

@interface SwipeDetectorWindow : UIWindow

@end

@implementation SwipeDetectorWindow

+ (BOOL)canSendEvents {
    return [SBApp _accessibilityFrontMostApplication] != nil
        && [SBApp activeInterfaceOrientation] == UIInterfaceOrientationPortrait
        && ![[objc_getClass("SBUIController") sharedInstance] isSwitcherShowing];
}

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        [self setWindowLevel:99999.0f];
        [self setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:(2.0f / 255.0f)]];
    }

    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    if (![[self class] canSendEvents]) return;

    id uic = [objc_getClass("SBUIController") sharedInstance];
    [uic _switchAppGestureBegan];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    if (![[self class] canSendEvents]) return;

    id uic = [objc_getClass("SBUIController") sharedInstance];
    CGPoint pt = [[touches anyObject] locationInView:self];
    [uic _switchAppGestureChanged:(pt.x / [[UIScreen mainScreen] bounds].size.width)];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    if (![[self class] canSendEvents]) return;

    // XXX: choose the correct completion type here

    id uic = [objc_getClass("SBUIController") sharedInstance];
    CGPoint pt = [[touches anyObject] locationInView:self];
    [uic _switchAppGestureEndedWithCompletionType:1 cumulativePercentage:(pt.x / [[UIScreen mainScreen] bounds].size.width)];
}

@end

NSMutableArray *displayStacks = nil;

#define SBWPreActivateDisplayStack        [displayStacks objectAtIndex:0]
#define SBWActiveDisplayStack             [displayStacks objectAtIndex:1]
#define SBWSuspendingDisplayStack         [displayStacks objectAtIndex:2]
#define SBWSuspendedEventOnlyDisplayStack [displayStacks objectAtIndex:3]

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

@interface SBUIController (SwipeDetectorWindow)
- (void)showSwipeDetectorWindows;
- (void)hideSwipeDetectorWindows;
@end

%hook SBUIController

static SwipeDetectorWindow *leftWindow, *rightWindow;

%new(v@:)
- (void)showSwipeDetectorWindows {
    [leftWindow setHidden:NO];
    [rightWindow setHidden:NO];
}

%new(v@:)
- (void)hideSwipeDetectorWindows {
    [leftWindow setHidden:YES];
    [rightWindow setHidden:YES];
}

// This is dumb as fuck. The "has multitasking gestures" state is stored in
// a random global variable which we cannot hook, and is set in a C function
// without an (exposed) name, so we also cannot hook that. This C function is
// called from dozens of methods, and as such cannot be hooked, especially as
// many of those functions that call it /break/ if you apply the necessary
// hooks around them (as well as the C function setting the varaible). Ugh. :(
- (void)_switchAppGestureBegan {
    SBApplication *topApplication = [SBApp _accessibilityFrontMostApplication];

    // XXX: what does this do, why does it not work here?
    /*if (topApplication != nil) {
        if ([topApplication displayFlag:0x3]) return;
        if ([topApplication displayFlag:0x1]) return;
    }*/

    // (there is some condition here in a C function, dunno what it does)
    if (![self _dismissSheetsAndDetermineAlertStateForMenuClickOrSystemGesture]) return;

    if (topApplication == nil) {
        topApplication = MSHookIvar<SBApplication *>(self, "_pendingAppActivatedByGesture");
        if (topApplication == nil) return;
    }

    NSMutableArray *unfilteredList = MSHookIvar<NSMutableArray *>(self, "_switchAppFullyOrderedList");
    if (unfilteredList == nil) {
        [self _calculateSwitchAppList];
        unfilteredList = MSHookIvar<NSMutableArray *>(self, "_switchAppFullyOrderedList");
    }

    NSArray *filteredList = [self _makeSwitchAppFilteredList:unfilteredList initialApp:topApplication];
    int topApplicationIndex = [filteredList indexOfObject:[topApplication displayIdentifier]];

    if ([filteredList count] == 0 || topApplicationIndex == NSNotFound) return;

    id bulletinListController = [objc_getClass("SBBulletinListController") sharedInstanceIfExists];
    if ([bulletinListController listViewIsActive]) {
        [bulletinListController hideListViewAnimated:YES];
    }

    MSHookIvar<BOOL>(self, "_switcherVisibleWhenSwitchAppGestureStarted") = [self isSwitcherShowing];

    [self clearPendingAppActivatedByGesture];
    [self _lockOrientationForSystemGesture];
    [self cleanupSwitchAppGestureViews];

    if (topApplication != nil) {
        if (![topApplication displayFlag:0x22]) {
            if (![topApplication displayFlag:0x1]) {
                if ([topApplication suspensionType] == 0) {
                    // call some C functions, that sorta do this (i'm too lazy to reverse these:)
                    [topApplication setDeactivationSetting:0xC flag:YES];
                    [[topApplication process] killWithSignal:9];
                }
            }
        } else {
            [self notifyAppResignActive:topApplication];
        }
    }

    // some c function... and another one.. sorta the second one below
    UIInterfaceOrientation currentOrientation = [SBApp activeInterfaceOrientation]; // also someting about "CAMediaTime", huh
    [[UIDevice currentDevice] setOrientation:currentOrientation animated:NO];
    [SBApp noteInterfaceOrientationChanged:currentOrientation];

    [self showSystemGestureBackdrop];

    id applicationController = [objc_getClass("SBApplicationController") sharedInstance];
    SBApplication *leftApplication = [applicationController applicationWithDisplayIdentifier:[filteredList objectAtIndex:0]];
    SBApplication *rightApplication = [applicationController applicationWithDisplayIdentifier:[filteredList lastObject]];

    if (leftApplication == topApplication) leftApplication = nil;
    if (rightApplication == topApplication) rightApplication = nil;

    [MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView") removeFromSuperview];
    [MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView") release];

    MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView") = [[objc_getClass("SBSwitchAppGestureView") alloc] initWithInterfaceOrientation:currentOrientation startingApp:topApplication leftwardApp:leftApplication rightwardApp:rightApplication];

    [MSHookIvar<UIView *>(self, "_contentView") addSubview:MSHookIvar<id>(self, "_switchAppGestureView")];
    [MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView") beginPaging];

    [self prepareSwitchAppGestureStatusBar];
    [self setRootViewHiddenForScatter:0 duration:0.0 startTime:0.0];
    [self updateSwitchAppGestureStatusBar];

    if ([self isSwitcherShowing]) {
        [self _dismissShowcase:0.0f unhost:NO];
    }
}

- (void)_switchAppGestureChanged:(CGFloat)percentage {
    [MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView") updatePaging:percentage];
    [self updateSwitchAppGestureStatusBar];
}

- (void)_switchAppGestureEndedWithCompletionType:(int)type cumulativePercentage:(float)percentage {
    SBSwitchAppGestureView *gestureView = MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView");

    id completion = ^{
        [self _switchAppGestureViewAnimationComplete];
    };

    if (type == 1) {
        [gestureView finishForwardToEndWithPercentage:percentage completion:completion];
    } else if (type == 0) {
        [gestureView finishBackwardToStartWithCompletion:completion];
    }

    [self updateSwitchAppGestureStatusBar];
}

- (void)_switchAppGestureViewAnimationComplete {
    SBSwitchAppGestureView *gestureView = MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView");
    if (gestureView == nil) return;

    [self hideSystemGestureBackdrop];

    SBApplication *startingApplication = [gestureView startingApp];
    SBApplication *endingApplication = [gestureView endingApp];

    [gestureView removeFromSuperview];
    [gestureView release];
    MSHookIvar<SBSwitchAppGestureView *>(self, "_switchAppGestureView") = nil;

    BOOL endingAppHasLaunchedFrontmost = [endingApplication displayFlag:1];

    [self clearZoomLayer];

    if (startingApplication != endingApplication) {
        UIInterfaceOrientation statusOrientation = [startingApplication statusBarOrientation];
        [startingApplication setDeactivationSetting:0x18 flag:YES];

        /* sub_2C330 */ {
            if ([SBWActiveDisplayStack containsDisplay:startingApplication] || [SBWSuspendedEventOnlyDisplayStack containsDisplay:startingApplication]) {
                /* sub_2B9B8 */ {
                    // this is a crude approximation of sorta kinda what this gigantic
                    // function does, since I'm waaaaay too lazy to reverse the whole
                    // thing: even just the graph in IDA is quite scary to look at! :(
                    [SBWActiveDisplayStack popDisplay:startingApplication];
                    [SBWSuspendingDisplayStack pushDisplay:startingApplication];
                }
            } else if (![SBWSuspendingDisplayStack containsDisplay:startingApplication]) {
                [startingApplication clearDeactivationSettings];
            }
        }
    }

    id applicationController = [objc_getClass("SBApplicationController") sharedInstance];
    for (NSString *displayIdentifier in MSHookIvar<NSArray *>(self, "_switchAppFilteredList")) {
        SBApplication *application = [applicationController applicationWithDisplayIdentifier:displayIdentifier];

        if (application != endingApplication) {
            [application disableContextHostingForRequester:CFSTR("SwitchApp")];
        }
    }

    [self cleanupSwitchAppGestureViews];

    BOOL shouldShowSwitcherAgain = NO;

    if (!endingAppHasLaunchedFrontmost) {
        // ending app hasn't launched; launch it now
        [self showSystemGestureBackdrop];
        [self scheduleApplicationForLaunchByGesture:endingApplication];
        [self _installSwitchAppGesturePlaceholderViewForEndingApp:endingApplication];

        shouldShowSwitcherAgain = YES;
    } else {
        [endingApplication disableContextHostingForRequester:CFSTR("SwitchApp")];
        [endingApplication disableContextHostingForRequester:CFSTR("LaunchSuspend")];

        if (startingApplication == endingApplication) {
            // ending app is same as starting app, resume it
            [self notifyAppResumeActive:endingApplication];

            shouldShowSwitcherAgain = YES;
        } else {
            // ending app needs to be re-launched, do it
            [self showSystemGestureBackdrop];
            [self scheduleApplicationForLaunchByGesture:endingApplication];
            [self _installSwitchAppGesturePlaceholderViewForEndingApp:endingApplication];
        }
    }

    if (shouldShowSwitcherAgain && MSHookIvar<BOOL>(self, "_switcherVisibleWhenSwitchAppGestureStarted")) {
        // show switcher again if it was hidden for the gesture to start

        id appSwitcherController = [objc_getClass("SBAppSwitcherController") sharedInstance];
        id zeroContext = [self _showcaseContextForOffset:0];
        id barContext = [self _showcaseContextForOffset:[self bottomBarHeight]];

        UIInterfaceOrientation currentOrientation = [SBApp activeInterfaceOrientation]; // also someting about "CAMediaTime", huh
        [zeroContext setShowcaseOrientation:currentOrientation];
        [barContext setShowcaseOrientation:currentOrientation];

        [self _activateSwitcherFrom:zeroContext to:barContext duration:0];
    }

    MSHookIvar<BOOL>(self, "_switcherVisibleWhenSwitchAppGestureStarted") = NO;
    MSHookIvar<BOOL>(self, "_switchAppGestureStatusBarMaintained") = NO;

    // two more C functions; unknown purpose

    [self _resumeEventsIfNecessary];

    if (endingAppHasLaunchedFrontmost) {
        [self _releaseSystemGestureOrientationLock];
    }
}

- (void)finishLaunching {
    CGFloat windowPercentage = 0.03f;
    CGRect windowFrame;

    windowFrame = [[UIScreen mainScreen] bounds];
    windowFrame.size.width *= windowPercentage;
    leftWindow = [[SwipeDetectorWindow alloc] initWithFrame:windowFrame];

    windowFrame = [[UIScreen mainScreen] bounds];
    windowFrame.origin.x += windowFrame.size.width * (1.0f - windowPercentage);
    windowFrame.size.width *= windowPercentage;
    rightWindow = [[SwipeDetectorWindow alloc] initWithFrame:windowFrame];

    %orig;
    SBApp = (SpringBoard *) [objc_getClass("SpringBoard") sharedApplication];

    [self performSelector:@selector(showSwipeDetectorWindows) withObject:nil afterDelay:1.0];
}

- (void)tearDownIconListAndBar {
    %orig;
    [self showSwipeDetectorWindows];
}

- (void)restoreIconList:(BOOL)animate {
    %orig;
    [self hideSwipeDetectorWindows];
}

- (void)lock {
    %orig;
    [self hideSwipeDetectorWindows];
}

- (void)lockFromSource:(int)source {
    %orig;
    [self hideSwipeDetectorWindows];
}

%end

%ctor {
    displayStacks = [[NSMutableArray alloc] init];
}


/*
typedef enum {
    kSBOffscreenEdgeLeft = 1,
    kSBOffscreenEdgeRight = 4,
    kSBOffscreenEdgeTop = 2,
    kSBOffscreenEdgeBottom = 8
} SBOffscreenEdge;

static BOOL began = NO;

@interface SBGestureRecognizer : NSObject
@property (nonatomic, copy) void (^handler)(id gestureRecognizer);
@property (nonatomic, copy) BOOL (^canBeginCondition)();
@property (nonatomic, assign) int types;
@property (nonatomic, assign) int minTouches;
@end

@interface SBFluidSwipeGestureRecognizer : SBGestureRecognizer
- (CGPoint)centroidPoint;
@end

@interface SBPanGestureRecognizer : SBFluidSwipeGestureRecognizer
@end

@interface SBOffscreenSwipeGestureRecognizer : SBPanGestureRecognizer
@property (nonatomic, assign) BOOL sendsTouchesCancelledToApplication;
@property (nonatomic, assign) BOOL allowableDistanceFromEdgeCenter;
@end

%hook SBUIController

- (void)finishLaunching {

    NSLog(@"before");

    SBOffscreenSwipeGestureRecognizer *gu = [[objc_getClass("SBOffscreenSwipeGestureRecognizer") alloc] initForOffscreenEdge:kSBOffscreenEdgeTop];
    NSLog(@"init'd");
    //[gu setTypes:8];
    NSLog(@"types");
    [gu setMinTouches:1];
    NSLog(@"touched");
//%hook SBOffscreenSwipeGestureRecognizer
//- (void)setHandler:(id)h { 
    void (^handler)(id) = ^void (SBFluidSwipeGestureRecognizer *gesture) {
        NSLog(@"handled");

        id app = topapp();
        NSLog(@"top app is: %@", topapp());
        if (!app) return;

        float y = [gesture 
        id uic = [objc_getClass("SBUIController") sharedInstance];
        
        if (!began) [uic _switchAppGestureBegan];
        began = YES;

        [uic _switchAppGestureChanged:y];

//150 - (void)_switchAppGestureBegan;
//151 - (void)_switchAppGestureCancelled;
//152 - (void)_switchAppGestureChanged:(float)changed;
//153 - (void)_switchAppGestureEndedWithCompletionType:(int)completionType cumulativePercentage:(float)percentage;
    };

    //%orig(handler);;
    //NSLog(@"set handler");
    
    NSLog(@"set handler");
    [gu setCanBeginCondition:^BOOL () {
        NSLog(@"can begin?");
        return topapp() != nil;
    }];
    NSLog(@"can begin!");
    [gu setSendsTouchesCancelledToApplication:YES];
    NSLog(@"set cancelled");
    [gu setAllowableDistanceFromEdgeCenter:0.5f];
    NSLog(@"set allow");

    %orig;
}

%end

*/


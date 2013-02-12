
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <GraphicsServices/GraphicsServices.h>
#import <objc/runtime.h>
#import <substrate.h>

%config(generator=internal);

extern NSString *kGSMultitaskingGesturesCapability;

@interface UIApplication (Private)
- (UIWindow *)statusBarWindow;
- (UIInterfaceOrientation)activeInterfaceOrientation;
@end

@class SBApplication;
@interface SpringBoard : UIApplication
- (SBApplication *)_accessibilityFrontMostApplication;
- (BOOL)_accessibilityIsSystemGestureActive;
- (void)_accessibilitySetSystemGesturesDisabledByAccessibility:(BOOL)disabled;

- (void)applicationOpenURL:(NSURL *)url publicURLsOnly:(BOOL)publicOnly;

- (void)_handleMenuButtonEvent;
- (void)clearMenuButtonTimer;
- (void)menuButtonDown:(GSEventRef)event;
- (void)menuButtonUp:(GSEventRef)event;
- (void)lockButtonDown:(GSEventRef)event;
- (void)lockButtonUp:(GSEventRef)event;

- (void)showSpringBoardStatusBar;
- (void)hideSpringBoardStatusBar;

- (UIInterfaceOrientation)_frontMostAppOrientation;
- (UIInterfaceOrientation)interfaceOrientationForCurrentDeviceOrientation;
- (void)noteInterfaceOrientationChanged:(UIInterfaceOrientation)orientation;
@end

static SpringBoard *SBApp = nil;

@interface UIDevice (Private)
- (void)setOrientation:(int)orientation animated:(BOOL)animated; // not sure if UIInterfaceOrientation or UIDeviceOrientation
@end

@interface UIStatusBar : UIView
- (void)requestStyle:(UIStatusBarStyle)style animated:(BOOL)animated;
@end

extern CGFloat UIStatusBarHeight;

@interface SBDisplay : NSObject // iOS 5
- (BOOL)displayFlag:(unsigned)flag;
@end

@interface SBDisplayStack : NSObject // iOS 5
- (void)pushDisplay:(SBDisplay *)display;
- (void)popDisplay:(SBDisplay *)display;
- (BOOL)containsDisplay:(SBDisplay *)display;
@end

@interface SBAlert : SBDisplay
@end

@interface SBProcess : NSObject // iOS 5
- (void)killWithSignal:(int)signal;
@end

@interface SBApplication : SBDisplay // iOS 6: NSObject
+ (BOOL)multitaskingIsSupported; // iOS 5
- (SBProcess *)process; // iOS 5
- (int)suspensionType; // iOS 5
- (NSString *)displayIdentifier;
- (void)enableContextHostingForRequester:(CFStringRef)requester orderFront:(BOOL)orderFront;
- (void)disableContextHostingForRequester:(CFStringRef)requester;
- (void)setActivationSetting:(unsigned)setting flag:(BOOL)flag;
- (void)setActivationSetting:(unsigned)setting value:(id)value;
- (void)setDeactivationSetting:(unsigned)setting flag:(BOOL)flag;
- (void)setDeactivationSetting:(unsigned)setting value:(id)value;
- (void)setDisplaySetting:(unsigned)setting flag:(BOOL)flag;
- (void)setDisplaySetting:(unsigned)setting value:(id)value;
- (UIInterfaceOrientation)statusBarOrientation;
- (void)clearDeactivationSettings;
- (void)willAnimateActivation; // iOS 6
- (void)didAnimateActivation; // iOS 6
@end

@interface SBApplicationController : NSObject
+ (id)sharedInstance;
- (SBApplication *)applicationWithDisplayIdentifier:(NSString *)displayIdentifier;
@end

typedef enum {
    SBShowcaseModeHidden,
    SBShowcaseModeDefault,
    SBShowcaseModeFull
} SBShowcaseMode; // iOS 6

@interface SBShowcaseViewController : NSObject
- (CGFloat)revealAmountForMode:(SBShowcaseMode)mode; // iOS 6
@end

@interface SBAppSwitcherController : SBShowcaseViewController
+ (id)sharedInstance;
- (BOOL)printViewIsShowing;
- (CGFloat)bottomBarHeight;
- (void)setupForApp:(SBApplication *)app orientation:(UIInterfaceOrientation)orientation;
@end

@interface SBAssistantController : SBShowcaseViewController
+ (id)sharedInstance;
+ (BOOL)isAssistantVisible; // iOS 6
- (BOOL)isAssistantVisible; // iOS 5
@end

@interface SBShowcaseContext : NSObject
@property(assign, nonatomic) UIInterfaceOrientation showcaseOrientation;
@end

@interface SBOrientationLockManager : NSObject
+ (id)sharedInstance;
- (void)setLockOverrideEnabled:(BOOL)enabled forReason:(id)reason;
@end

@interface SBBulletinListTabView : UIView
@end

@interface SBBulletinListView : UIView
@property(readonly, assign) CGFloat currentY;
@property(readonly, retain) UIImageView *linenView;
@property(readonly, retain) UIView *slidingView;
@property(readonly, retain) UITableView *tableView;
- (CGFloat)offscreenY;
- (CGFloat)onscreenY;
- (void)positionSlidingViewAtY:(CGFloat)y;
- (void)setBottomCornersOffscreen:(BOOL)offscreen animated:(BOOL)animated;
- (void)setBottomShadowAlpha:(CGFloat)alpha;
- (void)setCornerAlpha:(CGFloat)alpha;
- (void)setShowsNoNotificationsLabel:(BOOL)label animated:(BOOL)animated;
- (CGRect)slidingViewFrame;
@end

@interface SBBulletinListController : NSObject
@property(readonly, retain) SBBulletinListView *listView;
@property(readonly, assign) BOOL listViewIsActive;
+ (id)sharedInstance;
+ (id)sharedInstanceIfExists;
- (void)_updateForTouchBeganOrMovedWithLocation:(CGPoint)location velocity:(CGPoint)velocity;
- (void)_updateForTouchCanceled;
- (void)_updateForTouchEndedWithVelocity:(CGPoint)velocity completion:(id)completion;

- (void)handleShowNotificationsGestureBeganWithTouchLocation:(CGPoint)touchLocation;
- (void)handleShowNotificationsGestureCanceled;
- (void)handleShowNotificationsGestureChangedWithTouchLocation:(CGPoint)touchLocation velocity:(CGPoint)velocity;
- (void)handleShowNotificationsGestureEndedWithVelocity:(CGPoint)velocity completion:(id)completion;

- (void)hideListViewAnimated:(BOOL)animated;
- (void)hideListViewWithInitialVelocity:(CGFloat)initialVelocity completion:(id)completion;
- (void)hideListViewWithInitialVelocity:(CGFloat)initialVelocity hiddenY:(CGFloat)y extraPull:(BOOL)pull additionalValueApplier:(id)applier completion:(id)completion;

- (void)prepareToHideListViewAnimated:(BOOL)hideListViewAnimated;
- (void)prepareToShowListViewAnimated:(BOOL)showListViewAnimated aboveBanner:(BOOL)banner;

- (void)positionListViewAtY:(CGFloat)y;

- (void)showListViewAnimated:(BOOL)animated;
- (void)showListViewWithInitialVelocity:(CGFloat)initialVelocity additionalValueApplier:(id)applier completion:(id)completion;
- (void)showListViewWithInitialVelocity:(CGFloat)initialVelocity completion:(id)completion;

- (void)_cleanupAfterShowListView;
- (void)_cleanupAfterHideListView; // iOS 5
- (void)_cleanupAfterHideListViewKeepingWindow:(BOOL)window; // iOS 6
@end

@interface SBBulletinWindowController : NSObject
@property(readonly, assign, nonatomic) UIWindow *window;
@property(readonly, assign, nonatomic) UIInterfaceOrientation windowOrientation;
+ (id)sharedInstance;
- (BOOL)allowsDismissBannerGesture;
- (BOOL)allowsHideNotificationsGesture;
- (BOOL)allowsShowNotificationsGesture;
- (BOOL)isBusy;
@end

@interface SBLinenView : UIView
@end

@interface SBSwitchAppGestureView : UIView
@property(assign, nonatomic) CGFloat percentage;
@property(retain, nonatomic) SBApplication *endingApp;
@property(retain, nonatomic) SBApplication *leftwardApp;
@property(retain, nonatomic) SBApplication *rightwardApp;
@property(retain, nonatomic) SBApplication *startingApp;
- (id)initWithInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation startingApp:(SBApplication *)app leftwardApp:(SBApplication *)app3 rightwardApp:(SBApplication *)app4;
- (void)beginPaging;
- (void)finishBackwardToStartWithCompletion:(id)completion;
- (void)finishForwardToEndWithPercentage:(CGFloat)percentage completion:(id)completion;
- (void)moveToApp:(SBApplication *)app;
- (void)moveToApp:(SBApplication *)app animated:(BOOL)animated;
- (CGFloat)percentageForApp:(SBApplication *)app;
- (void)updatePaging:(CGFloat)paging;
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
- (void)clearCacheForApp:(SBApplication *)app reason:(id)reason;
- (UIView *)viewForApp:(SBApplication *)app gestureType:(SBGestureType)type includeStatusBar:(BOOL)include;
- (UIView *)viewForApp:(SBApplication *)app gestureType:(SBGestureType)type includeStatusBar:(BOOL)include decodeImage:(BOOL)decode; // iOS 5.1
@end

@class SBGestureRecognizer;

@interface SBUIController : NSObject
+ (id)sharedInstance;
- (UIView *)rootView;

- (BOOL)_ignoringEvents;

- (void)_noteAppDidAcitvate:(SBApplication *)app; // iOS 6
- (void)_noteAppDidFailToAcitvate:(SBApplication *)app; // iOS 6

- (void)_setToggleSwitcherAfterLaunchApp:(SBApplication *)app; // iOS 6
- (SBApplication *)_toggleSwitcherAfterLaunchApp; // iOS 6

- (BOOL)_canActivateShowcaseIgnoringTouches:(BOOL)touches;
- (void)_activateSwitcher:(NSTimeInterval)duration;
- (void)_dismissShowcase:(NSTimeInterval)duration unhost:(BOOL)unhost;

- (void)_clearSwitchAppList;
- (id)_calculateSwitchAppList;

- (void)_switchAppGestureBegan; // iOS 5.0
- (void)_switchAppGestureBegan:(CGFloat)location; // iOS 5.1
- (void)_switchAppGestureChanged:(CGFloat)location;
- (void)_switchAppGestureEndedWithCompletionType:(int)type cumulativePercentage:(CGFloat)location;
- (void)_switchAppGestureCancelled;
- (void)_switchAppGestureViewAnimationComplete;

- (void)handleDismissBannerSystemGesture:(SBGestureRecognizer *)recognizer;
- (void)handleFluidHorizontalSystemGesture:(SBGestureRecognizer *)recognizer;
- (void)handleFluidVerticalSystemGesture:(SBGestureRecognizer *)recognizer;
- (void)handleFluidScaleSystemGesture:(SBGestureRecognizer *)recognizer;
- (void)handleHideNotificationsSystemGesture:(SBGestureRecognizer *)recognizer;

- (SBShowcaseContext *)_showcaseContextForOffset:(CGFloat)offset;
- (void)_toggleSwitcher;
- (BOOL)_activateSwitcherFrom:(SBShowcaseContext *)from to:(SBShowcaseContext *)to duration:(NSTimeInterval)duration; // iOS 5
- (BOOL)_activateSwitcher:(NSTimeInterval)duration fromSystemGesture:(BOOL)systemGesture; // iOS 6

- (void)_clearGestureViewVendorCacheForAppWithDisplayIdenitifier:(NSString *)displayIdenitifier;
- (void)_prefetchAdjacentAppsAndEvictRemotes:(SBApplication *)currentApplication; // iOS 5.1
- (void)prefetchAdjacentAppsAndEvictRemotes:(SBApplication *)currentApplication; // iOS 6

- (id)_makeSwitchAppValidList:(id)list;
- (id)_makeSwitchAppFilteredList:(id)list initialApp:(SBApplication *)app;
- (void)_getSwitchAppPrefetchApps:(id)apps initialApp:(SBApplication *)app outLeftwardAppIdentifier:(NSString **)leftwardIdentifier outRightwardAppIdentifier:(NSString **)rightwardIdentifier; // iOS 6

- (int)_dismissSheetsAndDetermineAlertStateForMenuClickOrSystemGesture;
- (void)_resumeEventsIfNecessary;
- (void)_lockOrientationForSystemGesture;
- (void)_releaseSystemGestureOrientationLock;
- (void)_releaseSystemGestureOrientationLock;

- (void)_clearAllInstalledSystemGestureViews;
- (void)_installSwitchAppGesturePlaceholderViewForEndingApp:(SBApplication *)endingApp;

- (void)createFakeSpringBoardStatusBar;
- (void)setFakeSpringBoardStatusBarVisible:(BOOL)visible;
- (void)clearFakeSpringBoardStatusBarAndCorners;

- (void)setRootViewHiddenForScatter:(BOOL)scatter duration:(NSTimeInterval)duration startTime:(NSTimeInterval)time; // iOS 5
- (void)setRootViewHiddenForScatter:(BOOL)scatter duration:(NSTimeInterval)duration delay:(NSTimeInterval)delay; // iOS 6

- (void)restoreIconListAnimated:(BOOL)animated animateWallpaper:(BOOL)animateWallpaper keepSwitcher:(BOOL)keepSwitcher;
- (void)stopRestoringIconList;
- (void)tearDownIconListAndBar;

- (BOOL)isSwitcherShowing;

- (void)clearZoomLayer; // iOS 5

- (void)prepareSwitchAppGestureStatusBar;
- (void)updateSwitchAppGestureStatusBar;
- (void)cleanupSwitchAppGestureStatusBar;

- (void)cleanupSwitchAppGestureViews;
- (void)cleanupRunningGestureIfNeeded;

- (void)notifyAppResignActive:(SBApplication *)application;
- (void)notifyAppResumeActive:(SBApplication *)application;

- (void)showSystemGestureBackdrop;
- (void)hideSystemGestureBackdrop;

- (void)programmaticSwitchAppGestureApplyWithPercentage:(CGFloat)percentage;
- (void)programmaticSwitchAppGestureMoveToLeft;
- (void)programmaticSwitchAppGestureMoveToRight;

- (void)scheduleApplicationForLaunchByGesture:(SBApplication *)application;
- (void)clearPendingAppActivatedByGesture;
@end

@interface SBFolder : NSObject
@end

@interface SBIconController : NSObject
+ (id)sharedInstance;
@property (assign) BOOL isEditing;
@property (retain) SBFolder *openFolder;
@end

@interface SBAwayController : SBAlert
+ (id)sharedAwayController;
+ (id)sharedAwayControllerIfExists;
- (BOOL)allowDismissCameraSystemGesture; // iOS 5.1+
- (void)handleDismissCameraSystemGesture:(SBGestureRecognizer *)gesture; // iOS 5.1+
- (BOOL)isLocked;
@end

@interface SBLockdownManager : NSObject
+ (id)sharedInstance;
- (void)_developerDeviceStateChanged;
@end

typedef enum { /* no fucking clue */ } SBTouchType;

typedef struct {
    SBTouchType type;
    NSUInteger pathIndex;
    CGPoint location;
    CGPoint previousLocation;
    CGFloat totalDistanceTraveled;
    UIInterfaceOrientation interfaceOrientation;
    UIInterfaceOrientation previousInterfaceOrientation;
} SBTouchInfo;

typedef struct {
    UIEdgeInsets pixelDeltas; // 0x00, 0x04, 0x08, 0x0C
    UIEdgeInsets averageVelocities; // 0x10, 0x14, 0x18, 0x1C
    CGFloat averageTranslation; // 0x20
    CGPoint movementVelocityInPointsPerSecond; // 0x24, 0x28
    CGFloat farthestFingerSeparation; // 0x2C
    NSInteger activeTouchCount; // 0x30

    int unk1;
    int unk2;
    int unk3;
    int unk4;

    SBTouchInfo activeTouches[30]; // 0x44; count is activeTouchCount
} SBGestureContext;

typedef enum {
    SBGestureRecognizerStatePossible,
    SBGestureRecognizerStateBegan,
    SBGestureRecognizerStateChanged,
    SBGestureRecognizerStateEnded,
    SBGestureRecognizerStateCancelled,
    SBGestureRecognizerStateFailed,
    SBGestureRecognizerStateRecognized = SBGestureRecognizerStateEnded
} SBGestureRecognizerState;

typedef enum {
    kSBOffscreenEdgeLeft = 1,
    kSBOffscreenEdgeTop = 2,
    kSBOffscreenEdgeRight = 4,
    kSBOffscreenEdgeBottom = 8
} SBOffscreenEdge;

@interface SBGestureRecognizer : NSObject
@property (nonatomic, copy) void (^handler)();
@property (nonatomic, copy) BOOL (^canBeginCondition)();
@property (nonatomic, assign) int types;
@property (nonatomic, assign) SBGestureRecognizerState state;
@property (assign, nonatomic) BOOL sendsTouchesCancelledToApplication;
- (void)reset;
- (BOOL)shouldReceiveTouches;
- (int)templateMatch;
- (void)touchesBegan:(SBGestureContext *)began;
- (void)touchesCancelled:(SBGestureContext *)cancelled;
- (void)touchesEnded:(SBGestureContext *)ended;
- (void)touchesMoved:(SBGestureContext *)moved;
@end

@interface SBFluidSlideGestureRecognizer : SBGestureRecognizer
@property (nonatomic, assign) NSInteger minTouches;
@property(assign, nonatomic) int requiredDirectionality;
@property(assign, nonatomic) CGFloat accelerationPower;
@property(assign, nonatomic) CGFloat accelerationThreshold;
@property(assign, nonatomic) CGFloat animationDistance;
@property(readonly, assign, nonatomic) int degreeOfFreedom;
@property(readonly, assign, nonatomic) CGFloat cumulativeMotion;
@property(readonly, assign, nonatomic) CGFloat cumulativePercentage;
@property(readonly, assign, nonatomic) CGFloat incrementalMotion;
@property(readonly, assign, nonatomic) CGFloat skippedCumulativePercentage;
@property(readonly, assign, nonatomic) CGPoint centroidPoint;
@property(readonly, assign, nonatomic) CGPoint movementVelocityInPointsPerSecond;
- (int)completionTypeProjectingMomentumForInterval:(NSTimeInterval)interval;
- (CGPoint)centroidPoint;
@end

@interface SBPanGestureRecognizer : SBFluidSlideGestureRecognizer
@end

@interface SBOffscreenSwipeGestureRecognizer : SBPanGestureRecognizer
@property(assign, nonatomic) CGFloat allowableDistanceFromEdgeCenter;
@property(assign, nonatomic) CGFloat edgeCenter;
@property(assign, nonatomic) CGFloat edgeMargin;
@property(assign, nonatomic) CGFloat falseEdge;
@property(assign, nonatomic) BOOL requiresSecondTouchInRange;
- (id)initForOffscreenEdge:(SBOffscreenEdge)edge;
- (void)_updateAnimationDistanceAndEdgeCenter;
- (BOOL)firstTouchInRange:(CGPoint)range;
- (BOOL)secondTouchInRange:(CGPoint)range;
@end

@interface SBHandMotionExtractor : NSObject
@property (readonly, assign, nonatomic) UIEdgeInsets allPixelDeltas;
@property (readonly, assign, nonatomic) CGFloat averageTranslation;
@property (readonly, assign, nonatomic) UIEdgeInsets averageVelocities;
@property (readonly, assign, nonatomic) CGFloat farthestFingerSeparation;
@property (readonly, assign, nonatomic) CGPoint movementVelocityInPointsPerSecond;
@property (readonly, assign, nonatomic) UIEdgeInsets pixelDeltas;
- (void)clear;
- (void)extractHandMotionForActiveTouches:(SBTouchInfo *)activeTouches count:(NSUInteger)count centroid:(CGPoint)centroid;
@end

@interface BKSWorkspace : NSObject // iOS 6
@end

@interface SBWorkspaceTransaction : NSObject // iOS 6
@property (readonly, assign) BOOL completed;
@property (readonly, assign, nonatomic) BKSWorkspace *workspace;
- (id)initWithWorkspace:(BKSWorkspace *)workspace alertManager:(id)manager;
- (void)commit;
- (BOOL)canBeInterrupted;
- (void)interrupt;
@end

@interface SBToAppWorkspaceTransaction : SBWorkspaceTransaction // iOS 6
@property (retain, nonatomic) SBApplication *toApplication;
- (id)initWithWorkspace:(BKSWorkspace *)workspace alertManager:(id)manager toApplication:(SBApplication *)application;
@end

@interface SBAppToAppWorkspaceTransaction : SBToAppWorkspaceTransaction // iOS 6
@property (retain, nonatomic) SBApplication *fromApp;
- (id)initWithWorkspace:(BKSWorkspace *)workspace alertManager:(id)manager exitedApp:(SBApplication *)app;
- (id)initWithWorkspace:(BKSWorkspace *)workspace alertManager:(id)manager from:(SBApplication *)from to:(SBApplication *)to;
@end

@interface SBWorkspace : NSObject // iOS 6
@property (nonatomic, assign, readonly) BKSWorkspace *bksWorkspace;
@property (nonatomic, retain) SBWorkspaceTransaction *currentTransaction;
- (void)updateInterruptedByCallSettingsFrom:(SBApplication *)from to:(SBApplication *)to;
@end

@interface SBWorkspaceEvent : NSObject // iOS 6
+ (id)eventWithLabel:(NSString *)label handler:(void (^)())handler;
@end

@interface SBWorkspaceEventQueue : NSObject // iOS 6
+ (id)sharedInstance;
- (void)executeOrPrependEvent:(SBWorkspaceEvent *)event;
- (void)executeOrAppendEvent:(SBWorkspaceEvent *)event;
@end

static NSMutableArray *displayStacks = nil;

#define SBWPreActivateDisplayStack        [displayStacks objectAtIndex:0]
#define SBWActiveDisplayStack             [displayStacks objectAtIndex:1]
#define SBWSuspendingDisplayStack         [displayStacks objectAtIndex:2]
#define SBWSuspendedEventOnlyDisplayStack [displayStacks objectAtIndex:3]

static SBWorkspace *sharedWorkspace = nil;

#define SBWSharedWorkspace sharedWorkspace

%group Shared

%hook SBDisplayStack

- (id)init {
    self = %orig;
    [displayStacks addObject:self];
    return self;
}

- (void)dealloc {
    [displayStacks removeObject:self];
    %orig;
}

%end

%hook SBWorkspace

- (id)init {
    self = %orig;
    sharedWorkspace = self;
    return self;
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


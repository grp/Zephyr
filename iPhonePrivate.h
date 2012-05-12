
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <GraphicsServices/GraphicsServices.h>
#import <objc/runtime.h>
#import <substrate.h>

%config(generator=internal);

@class SBApplication;
@interface SpringBoard : UIApplication
- (SBApplication *)_accessibilityFrontMostApplication;
- (BOOL)_accessibilityIsSystemGestureActive;
- (UIInterfaceOrientation)_frontMostAppOrientation;
- (void)menuButtonDown:(GSEventRef)event;
- (void)menuButtonUp:(GSEventRef)event;
- (void)lockButtonDown:(GSEventRef)event;
- (void)lockButtonUp:(GSEventRef)event;
- (void)showSpringBoardStatusBar;
- (void)hideSpringBoardStatusBar;
- (UIInterfaceOrientation)activeInterfaceOrientation;
- (UIInterfaceOrientation)interfaceOrientationForCurrentDeviceOrientation;
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
+ (BOOL)multitaskingIsSupported;
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

@interface SBShowcaseViewController : NSObject
@end

@interface SBAppSwitcherController : SBShowcaseViewController
+ (id)sharedInstance;
- (BOOL)printViewIsShowing;
- (CGFloat)bottomBarHeight;
- (void)setupForApp:(SBApplication *)app orientation:(UIInterfaceOrientation)orientation;
@end

@interface SBAssistantController : SBShowcaseViewController
+ (id)sharedInstance;
- (BOOL)isAssistantVisible;
@end

@interface SBShowcaseContext : NSObject
@property(assign, nonatomic) int showcaseOrientation;
@end

@interface SBOrientationLockManager : NSObject
+ (id)sharedInstance;
- (void)setLockOverrideEnabled:(BOOL)enabled forReason:(id)reason;
@end

@interface SBBulletinListView : UIView
@property(readonly, assign) float currentY;
@property(readonly, retain) UIImageView *linenView;
@property(readonly, retain) UIView *slidingView;
@property(readonly, retain) UITableView *tableView;
+ (id)_pathToLinenCache;
+ (id)linen;
+ (void)loadLinen;
+ (void)removeCachedLinen;
- (float)offscreenY;
- (float)onscreenY;
- (void)positionSlidingViewAtY:(float)y;
- (void)setBottomCornersOffscreen:(BOOL)offscreen animated:(BOOL)animated;
- (void)setBottomShadowAlpha:(float)alpha;
- (void)setCornerAlpha:(float)alpha;
- (void)setShowsNoNotificationsLabel:(BOOL)label animated:(BOOL)animated;
- (CGRect)slidingViewFrame;
@end

@interface SBBulletinListController : NSObject
@property(readonly, retain) SBBulletinListView *listView;
@property(readonly, assign) BOOL listViewIsActive;
+ (id)sharedInstance;
+ (id)sharedInstanceIfExists;
- (void)_cleanupAfterHideListView;
- (void)_cleanupAfterShowListView;
- (void)_updateForTouchBeganOrMovedWithLocation:(CGPoint)location velocity:(CGPoint)velocity;
- (void)_updateForTouchCanceled;
- (void)_updateForTouchEndedWithVelocity:(CGPoint)velocity completion:(id)completion;
- (void)handleShowNotificationsGestureBeganWithTouchLocation:(CGPoint)touchLocation;
- (void)handleShowNotificationsGestureCanceled;
- (void)handleShowNotificationsGestureChangedWithTouchLocation:(CGPoint)touchLocation velocity:(CGPoint)velocity;
- (void)handleShowNotificationsGestureEndedWithVelocity:(CGPoint)velocity completion:(id)completion;
- (void)hideListViewAnimated:(BOOL)animated;
- (void)hideListViewWithInitialVelocity:(float)initialVelocity completion:(id)completion;
- (void)hideListViewWithInitialVelocity:(float)initialVelocity hiddenY:(float)y extraPull:(BOOL)pull additionalValueApplier:(id)applier completion:(id)completion;
- (void)prepareToHideListViewAnimated:(BOOL)hideListViewAnimated;
- (void)prepareToShowListViewAnimated:(BOOL)showListViewAnimated aboveBanner:(BOOL)banner;
- (void)positionListViewAtY:(float)y;
- (void)showListViewAnimated:(BOOL)animated;
- (void)showListViewWithInitialVelocity:(float)initialVelocity additionalValueApplier:(id)applier completion:(id)completion;
- (void)showListViewWithInitialVelocity:(float)initialVelocity completion:(id)completion;
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
- (id)initWithInterfaceOrientation:(int)interfaceOrientation startingApp:(SBApplication *)app leftwardApp:(SBApplication *)app3 rightwardApp:(SBApplication *)app4;
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
- (UIView *)viewForApp:(SBApplication *)app gestureType:(SBGestureType)type includeStatusBar:(BOOL)include;
@end

@interface SBUIController : NSObject
+ (id)sharedInstance;
- (void)_revealShowcase:(SBShowcaseViewController *)showcase duration:(NSTimeInterval)duration from:(SBShowcaseContext *)from to:(SBShowcaseContext *)to;

- (id)_calculateSwitchAppList;
- (void)_switchAppGestureBegan; // iOS 5.0
- (void)_switchAppGestureBegan:(float)location; // iOS 5.1
- (void)_switchAppGestureChanged:(float)location;
- (void)_switchAppGestureEndedWithCompletionType:(int)type cumulativePercentage:(float)location;
- (void)_switchAppGestureCancelled;
- (void)_switchAppGestureViewAnimationComplete;

- (void)_dismissShowcase:(double)unk unhost:(BOOL)unhost;
- (int)_dismissSheetsAndDetermineAlertStateForMenuClickOrSystemGesture;
- (BOOL)_activateSwitcherFrom:(SBShowcaseContext *)from to:(SBShowcaseContext *)to duration:(NSTimeInterval)duration;
- (void)_resumeEventsIfNecessary;
- (void)_lockOrientationForSystemGesture;
- (void)_releaseSystemGestureOrientationLock;
- (id)_makeSwitchAppFilteredList:(id)list initialApp:(SBApplication *)app;
- (void)_releaseSystemGestureOrientationLock;
- (void)_installSwitchAppGesturePlaceholderViewForEndingApp:(SBApplication *)endingApp;
- (id)_showcaseContextForOffset:(CGFloat)offset;

- (void)restoreIconListAnimated:(BOOL)animated animateWallpaper:(BOOL)animateWallpaper keepSwitcher:(BOOL)keepSwitcher;
- (void)stopRestoringIconList;
- (void)tearDownIconListAndBar;
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

@interface SBIconController : NSObject
+ (id)sharedInstance;
@property (assign) BOOL isEditing;
@end

@interface SBAwayController : SBAlert
+ (id)sharedAwayController;
- (BOOL)isLocked;
@end

typedef enum { /* no fucking clue */ } SBTouchType;

typedef struct {
    SBTouchType type;
    unsigned pathIndex;
    CGPoint location;
    CGPoint previousLocation;
    float totalDistanceTraveled;
    UIInterfaceOrientation interfaceOrientation;
    UIInterfaceOrientation previousInterfaceOrientation;
} SBTouchInfo;

typedef struct {
    UIEdgeInsets pixelDeltas; // 0x00, 0x04, 0x08, 0x0C
    UIEdgeInsets averageVelocities; // 0x10, 0x14, 0x18, 0x1C
    float averageTranslation; // 0x20
    CGPoint movementVelocityInPointsPerSecond; // 0x24, 0x28
    float farthestFingerSeparation; // 0x2C
    int activeTouchCount; // 0x30

    int unk1;
    int unk2;
    int unk3;
    int unk4;

    SBTouchInfo activeTouches[30]; // 0x44; count is activeTouchCount
} __SBGestureContext;

typedef __SBGestureContext *SBGestureContextRef;

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
@property (nonatomic, assign) int state;
@property (nonatomic, assign) int minTouches;
@property (assign, nonatomic) BOOL sendsTouchesCancelledToApplication;
- (void)reset;
- (BOOL)shouldReceiveTouches;
- (int)templateMatch;
- (void)touchesBegan:(SBGestureContextRef)began;
- (void)touchesCancelled:(SBGestureContextRef)cancelled;
- (void)touchesEnded:(SBGestureContextRef)ended;
- (void)touchesMoved:(SBGestureContextRef)moved;
@end

@interface SBFluidSlideGestureRecognizer : SBGestureRecognizer
@property(assign, nonatomic) int requiredDirectionality;
@property(assign, nonatomic) float accelerationPower;
@property(assign, nonatomic) float accelerationThreshold;
@property(assign, nonatomic) float animationDistance;
@property(readonly, assign, nonatomic) int degreeOfFreedom;
@property(readonly, assign, nonatomic) float cumulativeMotion;
@property(readonly, assign, nonatomic) float cumulativePercentage;
@property(readonly, assign, nonatomic) float incrementalMotion;
@property(readonly, assign, nonatomic) float skippedCumulativePercentage;
@property(readonly, assign, nonatomic) CGPoint centroidPoint;
@property(readonly, assign, nonatomic) CGPoint movementVelocityInPointsPerSecond;
- (int)completionTypeProjectingMomentumForInterval:(double)interval;
- (CGPoint)centroidPoint;
@end

@interface SBPanGestureRecognizer : SBFluidSlideGestureRecognizer
@end

@interface SBOffscreenSwipeGestureRecognizer : SBPanGestureRecognizer
@property(assign, nonatomic) float allowableDistanceFromEdgeCenter;
@property(assign, nonatomic) float edgeCenter;
@property(assign, nonatomic) float edgeMargin;
@property(assign, nonatomic) float falseEdge;
@property(assign, nonatomic) BOOL requiresSecondTouchInRange;
- (id)initForOffscreenEdge:(SBOffscreenEdge)edge;
- (void)_updateAnimationDistanceAndEdgeCenter;
- (BOOL)firstTouchInRange:(CGPoint)range;
- (BOOL)secondTouchInRange:(CGPoint)range;
@end

@interface SBHandMotionExtractor : NSObject
@property(readonly, assign, nonatomic) UIEdgeInsets allPixelDeltas;
@property(readonly, assign, nonatomic) float averageTranslation;
@property(readonly, assign, nonatomic) UIEdgeInsets averageVelocities;
@property(readonly, assign, nonatomic) float farthestFingerSeparation;
@property(readonly, assign, nonatomic) CGPoint movementVelocityInPointsPerSecond;
@property(readonly, assign, nonatomic) UIEdgeInsets pixelDeltas;
- (void)clear;
- (void)extractHandMotionForActiveTouches:(SBTouchInfo *)activeTouches count:(unsigned)count centroid:(CGPoint)centroid;
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



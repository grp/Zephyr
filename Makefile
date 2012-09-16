include theos/makefiles/common.mk

TWEAK_NAME = Zephyr ZephyrKeyboardProxy

export TARGET_IPHONEOS_DEPLOYMENT_VERSION = 5.0

Zephyr_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi BaseGesture.xmi OffscreenGesture.xmi Keyboard.xmi NSTimer+Blocks.m Common.xmi Notification.xmi Grabber.xmi
Zephyr_FRAMEWORKS = UIKit QuartzCore CoreGraphics
Zephyr_PRIVATE_FRAMEWORKS = AppSupport
export ARCHS = armv7

ZephyrKeyboardProxy_FILES = KeyboardProxy.xmi
ZephyrKeyboardProxy_FRAMEWORKS = UIKit
ZephyrKeyboardProxy_PRIVATE_FRAMEWORKS = AppSupport

include $(THEOS_MAKE_PATH)/tweak.mk

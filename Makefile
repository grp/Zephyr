export TARGET_CXX = xcrun -sdk iphoneos clang++
export TARGET_LD = xcrun -sdk iphoneos clang++
export TARGET = iphone:6.0:5.0
export ARCHS = armv7 # pending theos bug: armv7s

include theos/makefiles/common.mk

TWEAK_NAME = Zephyr ZephyrKeyboardProxy

Zephyr_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi BaseGesture.xmi OffscreenGesture.xmi Keyboard.xmi NSTimer+Blocks.m Common.xmi Notification.xmi Grabber.xmi Ping.xmi
Zephyr_FRAMEWORKS = UIKit QuartzCore CoreGraphics
Zephyr_PRIVATE_FRAMEWORKS = AppSupport

ZephyrKeyboardProxy_FILES = KeyboardProxy.xmi
ZephyrKeyboardProxy_FRAMEWORKS = UIKit
ZephyrKeyboardProxy_PRIVATE_FRAMEWORKS = AppSupport

include $(THEOS_MAKE_PATH)/tweak.mk

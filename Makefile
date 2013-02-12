export GO_EASY_ON_ME = 1

export TARGET_CXX = xcrun -sdk iphoneos clang++
export TARGET_LD = xcrun -sdk iphoneos clang++
export TARGET = iphone:latest:5.0
export ARCHS = armv7 # pending theos bug: armv7s

include theos/makefiles/common.mk

TWEAK_NAME = Zephyr ZephyrKeyboardProxy

Zephyr_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi BaseGesture.xmi OffscreenGesture.xmi Keyboard.xmi NSTimer+Blocks.m ActivateSwitcher.xmi Common.xmi Notification.xmi Grabber.xmi GestureEnabler.xmi Lockscreen.xmi
Zephyr_FRAMEWORKS = UIKit QuartzCore CoreGraphics CoreTelephony
Zephyr_PRIVATE_FRAMEWORKS = AppSupport GraphicsServices

ZephyrKeyboardProxy_FILES = KeyboardProxy.xmi
ZephyrKeyboardProxy_FRAMEWORKS = UIKit
ZephyrKeyboardProxy_PRIVATE_FRAMEWORKS = AppSupport

include $(THEOS_MAKE_PATH)/tweak.mk

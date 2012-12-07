export GO_EASY_ON_ME = 1

export TARGET_CXX = xcrun -sdk iphoneos clang++
export TARGET_LD = xcrun -sdk iphoneos clang++
export TARGET = iphone:latest:5.0
export ARCHS = armv7 # pending theos bug: armv7s

COUNTLY_TOKEN = b08522551772fc060276ec62c1c36ce5e56ecd01
COUNTLY_NAME = $(shell cat layout/DEBIAN/control | grep Name | cut -d ":" -f 2- | cut -c 2-)
COUNTLY_VERSION = $(shell cat layout/DEBIAN/control | grep Version | cut -d ":" -f 2- | cut -c 2-)
COUNTLY_IDENTIFIER = $(shell cat layout/DEBIAN/control | grep Package | cut -d ":" -f 2- | cut -c 2-)

include theos/makefiles/common.mk

TWEAK_NAME = Zephyr ZephyrKeyboardProxy

Zephyr_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi BaseGesture.xmi OffscreenGesture.xmi Keyboard.xmi NSTimer+Blocks.m Common.xmi Notification.xmi Grabber.xmi Analytics.xmi countly/Countly.m
Zephyr_FRAMEWORKS = UIKit QuartzCore CoreGraphics CoreTelephony
Zephyr_PRIVATE_FRAMEWORKS = AppSupport
Zephyr_CFLAGS = -DCountlyAppVersion=$(COUNTLY_VERSION) -DCountlyPrefix=$(COUNTLY_NAME) -DCountlyAppIdentifier=$(COUNTLY_IDENTIFIER) -DCountlyAppToken=$(COUNTLY_TOKEN)

ZephyrKeyboardProxy_FILES = KeyboardProxy.xmi
ZephyrKeyboardProxy_FRAMEWORKS = UIKit
ZephyrKeyboardProxy_PRIVATE_FRAMEWORKS = AppSupport

include $(THEOS_MAKE_PATH)/tweak.mk

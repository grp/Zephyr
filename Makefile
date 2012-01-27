include theos/makefiles/common.mk

TWEAK_NAME = Zephyr ZephyrKeyboardProxy 

Zephyr_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi OffscreenGesture.xmi Keyboard.xmi NSTimer+Blocks.m
Zephyr_FRAMEWORKS = UIKit QuartzCore CoreGraphics
Zephyr_PRIVATE_FRAMEWORKS = AppSupport

ZephyrKeyboardProxy_FILES = KeyboardProxy.xmi
ZephyrKeyboardProxy_FRAMEWORKS = UIKit
ZephyrKeyboardProxy_PRIVATE_FRAMEWORKS = AppSupport

include $(THEOS_MAKE_PATH)/tweak.mk

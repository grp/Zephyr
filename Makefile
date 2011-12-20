include theos/makefiles/common.mk

TWEAK_NAME = swipeaway
swipeaway_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi SwipeDetectorWindow.xmi
swipeaway_FRAMEWORKS = UIKit QuartzCore CoreGraphics

include $(THEOS_MAKE_PATH)/tweak.mk

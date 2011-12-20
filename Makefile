include theos/makefiles/common.mk

TWEAK_NAME = swipeaway
swipeaway_FILES = Tweak.xmi Switcher.xmi SwitchApp.xmi SwipeDetectorWindow.xmi
swipeaway_FRAMEWORKS = UIKit QuartzCore CoreGraphics

include $(THEOS_MAKE_PATH)/tweak.mk

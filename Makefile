include theos/makefiles/common.mk

TWEAK_NAME = swipeaway
swipeaway_FILES = Tweak.xm
swipeaway_FRAMEWORKS = UIKit QuartzCore CoreGraphics

include $(THEOS_MAKE_PATH)/tweak.mk

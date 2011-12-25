include theos/makefiles/common.mk

TWEAK_NAME = Zephyr
Zephyr_FILES = Preferences.xmi Switcher.xmi SwitchApp.xmi OffscreenGesture.xmi
Zephyr_FRAMEWORKS = UIKit QuartzCore CoreGraphics

include $(THEOS_MAKE_PATH)/tweak.mk

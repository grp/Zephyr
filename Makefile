include theos/makefiles/common.mk

override TARGET_CODESIGN = xcrun -sdk iphoneos codesign
override TARGET_CODESIGN_FLAGS = -fs "iPhone Developer: Grant Paul"

LIBRARY_NAME = swipeaway
swipeaway_FILES = Tweak.xmi Switcher.xmi SwitchApp.xmi SwipeDetectorWindow.xmi
swipeaway_FRAMEWORKS = UIKit QuartzCore CoreGraphics
swipeaway_INSTALL_PATH = /Library/MobileSubstrate/DynamicLibraries

include $(THEOS_MAKE_PATH)/library.mk

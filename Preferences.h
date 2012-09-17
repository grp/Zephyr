
#define kZephyrPreferencesBundleIdentifier @"com.chpwn.zephyr"
typedef void (^ZephyrPreferencesApplyAction)();

extern "C" void ZephyrPreferencesApplyActionRegister(ZephyrPreferencesApplyAction block);
extern "C" id ZephyrPreferencesGet(NSString *key, id defaultValue);
extern "C" void ZephyrPreferencesSet(NSString *key, id value);


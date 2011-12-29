
#define kPreferencesBundleIdentifier @"com.chpwn.zephyr"

typedef void (^PreferencesApplyAction)();

void PreferencesApplyActionRegister(PreferencesApplyAction block);
id PreferencesGet(NSString *key, id defaultValue);
void PreferencesSet(NSString *key, id value);



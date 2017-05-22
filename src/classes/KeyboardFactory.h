#ifndef KEYBOARD_FACTORY_CLASS
#define KEYBOARD_FACTORY_CLASS

#include <string>
#include <vector>
#include "Keyboard.h"

class LedKeyboardFactory {
	public:

		static LedKeyboard* getKeyboard(uint16_t vendorID, uint16_t productID, std::string serial);

		// Supported keyboards plugged into the system
		static std::vector<LedKeyboard::DeviceInfo> listAttachedKeyboards();

		// Keyboards supported by the system
		static std::vector<LedKeyboard::DeviceInfo> listSupportedKeyboards();
	
	private:
		LedKeyboardFactory();

		static std::vector<LedKeyboard*> getInstances();

		static void setDeviceInfo(LedKeyboard::DeviceInfo deviceInfo, struct hid_device_info *dev);

};
#endif

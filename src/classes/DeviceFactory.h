#ifndef KEYBOARD_FACTORY_CLASS
#define KEYBOARD_FACTORY_CLASS

#include <string>
#include <vector>
#include "Device.h"

class LedDeviceFactory {
	public:

		static LedDevice* getDevice(uint16_t vendorID, uint16_t productID, std::string serial);

		// Supported keyboards plugged into the system
		static std::vector<LedDevice::DeviceInfo> listAttachedDevices();

		// Devices supported by the system
		static std::vector<LedDevice::DeviceInfo> listSupportedDevices();
	
	private:
		LedDeviceFactory();

		static std::vector<LedDevice*> getInstances();

		static void setDeviceInfo(LedDevice::DeviceInfo deviceInfo, struct hid_device_info *dev);

};
#endif

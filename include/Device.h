#ifndef KEYBOARD_CLASS
#define KEYBOARD_CLASS

#include <iostream>
#include <unordered_map>
#include <vector>
#include <linux/input.h>

#if defined(hidapi)
	#include "hidapi/hidapi.h"
#elif defined(libusb)
	#include "libusb-1.0/libusb.h"
#endif

class LedDevice {
	
	public:
		LedDevice();
		virtual ~LedDevice();

		typedef struct {
			uint16_t vendorID = 0x0;
			uint16_t productID = 0x0;
			std::string manufacturer = "";
			std::string product = "";
			std::string serialNumber = "";
			uint32_t features;
		} DeviceInfo;
		
		typedef struct {
			std::string name;
			uint16_t code;
		} LED;
	
		typedef struct {
			uint8_t red;
			uint8_t green;
			uint8_t blue;
		} Color;

		typedef struct {
			LED led;
			Color color;
		} LEDValue;

		typedef std::vector<LEDValue> LEDValueArray;

		void addGroupAndLEDs(std::string name, std::vector<LED> group);
		bool close();
		DeviceInfo getCurrentDevice();
		std::unordered_map<std::string, std::vector<LED>> getLEDGroups();
		std::vector<LED> getLEDs();
		std::vector<DeviceInfo> getSupportedDevices();

#if defined(hidapi)
		bool initialize(hid_device* handle);
#elif defined(libusb)
		bool initialize(libusb_context* context, libusb_device_handle* handle);
#endif

		bool isOpen();
		bool isSupported(uint16_t vendorID, uint16_t productID);
		bool setAllLEDs(Color color);
		bool setLED(LED led, Color color);
		bool setLEDGroup(std::string name, Color color);

		virtual bool setLED(LEDValue value) = 0;
		virtual bool setLEDs(LEDValueArray values) = 0;
		virtual bool commit() = 0;

	protected:

#if defined(hidapi)
			hid_device *m_hidHandle;
#elif defined(libusb)
			bool m_isKernellDetached = false;
			libusb_context *m_ctx = NULL;
			libusb_device_handle *m_hidHandle;
#endif

		DeviceInfo currentDevice;
		std::unordered_map<std::string, std::vector<LED>> LEDGroupMap;
		std::vector<LED> LEDs;
		bool m_isOpen = false;
		std::vector<DeviceInfo> supportedDevices;

};

#endif

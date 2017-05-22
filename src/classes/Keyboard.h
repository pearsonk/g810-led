#ifndef KEYBOARD_CLASS
#define KEYBOARD_CLASS

#include <iostream>
#include <vector>
#include <linux/input.h>

#if defined(hidapi)
	#include "hidapi/hidapi.h"
#elif defined(libusb)
	#include "libusb-1.0/libusb.h"
#endif


class LedKeyboard {
	
	public:
		LedKeyboard();
		virtual ~LedKeyboard() = 0;

/*    
		std::vector<std::vector<uint16_t>> SupportedKeyboards = {
			{ 0x46d, 0xc336, (u_int16_t)KeyboardModel::g213 },
			{ 0x46d, 0xc330, (u_int16_t)KeyboardModel::g410 },
			{ 0x46d, 0xc333, (u_int16_t)KeyboardModel::g610 },
			{ 0x46d, 0xc338, (u_int16_t)KeyboardModel::g610 },
			{ 0x46d, 0xc331, (u_int16_t)KeyboardModel::g810 },
			{ 0x46d, 0xc337, (u_int16_t)KeyboardModel::g810 },
			{ 0x46d, 0xc32b, (u_int16_t)KeyboardModel::g910 },
			{ 0x46d, 0xc335, (u_int16_t)KeyboardModel::g910 },
			{ 0x46d, 0xc339, (u_int16_t)KeyboardModel::gpro }
		};
*/		

		typedef struct {
			uint16_t vendorID = 0x0;
			uint16_t productID = 0x0;
			std::string manufacturer = "";
			std::string product = "";
			std::string serialNumber = "";
			uint32_t features;
		} DeviceInfo;
		
		typedef struct {
			uint8_t red;
			uint8_t green;
			uint8_t blue;
		} Color;

		typedef struct {
			uint16_t key;
			Color color;
		} KeyValue;

		typedef std::vector<KeyValue> KeyValueArray;

		bool isOpen();
		bool isSupported(uint16_t vendorID, uint16_t productID);
#if defined(hidapi)
		bool initialize(hid_device* handle);
#elif defined(libusb)
		bool initialize(libusb_context* context, libusb_device_handle* handle);
#endif

		DeviceInfo getCurrentDevice();
		bool close();
		std::vector<DeviceInfo> getSupportedDevices();
		
		virtual bool setKey(KeyValue keyValue)= 0;
		virtual bool setKeys(KeyValueArray keyValues) = 0;
		virtual bool setAllKeys(Color color) = 0;
		virtual bool commit() = 0;
		
		virtual bool setRegion(uint8_t region, Color color) = 0;
		
	protected:
	
		#if defined(hidapi)
			hid_device *m_hidHandle;
		#elif defined(libusb)
			bool m_isKernellDetached = false;
			libusb_device_handle *m_hidHandle;
			libusb_context *m_ctx = NULL;
		#endif
		
		DeviceInfo currentDevice;
		bool m_isOpen = false;
		std::vector<DeviceInfo> supportedDevices;
};

#endif

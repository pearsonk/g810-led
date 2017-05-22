#include "KeyboardFactory.h"
#include "Keyboard.h"

#include <vector>
#include <string>

#if defined(hidapi)
	#include <locale>
	#include "hidapi/hidapi.h"
#elif defined(libusb)
	#include "libusb-1.0/libusb.h"
#endif

//Keyboard classes
#include "LogitechG410.h"


std::vector<LedKeyboard*> LedKeyboardFactory::getInstances() {
	std::vector<LedKeyboard*> keyboards;

	// Add device instances here
	keyboards.push_back(new LogitechG410());

	return keyboards;
}

#if defined(hidapi)

void LedKeyboardFactory::setDeviceInfo(LedKeyboard::DeviceInfo deviceInfo, struct hid_device_info *dev) {
	deviceInfo.vendorID=dev->vendor_id;
	deviceInfo.productID=dev->product_id;
					
	if (dev->serial_number != NULL) {
		char buf[256];
		wcstombs(buf, dev->serial_number, 256);
		deviceInfo.serialNumber = std::string(buf);
	}

	if (dev->manufacturer_string != NULL)	{
		char buf[256];
		wcstombs(buf, dev->manufacturer_string, 256);
		deviceInfo.manufacturer = std::string(buf);
	}

	if (dev->product_string != NULL)
	{
		char buf[256];
		wcstombs(buf, dev->product_string, 256);
		deviceInfo.product = std::string(buf);
	}
}

LedKeyboard* LedKeyboardFactory::getKeyboard(uint16_t vendorID, uint16_t productID, std::string serial) {
	std::vector<LedKeyboard*> keyboards = getInstances();
	LedKeyboard* matchedKeyboard = NULL;

	//Iterate USB devices to find a match
	struct hid_device_info *devs, *dev;
	devs = hid_enumerate(vendorID, productID);
	dev = devs;
	std::wstring wideSerial;

	if (!serial.empty()) {
		wchar_t tempSerial[256];
		if (mbstowcs(tempSerial, serial.c_str(), 256) < 1) return NULL;
		wideSerial = std::wstring(tempSerial);
	}

	while (dev) {
		//Iterate classes to find support
		for (unsigned int index = 0; index < keyboards.size(); index++) {
			LedKeyboard* keyboard = keyboards.at(index);
			if (keyboard->isSupported(dev->vendor_id, dev->product_id)) {
				if (!serial.empty() && dev->serial_number != NULL && wideSerial.compare(dev->serial_number) != 0) break; //Serial didn't match

				matchedKeyboard = keyboard;
        wideSerial = std::wstring(dev->serial_number);
			}
		}
		if (matchedKeyboard != NULL) break;
		dev = dev->next;
	} //End dev iteration loop
	hid_free_enumeration(devs);
	hid_exit();

	//Clean up all keyboards except the match we will be returning
	for (unsigned int index=0; index < keyboards.size(); index++) {
		LedKeyboard* keyboard = keyboards.at(index);
		if (keyboard != matchedKeyboard) delete keyboard;
	}

	if (matchedKeyboard != NULL) {
		matchedKeyboard->initialize(hid_open(dev->vendor_id, dev->product_id, wideSerial.c_str()));
	}

	return matchedKeyboard;
}

std::vector<LedKeyboard::DeviceInfo> LedKeyboardFactory::listAttachedKeyboards() {
	std::vector<LedKeyboard*> keyboardClasses = getInstances();
	std::vector<LedKeyboard::DeviceInfo> deviceList;

	if (hid_init() < 0) return deviceList;
		
	struct hid_device_info *devs, *dev;
	devs = hid_enumerate(0x0, 0x0);
	dev = devs;
	while (dev) {
		for (unsigned int index = 0; index < keyboardClasses.size(); index++) {
			LedKeyboard* keyboard = keyboardClasses.at(index);
				
			if (keyboard->isSupported(dev->vendor_id,dev->product_id)) {
				LedKeyboard::DeviceInfo deviceInfo;
				
				setDeviceInfo(deviceInfo,dev);

				deviceList.push_back(deviceInfo);
				dev = dev->next;
				break;
			}
		}
		
		if (dev != NULL) dev = dev->next;
	}
	
	hid_free_enumeration(devs);
	hid_exit();
	
	return deviceList;
}

#elif defined(libusb)
std::vector<LedKeyboard::DeviceInfo> LedKeyboardFactory::listAttachedKeyboards() {
	std::vector<LedKeyboard*> keyboardClasses = getInstances();
	std::vector<LedKeyboard::DeviceInfo> deviceList;

//TODO:	Fix since no "SupportedKeyboards[][]"
		libusb_context *ctx = NULL;
		if(libusb_init(&m_ctx) < 0) return deviceList;
		
		libusb_device **devs;
		ssize_t cnt = libusb_get_device_list(ctx, &devs);
		for(ssize_t i = 0; i < cnt; i++) {
			libusb_device *device = devs[i];
			libusb_device_descriptor desc;
			libusb_get_device_descriptor(device, &desc);
			for (int i=0; i<(int)SupportedKeyboards.size(); i++) {
				if (desc.idVendor == SupportedKeyboards[i][0]) {
					if (desc.idProduct == SupportedKeyboards[i][1]) {
					  unsigned char buf[256];
						DeviceInfo deviceInfo;
						deviceInfo.vendorID=desc.idVendor;
						deviceInfo.productID=desc.idProduct;

						if (libusb_open(device, &m_hidHandle) != 0)	continue;

						if (libusb_get_string_descriptor_ascii(m_hidHandle, desc.iSerialNumber, buf, 256) >= 1) deviceInfo.serialNumber = string((char*)buf);
						if (libusb_get_string_descriptor_ascii(m_hidHandle, desc.iManufacturer, buf, 256) >= 1) deviceInfo.manufacturer = string((char*)buf);
						if (libusb_get_string_descriptor_ascii(m_hidHandle, desc.iProduct, buf, 256) >= 1) deviceInfo.product = string((char*)buf);

						deviceList.push_back(deviceInfo);
						libusb_close(m_hidHandle);
						m_hidHandle = NULL;
						break;
					}
				}
			}
		}
		libusb_free_device_list(devs, 1);

		if (m_hidHandle != NULL) {
			libusb_close(m_hidHandle);
			m_hidHandle = NULL;
		}
		
		libusb_exit(m_ctx);
		m_ctx = NULL;
	return deviceList;
}
#endif

// Give a list of all supported keyboards. Will likely only populate vendor and device IDs.
std::vector<LedKeyboard::DeviceInfo> LedKeyboardFactory::listSupportedKeyboards() {
	std::vector<LedKeyboard::DeviceInfo> supportedKeyboards;
	std::vector<LedKeyboard*> keyboards = getInstances();

	for (unsigned int index=0; index < keyboards.size(); index++) {
		LedKeyboard* keyboard = keyboards.at(index);
		std::vector<LedKeyboard::DeviceInfo> devices = keyboard->getSupportedDevices();
		for (unsigned int deviceIndex=0; deviceIndex < devices.size(); deviceIndex++) {
			supportedKeyboards.push_back(devices.at(deviceIndex));
		}

		delete keyboard;
	}
	return supportedKeyboards;
}

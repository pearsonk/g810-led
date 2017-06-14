#include "Device.h"

#include <iostream>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#if defined(hidapi)
	#include <locale>
	#include "hidapi/hidapi.h"
#elif defined(libusb)
	#include "libusb-1.0/libusb.h"
#endif

LedDevice::LedDevice() {
}

LedDevice::~LedDevice() {
	close();
}

std::vector<LedDevice::LED> LedDevice::getLEDs() {
	std::vector<LedDevice::LED> copy = std::vector<LedDevice::LED>(LEDs);
	return copy;
}

std::unordered_map<std::string, std::vector<LedDevice::LED>> LedDevice::getLEDGroups() {
	std::unordered_map<std::string, std::vector<LedDevice::LED>> copy = std::unordered_map<std::string, std::vector<LedDevice::LED>>(LEDGroupMap);
	return copy;
}

bool LedDevice::isOpen() {
	return m_isOpen;
}

bool LedDevice::setAllLEDs(LedDevice::Color color) {
	LEDValueArray ledValues;

	for (auto led : LEDs)
	{
		ledValues.push_back({led, color});
	}
	return setLEDs(ledValues);
}

bool LedDevice::setLED(LED led, Color color) {
	LEDValue singleLED = { led, color };
	return setLED(singleLED);
}

void LedDevice::addGroupAndLEDs(std::string name, std::vector<LED> group) {
	LEDGroupMap.insert({name, group});
	for (auto led : group) {
		LEDs.push_back(led);
	}
}

bool LedDevice::isSupported(uint16_t vendorID, uint16_t productID) {
	for (unsigned int index=0; index<supportedDevices.size(); index++) {
		DeviceInfo supportedDevice = supportedDevices.at(index);
		if (supportedDevice.vendorID == vendorID && 
				supportedDevice.productID == productID)
			return true;
	}
	return false;
}

bool LedDevice::setLEDGroup(std::string name, Color color) {
	std::unordered_map<std::string, std::vector<LED>>::const_iterator element = LEDGroupMap.find(name);

	if (element == LEDGroupMap.end())
	return false;

	LEDValueArray array;

	for (LED led : element->second) {
		LEDValue value = { led, color };
		array.push_back(value);
	}
	return setLEDs(array);
}

#if defined(hidapi)
bool LedDevice::initialize(hid_device* handle) {
  if (isOpen() || handle == NULL) return false;

  m_hidHandle = handle;
	m_isOpen = true;

  return true;
}
#elif defined(libusb)
bool LedDevice::initialize(libusb_context* context, libusb_device_handle* handle) {
	if (isOpen() || context == NULL || handle == NULL) return false;

	m_ctx = context;
	m_hidHandle = handle;
	m_isOpen = true;

	return true;
}
#endif

LedDevice::DeviceInfo LedDevice::getCurrentDevice() {
	return currentDevice;
}

std::vector<LedDevice::DeviceInfo> LedDevice::getSupportedDevices() {
	std::vector<LedDevice::DeviceInfo> copy = std::vector<LedDevice::DeviceInfo>(supportedDevices);
	return copy;
}

#if defined(hidapi)
bool LedDevice::close() {
	if (! m_isOpen) return true;
	m_isOpen = false;
	
	hid_close(m_hidHandle);
	m_hidHandle = NULL;
	hid_exit();
	return true;
}

#elif defined(libusb)
bool LedDevice::close() {
	if (! m_isOpen) return true;
	m_isOpen = false;

	if (m_hidHandle == NULL) return true;
	if(libusb_release_interface(m_hidHandle, 1) != 0) return false;
	if(m_isKernellDetached==true) {
		libusb_attach_kernel_driver(m_hidHandle, 1);
		m_isKernellDetached = false;
	}
	libusb_close(m_hidHandle);
	m_hidHandle = NULL;
	libusb_exit(m_ctx);
	m_ctx = NULL;
	return true;
}
#endif



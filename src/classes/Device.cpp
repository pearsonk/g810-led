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

std::unordered_map<std::string, uint16_t> LedDevice::getLEDMap() {
	std::unordered_map<std::string, uint16_t> copy = std::unordered_map<std::string, uint16_t>(LEDMap);
	return copy;
}

std::unordered_map<std::string, std::vector<uint16_t>> LedDevice::getLEDGroupMap() {
	std::unordered_map<std::string, std::vector<uint16_t>> copy = std::unordered_map<std::string, std::vector<uint16_t>>(LEDGroupMap);
	return copy;
}

std::vector<std::string> LedDevice::getLEDs() {
	std::vector<std::string> keys;
	for (auto iterator :  LEDMap) {
		keys.push_back(iterator.first);
	}
	return keys;
}

std::vector<std::string> LedDevice::getLEDGroups() {
	std::vector<std::string> keys;
	for (auto iterator :  LEDGroupMap) {
		keys.push_back(iterator.first);
	}
	return keys;
}

bool LedDevice::isOpen() {
	return m_isOpen;
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
	


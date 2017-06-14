#include "DeviceFactory.h"
#include "Device.h"

#include <vector>
#include <string>

#if defined(hidapi)
	#include <locale>
	#include "hidapi/hidapi.h"
#elif defined(libusb)
	#include "libusb-1.0/libusb.h"
#endif

// Logitech classes
#include "Logitech/Devices/LogitechG213.h"
#include "Logitech/Devices/LogitechG410.h"
#include "Logitech/Devices/LogitechG810.h"


std::vector<LedDevice*> LedDeviceFactory::getInstances() {
	std::vector<LedDevice*> devices;

	// Add device instances here
	devices.push_back(new LogitechG410());
	devices.push_back(new LogitechG810());
	devices.push_back(new LogitechG213());

	return devices;
}

#if defined(hidapi)

void LedDeviceFactory::setDeviceInfo(LedDevice::DeviceInfo& deviceInfo, struct hid_device_info *dev) {
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

LedDevice* LedDeviceFactory::getDevice(uint16_t vendorID, uint16_t productID, std::string serial) {
	std::vector<LedDevice*> devices = getInstances();
	LedDevice* matchedDevice = NULL;

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
		for (unsigned int index = 0; index < devices.size(); index++) {
			LedDevice* device = devices.at(index);
			if (device->isSupported(dev->vendor_id, dev->product_id)) {
				if (!serial.empty() && dev->serial_number != NULL && wideSerial.compare(dev->serial_number) != 0) break; //Serial didn't match

				matchedDevice = device;
        wideSerial = std::wstring(dev->serial_number);
			}
		}
		if (matchedDevice != NULL) break;
		dev = dev->next;
	} //End dev iteration loop

	//Clean up all devices except the match we will be returning
	for (unsigned int index=0; index < devices.size(); index++) {
		LedDevice* device = devices.at(index);
		if (device != matchedDevice) delete device;
	}

	if (matchedDevice != NULL) {
		matchedDevice->initialize(hid_open(dev->vendor_id, dev->product_id, wideSerial.c_str()));
	}

	hid_free_enumeration(devs);
	hid_exit();

	return matchedDevice;
}

std::vector<LedDevice::DeviceInfo> LedDeviceFactory::listAttachedDevices() {
	std::vector<LedDevice*> deviceClasses = getInstances();
	std::vector<LedDevice::DeviceInfo> deviceList;

	if (hid_init() < 0) return deviceList;
		
	struct hid_device_info *devs, *dev;
	devs = hid_enumerate(0x0, 0x0);
	dev = devs;
	while (dev) {
		for (unsigned int index = 0; index < deviceClasses.size(); index++) {
			LedDevice* device = deviceClasses.at(index);
				
			if (device->isSupported(dev->vendor_id,dev->product_id)) {
				LedDevice::DeviceInfo deviceInfo;
				
				setDeviceInfo(deviceInfo,dev);

				deviceList.push_back(deviceInfo);
				dev = dev->next;
				break;
			}
		}
		
		if (dev != NULL) dev = dev->next;
	}

	//Clean up all devices
	for (unsigned int index=0; index<deviceClasses.size(); index++) {
		LedDevice* device = deviceClasses.at(index);
		delete device;
	}

	hid_free_enumeration(devs);
	hid_exit();
	
	return deviceList;
}

#elif defined(libusb)
std::vector<LedDevice::DeviceInfo> LedDeviceFactory::listAttachedDevices() {
	std::vector<LedDevice*> deviceClasses = getInstances();
	std::vector<LedDevice::DeviceInfo> deviceList;

//TODO:	Fix since no "SupportedDevices[][]"
		libusb_context *ctx = NULL;
		if(libusb_init(&m_ctx) < 0) return deviceList;
		
		libusb_device **devs;
		ssize_t cnt = libusb_get_device_list(ctx, &devs);
		for(ssize_t i = 0; i < cnt; i++) {
			libusb_device *device = devs[i];
			libusb_device_descriptor desc;
			libusb_get_device_descriptor(device, &desc);
			for (int i=0; i<(int)SupportedDevices.size(); i++) {
				if (desc.idVendor == SupportedDevices[i][0]) {
					if (desc.idProduct == SupportedDevices[i][1]) {
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

// Give a list of all supported devices. Will likely only populate vendor and device IDs.
std::vector<LedDevice::DeviceInfo> LedDeviceFactory::listSupportedDevices() {
	std::vector<LedDevice::DeviceInfo> supportedDevices;
	std::vector<LedDevice*> devices = getInstances();

	for (unsigned int index=0; index < devices.size(); index++) {
		LedDevice* device = devices.at(index);
		std::vector<LedDevice::DeviceInfo> devices = device->getSupportedDevices();
		for (unsigned int deviceIndex=0; deviceIndex < devices.size(); deviceIndex++) {
			supportedDevices.push_back(devices.at(deviceIndex));
		}

		delete device;
	}
	return supportedDevices;
}

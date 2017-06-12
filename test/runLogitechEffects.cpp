#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <hidapi/hidapi.h>
#include <DeviceFactory.h>
#include <Device.h>
#include <Logitech/LogitechDevice.h>
#include <Logitech/LogitechPerKeyLED.h>
#include <unistd.h>

using namespace std;

LedDevice::Color red = { 0xff, 0x0, 0x0 };
LedDevice::Color green = { 0x0, 0xff, 0x0 };
LedDevice::Color blue = { 0x0, 0x0, 0xff };
LedDevice::Color black = { 0x0, 0x0, 0x0 };
LedDevice::Color white = { 0xff, 0xff, 0xff };

int main(int argc, char** argv) {
	vector<LedDevice::DeviceInfo> keyboards;
	keyboards = LedDeviceFactory::listAttachedDevices();

	cout << "Number of devices: " << keyboards.size() << endl;

	for(unsigned int index=0;index<keyboards.size();index++) {
		LedDevice::DeviceInfo device = keyboards.at(index);
		cout << "Device: vendorID=" <<std::hex<<device.vendorID<<", productID="<<device.productID<<std::hex<<", serial="<<device.serialNumber<<std::endl;

		LedDevice* keyboard = LedDeviceFactory::getDevice(device.vendorID, device.productID, device.serialNumber);
		if (keyboard == NULL) {
			cout << "Device failure" <<endl;
			continue;
		}

		if (device.vendorID != 0x046d) {
			cout << "Skipping device, not Logitech" << endl;
			continue;
		}

		LogitechDevice* logitech = static_cast<LogitechDevice*>(keyboard);

		cout << "Setting native color blue" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::color, LogitechDevice::NativeEffectPart::all, 0, blue)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);

		cout << "Setting native breath" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::breathing, LogitechDevice::NativeEffectPart::keys, 2, red)) return 4;
		if (! logitech->commit()) return -1;

		delete keyboard;
	}
}

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

		// Color
		cout << "Setting native color blue" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::color, LogitechDevice::NativeEffectPart::all, 0, blue)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);

		 // Breath/Blink
		cout << "Setting native breath" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::breathing, LogitechDevice::NativeEffectPart::all, 2, red)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);

		// Cycle
		cout << "Setting cycle" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::cycle, LogitechDevice::NativeEffectPart::all, 5, green)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);
		
		// H-Wave
		cout << "Setting horizontal wave" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::hwave, LogitechDevice::NativeEffectPart::all, 5, blue)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);

		// V-Wave
		cout << "Setting vertical wave" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::vwave, LogitechDevice::NativeEffectPart::all, 5, red)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);

		// C-Wave
		cout << "Setting C wave" << endl;
		if (! logitech->setNativeEffect(LogitechDevice::NativeEffect::cwave, LogitechDevice::NativeEffectPart::all, 5, white)) return 4;
		if (! logitech->commit()) return -1;

		sleep(5);

		delete keyboard;
	}
}

#include <vector>
#include "Logitech/LogitechDevice.h"
#include "Logitech/Devices/LogitechG213.h"

LogitechG213::LogitechG213() {
	DeviceInfo device;
		device.vendorID=0x046d;
		device.productID=0xc336;
	supportedDevices.push_back(device);

	nativeEffectProtocolByte = 0x0c;

	addGroupAndLEDs("Left", {left});
	addGroupAndLEDs("Mid-Left", {midLeft});
	addGroupAndLEDs("Middle", {middle});
	addGroupAndLEDs("Mid-Right", {midRight});
	addGroupAndLEDs("Right", {right});
}

LogitechG213::~LogitechG213() {
}

bool LogitechG213::setMRKey(uint8_t) {
	return false;
}

bool LogitechG213::setMNKey(uint8_t) {
	return false;
}

bool LogitechG213::setGKeysMode(uint8_t) {
	return false;
}

bool LogitechG213::setLED(LEDValue value) {
	return setLEDs({value});	
}

bool LogitechG213::setLEDs(LEDValueArray values) {
	for (auto value : values) {
		LogitechDevice::byte_buffer_t data;
		data = { 0x11, 0xff, 0x0c, 0x3a, (uint8_t)value.led.code, 0x01, value.color.red, value.color.green, value.color.blue };
		data.resize(20,0x00);
		if (! sendDataInternal(data)) return false;
	}
	return true;	
}

bool LogitechG213::commit() {
	// Simply return true since the device is non-transactional
	return true;
}

bool LogitechG213::hasNativeEffectPart(NativeEffectPart part) {
	switch (part) {
		case NativeEffectPart::keys:
			return true;
		case NativeEffectPart::logo:
			return false;
		default:
			return false;
	}
	return false;
}

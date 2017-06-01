#include <vector>
#include "LogitechG410.h"

LogitechG410::LogitechG410() {
	DeviceInfo device;
		device.vendorID=0x046d;
		device.productID=0xc330;
	supportedDevices.push_back(device);

  nativeEffectProtocolByte = 0x0d;

	populateLEDs("F-Keys", keyGroupFKeys);
	populateLEDs("Modifiers", keyGroupModifiers);
	populateLEDs("Functions", keyGroupFunctions);
	populateLEDs("Arrows", keyGroupArrows);
	populateLEDs("Numpad", keyGroupNumeric);
	populateLEDs("Keys", keyGroupKeys);
}

void LogitechG410::populateLEDs(std::string name, std::vector<LED> group) {
	LEDGroupMap.insert({name, group});
	for (auto led : group) {
		LEDs.push_back(led);
	}
}

bool LogitechG410::setMRKey(uint8_t) {
	return false;
}

bool LogitechG410::setMNKey(uint8_t) {
	return false;
}

void LogitechG410::getSortedKeys(LogitechPerKeyLED::LEDValueArray values, std::vector<std::vector<LogitechPerKeyLED::LEDValue>>& sortedKeys) {
	for (uint8_t i = 0; i < values.size(); i++) {
		//Simplify?
		switch(static_cast<LogitechPerKeyLED::KeyAddressGroup>(values[i].led.code >> 8 )) {
			case LogitechPerKeyLED::KeyAddressGroup::keys:
				if (sortedKeys[4].size() <= 120) {
					if (values[i].led.code < LogitechPerKeyLED::num_lock.code || values[i].led.code > (uint16_t)LogitechPerKeyLED::num_dot.code) {
						sortedKeys[4].push_back(values[i]);
					}
				}
				break;
			default:
				break;
		}
	}
}

bool LogitechG410::setGKeysMode(uint8_t)
{
	return false;
}

bool LogitechG410::setRegion(uint8_t, LedDevice::Color) {
	return false;
}

bool LogitechG410::setStartupMode(StartupMode startupMode) {
	byte_buffer_t data;
	data = { 0x11, 0xff, 0x0d, 0x5a, 0x00, 0x01 };
	data.push_back((unsigned char)startupMode);
	data.resize(20, 0x00);
	return sendDataInternal(data);
}

bool LogitechG410::hasNativeEffectPart(NativeEffectPart part) {
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

#include <vector>
#include "Logitech/Devices/LogitechG810.h"

LogitechG810::LogitechG810() {
	DeviceInfo device1;
		device1.vendorID=0x046d;
		device1.productID=0xc331;
	supportedDevices.push_back(device1);
	DeviceInfo device2;
		device2.vendorID=0x046d;
		device2.productID=0xc337;
	supportedDevices.push_back(device2);

  nativeEffectProtocolByte = 0x0d;

  populateLEDs("Logo", keyGroupLogo);
  populateLEDs("F-Keys", keyGroupFKeys);
	populateLEDs("Modifiers", keyGroupModifiers);
	populateLEDs("Functions", keyGroupFunctions);
	populateLEDs("Arrows", keyGroupArrows);
	populateLEDs("Numpad", keyGroupNumeric);
	populateLEDs("Keys", keyGroupKeys);
	populateLEDs("Indicators", keyGroupIndicators);
	populateLEDs("Multimedia", keyGroupMultimedia);
}

bool LogitechG810::setMRKey(uint8_t) {
  return false;
}

bool LogitechG810::setMNKey(uint8_t) {
  return false;
}

void LogitechG810::populateLEDs(std::string name, std::vector<LED> group) {
	LEDGroupMap.insert({name, group});
	for (auto led : group) {
		LEDs.push_back(led);
	}
}

void LogitechG810::getSortedKeys(LogitechPerKeyLED::LEDValueArray values, std::vector<std::vector<LogitechPerKeyLED::LEDValue>>& sortedKeys) {
	for (uint8_t i = 0; i < values.size(); i++) {
		//Simplify?
		switch(static_cast<LogitechPerKeyLED::KeyAddressGroup>(values[i].led.code >> 8 )) {
			case LogitechPerKeyLED::KeyAddressGroup::keys:
        if (sortedKeys[4].size() <= 120) sortedKeys[4].push_back(values[i]);
        break;
      case LogitechPerKeyLED::KeyAddressGroup::indicators:
				if (sortedKeys[1].size() <= 5) sortedKeys[1].push_back(values[i]);
        break;
      case LogitechPerKeyLED::KeyAddressGroup::multimedia:
        if (sortedKeys[2].size() <= 5) sortedKeys[2].push_back(values[i]);
        break;
      case LogitechPerKeyLED::KeyAddressGroup::logo:
        if (sortedKeys[0].size() <= 1) sortedKeys[0].push_back(values[i]);
        break;
			default:
				break;
		}
	}
}

bool LogitechG810::setGKeysMode(uint8_t) {
  return false;
}

bool LogitechG810::setStartupMode(StartupMode startupMode) {
	byte_buffer_t data;
	data = { 0x11, 0xff, 0x0d, 0x5a, 0x00, 0x01 };
	data.push_back((unsigned char)startupMode);
	data.resize(20, 0x00);
	return sendDataInternal(data);
}

bool LogitechG810::hasNativeEffectPart(NativeEffectPart part) {
  switch (part) {
    case NativeEffectPart::keys:
      return true;
    case NativeEffectPart::logo:
      return true;
    default:
      return false;
  }
  return false;
}

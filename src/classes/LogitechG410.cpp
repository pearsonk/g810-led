#include <vector>
#include "LogitechG410.h"

LogitechG410::LogitechG410() {
	DeviceInfo device;
		device.vendorID=0x046d;
		device.productID=0xc330;
	supportedDevices.push_back(device);

  nativeEffectProtocolByte = 0x0d;
}

bool LogitechG410::setMRKey(uint8_t value) {
	return false;
}

bool LogitechG410::setMNKey(uint8_t value) {
	return false;
}

void LogitechG410::getSortedKeys(LogitechPerKeyLED::KeyValueArray keyValues, std::vector<std::vector<LogitechPerKeyLED::KeyValue>>& sortedKeys) {
	for (uint8_t i = 0; i < keyValues.size(); i++) {
		//Simplify?
		switch(static_cast<LogitechPerKeyLED::KeyAddressGroup>(static_cast<uint16_t>(keyValues[i].key) >> 8 )) {
			case LogitechPerKeyLED::KeyAddressGroup::keys:
				if (sortedKeys[4].size() <= 120) {
					if (keyValues[i].key < (uint16_t)LogitechPerKeyLED::Key::num_lock || keyValues[i].key > (uint16_t)LogitechPerKeyLED::Key::num_dot) {
						sortedKeys[4].push_back(keyValues[i]);
					}
				}
				break;
			default:
				break;
		}
	}
}

bool LogitechG410::setGKeysMode(uint8_t value)
{
	return false;
}

bool LogitechG410::setRegion(uint8_t region, LedKeyboard::Color color) {
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

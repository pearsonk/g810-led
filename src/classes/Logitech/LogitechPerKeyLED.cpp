#include "Logitech/LogitechPerKeyLED.h"

bool LogitechPerKeyLED::setLED(LEDValue keyValue) {
	return setLEDs(LEDValueArray {keyValue});
}

bool LogitechPerKeyLED::commit() {
	byte_buffer_t data;
	data = { 0x11, 0xff, 0x0c, 0x5a };
	data.resize(20, 0x00);
	return sendDataInternal(data);
}

bool LogitechPerKeyLED::setLEDs(LEDValueArray keyValues) {
	if (keyValues.empty()) return false;
	
	bool retval = true;
	
	std::vector<std::vector<LEDValue>> SortedKeys = {
		{}, // Logo AddressGroup
		{}, // Indicators AddressGroup
		{}, // Multimedia AddressGroup
		{}, // GKeys AddressGroup
		{} // Keys AddressGroup
	};

	getSortedKeys(keyValues,SortedKeys);	

	for (uint8_t kag = 0; kag < 5; kag++) {
		
		if (SortedKeys[kag].size() > 0) {
			
			uint8_t gi = 0;
			while (gi < SortedKeys[kag].size()) {
				
				size_t data_size = 0;
				byte_buffer_t data = {};
				
				switch (kag) {
					case 0:
						data_size = 20;
						data = getKeyGroupAddress(LogitechPerKeyLED::KeyAddressGroup::logo);
						break;
					case 1:
						data_size = 64;
						data = getKeyGroupAddress(LogitechPerKeyLED::KeyAddressGroup::indicators);
						break;
					case 2:
						data_size = 64;
						data = getKeyGroupAddress(LogitechPerKeyLED::KeyAddressGroup::multimedia);
						break;
					case 3:
						data_size = 64;
						data = getKeyGroupAddress(LogitechPerKeyLED::KeyAddressGroup::gkeys);
						break;
					case 4:
						data_size = 64;
						data = getKeyGroupAddress(LogitechPerKeyLED::KeyAddressGroup::keys);
						break;
				}
				
				const uint8_t maxKeyCount = (data_size - 8) / 4;
				
				if (data.size() > 0) {
					
					for (uint8_t i = 0; i < maxKeyCount; i++) {
						if (gi + i < SortedKeys[kag].size()) {
							data.push_back(static_cast<uint8_t>(SortedKeys[kag][gi+i].led.code) & 0x00ff);
							data.push_back(SortedKeys[kag][gi+i].color.red);
							data.push_back(SortedKeys[kag][gi+i].color.green);
							data.push_back(SortedKeys[kag][gi+i].color.blue);
						}
					}
					
					data.resize(data_size, 0x00);
					
					if (retval) retval = sendDataInternal(data);
					else sendDataInternal(data);
					
				}
				
				gi = gi + maxKeyCount;
			}
			
		}
	}
	return retval;
}

LogitechPerKeyLED::byte_buffer_t LogitechPerKeyLED::getKeyGroupAddress(LogitechPerKeyLED::KeyAddressGroup keyAddressGroup) {
	switch (keyAddressGroup) {
		case LogitechPerKeyLED::KeyAddressGroup::logo:
			return { 0x11, 0xff, 0x0c, 0x3a, 0x00, 0x10, 0x00, 0x01 };
		case LogitechPerKeyLED::KeyAddressGroup::indicators:
			return { 0x12, 0xff, 0x0c, 0x3a, 0x00, 0x40, 0x00, 0x05 };
		case LogitechPerKeyLED::KeyAddressGroup::gkeys:
			return {};
		case LogitechPerKeyLED::KeyAddressGroup::multimedia:
			return { 0x12, 0xff, 0x0c, 0x3a, 0x00, 0x02, 0x00, 0x05 };
		case LogitechPerKeyLED::KeyAddressGroup::keys:
			return { 0x12, 0xff, 0x0c, 0x3a, 0x00, 0x01, 0x00, 0x0e };
		default:
			break;
	}
	return {};
}

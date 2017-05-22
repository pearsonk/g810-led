#include "LogitechPerKeyLED.h"

bool LogitechPerKeyLED::setAllKeys(LedKeyboard::Color color) {
	KeyValueArray keyValues;

	for (uint8_t i = 0; i < keyGroupLogo.size(); i++) keyValues.push_back({keyGroupLogo[i], color});
	for (uint8_t i = 0; i < keyGroupIndicators.size(); i++) keyValues.push_back({keyGroupIndicators[i], color});
	for (uint8_t i = 0; i < keyGroupMultimedia.size(); i++) keyValues.push_back({keyGroupMultimedia[i], color});
	for (uint8_t i = 0; i < keyGroupGKeys.size(); i++) keyValues.push_back({keyGroupGKeys[i], color});
	for (uint8_t i = 0; i < keyGroupFKeys.size(); i++) keyValues.push_back({keyGroupFKeys[i], color});
	for (uint8_t i = 0; i < keyGroupFunctions.size(); i++) keyValues.push_back({keyGroupFunctions[i], color});
	for (uint8_t i = 0; i < keyGroupArrows.size(); i++) keyValues.push_back({keyGroupArrows[i], color});
	for (uint8_t i = 0; i < keyGroupNumeric.size(); i++) keyValues.push_back({keyGroupNumeric[i], color});
	for (uint8_t i = 0; i < keyGroupModifiers.size(); i++) keyValues.push_back({keyGroupModifiers[i], color});
	for (uint8_t i = 0; i < keyGroupKeys.size(); i++) keyValues.push_back({keyGroupKeys[i], color});
	return setKeys(keyValues);	
}

bool LogitechPerKeyLED::setGroupKeys(KeyGroup keyGroup, LedKeyboard::Color color) {
	KeyValueArray keyValues;
	
	KeyArray keyArray;
	
	switch (keyGroup) {
		case KeyGroup::logo:
			keyArray = keyGroupLogo;
			break;
		case KeyGroup::indicators:
			keyArray = keyGroupIndicators;
			break;
		case KeyGroup::gkeys:
			keyArray = keyGroupGKeys;
			break;
		case KeyGroup::multimedia:
			keyArray = keyGroupMultimedia;
			break;
		case KeyGroup::fkeys:
			keyArray = keyGroupFKeys;
			break;
		case KeyGroup::modifiers:
			keyArray = keyGroupModifiers;
			break;
		case KeyGroup::arrows:
			keyArray = keyGroupArrows;
			break;
		case KeyGroup::numeric:
			keyArray = keyGroupNumeric;
			break;
		case KeyGroup::functions:
			keyArray = keyGroupFunctions;
			break;
		case KeyGroup::keys:
			keyArray = keyGroupKeys;
			break;
		default:
			break;
	}
	
	for (uint8_t i = 0; i < keyArray.size(); i++) keyValues.push_back({keyArray[i], color});
	
	return setKeys(keyValues);
}

bool LogitechPerKeyLED::setKey(KeyValue keyValue) {
	return setKeys(KeyValueArray {keyValue});
}

bool LogitechPerKeyLED::sendDataInternal(byte_buffer_t &data) {
	if (! m_isOpen) return false;
	
	if (data.size() > 0) {
		#if defined(hidapi)
			data.insert(data.begin(), 0x00);
			if (hid_write(m_hidHandle, const_cast<unsigned char*>(data.data()), data.size()) < 0) {
				std::cout<<"Error: Can not write to hidraw, try with the libusb version"<<std::endl;
				return false;
			}
			byte_buffer_t data2;
			data2.resize(21, 0x00);
			hid_read_timeout(m_hidHandle, const_cast<unsigned char*>(data2.data()), data2.size(), 1);
			return true;
		#elif defined(libusb)
			if (data.size() > 20) {
				if(libusb_control_transfer(m_hidHandle, 0x21, 0x09, 0x0212, 1, 
						const_cast<unsigned char*>(data.data()), data.size(), 2000) < 0)
					return false;
			} else {
				if(libusb_control_transfer(m_hidHandle, 0x21, 0x09, 0x0211, 1, 
						const_cast<unsigned char*>(data.data()), data.size(), 2000) < 0)
					return false;
			}
			usleep(1000);
			unsigned char buffer[64];
			int len = 0;
			libusb_interrupt_transfer(m_hidHandle, 0x82, buffer, sizeof(buffer), &len, 1);
			return true;
		#endif
	}
	
	return false;
}

bool LogitechPerKeyLED::commit() {
	byte_buffer_t data;
	data = { 0x11, 0xff, 0x0c, 0x5a };
	data.resize(20, 0x00);
	return sendDataInternal(data);
}

bool LogitechPerKeyLED::setKeys(KeyValueArray keyValues) {
	if (keyValues.empty()) return false;
	
	bool retval = true;
	
	std::vector<std::vector<KeyValue>> SortedKeys = {
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
							data.push_back(static_cast<uint8_t>(
								static_cast<uint16_t>(SortedKeys[kag][gi+i].key) & 0x00ff));
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

bool LogitechPerKeyLED::setNativeEffect(NativeEffect effect, NativeEffectPart part, uint8_t speed, Color color) {

  // The 'all' is handled in an odd and separate fashion, and should be implemented by the application, to set indicator colors if desired.
  if (part == NativeEffectPart::all) {
    setNativeEffect(effect,NativeEffectPart::keys,speed,color);
    setNativeEffect(effect,NativeEffectPart::logo,speed,color);
    return true; //May not have all parts
  }

  if (! hasNativeEffectPart(part)) return false;

	byte_buffer_t data;
	
	switch (effect) {
		
		case NativeEffect::color:
			data = { 0x11, 0xff, nativeEffectProtocolByte, 0x3c, (uint8_t)part, 0x01, color.red, color.green, color.blue, 0x02 };
			break;
		case NativeEffect::breathing:
			data = {
				0x11, 0xff, nativeEffectProtocolByte, 0x3c, (uint8_t)part, 0x02,
				color.red, color.green, color.blue, speed, 
				0x10, 0x00, 0x64 
			};
			break;
		case NativeEffect::cycle:
			data = {
				0x11, 0xff, nativeEffectProtocolByte, 0x3c, (uint8_t)part, 0x03,
				0x00, 0x00, 0x00, 0x00, 0x00, speed, 0x00, 0x00, 0x64
			};
			break;
		case NativeEffect::hwave:
			switch (part) {
				case NativeEffectPart::logo:
					setNativeEffect(NativeEffect::color, part, 0, Color({0x00, 0xff, 0xff}));
					break;
				default:
					data = {
						0x11, 0xff, nativeEffectProtocolByte, 0x3c, (uint8_t)part, 0x04,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x01, 0x64, speed
					};
					break;
			}
			break;
		case NativeEffect::vwave:
			switch (part) {
				case NativeEffectPart::logo:
					setNativeEffect(NativeEffect::color, part, 0, Color({0x00, 0xff, 0xff}));
					break;
				default:
					data = {
						0x11, 0xff, nativeEffectProtocolByte, 0x3c, (uint8_t)part, 0x04,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x02, 0x64, speed
					};
					break;
			}
			break;
		case NativeEffect::cwave:
			switch (part) {
				case NativeEffectPart::logo:
					setNativeEffect(NativeEffect::color, part, 0, Color({0x00, 0xff, 0xff}));
					break;
				default:
					data = {
						0x11, 0xff, nativeEffectProtocolByte, 0x3c, (uint8_t)part, 0x04,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x03, 0x64, speed
					};
					break;
			}
			break;
		
		default:
			return false;
	}
	
	data.resize(20, 0x00);
	return sendDataInternal(data);
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

bool setRegion(uint8_t region, LedKeyboard::Color color) {
	return false;
}

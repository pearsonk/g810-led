#include "Logitech/LogitechDevice.h"

bool LogitechDevice::sendDataInternal(byte_buffer_t &data) {
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

bool LogitechDevice::setStartupMode(StartupMode startupMode) {
	byte_buffer_t data;
	data = { 0x11, 0xff, 0x0d, 0x5a, 0x00, 0x01 };
	data.push_back((unsigned char)startupMode);
	data.resize(20, 0x00);
	return sendDataInternal(data);
}

bool LogitechDevice::setNativeEffect(NativeEffect effect, NativeEffectPart part, uint8_t speed, Color color) {

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

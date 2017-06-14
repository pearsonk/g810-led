#ifndef KEYBOARD_LOGITECH_CLASS
#define KEYBOARD_LOGITECH_CLASS

#include "../Device.h"

class LogitechDevice : public LedDevice {
	public:

		enum class NativeEffect : uint8_t {
			color = 0x01,
			breathing,
			cycle,
			hwave,
			vwave,
			cwave
		};

		enum class NativeEffectPart : uint8_t {
			all = 0xff,
			keys = 0x00,
			logo
		};

		enum class StartupMode : uint8_t {
			wave = 0x01,
			color
		};

		bool setNativeEffect(NativeEffect effect, NativeEffectPart part, uint8_t speed, Color color);
		bool setStartupMode(StartupMode startupMode);

		virtual bool setGKeysMode(uint8_t value) = 0;
		virtual bool setMNKey(uint8_t value) = 0;
		virtual bool setMRKey(uint8_t value) = 0;

	private:

	protected:
		typedef std::vector<unsigned char> byte_buffer_t;

		uint8_t nativeEffectProtocolByte;

		bool sendDataInternal(byte_buffer_t &data);

		virtual bool hasNativeEffectPart(NativeEffectPart part) = 0;
};

#endif

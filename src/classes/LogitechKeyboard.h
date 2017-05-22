#ifndef KEYBOARD_LOGITECH_CLASS
#define KEYBOARD_LOGITECH_CLASS

#include "Keyboard.h"

class LogitechKeyboard : public LedKeyboard {
	public:
		enum class StartupMode : uint8_t {
			wave = 0x01,
			color
		};

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

		virtual bool setMRKey(uint8_t value) = 0;
		virtual bool setMNKey(uint8_t value) = 0;
		virtual bool setGKeysMode(uint8_t value) = 0;
		virtual bool setNativeEffect(NativeEffect effect, NativeEffectPart part, uint8_t speed, Color color) = 0;
		virtual bool setStartupMode(StartupMode startupMode) = 0;

	private:

		/*
		enum class KeyboardModel : uint8_t {
			unknown = 0x00,
			g213,
			g410,
			g610,
			g810,
			g910,
			gpro
		};*/
		
	protected:
		typedef std::vector<unsigned char> byte_buffer_t;
		virtual bool sendDataInternal(byte_buffer_t &data) = 0;
    virtual bool hasNativeEffectPart(NativeEffectPart part) = 0;
};

#endif

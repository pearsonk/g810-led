#ifndef KEYBOARD_LOGITECH_G213_CLASS
#define KEYBOARD_LOGITECH_G213_CLASS

#include "../LogitechDevice.h"

class LogitechG213 : public LogitechDevice {

	public:
		LogitechG213();
		~LogitechG213();

		bool setGKeysMode(uint8_t value) override;
		bool setMNKey(uint8_t value) override;
		bool setMRKey(uint8_t value) override;

		bool setLED(LEDValue value) override;
		bool setLEDs(LEDValueArray values) override;
		bool commit() override;

		const LED left = { "Left", 0x1 };
		const LED midLeft = { "Middle-left", 0x2 };
		const LED middle = { "Middle", 0x3 };
		const LED midRight = { "Middle-right", 0x4 };
		const LED right = { "Right", 0x5 };

		bool hasNativeEffectPart(NativeEffectPart part) override;

	private:

	protected:

};
#endif

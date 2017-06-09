#ifndef KEYBOARD_LOGITECH_G810_CLASS
#define KEYBOARD_LOGITECH_G810_CLASS

#include "../LogitechPerKeyLED.h"

class LogitechG810 : public LogitechPerKeyLED {

	public:
		LogitechG810();

    bool hasNativeEffectPart(LogitechDevice::NativeEffectPart part) override;
		bool setMRKey(uint8_t value) override;	
		bool setMNKey(uint8_t value) override;
		bool setGKeysMode(uint8_t value) override;
		bool setStartupMode(StartupMode startupMode) override;

	private:
    void populateLEDs(std::string name, std::vector<LED> group);

	protected:
		void getSortedKeys(LogitechPerKeyLED::LEDValueArray keyValues, std::vector<std::vector<LogitechPerKeyLED::LEDValue>>& sortedKeys) override;
};

#endif

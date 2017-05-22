#ifndef KEYBOARD_LOGITECH_G410_CLASS
#define KEYBOARD_LOGITECH_G410_CLASS

#include "LogitechPerKeyLED.h"

class LogitechG410 : public LogitechPerKeyLED {

	public:
		LogitechG410();

		LogitechG410(uint16_t vendorID, uint16_t productID, std::string serial);
	
    bool hasNativeEffectPart(LogitechKeyboard::NativeEffectPart part) override;
		bool setMRKey(uint8_t value) override;	
		bool setMNKey(uint8_t value) override;
		bool setGKeysMode(uint8_t value) override;
		bool setStartupMode(StartupMode startupMode) override;
		bool setRegion(uint8_t region, Color color) override;

	private:

	protected:
		void getSortedKeys(LogitechPerKeyLED::KeyValueArray keyValues, std::vector<std::vector<LogitechPerKeyLED::KeyValue>>& sortedKeys) override;
};

#endif

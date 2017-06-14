#ifndef KEYBOARD_LOGITECH_PERKEY_CLASS
#define KEYBOARD_LOGITECH_PERKEY_CLASS

#include "LogitechDevice.h"
#include "LogitechKeyLEDs.h"

class LogitechPerKeyLED : public LogitechDevice, public LogitechKeyLEDs {

	public:
		enum class KeyAddressGroup : uint8_t {
			logo = 0x00,
			indicators,
			multimedia,
			gkeys,
			keys
		};

		enum class KeyGroup : uint8_t {
			logo = 0x00,
			indicators,
			multimedia,
			gkeys,
			fkeys,
			modifiers,
			functions,
			arrows,
			numeric,
			keys
		};

		typedef struct {
			std::string name;
			uint16_t value;
		} Key;

		typedef struct {
			Key logitechCode;
			uint16_t scanCode;
		} KeyMap;
		
		Key getKey(uint16_t scanCode);
    Key getKey(std::string ledName);
		bool setLEDs(LEDValueArray keyValues) override;
		bool setLED(LEDValue keyValue) override;
		bool commit() override;

	private:

	protected:


		byte_buffer_t getKeyGroupAddress(KeyAddressGroup keyAddressGroup);

		virtual void getSortedKeys(LEDValueArray keyValues, std::vector<std::vector<LEDValue>>& sortedKeys) = 0;

		virtual bool hasNativeEffectPart(NativeEffectPart part) = 0;

};

#endif

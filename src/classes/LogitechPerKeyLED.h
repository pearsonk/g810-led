#ifndef KEYBOARD_LOGITECH_PERKEY_CLASS
#define KEYBOARD_LOGITECH_PERKEY_CLASS

#include "LogitechDevice.h"

class LogitechPerKeyLED : public LogitechDevice {

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

		enum class Key : uint16_t { // 127 items
			
			logo = static_cast<uint8_t>(KeyAddressGroup::logo) << 8 | 0x01,
			logo2,
			
			backlight = static_cast<uint8_t>(KeyAddressGroup::indicators) << 8| 0x01,
			game, caps, scroll, num, 
			
			next = static_cast<uint8_t>(KeyAddressGroup::multimedia) << 8 | 0xb5,
			prev, stop,
			play = static_cast<uint8_t>(KeyAddressGroup::multimedia) << 8 | 0xcd,
			mute = static_cast<uint8_t>(KeyAddressGroup::multimedia) << 8 | 0xe2,
			
			g1 = static_cast<uint8_t>(KeyAddressGroup::gkeys) << 8 | 0x01,
			g2, g3, g4, g5, g6, g7, g8, g9,
			
			a = static_cast<uint8_t>(KeyAddressGroup::keys) << 8 | 0x04,
			b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
			n1, n2, n3, n4, n5, n6, n7, n8, n9, n0,
			enter, esc, backspace, tab, space, minus, equal, open_bracket, close_bracket,
			backslash, dollar, semicolon, quote, tilde, comma, period, slash, caps_lock,
			f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
			print_screen, scroll_lock, pause_break, insert, home, page_up, del, end, page_down,
			arrow_right, arrow_left, arrow_bottom, arrow_top, num_lock, num_slash, num_asterisk,
			num_minus, num_plus, num_enter,
			num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_0,
			num_dot, intl_backslash, menu,
			
			ctrl_left = static_cast<uint8_t>(KeyAddressGroup::keys) << 8 | 0xe0,
			shift_left, alt_left, win_left,
			ctrl_right, shift_right, alt_right, win_right
			
		};
		
		typedef struct {
			Key logitechCode;
			uint16_t scanCode;
		} KeyMap;
		
/*		struct KeyValue {
			Key key;
			LedDevice::Color color;
		};*/

		Key getKey(uint16_t scanCode);
		bool setGroupKeys(KeyGroup keyGroup, Color color);
		bool setKeys(KeyValueArray keyValues) override;
		bool setKey(KeyValue keyValue) override;
		bool setNativeEffect(NativeEffect effect, NativeEffectPart part, uint8_t speed, Color color) override;
		bool commit() override;


		bool setAllKeys(Color color) override;

	private:
		std::vector<KeyMap> keyMap;


	protected:
		typedef std::vector<uint16_t> KeyArray;

		const KeyArray keyGroupLogo = { 
			(uint16_t)Key::logo, 
			(uint16_t)Key::logo2
		};

		const KeyArray keyGroupIndicators = { 
			(uint16_t)Key::caps,
			(uint16_t)Key::num,
			(uint16_t)Key::scroll,
			(uint16_t)Key::game,
			(uint16_t)Key::backlight
		};

		const KeyArray keyGroupMultimedia = { 
			(uint16_t)Key::next,
			(uint16_t)Key::prev,
			(uint16_t)Key::stop,
			(uint16_t)Key::play,
			(uint16_t)Key::mute
		};

		const KeyArray keyGroupGKeys = {
			(uint16_t)Key::g1,
			(uint16_t)Key::g2,
			(uint16_t)Key::g3,
			(uint16_t)Key::g4,
			(uint16_t)Key::g5,
			(uint16_t)Key::g6,
			(uint16_t)Key::g7,
			(uint16_t)Key::g8,
			(uint16_t)Key::g9
		};

		const KeyArray keyGroupFKeys = {
			(uint16_t)Key::f1,
			(uint16_t)Key::f2,
			(uint16_t)Key::f3,
			(uint16_t)Key::f4,
			(uint16_t)Key::f5,
			(uint16_t)Key::f6,
			(uint16_t)Key::f7,
			(uint16_t)Key::f8,
			(uint16_t)Key::f9,
			(uint16_t)Key::f10,
			(uint16_t)Key::f11,
			(uint16_t)Key::f12 
		};

		const KeyArray keyGroupModifiers = {
			(uint16_t)Key::shift_left,
			(uint16_t)Key::ctrl_left,
			(uint16_t)Key::win_left,
			(uint16_t)Key::alt_left,
			(uint16_t)Key::alt_right,
			(uint16_t)Key::win_right,
			(uint16_t)Key::ctrl_right,
			(uint16_t)Key::shift_right,
			(uint16_t)Key::menu
		};

		const KeyArray keyGroupFunctions = {
			(uint16_t)Key::esc,
			(uint16_t)Key::print_screen,
			(uint16_t)Key::scroll_lock,
			(uint16_t)Key::pause_break,
			(uint16_t)Key::insert,
			(uint16_t)Key::del,
			(uint16_t)Key::home,
			(uint16_t)Key::end,
			(uint16_t)Key::page_up,
			(uint16_t)Key::page_down
		};

		const KeyArray keyGroupArrows = {
			(uint16_t)Key::arrow_top,
			(uint16_t)Key::arrow_left,
			(uint16_t)Key::arrow_bottom,
			(uint16_t)Key::arrow_right
		};

		const KeyArray keyGroupNumeric = {
			(uint16_t)Key::num_1,
			(uint16_t)Key::num_2,
			(uint16_t)Key::num_3,
			(uint16_t)Key::num_4,
			(uint16_t)Key::num_5,
			(uint16_t)Key::num_6,
			(uint16_t)Key::num_7,
			(uint16_t)Key::num_8,
			(uint16_t)Key::num_9,
			(uint16_t)Key::num_0, 
			(uint16_t)Key::num_dot,
			(uint16_t)Key::num_enter,
			(uint16_t)Key::num_plus,
			(uint16_t)Key::num_minus,
			(uint16_t)Key::num_asterisk,
			(uint16_t)Key::num_slash,
			(uint16_t)Key::num_lock
		};

		const KeyArray keyGroupKeys = {
			(uint16_t)Key::a,
			(uint16_t)Key::b,
			(uint16_t)Key::c,
			(uint16_t)Key::d,
			(uint16_t)Key::e,
			(uint16_t)Key::f,
			(uint16_t)Key::g,
			(uint16_t)Key::h,
			(uint16_t)Key::i,
			(uint16_t)Key::j,
			(uint16_t)Key::k,
			(uint16_t)Key::l,
			(uint16_t)Key::m,
			(uint16_t)Key::n,
			(uint16_t)Key::o,
			(uint16_t)Key::p,
			(uint16_t)Key::q,
			(uint16_t)Key::r,
			(uint16_t)Key::s,
			(uint16_t)Key::t,
			(uint16_t)Key::u,
			(uint16_t)Key::v,
			(uint16_t)Key::w,
			(uint16_t)Key::x,
			(uint16_t)Key::y,
			(uint16_t)Key::z,
			(uint16_t)Key::n1,
			(uint16_t)Key::n2,
			(uint16_t)Key::n3,
			(uint16_t)Key::n4,
			(uint16_t)Key::n5,
			(uint16_t)Key::n6,
			(uint16_t)Key::n7,
			(uint16_t)Key::n8,
			(uint16_t)Key::n9,
			(uint16_t)Key::n0,
			(uint16_t)Key::enter,
			(uint16_t)Key::backspace,
			(uint16_t)Key::tab,
			(uint16_t)Key::space,
			(uint16_t)Key::minus,
			(uint16_t)Key::equal,
			(uint16_t)Key::open_bracket,
			(uint16_t)Key::close_bracket,
			(uint16_t)Key::backslash,
			(uint16_t)Key::dollar,
			(uint16_t)Key::semicolon,
			(uint16_t)Key::quote,
			(uint16_t)Key::tilde,
			(uint16_t)Key::comma,
			(uint16_t)Key::period,
			(uint16_t)Key::slash,
			(uint16_t)Key::caps_lock,
			(uint16_t)Key::intl_backslash
		};
		
		uint8_t nativeEffectProtocolByte;

		byte_buffer_t getKeyGroupAddress(KeyAddressGroup keyAddressGroup);

		virtual void getSortedKeys(KeyValueArray keyValues, std::vector<std::vector<KeyValue>>& sortedKeys) = 0;

		bool sendDataInternal(byte_buffer_t &data) override;
    virtual bool hasNativeEffectPart(NativeEffectPart part) = 0;
};

#endif

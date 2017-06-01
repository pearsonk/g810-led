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
/*
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
			
		}; */

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
//		bool setGroupKeys(KeyGroup keyGroup, Color color);
		bool setLEDs(LEDValueArray keyValues) override;
		bool setLED(LEDValue keyValue) override;
		bool setNativeEffect(NativeEffect effect, NativeEffectPart part, uint8_t speed, Color color) override;
		bool commit() override;


		bool setAllLEDs(Color color) override;


LED logo = {"logo", 0x0001};
LED badge = {"badge", 0x0002};
LED backlight = {"backlight", 0x0101};
LED game = {"game", 0x0102};
LED caps = {"caps", 0x0103};
LED scroll = {"scroll", 0x0104};
LED num = {"num", 0x0105};
LED next = {"next", 0x02b5};
LED prev = {"prev", 0x02b6};
LED stop = {"stop", 0x02b7};
LED play = {"play", 0x02cd};
LED mute = {"mute", 0x02e2};
LED g1 = {"g1", 0x0301};
LED g2 = {"g2", 0x0302};
LED g3 = {"g3", 0x0303};
LED g4 = {"g4", 0x0304};
LED g5 = {"g5", 0x0305};
LED g6 = {"g6", 0x0306};
LED g7 = {"g7", 0x0307};
LED g8 = {"g8", 0x0308};
LED g9 = {"g9", 0x0309};
LED a = {"a", 0x0404};
LED b = {"b", 0x0405};
LED c = {"c", 0x0406};
LED d = {"d", 0x0407};
LED e = {"e", 0x0408};
LED f = {"f", 0x0409};
LED g = {"g", 0x040a};
LED h = {"h", 0x040b};
LED i = {"i", 0x040c};
LED j = {"j", 0x040d};
LED k = {"k", 0x040e};
LED l = {"l", 0x040f};
LED m = {"m", 0x0410};
LED n = {"n", 0x0411};
LED o = {"o", 0x0412};
LED p = {"p", 0x0413};
LED q = {"q", 0x0414};
LED r = {"r", 0x0415};
LED s = {"s", 0x0416};
LED t = {"t", 0x0417};
LED u = {"u", 0x0418};
LED v = {"v", 0x0419};
LED w = {"w", 0x041a};
LED x = {"x", 0x041b};
LED y = {"y", 0x041c};
LED z = {"z", 0x041d};
LED n1 = {"n2", 0x041e};
LED n2 = {"n2", 0x041f};
LED n3 = {"n3", 0x0420};
LED n4 = {"n4", 0x0421};
LED n5 = {"n5", 0x0422};
LED n6 = {"n6", 0x0423};
LED n7 = {"n7", 0x0424};
LED n8 = {"n8", 0x0425};
LED n9 = {"n9", 0x0426};
LED n0 = {"n0", 0x0427};
LED enter = {"enter", 0x0428};
LED esc = {"esc", 0x0429};
LED backspace = {"backspace", 0x042a};
LED tab = {"tab", 0x042b};
LED space = {"space", 0x042c};
LED minus = {"minus", 0x042d};
LED equal = {"equal", 0x042e};
LED open_bracket = {"open_bracket", 0x042f};
LED close_bracket = {"close_bracket", 0x0430};
LED backslash = {"backslash", 0x0431};
LED dollar = {"dollar", 0x0432};
LED semicolon = {"semicolon", 0x0433};
LED quote = {"quote", 0x0434};
LED tilde = {"tilde", 0x0435};
LED comma = {"comma", 0x0436};
LED period = {"period", 0x0437};
LED slash = {"slash", 0x0438};
LED caps_lock = {"caps_lock", 0x0439};
LED f1 = {"f1", 0x043a};
LED f2 = {"f2", 0x043b};
LED f3 = {"f3", 0x043c};
LED f4 = {"f4", 0x043d};
LED f5 = {"f5", 0x043e};
LED f6 = {"f6", 0x043f};
LED f7 = {"f7", 0x0440};
LED f8 = {"f8", 0x0441};
LED f9 = {"f9", 0x0442};
LED f10 = {"f10", 0x0443};
LED f11 = {"f11", 0x0444};
LED f12 = {"f12", 0x0445};
LED print_screen = {"print_screen", 0x0446};
LED scroll_lock = {"scroll_lock", 0x0447};
LED pause_break = {"pause_break", 0x0448};
LED insert = {"insert", 0x0449};
LED home = {"home", 0x044a};
LED page_up = {"page_up", 0x044b};
LED del = {"del", 0x044c};
LED end = {"end", 0x044d};
LED page_down = {"page_down", 0x044e};
LED arrow_right = {"arrow_right", 0x044f};
LED arrow_left = {"arrow_left", 0x0450};
LED arrow_bottom = {"arrow_bottom", 0x0451};
LED arrow_top = {"arrow_top", 0x0452};
LED num_lock = {"num_lock", 0x0453};
LED num_slash = {"num_slash", 0x0454};
LED num_asterisk = {"num_asterisk", 0x0455};
LED num_minus = {"num_minus", 0x0456};
LED num_plus = {"num_plus", 0x0457};
LED num_enter = {"num_enter", 0x0458};
LED num_1 = {"num_1", 0x0459};
LED num_2 = {"num_2", 0x045a};
LED num_3 = {"num_3", 0x045b};
LED num_4 = {"num_4", 0x045c};
LED num_5 = {"num_5", 0x045d};
LED num_6 = {"num_6", 0x045e};
LED num_7 = {"num_7", 0x045f};
LED num_8 = {"num_8", 0x0460};
LED num_9 = {"num_9", 0x0461};
LED num_0 = {"num_0", 0x0462};
LED num_dot = {"num_dot", 0x0463};
LED intl_backslash = {"intl_backslash", 0x0464};
LED menu = {"menu", 0x0465};
LED ctrl_left = {"ctrl_left", 0x04e0};
LED shift_left = {"shift_left", 0x04e1};
LED alt_left = {"alt_left", 0x04e2};
LED win_left = {"win_left", 0x04e3};
LED ctrl_right = {"ctrl_right", 0x04e4};
LED shift_right = {"shift_right", 0x04e5};
LED alt_right = {"alt_right", 0x04e6};
LED win_right = {"win_right", 0x04e7};

	private:


	protected:

		const std::vector<LED> keyGroupLogo = { 
			logo, 
			badge
		};

		const std::vector<LED> keyGroupIndicators = { 
			caps,
			num,
			scroll,
			game,
			backlight
		};

		const std::vector<LED> keyGroupMultimedia = { 
			next,
			prev,
			stop,
			play,
			mute
		};

		const std::vector<LED> keyGroupGKeys = {
			g1,
			g2,
			g3,
			g4,
			g5,
			g6,
			g7,
			g8,
			g9
		};

		const std::vector<LED> keyGroupFKeys = {
			f1,
			f2,
			f3,
			f4,
			f5,
			f6,
			f7,
			f8,
			f9,
			f10,
			f11,
			f12 
		};

		const std::vector<LED> keyGroupModifiers = {
			shift_left,
			ctrl_left,
			win_left,
			alt_left,
			alt_right,
			win_right,
			ctrl_right,
			shift_right,
			menu
		};

		const std::vector<LED> keyGroupFunctions = {
			esc,
			print_screen,
			scroll_lock,
			pause_break,
			insert,
			del,
			home,
			end,
			page_up,
			page_down
		};

		const std::vector<LED> keyGroupArrows = {
			arrow_top,
			arrow_left,
			arrow_bottom,
			arrow_right
		};

		const std::vector<LED> keyGroupNumeric = {
			num_1,
			num_2,
			num_3,
			num_4,
			num_5,
			num_6,
			num_7,
			num_8,
			num_9,
			num_0, 
			num_dot,
			num_enter,
			num_plus,
			num_minus,
			num_asterisk,
			num_slash,
			num_lock
		};

		const std::vector<LED> keyGroupKeys = {
			a,
			b,
			c,
			d,
			e,
			f,
			g,
			h,
			i,
			j,
			k,
			l,
			m,
			n,
			o,
			p,
			q,
			r,
			s,
			t,
			u,
			v,
			w,
			x,
			y,
			z,
			n1,
			n2,
			n3,
			n4,
			n5,
			n6,
			n7,
			n8,
			n9,
			n0,
			enter,
			backspace,
			tab,
			space,
			minus,
			equal,
			open_bracket,
			close_bracket,
			backslash,
			dollar,
			semicolon,
			quote,
			tilde,
			comma,
			period,
			slash,
			caps_lock,
			intl_backslash
		};
		
		uint8_t nativeEffectProtocolByte;

		byte_buffer_t getKeyGroupAddress(KeyAddressGroup keyAddressGroup);

		virtual void getSortedKeys(LEDValueArray keyValues, std::vector<std::vector<LEDValue>>& sortedKeys) = 0;

		bool sendDataInternal(byte_buffer_t &data) override;
    virtual bool hasNativeEffectPart(NativeEffectPart part) = 0;

};

#endif

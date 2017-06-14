#ifndef KEYBOARD_LOGITECK_KEY_LEDS_CLASS
#define KEYBOARD_LOGITECK_KEY_LEDS_CLASS

#include "Device.h"

class LogitechKeyLEDs {

	public:

///////////////
// LEDs
///////////////
		const LedDevice::LED logo = {"logo", 0x0001};
		const LedDevice::LED badge = {"badge", 0x0002};
		const LedDevice::LED backlight = {"backlight", 0x0101};
		const LedDevice::LED game = {"game", 0x0102};
		const LedDevice::LED caps = {"caps", 0x0103};
		const LedDevice::LED scroll = {"scroll", 0x0104};
		const LedDevice::LED num = {"num", 0x0105};
		const LedDevice::LED next = {"next", 0x02b5};
		const LedDevice::LED prev = {"prev", 0x02b6};
		const LedDevice::LED stop = {"stop", 0x02b7};
		const LedDevice::LED play = {"play", 0x02cd};
		const LedDevice::LED mute = {"mute", 0x02e2};
		const LedDevice::LED g1 = {"g1", 0x0301};
		const LedDevice::LED g2 = {"g2", 0x0302};
		const LedDevice::LED g3 = {"g3", 0x0303};
		const LedDevice::LED g4 = {"g4", 0x0304};
		const LedDevice::LED g5 = {"g5", 0x0305};
		const LedDevice::LED g6 = {"g6", 0x0306};
		const LedDevice::LED g7 = {"g7", 0x0307};
		const LedDevice::LED g8 = {"g8", 0x0308};
		const LedDevice::LED g9 = {"g9", 0x0309};
		const LedDevice::LED a = {"a", 0x0404};
		const LedDevice::LED b = {"b", 0x0405};
		const LedDevice::LED c = {"c", 0x0406};
		const LedDevice::LED d = {"d", 0x0407};
		const LedDevice::LED e = {"e", 0x0408};
		const LedDevice::LED f = {"f", 0x0409};
		const LedDevice::LED g = {"g", 0x040a};
		const LedDevice::LED h = {"h", 0x040b};
		const LedDevice::LED i = {"i", 0x040c};
		const LedDevice::LED j = {"j", 0x040d};
		const LedDevice::LED k = {"k", 0x040e};
		const LedDevice::LED l = {"l", 0x040f};
		const LedDevice::LED m = {"m", 0x0410};
		const LedDevice::LED n = {"n", 0x0411};
		const LedDevice::LED o = {"o", 0x0412};
		const LedDevice::LED p = {"p", 0x0413};
		const LedDevice::LED q = {"q", 0x0414};
		const LedDevice::LED r = {"r", 0x0415};
		const LedDevice::LED s = {"s", 0x0416};
		const LedDevice::LED t = {"t", 0x0417};
		const LedDevice::LED u = {"u", 0x0418};
		const LedDevice::LED v = {"v", 0x0419};
		const LedDevice::LED w = {"w", 0x041a};
		const LedDevice::LED x = {"x", 0x041b};
		const LedDevice::LED y = {"y", 0x041c};
		const LedDevice::LED z = {"z", 0x041d};
		const LedDevice::LED n1 = {"n2", 0x041e};
		const LedDevice::LED n2 = {"n2", 0x041f};
		const LedDevice::LED n3 = {"n3", 0x0420};
		const LedDevice::LED n4 = {"n4", 0x0421};
		const LedDevice::LED n5 = {"n5", 0x0422};
		const LedDevice::LED n6 = {"n6", 0x0423};
		const LedDevice::LED n7 = {"n7", 0x0424};
		const LedDevice::LED n8 = {"n8", 0x0425};
		const LedDevice::LED n9 = {"n9", 0x0426};
		const LedDevice::LED n0 = {"n0", 0x0427};
		const LedDevice::LED enter = {"enter", 0x0428};
		const LedDevice::LED esc = {"esc", 0x0429};
		const LedDevice::LED backspace = {"backspace", 0x042a};
		const LedDevice::LED tab = {"tab", 0x042b};
		const LedDevice::LED space = {"space", 0x042c};
		const LedDevice::LED minus = {"minus", 0x042d};
		const LedDevice::LED equal = {"equal", 0x042e};
		const LedDevice::LED open_bracket = {"open_bracket", 0x042f};
		const LedDevice::LED close_bracket = {"close_bracket", 0x0430};
		const LedDevice::LED backslash = {"backslash", 0x0431};
		const LedDevice::LED dollar = {"dollar", 0x0432};
		const LedDevice::LED semicolon = {"semicolon", 0x0433};
		const LedDevice::LED quote = {"quote", 0x0434};
		const LedDevice::LED tilde = {"tilde", 0x0435};
		const LedDevice::LED comma = {"comma", 0x0436};
		const LedDevice::LED period = {"period", 0x0437};
		const LedDevice::LED slash = {"slash", 0x0438};
		const LedDevice::LED caps_lock = {"caps_lock", 0x0439};
		const LedDevice::LED f1 = {"f1", 0x043a};
		const LedDevice::LED f2 = {"f2", 0x043b};
		const LedDevice::LED f3 = {"f3", 0x043c};
		const LedDevice::LED f4 = {"f4", 0x043d};
		const LedDevice::LED f5 = {"f5", 0x043e};
		const LedDevice::LED f6 = {"f6", 0x043f};
		const LedDevice::LED f7 = {"f7", 0x0440};
		const LedDevice::LED f8 = {"f8", 0x0441};
		const LedDevice::LED f9 = {"f9", 0x0442};
		const LedDevice::LED f10 = {"f10", 0x0443};
		const LedDevice::LED f11 = {"f11", 0x0444};
		const LedDevice::LED f12 = {"f12", 0x0445};
		const LedDevice::LED print_screen = {"print_screen", 0x0446};
		const LedDevice::LED scroll_lock = {"scroll_lock", 0x0447};
		const LedDevice::LED pause_break = {"pause_break", 0x0448};
		const LedDevice::LED insert = {"insert", 0x0449};
		const LedDevice::LED home = {"home", 0x044a};
		const LedDevice::LED page_up = {"page_up", 0x044b};
		const LedDevice::LED del = {"del", 0x044c};
		const LedDevice::LED end = {"end", 0x044d};
		const LedDevice::LED page_down = {"page_down", 0x044e};
		const LedDevice::LED arrow_right = {"arrow_right", 0x044f};
		const LedDevice::LED arrow_left = {"arrow_left", 0x0450};
		const LedDevice::LED arrow_bottom = {"arrow_bottom", 0x0451};
		const LedDevice::LED arrow_top = {"arrow_top", 0x0452};
		const LedDevice::LED num_lock = {"num_lock", 0x0453};
		const LedDevice::LED num_slash = {"num_slash", 0x0454};
		const LedDevice::LED num_asterisk = {"num_asterisk", 0x0455};
		const LedDevice::LED num_minus = {"num_minus", 0x0456};
		const LedDevice::LED num_plus = {"num_plus", 0x0457};
		const LedDevice::LED num_enter = {"num_enter", 0x0458};
		const LedDevice::LED num_1 = {"num_1", 0x0459};
		const LedDevice::LED num_2 = {"num_2", 0x045a};
		const LedDevice::LED num_3 = {"num_3", 0x045b};
		const LedDevice::LED num_4 = {"num_4", 0x045c};
		const LedDevice::LED num_5 = {"num_5", 0x045d};
		const LedDevice::LED num_6 = {"num_6", 0x045e};
		const LedDevice::LED num_7 = {"num_7", 0x045f};
		const LedDevice::LED num_8 = {"num_8", 0x0460};
		const LedDevice::LED num_9 = {"num_9", 0x0461};
		const LedDevice::LED num_0 = {"num_0", 0x0462};
		const LedDevice::LED num_dot = {"num_dot", 0x0463};
		const LedDevice::LED intl_backslash = {"intl_backslash", 0x0464};
		const LedDevice::LED menu = {"menu", 0x0465};
		const LedDevice::LED ctrl_left = {"ctrl_left", 0x04e0};
		const LedDevice::LED shift_left = {"shift_left", 0x04e1};
		const LedDevice::LED alt_left = {"alt_left", 0x04e2};
		const LedDevice::LED win_left = {"win_left", 0x04e3};
		const LedDevice::LED ctrl_right = {"ctrl_right", 0x04e4};
		const LedDevice::LED shift_right = {"shift_right", 0x04e5};
		const LedDevice::LED alt_right = {"alt_right", 0x04e6};
		const LedDevice::LED win_right = {"win_right", 0x04e7};

///////////////
// LED Groups
///////////////
		std::vector<LedDevice::LED> keyGroupArrows = {
			arrow_top,
			arrow_left,
			arrow_bottom,
			arrow_right
		};

		std::vector<LedDevice::LED> keyGroupBadge = {
			badge
		};

		std::vector<LedDevice::LED> keyGroupFKeys = {
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

		std::vector<LedDevice::LED> keyGroupFunctions = {
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

		std::vector<LedDevice::LED> keyGroupGKeys = {
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

		std::vector<LedDevice::LED> keyGroupIndicators = { 
			caps,
			num,
			scroll,
			game,
			backlight
		};

		std::vector<LedDevice::LED> keyGroupKeys = {
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

		std::vector<LedDevice::LED> keyGroupLogo = { 
			logo
		};

		std::vector<LedDevice::LED> keyGroupMultimedia = { 
			next,
			prev,
			stop,
			play,
			mute
		};

		std::vector<LedDevice::LED> keyGroupModifiers = {
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

		std::vector<LedDevice::LED> keyGroupNumeric = {
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

};
#endif

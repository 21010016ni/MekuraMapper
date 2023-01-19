#pragma once
#include <DxLib.h>
//#include <Windows.h>
#include "Point.hpp"

class Keyboard
{
	Keyboard() = delete;

protected:
	struct Value
	{
		BYTE v = 0;
		void operator<<(BYTE n)noexcept { (v <<= 1) += n; }
		explicit operator BYTE& ()noexcept { return v; }
		bool press()const noexcept { return v & 1; }
		bool push()const noexcept { return (v & 3) == 1; }
		bool pull()const noexcept { return (v & 3) == 2; }
	};
	static inline Value value[256];

public:
	static void update()noexcept
	{
		static BYTE key[256] = {0};
		static BYTE i = 0;
		(void)GetKeyboardState(key);
		do
			value[i] << bool(key[i] & 0x80);
		while (++i != 0);
	}

	static BYTE& get(BYTE code)noexcept { return (BYTE&)value[code]; }
	static bool press(BYTE code)noexcept { return value[code].press(); }
	static bool push(BYTE code)noexcept { return value[code].push(); }
	static bool pull(BYTE code)noexcept { return value[code].pull(); }
	static bool press()
	{
		for (BYTE i = 0; i < 240; ++i)
			if (press(i))
				return true;
		return false;
	}
	static bool push()
	{
		for (BYTE i = 0; i < 240; ++i)
			if (push(i))
				return true;
		return false;
	}
};

//class Mouse
//{
//	Mouse() = delete;
//
//protected:
//	static inline int _button = 0, _type = -1;
//	static inline Point<int> _pos = { -1,-1 };
//	static inline bool _update = false;
//	static inline int _wheel = 0;
//
//public:
//	static bool update()noexcept { return _wheel = GetMouseWheelRotVol(), _update = (GetMouseInputLog2(&_button, &_pos.x, &_pos.y, &_type) ? (GetMousePoint(&_pos.x, &_pos.y), false) : true); }
//
//	static bool change()noexcept { return _update; }
//	static bool button(int b)noexcept { return _button & b; }
//	static const Point<int>& pos()noexcept { return _pos; }
//	static int x()noexcept { return _pos.x; }
//	static int y()noexcept { return _pos.y; }
//	static bool type()noexcept { return !_type; }
//	static int wheel()noexcept { return _wheel; }
//	static bool click(int b)noexcept { return _update && _button & b && !_type; }
//	static bool releace(int b)noexcept { return _update && _button & b && _type; }
//};

class Mouse
{
	Mouse() = delete;

public:
	struct Log
	{
		int button;
		Point<int> pos;
		bool type;

		Log() :button(0), pos(-1, -1), type(false) {}

		bool left()const noexcept { return button & MOUSE_INPUT_LEFT; }
		bool right()const noexcept { return button & MOUSE_INPUT_RIGHT; }
		bool middle()const noexcept { return button & MOUSE_INPUT_MIDDLE; }
		bool b1()const noexcept { return button & MOUSE_INPUT_1; }
		bool b2()const noexcept { return button & MOUSE_INPUT_2; }
		bool b3()const noexcept { return button & MOUSE_INPUT_3; }
		bool b4()const noexcept { return button & MOUSE_INPUT_4; }
		bool b5()const noexcept { return button & MOUSE_INPUT_5; }
		bool b6()const noexcept { return button & MOUSE_INPUT_6; }
		bool b7()const noexcept { return button & MOUSE_INPUT_7; }
		bool b8()const noexcept { return button & MOUSE_INPUT_8; }
	};

	static inline Point<int> pos = Point<int>(-1, -1);
	static inline int button = 0;
	static inline int wheel = 0;

	static void update()
	{
		GetMousePoint(&pos.x, &pos.y);
		button = GetMouseInput();
		wheel = GetMouseWheelRotVol();
	}

	static bool left()noexcept { return button & MOUSE_INPUT_LEFT; }
	static bool right()noexcept { return button & MOUSE_INPUT_RIGHT; }
	static bool middle()noexcept { return button & MOUSE_INPUT_MIDDLE; }
	static bool b1()noexcept { return button & MOUSE_INPUT_1; }
	static bool b2()noexcept { return button & MOUSE_INPUT_2; }
	static bool b3()noexcept { return button & MOUSE_INPUT_3; }
	static bool b4()noexcept { return button & MOUSE_INPUT_4; }
	static bool b5()noexcept { return button & MOUSE_INPUT_5; }
	static bool b6()noexcept { return button & MOUSE_INPUT_6; }
	static bool b7()noexcept { return button & MOUSE_INPUT_7; }
	static bool b8()noexcept { return button & MOUSE_INPUT_8; }

	static bool getLog(Log& ret)
	{
		int buf;
		if (GetMouseInputLog2(&ret.button, &ret.pos.x, &ret.pos.y, &buf) == 0)
		{
			ret.type = buf == MOUSE_INPUT_LOG_DOWN;
			return true;
		}
		return false;
	}
};

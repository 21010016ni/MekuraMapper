#pragma once
#include "Draw.hpp"

class Game
{
	static inline int command = -1;

public:
	enum class Message
	{
		none,
		quit,
	};

	static Draw display;

	static void preset();
	static Message update();
	static void draw();

	static bool editmap();
	static int pop();
};


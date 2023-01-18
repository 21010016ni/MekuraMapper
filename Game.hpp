#pragma once
#include "Draw.hpp"

class Game
{
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
};


#pragma once
#include "Draw.hpp"

class Game
{
	static int command;

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

	static int pop();
};


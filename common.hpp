#pragma once
#include <random>
#include <Windows.h>

// 使用しない場合コメントアウト
//#define USE_RESOURCE
#define USE_CONSOLE

namespace common
{
	extern HWND hwnd;
	extern int width;
	extern int height;
	extern int colorbit;
	extern int fps;
	extern bool windowmode;

	extern int fc[8];
	extern int lc[2];
	extern int bc;

	extern std::mt19937 engine;

	constexpr float pi = 3.14159265359f;
	constexpr float pi2 = 6.28318530718f;

	inline bool onWindow(int x, int y) { return x >= 0 && x < width&& y >= 0 && y < height; }
}


#pragma once
#include <vector>
#include "Draw.hpp"
#include "Point.hpp"

class IconSet
{
public:
	static bool view;
	static Draw display;
	static Point<int> siz;

	static inline std::vector<std::vector<char>> icon;

	//IconSet(int x, int y, int sx, int sy) :view(true), display(x, y, 0), siz(sy, sx) {}

	static bool on(Point<int> t)/*const*/ { return display.pos.y <= t.y && t.y < display.pos.y + siz.y * icon.size() && display.pos.x <= t.x && t.x < display.pos.x + siz.x * icon.front().size(); }
	static char get(const Point<int> i)/*const*/
	{
		return icon.at(i.y).at(i.x);
	}

	static void draw()/*const*/;
};


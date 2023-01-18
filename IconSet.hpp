#pragma once
#include <vector>
#include "Draw.hpp"
#include "Point.hpp"

class IconSet
{
public:
	bool view;
	Draw display;
	Point<int> siz;

	std::vector<std::vector<char>> icon;

	IconSet(int x, int y, int sx, int sy) :view(true), display(x, y, 0), siz(sy, sx) {}

	bool on(Point<int> t)const { return display.pos.y <= t.y && t.y < display.pos.y + siz.y * icon.size() && display.pos.x <= t.x && t.x < display.pos.x + siz.x * icon.front().size(); }
	char get(const Point<int> i)const
	{
		return icon.at(i.y).at(i.x);
	}

	void draw()const;
};


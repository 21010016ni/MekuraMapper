#pragma once
#include "Draw.hpp"
//#include "Field.hpp"
#include "Grid.hpp"

class UI
{
public:
	static Point<int> gridSize, mapSize;
	static Draw map;

	static Point<int> GetMapRelativePoint(const Point<int>& mouse)
	{
		return mouse - map.pos;
	}

	static void draw(Grid& grid);

	//static void drawField(const Grid& target);
};


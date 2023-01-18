#pragma once
#include <bitset>
#include <array>
#include "IconSet.hpp"
#include "Draw.hpp"
#include "Point.hpp"

class Grid
{
	struct Tile
	{
		std::bitset<8> edge = 0;
		char face = -1;
		char icon = -1;
		bool signal = false;

		bool set(char bit, bool val)
		{
			if (edge[bit] != val)
			{
				// SEçƒê∂
				edge.set(bit, val);
				return true;
			}
			return false;
		}
		bool up() { return edge[0]; }
		bool left() { return edge[1]; }
	};

	template <size_t x,size_t y>struct GridData
	{
		std::array<std::array<Tile, x>, y> data;
		std::array<Tile, x>& operator[](size_t i) { return data[i]; }
		Tile& operator[](const Point<int>& i) { return data[i.y][i.x]; }
	};

public:
	Draw display;

	GridData<32, 24> grid;
	Point<int> size;
	IconSet iconset;

	char tool, brushColor, hasIcon;
	Point<int> linePoint, circle;
	
	static constexpr int lineThick = 4, ColorchangeActivateLength = 30, ColorNum = 8;
	static inline const Point<int> null = Point<int>(-1);

	Grid(int x, int y, int scroolX = 0, int scroolY = 0) :size(y, x), display(scroolY, scroolX, 0), iconset(0, 0, 16, 16), tool(0), brushColor(0), hasIcon(-1), linePoint(-1, -1), circle(-1, -1) {}

	bool controll();
	const Point<int> GetGridPoint(const Point<int>& p)const
	{
		auto buf = (p + size / 2) / size;
		return (p.distance<float>(buf * size) < size.length<float>() / 2) ? buf : null;
	}

	void draw();
};


#pragma once
#include <cmath>
#include <bitset>
#include <array>
#include "IconSet.hpp"
#include "Draw.hpp"
#include "Point.hpp"
#include "Input.hpp"
#include "common.hpp"

template<size_t sizeX,size_t sizeY> class Grid
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
				// SE再生
				edge.set(bit, val);
				return true;
			}
			return false;
		}
		bool up() { return edge[0]; }
		bool left() { return edge[1]; }
	};

	template <size_t _x,size_t _y>struct GridData
	{
		std::array<std::array<Tile, _x>, _y> data;
		std::array<Tile, _x>& operator[](size_t i) { return data[i]; }
		Tile& operator[](const Point<int>& i) { return data[i.y][i.x]; }
	};

public:
	Draw display;

	GridData<sizeX, sizeY> grid;
	Point<int> size;
	IconSet iconset;

	char tool, brushColor, hasIcon;
	Point<int> linePoint, circle;
	
	static constexpr int lineThick = 4, ColorchangeActivateLength = 30, ColorNum = 8;
	static inline const Point<int> null = Point<int>(-1);

	Grid(int x, int y, int scroolX = 0, int scroolY = 0) :size(y, x), display(scroolY, scroolX, 0), iconset(0, 0, 16, 16), tool(0), brushColor(0), hasIcon(-1), linePoint(-1, -1), circle(-1, -1) {}

	bool controll()
	{
		static Mouse::Log log;

		if (Mouse::wheel != 0)
		{
			// ツール切り替え
			tool ^= 1;
			tool &= 1;
			linePoint = null;
			circle = null;
			return true;
		}
		if (Mouse::getLog(log))
		{
			if (log.b3())
			{
				if (log.type)
				{
					if (tool == 0 || tool == 2)
					{
						// アイコンセットの表示非表示切り替え
						iconset.view ^= 1;
					}
					else if (tool == 1)
					{
						// 色切り替え表示
						circle = log.pos;
						return true;
					}
				}
				else
				{
					if (tool == 1 && circle != null)
					{
						// 色切り替え決定
						circle = log.pos - circle;
						if (circle.length<float>() > ColorchangeActivateLength)
						{
							float buf = std::atan2f(circle.y, circle.x);
							if (buf < 0)
								buf += common::pi * 2;
							buf /= common::pi / 4;
							brushColor = static_cast<char>(floor(buf));
						}
					}
				}
			}
			if (log.b1())
			{
				if (log.type)
				{
					char buf;
					if (iconset.view && iconset.on(log.pos))
					{
						// アイコンセットからアイコンを持ち上げる
						hasIcon = iconset.get((log.pos - iconset.display.pos) / iconset.siz);
						if (hasIcon != -1)
						{
							tool = 2;
							linePoint = null;
							circle = null;
						}
						return true;
					}
					else if (tool == 0 && common::onWindow(log.pos.x, log.pos.y) && (buf = grid[(log.pos - display.pos) / size].icon) != -1)
					{
						// アイコンを持ち上げる
						// SE再生
						grid[(log.pos - display.pos) / size].icon = -1;
						tool = 2;
						hasIcon = buf;
						linePoint = null;
						return true;
					}
				}
				else
				{
					if (tool == 0)
					{
						linePoint = null;
						return true;
					}
					if (tool == 2)
					{
						if (common::onWindow(log.pos.x, log.pos.y))
						{
							// アイコンを置く
							if (!iconset.view || !iconset.on(log.pos)) // アイコンセット以外の場所にドロップしたなら置く
							{
								grid[(log.pos - display.pos) / size].icon = hasIcon;
							}
							tool = 0;
							return true;
						}
					}
				}
			}
		}

		if (common::onWindow(Mouse::pos.x, Mouse::pos.y))
		{
			if (Mouse::b2())
			{
				if (tool == 0)
				{
					// 線を消す
					if ((Mouse::pos.y - display.pos.y + lineThick) % size.y <= lineThick * 2)
					{
						grid[(Mouse::pos - display.pos + Point<int>(lineThick, 0)) / size].set(0, false);
					}
					if ((Mouse::pos.x - display.pos.x + lineThick) % size.x <= lineThick * 2)
					{
						grid[(Mouse::pos - display.pos + Point<int>(0, lineThick)) / size].set(1, false);
					}
					return true;
				}
				else if (tool == 1)
				{
					// 面を消す
					grid[(Mouse::pos - display.pos) / size].face = -1;
					return true;
				}
			}
			else if (Mouse::b1())
			{
				if (tool == 0)
				{
					// 線を引く
					Point<int> buf = linePoint;
					linePoint = GetGridPoint(Mouse::pos - display.pos);
					if (linePoint != null)
					{
						if (buf != null)
						{
							buf = linePoint - buf;
							while (buf.y != 0 || buf.x != 0)
							{
								if (abs(buf.x) > abs(buf.y))
								{
									grid[linePoint.y - buf.y][linePoint.x - (buf.x > 0 ? buf.x-- : ++buf.x)].set(0, true);
								}
								else
								{
									grid[linePoint.y - (buf.y > 0 ? buf.y-- : ++buf.y)][linePoint.x - buf.x].set(1, true);
								}
							}
						}
					}
					else
					{
						linePoint = buf;
					}
					return true;
				}
				else if (tool == 1)
				{
					// 面を塗る
					grid[(Mouse::pos - display.pos) / size].face = brushColor;
					return true;
				}
			}
		}
		return false;
	}

	const Point<int> GetGridPoint(const Point<int>& p)const
	{
		auto buf = (p + size / 2) / size;
		return (p.distance<float>(buf * size) < size.length<float>() / 2) ? buf : null;
	}

	void draw()
	{
		for (int y = 0; y < sizeY; ++y)
		{
			for (int x = 0; x < sizeX; ++x)
			{
				int color = -1;
				switch (grid[y][x].face)
				{
					//case -1:color = 0xefcd9a; break;
				case 0:color = common::fc[0]; break;
				case 1:color = common::fc[1]; break;
				case 2:color = common::fc[2]; break;
				case 3:color = common::fc[3]; break;
				case 4:color = common::fc[4]; break;
				case 5:color = common::fc[5]; break;
				case 6:color = common::fc[6]; break;
				case 7:color = common::fc[7]; break;
				}
				if (color != -1)
					display.box(x * size.x, y * size.y, size.x, size.y, color, true);
				display.line(x * size.x, y * size.y, (x + 1) * size.x, y * size.y, grid[y][x].up() ? common::lc[0] : common::lc[1], grid[y][x].up() ? 2 : 1);
				display.line(x * size.x, y * size.y, x * size.x, (y + 1) * size.y, grid[y][x].left() ? common::lc[0] : common::lc[1], grid[y][x].left() ? 2 : 1);
				if (grid[y][x].icon != -1)
				{
					display.box(x * size.x + 3, y * size.y + 3, size.x - 5, size.y - 5, grid[y][x].icon * 6324891, true);
				}
			}
		}
		display.circle(12 * size.x + size.x / 2, 7 * size.y + size.y / 2, size.x / 2, 0xffffff, true);
	}
};


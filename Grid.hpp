#pragma once
#include <bitset>
#include <array>
#include "IconSet.hpp"
#include "Draw.hpp"
#include "Point.hpp"
#include "common.hpp"

constexpr size_t sizeX = 35, sizeY = 19;

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

	static constexpr int lineThick = 4, ColorchangeActivateLength = 30, ColorNum = 8;

	Grid(int x, int y, int scroolX = 0, int scroolY = 0) :size(y, x), display(scroolX, scroolY, 0) {}

	Point<int> GetRelativePoint(const Point<int>& mouse)
	{
		return mouse - display.pos;
	}

	const Point<int> GetGridPoint(const Point<int>& p)const
	{
		auto buf = (p + size / 2) / size;
		return (p.distance<float>(buf * size) < size.length<float>() / 2) ? buf : common::null;
	}

	// 線を引く
	void DrawLine(const Point<int>& mouse, Point<int>& prev)
	{
		auto buf = GetGridPoint(GetRelativePoint(mouse));
		if (buf != common::null)
		{
			if (prev != common::null && ((buf.y != 0 && buf.y != sizeY - 1 && buf.x != 0 && buf.x != sizeX - 1) || (buf.y != prev.y && buf.x != prev.x)))	// 両方とも画面端だった場合無効化
			{
				// SE再生()
				auto dif = prev - buf;
				while (dif.y != 0 || dif.x != 0)
				{
					if (abs(dif.x) > abs(dif.y))
					{
						grid[prev.y - dif.y][prev.x - (dif.x > 0 ? dif.x-- : ++dif.x)].set(0, true);
					}
					else
					{
						grid[prev.y - (dif.y > 0 ? dif.y-- : ++dif.y)][prev.x - dif.x].set(1, true);
					}
				}
			}
			prev = buf;
		}
	}

	// 線を消す
	void EraseLine(const Point<int>& mouse)
	{
		auto buf = GetRelativePoint(mouse);
		bool se = false;
		if ((buf.y + lineThick) % size.y <= lineThick * 2)
		{
			grid[(buf + Point<int>(lineThick, 0)) / size].set(0, false);
			se = true;
		}
		if ((buf.x + lineThick) % size.x <= lineThick * 2)
		{
			grid[(buf + Point<int>(0, lineThick)) / size].set(1, false);
			se = true;
		}
		if (se)
		{
			// SE再生()
		}
	}

	// 地図上のアイコンを持ち上げる
	char TakeIcon(const Point<int>& mouse)
	{
		char ret = -1;
		auto& buf = grid[GetRelativePoint(mouse) / size].icon;
		if (buf != -1)
		{
			// SE再生()
			ret = buf;
			buf = -1;
			//ResetPos();
		}
		return ret;
	}

	// 面を塗る
	void DrawFace(const Point<int>& mouse, char color)
	{
		// SE再生()
		grid[GetRelativePoint(mouse) / size].face = color;
	}

	// 面を消す
	void EraseFace(const Point<int>& mouse)
	{
		// SE再生()
		grid[GetRelativePoint(mouse) / size].face = -1;
	}

	// アイコンを置く
	void DropIcon(const Point<int>& mouse, char icon)
	{
		if (!IconSet::view || !IconSet::on(mouse)) // アイコンセット以外の場所にドロップしたなら置く
		{
			// SE再生()
			grid[GetRelativePoint(mouse) / size].icon = icon;
		}
		else
		{
			// SE再生()
		}
	}

	// ツール切り替え
	//void SwitchTool()
	//{
	//	tool ^= 1;
	//	tool &= 1;
	//	prevPos = null;
	//}

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


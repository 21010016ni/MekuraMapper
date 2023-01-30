#pragma once
#include <bitset>
#include <array>
#include "Point.hpp"
//#include "common.hpp"
//#include "UI.hpp"

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
	//Draw display;

	GridData<sizeX, sizeY> grid;
	//Point<int> gridSize, screenSize;

	static constexpr int lineThick = 4, ColorchangeActivateLength = 30, ColorNum = 8;

	Grid() {}

	const Point<int> GetGridPoint(const Point<int>& p)const;

	// 線を引く
	void DrawLine(const Point<int>& mouse, Point<int>& prev);

	// 線を消す
	void EraseLine(const Point<int>& mouse);

	// 地図上のアイコンを持ち上げる
	char TakeIcon(const Point<int>& mouse);

	// 面を塗る
	void DrawFace(const Point<int>& mouse, char color);

	// 面を消す
	void EraseFace(const Point<int>& mouse);

	// アイコンを置く
	void DropIcon(const Point<int>& mouse, char icon);

	// ツール切り替え
	//void SwitchTool()
	//{
	//	tool ^= 1;
	//	tool &= 1;
	//	prevPos = null;
	//}
};


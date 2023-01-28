#pragma once
#include <string>
#include <bitset>
#include "Point.hpp"

namespace ref
{
	constexpr std::bitset<8>
		top(0x00),
		bottom(0x01),
		middle(0x03),
		left(0x00),
		right(0x04),
		center(0x0c);
}

namespace blendmode
{
	constexpr unsigned char
		noblend = 0,
		alpha = 1,
		add = 2,
		sub = 3,
		mul = 4,
		sub2 = 5,
		xOR = 6,
		destcolor = 8,
		invdestcolor = 9,
		invsrc = 10,
		mula = 11,
		alpha_x4 = 12,
		add_x4 = 13,
		srccolor = 14,
		half_add = 15,
		sub1 = 16,
		pma_alpha = 17,
		pma_add = 18,
		pma_sub = 19,
		pma_invsrc = 20,
		pma_alpha_x4 = 21,
		pma_add_x4 = 22,
		live2d_zero = 23,
		live2d_normal = 24,
		live2d_add = 25,
		live2d_mult = 26,
		live2d_mask = 27,
		spine_normal = 28,
		spine_additive = 29,
		spine_multiply = 30,
		spine_screen = 31,
		custom = 32;
};

class Draw
{
	class Shake
	{
		friend Draw;

		Point<float> v;
		int count;

		char mode;
		int time;
		float power;
		Point<float> dir;
		int lvmx;
		int lvmn;

		Shake();

	public:
		void set(int time, float power, int mx, int mn = 0);
		void set(int time, float x, float y, int mx, int mn = 0);
		void update();
		const Point<float> get(int lv)const { return (lv >= lvmn && lv <= lvmx) ? v : Point<float>(0.0f); }
		const float x(int lv)const { return (lv >= lvmn && lv <= lvmx) ? v.x : 0; }
		const float y(int lv)const { return (lv >= lvmn && lv <= lvmx) ? v.y : 0; }
	};

	static const Point<int> GetRef(std::bitset<8> ref, int w, int h);

public:
	static inline int font = -1;

	static inline Shake shake;

	int lv;
	Point<int> pos;

	Draw(int x, int y, int lv) :pos(y, x), lv(lv) {}
	Draw(const Point<int>& pos, int lv) :pos(pos), lv(lv) {}

	static void blend();
	static void blend(unsigned char mode, unsigned char value);
	static void area();
	void area(int width, int height);
	void area(const Point<int>& size);

	void pixel(int x, int y, unsigned int color)const;
	void pixel(const Point<int>& dst, unsigned int color)const;

	void line(int x0, int y0, int x1, int y1, unsigned int color, int thick = 1)const;
	void line(const Point<int>& dst0, const Point<int>& dst1, unsigned int color, int thick = 1)const;
	void lineAA(float x0, float y0, float x1, float y1, unsigned int color, float thick = 1.0f)const;
	void lineAA(const Point<float>& dst0, const Point<float>& dst1, unsigned int color, float thick = 1.0f)const;

	void box(int x, int y, int w, int h, unsigned int color, bool fill)const;
	void box(const Point<int>& dst, const Point<int>& siz, unsigned int color, bool fill)const;
	void boxAA(float x, float y, float w, float h, unsigned int color, bool fill, float thick = 1.0f)const;
	void boxAA(const Point<float>& dst, const Point<float>& siz, unsigned int color, bool fill, float thick = 1.0f)const;

	void circle(int x, int y, int r, unsigned int color, bool fill, int thick = 1)const;
	void circle(const Point<int>& dst, int r, unsigned int color, bool fill, int thick = 1)const;
	void circleAA(float x, float y, float r, int num, unsigned int color, bool fill, float thick = 1.0f)const;
	void circleAA(const Point<float>& dst, float r, int num, unsigned int color, bool fill, float thick = 1.0f)const;

	void triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color, bool fill)const;
	void triangle(const Point<int>& dst0, const Point<int>& dst1, const Point<int>& dst2, unsigned int color, bool fill)const;
	void triangleAA(float x0, float y0, float x1, float y1, float x2, float y2, unsigned int color, bool fill, float thick = 1.0f)const;
	void triangleAA(const Point<float>& dst0, const Point<float>& dst1, const Point<float>& dst2, unsigned int color, bool fill, float thick = 1.0f)const;

	void graph(int x, int y, int graph, bool alpha)const;
	void graph(const Point<int>& dst, int graph, bool alpha)const;

	void sprite(int dstX, int dstY, int srcX, int srcY, int w, int h, int graph, bool alpha, bool reverseX = false, bool reverseY = false)const;
	void sprite(const Point<int>& dst, const Point<int>& src, const Point<int>& siz, int graph, bool alpha, bool reverseX = false, bool reverseY = false)const;

	int string(int x, int y, const std::u8string& v, unsigned int color, std::bitset<8> ref = 0, unsigned int edge = 0u)const;
	int string(const Point<int>& dst, const std::u8string& v, unsigned int color, std::bitset<8> ref = 0, unsigned int edge = 0u)const;
	static int getStringWidth(const std::u8string& v, bool vertical = false);
};


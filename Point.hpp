#pragma once
#include <cmath>
#include <compare>

template<typename T> class Point
{
public:
	T y, x;

	explicit constexpr Point(const T& v = 0) :y(v), x(v) {}
	explicit constexpr Point(const T& y, const T& x) :y(y), x(x) {}
	//constexpr ~Point() = default;

	constexpr Point operator+(const Point& v)const noexcept { return Point(y + v.y, x + v.x); }
	constexpr Point operator-(const Point& v)const noexcept { return Point(y - v.y, x - v.x); }
	constexpr Point operator*(const Point& v)const noexcept { return Point(y * v.y, x * v.x); }
	constexpr Point operator/(const Point& v)const noexcept { return Point(y / v.y, x / v.x); }

	constexpr Point operator*(const T& v)const noexcept { return Point(y * v, x * v); }
	constexpr Point operator/(const T& v)const noexcept { return Point(y / v, x / v); }

	Point& operator=(const Point& v)noexcept { return y = v.y, x = v.x, *this; }

	Point& operator+=(const Point& v)noexcept { return y += v.y, x += v.x, *this; }
	Point& operator-=(const Point& v)noexcept { return y -= v.y, x -= v.x, *this; }
	Point& operator*=(const Point& v)noexcept { return y *= v.y, x *= v.x, *this; }
	Point& operator/=(const Point& v)noexcept { return y /= v.y, x /= v.x, *this; }

	Point& operator*=(const T& v)noexcept { return y *= v, x *= v, *this; }
	Point& operator/=(const T& v)noexcept { return y /= v, x /= v, *this; }

	auto operator<=>(const Point&)const = default;

	constexpr Point operator()(const T& t)const noexcept { return Point(t / x, t % x); }
	constexpr Point<float> operator()(const float& t) = delete;

	constexpr Point approximate(const Point& siz, int level)const { return Point(y / (siz.y / level), x / (siz.x / level)); }
	constexpr Point normalize()const { return *this / length<T>(); }

	template<typename U> constexpr U length()const { return std::sqrt(y * y + x * x); }
	template<typename U> constexpr U distance(const Point& t)const { return std::sqrt((y - t.y) * (y - t.y) + (x - t.x) * (x - t.x)); }
	template<typename U> Point& rotate(const U& t)noexcept { return y = y * cos(t) + x * sin(t), x = -y * sin(t) + x * cos(t), *this; }
	template<typename U> constexpr U cross_check(const Point& t, const U& ang)const { return (y - t.y) * cos(ang) - (x - t.x) * sin(ang); }

	template<typename U> constexpr explicit operator Point<U>()const noexcept { return Point<U>(y, x); };
};


#pragma once
#include <memory>
#include <list>
#include "Point.hpp"

class SoundList
{
	struct Sound
	{
		int handle;
		int playtype;
		Point<float> pos;

		Sound(int handle, int playtype, Point<float> pos) :handle(handle), playtype(playtype), pos(pos) {}
	};

	struct Listener
	{
		template<typename T> struct SmoothChange
		{
			T start;
			T target;
			int time;
			int now;

			SmoothChange(T start, T target, int time) :start(start), target(target), time(time), now(0) {}
			bool update(T& val)
			{
				if (++now == time)
				{
					val = target;
					return true;
				}
				else
				{
					val = (target - start) * now / time;
					return false;
				}
			}
		};

		Point<float> pos;
		float rot;
		std::unique_ptr<SmoothChange<Point<float>>> changePos;
		std::unique_ptr<SmoothChange<float>> changeRot;

		void move(Point<float> target, int time);
		void rotate(float target, int time);
		void update();
	};

	std::list<Sound> list;
	Listener listener;

public:
	void push(int handle, int playtype, Point<float> pos);
	void update();
};


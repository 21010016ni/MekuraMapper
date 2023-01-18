#pragma once
#include "Particle.hpp"
#include <DxLib.h>
#include "Point.hpp"

class Dust :public Emitter
{
	class Dustflake :public Snowflake
	{
		Point<float> pos, vec;

	public:
		Dustflake(int duration, float x, float y, float vx, float vy) :Snowflake(duration), pos(y, x), vec(vy, vx) {}
		void update()override;
		void draw()const override;
	};

public:
	Dust(int spawnrate) :Emitter(spawnrate) {}

	std::unique_ptr<Snowflake> generate()override;
};


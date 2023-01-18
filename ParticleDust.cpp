#include "ParticleDust.hpp"

void Dust::Dustflake::update()
{
	pos += vec;
	vec.rotate(RF(-0.1f, 0.1f));
}

void Dust::Dustflake::draw()const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, duration / 2);
	DrawCircleAA(pos.x, pos.y, 2, 5, 0xffffffff, TRUE);
}

std::unique_ptr<Snowflake> Dust::generate()
{
	return std::unique_ptr<Snowflake>(new Dustflake(RI(60, 180), RF(0, (float)common::width), RF(0, (float)common::height), RF(-0.3f, 0.3f), RF(-0.3f, 0.3f)));
}

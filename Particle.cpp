#include "Particle.hpp"
#include "Draw.hpp"

void Particle::update()
{
	for(const auto& i : emitter)
		if(i->spawn())
			snowflake.emplace_back(i->generate());
	for (auto i = snowflake.begin(); i != snowflake.cend();)
	{
		(*i)->update();
		if (!(--(**i))())
		{
			i = snowflake.erase(i);
			continue;
		}
		++i;
	}
}

void Particle::draw()
{
	for (const auto& i : snowflake)
		i->draw();
	Draw::blend();
}


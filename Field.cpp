#include "Field.hpp"

void Field::update()
{
	for (const auto& i : mob)
	{
		if (i)
		{
			i->routine();
		}
	}
}


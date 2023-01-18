#include "IconSet.hpp"
#include <DxLib.h>
#include "UI.hpp"

void IconSet::draw()const
{
	if (view)
	{
		Point<int> p(0);
		for (const auto& i : icon)
		{
			for (const auto& j : i)
			{
				display.box(p, siz, j * 6324891, true);
				display.box(p, siz, 0xffffffff, false);
				//DrawBox(x, y, x + siz.x, y + siz.y, j * 6324891, true);
				//DrawBox(x, y, x + siz.x, y + siz.y, 0xffffffff, false);
				p.x += siz.x;
			}
			p.y += siz.y;
			p.x = 0;
		}
	}
}


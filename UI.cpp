#include "UI.hpp"
#include "common.hpp"

Draw UI::map(92, 204, 1);
Point<int> UI::gridSize(24, 24), UI::mapSize(456, 840);

void UI::draw(Grid& grid)
{
	for (int y = 0; y < sizeY; ++y)
	{
		if (y * UI::gridSize.y >= UI::mapSize.y)
			break;
		for (int x = 0; x < sizeX; ++x)
		{
			if (x * UI::gridSize.x >= UI::mapSize.x)
				break;
			int color = -1;
			switch (grid.grid[y][x].face)
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
				map.box(x * UI::gridSize.x, y * UI::gridSize.y, UI::gridSize.x, UI::gridSize.y, color, true);
			map.line(x * UI::gridSize.x, y * UI::gridSize.y, (x + 1) * UI::gridSize.x, y * UI::gridSize.y, grid.grid[y][x].up() ? common::lc[0] : common::lc[1], grid.grid[y][x].up() ? 2 : 1);
			map.line(x * UI::gridSize.x, y * UI::gridSize.y, x * UI::gridSize.x, (y + 1) * UI::gridSize.y, grid.grid[y][x].left() ? common::lc[0] : common::lc[1], grid.grid[y][x].left() ? 2 : 1);
			if (grid.grid[y][x].icon != -1)
			{
				map.box(x * UI::gridSize.x + 3, y * UI::gridSize.y + 3, UI::gridSize.x - 5, UI::gridSize.y - 5, grid.grid[y][x].icon * 6324891, true);
			}
		}
	}
}

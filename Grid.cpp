#include "Grid.hpp"
#include "UI.hpp"
#include "common.hpp"

const Point<int> Grid::GetGridPoint(const Point<int>& p) const
{
	auto buf = (p + UI::gridSize / 2) / UI::gridSize;
	return (p.distance<float>(buf * UI::gridSize) < UI::gridSize.length<float>() / 2) ? buf : common::null;
}

void Grid::DrawLine(const Point<int>& mouse, Point<int>& prev)
{
	auto buf = GetGridPoint(UI::GetMapRelativePoint(mouse));
	if (buf != common::null)
	{
		if (prev != common::null && ((buf.y != 0 && buf.y != sizeY - 1 && buf.x != 0 && buf.x != sizeX - 1) || (buf.y != prev.y && buf.x != prev.x)))	// óºï˚Ç∆Ç‡âÊñ í[ÇæÇ¡ÇΩèÍçáñ≥å¯âª
		{
			// SEçƒê∂()
			auto dif = prev - buf;
			while (dif.y != 0 || dif.x != 0)
			{
				if (abs(dif.x) > abs(dif.y))
				{
					grid[prev.y - dif.y][prev.x - (dif.x > 0 ? dif.x-- : ++dif.x)].set(0, true);
				}
				else
				{
					grid[prev.y - (dif.y > 0 ? dif.y-- : ++dif.y)][prev.x - dif.x].set(1, true);
				}
			}
		}
		prev = buf;
	}
}

void Grid::EraseLine(const Point<int>& mouse)
{
	auto buf = UI::GetMapRelativePoint(mouse);
	bool se = false;
	if ((buf.y + lineThick) % UI::gridSize.y <= lineThick * 2)
	{
		grid[(buf + Point<int>(lineThick, 0)) / UI::gridSize].set(0, false);
		se = true;
	}
	if ((buf.x + lineThick) % UI::gridSize.x <= lineThick * 2)
	{
		grid[(buf + Point<int>(0, lineThick)) / UI::gridSize].set(1, false);
		se = true;
	}
	if (se)
	{
		// SEçƒê∂()
	}
}

char Grid::TakeIcon(const Point<int>& mouse)
{
	char ret = -1;
	auto& buf = grid[UI::GetMapRelativePoint(mouse) / UI::gridSize].icon;
	if (buf != -1)
	{
		// SEçƒê∂()
		ret = buf;
		buf = -1;
		//ResetPos();
	}
	return ret;
}

void Grid::DrawFace(const Point<int>& mouse, char color)
{
	// SEçƒê∂()
	grid[UI::GetMapRelativePoint(mouse) / UI::gridSize].face = color;
}

void Grid::EraseFace(const Point<int>& mouse)
{
	// SEçƒê∂()
	grid[UI::GetMapRelativePoint(mouse) / UI::gridSize].face = -1;
}

void Grid::DropIcon(const Point<int>& mouse, char icon)
{
	// SEçƒê∂()
	grid[UI::GetMapRelativePoint(mouse) / UI::gridSize].icon = icon;
}


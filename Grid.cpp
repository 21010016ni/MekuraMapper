#include "Grid.hpp"
#include <cmath>
#include "Input.hpp"
#include "common.hpp"

bool Grid::controll()
{
	static Mouse::Log log;

	if (Mouse::wheel != 0)
	{
		// �c�[���؂�ւ�
		tool ^= 1;
		tool &= 1;
		linePoint = null;
		circle = null;
		return true;
	}
	if (Mouse::getLog(log))
	{
		if (log.b3())
		{
			if (log.type)
			{
				if (tool == 0 || tool == 2)
				{
					// �A�C�R���Z�b�g�̕\����\���؂�ւ�
					iconset.view ^= 1;
				}
				else if (tool == 1)
				{
					// �F�؂�ւ��\��
					circle = log.pos;
					return true;
				}
			}
			else
			{
				if (tool == 1 && circle != null)
				{
					// �F�؂�ւ�����
					circle = log.pos - circle;
					if (circle.length<float>() > ColorchangeActivateLength)
					{
						float buf = std::atan2f(circle.y, circle.x);
						if (buf < 0)
							buf += common::pi * 2;
						buf /= common::pi / 4;
						brushColor = static_cast<char>(floor(buf));
					}
				}
			}
		}
		if (log.b1())
		{
			if (log.type)
			{
				char buf;
				if (iconset.view && iconset.on(log.pos))
				{
					// �A�C�R���Z�b�g����A�C�R���������グ��
					hasIcon = iconset.get((log.pos - iconset.display.pos) / iconset.siz);
					if (hasIcon != -1)
					{
						tool = 2;
						linePoint = null;
						circle = null;
					}
					return true;
				}
				else if (tool == 0 && common::onWindow(log.pos.x, log.pos.y) && (buf = grid[(log.pos - display.pos) / size].icon) != -1)
				{
					// �A�C�R���������グ��
					// SE�Đ�
					grid[(log.pos - display.pos) / size].icon = -1;
					tool = 2;
					hasIcon = buf;
					linePoint = null;
					return true;
				}
			}
			else
			{
				if (tool == 0)
				{
					linePoint = null;
					return true;
				}
				if (tool == 2)
				{
					if (common::onWindow(log.pos.x, log.pos.y))
					{
						// �A�C�R����u��
						if (!iconset.view || !iconset.on(log.pos)) // �A�C�R���Z�b�g�ȊO�̏ꏊ�Ƀh���b�v�����Ȃ�u��
						{
							grid[(log.pos - display.pos) / size].icon = hasIcon;
						}
						tool = 0;
						return true;
					}
				}
			}
		}
	}

	if (common::onWindow(Mouse::pos.x, Mouse::pos.y))
	{
		if (Mouse::b2())
		{
			if (tool == 0)
			{
				// ��������
				if ((Mouse::pos.y - display.pos.y + lineThick) % size.y <= lineThick * 2)
				{
					grid[(Mouse::pos - display.pos + Point<int>(lineThick, 0)) / size].set(0, false);
				}
				if ((Mouse::pos.x - display.pos.x + lineThick) % size.x <= lineThick * 2)
				{
					grid[(Mouse::pos - display.pos + Point<int>(0, lineThick)) / size].set(1, false);
				}
				return true;
			}
			else if (tool == 1)
			{
				// �ʂ�����
				grid[(Mouse::pos - display.pos) / size].face = -1;
				return true;
			}
		}
		else if (Mouse::b1())
		{
			if (tool == 0)
			{
				// ��������
				Point<int> buf = linePoint;
				linePoint = GetGridPoint(Mouse::pos - display.pos);
				if (linePoint != null)
				{
					if (buf != null)
					{
						buf = linePoint - buf;
						while (buf.y != 0 || buf.x != 0)
						{
							if (abs(buf.x) > abs(buf.y))
							{
								grid[linePoint.y - buf.y][linePoint.x - (buf.x > 0 ? buf.x-- : ++buf.x)].set(0, true);
							}
							else
							{
								grid[linePoint.y - (buf.y > 0 ? buf.y-- : ++buf.y)][linePoint.x - buf.x].set(1, true);
							}
						}
					}
				}
				else
				{
					linePoint = buf;
				}
				return true;
			}
			else if (tool == 1)
			{
				// �ʂ�h��
				grid[(Mouse::pos - display.pos) / size].face = brushColor;
				return true;
			}
		}
	}
	return false;
}

void Grid::draw()
{
	for (int y = 0; y < 24; ++y)
	{
		for (int x = 0; x < 32; ++x)
		{
			int color = -1;
			switch (grid[y][x].face)
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
			if(color != -1)
				display.box(x * size.x, y * size.y, size.x, size.y, color, true);
			display.line(x * size.x, y * size.y, (x + 1) * size.x, y * size.y, grid[y][x].up() ? common::lc[0] : common::lc[1], grid[y][x].up() ? 2 : 1);
			display.line(x * size.x, y * size.y, x * size.x, (y + 1) * size.y, grid[y][x].left() ? common::lc[0] : common::lc[1], grid[y][x].left() ? 2 : 1);
			if (grid[y][x].icon != -1)
			{
				display.box(x * size.x + 3, y * size.y + 3, size.x - 5, size.y - 5, grid[y][x].icon * 6324891, true);
			}
		}
	}
}


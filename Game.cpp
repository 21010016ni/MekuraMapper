#include "Game.hpp"
#include "common.hpp"
#include "Input.hpp"
#include "convert_string.hpp"

#include "Handle.hpp"

#include "Field.hpp"
#include "IconSet.hpp"
#include "UI.hpp"

#include "common_functions.hpp"

Draw Game::display(0, 0, 0);
//Grid<35, 19> grid(24, 24, 204, 92);

Field field;
char tool, brushColor, hasIcon;
Point<int> prevPos = common::null;

int graph[4];
int se;

void Game::preset()
{
	//Particle::set<Dust>(20);
	Draw::font = LoadFontDataToHandle("data/font/NotoSansJPLight.dft");
	graph[0] = LoadGraph("data/pen.png");
	graph[1] = LoadGraph("data/eraser.png");
	graph[2] = LoadGraph("data/brush.png");
	graph[3] = LoadGraph("data/cloth.png");
	se = LoadSoundMem("data/Footstep-low.wav");

	for(int i = 0; i < 3; ++i)
	{
		IconSet::icon.emplace_back();
		for(int j = 0; j < 15; ++j)
		{
			IconSet::icon.back().emplace_back(i * 15 + j);
		}
	}

	field.mob.emplace_back(new Player(5, 5, 0));
}

Game::Message Game::update()
{
	if(Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}

	//if(Keyboard::push('C'))
	//{
	//	int buf;
	//	printf("%d�ʂ̐F����� : ", grid.brushColor);
	//	scanf_s("%x", &buf);
	//	common::fc[grid.brushColor] = buf;
	//}
	//else if(Keyboard::push('T'))
	//{
	//	int buf;
	//	printf("�L�����̐F����� : ");
	//	scanf_s("%x", &buf);
	//	common::lc[0] = buf;
	//}
	//else if(Keyboard::push('F'))
	//{
	//	int buf;
	//	printf("�������̐F����� : ");
	//	scanf_s("%x", &buf);
	//	common::lc[1] = buf;
	//}

	editmap();

	if (Keyboard::push('Q'))
	{
		command = 0;
	}
	else if (Keyboard::push('W'))
	{
		command = 1;
	}
	else if (Keyboard::push('E'))
	{
		command = 2;
	}
	else if (Keyboard::push('A'))
	{
		command = 3;
	}
	else if (Keyboard::push('D'))
	{
		command = 5;
	}
	else if (Keyboard::push('S'))
	{
		command = 7;
	}

	if (command != -1)
	{
		field.update();
	}

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	DrawBox(0, 0, common::width, common::height, common::bc, true);

	// �����A�O����n�}�G���A�̕`�搧�����|���Ă邯�ǁA���������`��@�\��Grid�ɓn���Ȃ��悤�Ɂ@Grid�ł͂Ȃ��t�B�[���h�A�������͕`�悷��UI������A�N�Z�X����
	//field.grid.display.area(field.grid.screenSize);
	//field.grid.draw();
	UI::map.area(UI::mapSize);
	UI::draw(field.grid);
	for (const auto& i : field.mob)
	{
		if ((i->pos.y - 1) * UI::gridSize.y >= UI::map.pos.y || i->pos.y * UI::gridSize.y + UI::map.pos.y < UI::mapSize.y ||
			(i->pos.x - 1) * UI::gridSize.x >= UI::map.pos.x || i->pos.x * UI::gridSize.x + UI::map.pos.x < UI::mapSize.x)
		{
			auto p = i->pos * UI::gridSize + UI::gridSize / 2;
			auto r = __min(UI::gridSize.y, UI::gridSize.x) / 2;
			float ang = (common::pi / 2) * (-i->rot + 2);
			UI::map.circle(p, r, 0xffffff, true);
			UI::map.triangle(p + Point<int>(std::cosf(ang) * r, std::sinf(ang) * r), p + Point<int>(std::cosf(ang + common::pi2 / 3) * r, std::sinf(ang + common::pi2 / 3) * r), p + Point<int>(std::cosf(ang - common::pi2 / 3) * r, std::sinf(ang - common::pi2 / 3) * r), 0xaaaaaa, true);
		}
	}
	
	Draw::area();

	IconSet::draw();
	//DrawGraph(Mouse::pos.x, Mouse::pos.y, testGraph, true);
	switch(tool)
	{
	case 0:
		if(Mouse::b2())
			DrawGraph(Mouse::pos.x - 3, Mouse::pos.y - 3, graph[1], true);
		else
			DrawGraph(Mouse::pos.x, Mouse::pos.y, graph[0], true);
		break;
	case 1:
		if(Mouse::b2())
			DrawGraph(Mouse::pos.x - 11, Mouse::pos.y - 11, graph[3], true);
		else
			DrawGraph(Mouse::pos.x - 3, Mouse::pos.y - 3, graph[2], true);
		break;
	case 2:
		DrawBox(Mouse::pos.x - 7, Mouse::pos.y - 7, Mouse::pos.x + 7, Mouse::pos.y + 7, hasIcon * 6324891, true);
		break;
	}
	if(Mouse::b3())
	{
		for(int i = 0; i < 8; ++i)
		{
			float x = std::cos(common::pi * i / 4), y = std::sin(common::pi * i / 4);
			DrawLine(prevPos.x + x * field.grid.ColorchangeActivateLength, prevPos.y + y * field.grid.ColorchangeActivateLength, prevPos.x + x * field.grid.ColorchangeActivateLength * 3, prevPos.y + y * field.grid.ColorchangeActivateLength * 3, 0xffffffff);
		}
	}

	//Particle::draw();
}

bool Game::editmap()
{
	static Mouse::Log log;

	if (Mouse::wheel != 0)
	{
		// �c�[���؂�ւ�
		tool ^= 1;
		tool &= 1;
		prevPos = common::null;
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
					IconSet::view ^= 1;
				}
				else if (tool == 1)
				{
					// �F�؂�ւ��\��
					prevPos = log.pos;
					return true;
				}
			}
			else
			{
				if (tool == 1 && prevPos != common::null)
				{
					// �F�؂�ւ�����
					prevPos = log.pos - prevPos;
					if (prevPos.length<float>() > Grid::ColorchangeActivateLength)
					{
						float buf = std::atan2f(prevPos.y, prevPos.x);
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
				if (IconSet::view && IconSet::on(log.pos))
				{
					// �A�C�R���Z�b�g����A�C�R���������グ��
					hasIcon = IconSet::get((log.pos - IconSet::display.pos) / IconSet::siz);
					if (hasIcon != -1)
					{
						tool = 2;
						prevPos = common::null;
					}
					return true;
				}
				else if (tool == 0 && (Mouse::pos.y >= UI::map.pos.y && Mouse::pos.y < UI::map.pos.y + UI::mapSize.y && Mouse::pos.x >= UI::map.pos.x && Mouse::pos.x < UI::map.pos.x + UI::mapSize.x))
				{
					hasIcon = field.grid.TakeIcon(log.pos);
					if (hasIcon != -1)
						tool = 2;
					return true;
				}
			}
			else
			{
				if (tool == 0)
				{
					prevPos = common::null;
					return true;
				}
				if (tool == 2)
				{
					if ((IconSet::view && IconSet::on(log.pos)) || Mouse::pos.y < UI::map.pos.y && Mouse::pos.y >= UI::map.pos.y + UI::mapSize.y && Mouse::pos.x < UI::map.pos.x && Mouse::pos.x >= UI::map.pos.x + UI::mapSize.x)
					{
						// �A�C�R�����̂Ă�
					}
					else
					{
						// �A�C�R����u����
						field.grid.DropIcon(log.pos, hasIcon);
					}
					tool = 0;
					return true;
				}
			}
		}
	}

	if (Mouse::pos.y >= UI::map.pos.y && Mouse::pos.y < UI::map.pos.y + UI::mapSize.y && Mouse::pos.x >= UI::map.pos.x && Mouse::pos.x < UI::map.pos.x + UI::mapSize.x)
	{
		if (Mouse::b2())
		{
			if (tool == 0)
			{
				field.grid.EraseLine(Mouse::pos);
				return true;
			}
			else if (tool == 1)
			{
				field.grid.EraseFace(Mouse::pos);
				return true;
			}
		}
		else if (Mouse::b1())
		{
			if (tool == 0)
			{
				field.grid.DrawLine(Mouse::pos, prevPos);
				return true;
			}
			else if (tool == 1)
			{
				field.grid.DrawFace(Mouse::pos, brushColor);
				return true;
			}
		}
	}
	return false;
}

int Game::pop()
{
	int ret = command;
	command = -1;
	return ret;
}


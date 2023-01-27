#include "Game.hpp"
#include "common.hpp"
#include "Input.hpp"
#include "convert_string.hpp"

#include "Handle.hpp"

#include "Field.hpp"

#include "common_functions.hpp"

Draw Game::display(0, 0, 0);
//Grid<35, 19> grid(24, 24, 204, 92);

Field field(24, 24, 92, 204);
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
	//	printf("%d面の色を入力 : ", grid.brushColor);
	//	scanf_s("%x", &buf);
	//	common::fc[grid.brushColor] = buf;
	//}
	//else if(Keyboard::push('T'))
	//{
	//	int buf;
	//	printf("有効線の色を入力 : ");
	//	scanf_s("%x", &buf);
	//	common::lc[0] = buf;
	//}
	//else if(Keyboard::push('F'))
	//{
	//	int buf;
	//	printf("無効線の色を入力 : ");
	//	scanf_s("%x", &buf);
	//	common::lc[1] = buf;
	//}

	//grid.controll();

	editmap();

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	DrawBox(0, 0, common::width, common::height, common::bc, true);
	field.grid.draw();
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
		// ツール切り替え
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
					// アイコンセットの表示非表示切り替え
					IconSet::view ^= 1;
				}
				else if (tool == 1)
				{
					// 色切り替え表示
					prevPos = log.pos;
					return true;
				}
			}
			else
			{
				if (tool == 1 && prevPos != common::null)
				{
					// 色切り替え決定
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
					// アイコンセットからアイコンを持ち上げる
					hasIcon = IconSet::get((log.pos - IconSet::display.pos) / IconSet::siz);
					if (hasIcon != -1)
					{
						tool = 2;
						prevPos = common::null;
					}
					return true;
				}
				else if (tool == 0 && common::onWindow(log.pos.x, log.pos.y) && (buf = field.grid.grid[(log.pos - display.pos) / field.grid.size].icon) != -1)
				{
					field.grid.TakeIcon(log.pos);
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
					if (common::onWindow(log.pos.x, log.pos.y))
					{
						field.grid.DropIcon(log.pos,hasIcon);
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


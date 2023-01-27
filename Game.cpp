#include "Game.hpp"
#include "common.hpp"
#include "Input.hpp"
#include "convert_string.hpp"

#include "Handle.hpp"

#include "Grid.hpp"

#include "common_functions.hpp"

Draw Game::display(0, 0, 0);
Grid<35, 19> grid(24, 24, 204, 92);
char tool = 0;
char toolmode;
Point<int> click;

int graph[4];
int testGraph;

int se;
int pan;
int vol;
Point<float> distance;

// 鉛筆/消しゴム
// 各色ブラシ/雑巾
// オブジェクト配置
//

void Game::preset()
{
	//Particle::set<Dust>(20);
	Draw::font = LoadFontDataToHandle("data/font/NotoSansJPLight.dft");
	graph[0] = LoadGraph("data/pen.png");
	graph[1] = LoadGraph("data/eraser.png");
	graph[2] = LoadGraph("data/brush.png");
	graph[3] = LoadGraph("data/cloth.png");
	testGraph = LoadGraph("cursor.png");
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

	grid.controll();

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	DrawBox(0, 0, common::width, common::height, common::bc, true);
	grid.draw();
	IconSet::draw();
	//DrawGraph(Mouse::pos.x, Mouse::pos.y, testGraph, true);
	switch(grid.tool)
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
		DrawBox(Mouse::pos.x - 7, Mouse::pos.y - 7, Mouse::pos.x + 7, Mouse::pos.y + 7, grid.hasIcon * 6324891, true);
		break;
	}
	if(Mouse::b3())
	{
		for(int i = 0; i < 8; ++i)
		{
			float x = std::cos(common::pi * i / 4), y = std::sin(common::pi * i / 4);
			DrawLine(grid.circle.x + x * grid.ColorchangeActivateLength, grid.circle.y + y * grid.ColorchangeActivateLength, grid.circle.x + x * grid.ColorchangeActivateLength * 3, grid.circle.y + y * grid.ColorchangeActivateLength * 3, 0xffffffff);
		}
	}

	//Particle::draw();
}

int Game::pop()
{
	int ret = command;
	command = -1;
	return ret;
}


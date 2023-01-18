#include "Game.hpp"
#include "common.hpp"
#include "Input.hpp"
#include "convert_string.hpp"

#include "Handle.hpp"

#include "Grid.hpp"

Draw Game::display(0, 0, 0);
Grid grid(24, 24);
char tool = 0;
char toolmode;
Point<int> click;

int graph[4];
int testGraph;

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

	for (int i = 0; i < 3; ++i)
	{
		grid.iconset.icon.emplace_back();
		for (int j = 0; j < 15; ++j)
		{
			grid.iconset.icon.back().emplace_back(i * 15 + j);
		}
	}
}

Game::Message Game::update()
{
	if (Keyboard::push(VK_ESCAPE))
	{
		return Message::quit;
	}

	grid.controll();

	//Particle::update();
	return Message::none;
}

void Game::draw()
{
	grid.draw();
	grid.iconset.draw();
	//DrawGraph(Mouse::pos.x, Mouse::pos.y, testGraph, true);
	switch (grid.tool)
	{
	case 0:
		if (Mouse::b2())
			DrawGraph(Mouse::pos.x - 3, Mouse::pos.y - 3, graph[1], true);
		else
			DrawGraph(Mouse::pos.x, Mouse::pos.y, graph[0], true);
		break;
	case 1:
		if (Mouse::b2())
			DrawGraph(Mouse::pos.x, Mouse::pos.y, graph[3], true);
		else
			DrawGraph(Mouse::pos.x, Mouse::pos.y, graph[2], true);
		break;
	case 2:
		DrawBox(Mouse::pos.x - 7, Mouse::pos.y - 7, Mouse::pos.x + 7, Mouse::pos.y + 7, grid.hasIcon * 6324891, true);
		break;
	}

	//Particle::draw();
}


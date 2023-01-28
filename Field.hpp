#pragma once

// 世界樹の迷宮は35*30
// これはおそらく3DSの画面サイズを考慮してのこと
// なので今回は変えてもよい
// ただ、マップを綺麗にするために縦横どちらも奇数にする　また、特定の数字の倍数にする　5とか
// マップを分かりやすく座標で指定することを考えると、アルファベットの26文字に足りる量がいいかも　つまり25
// A~Y
// 特定の数字の倍数はいったん無視　というかそもそも拡大表示するなら最大サイズはどうでもいいし
// 表示上は今は35*19にしてる　これ大きすぎるような気がする　考えるの面倒くさいな
// 
// 必要なのは
// グリッド帰属
// タイル情報（壁も含む）
// オブジェクト情報
// 
// リスト管理
// Mob情報
// 
// あとはこの辺のやつをグリッド地図情報に変換するのも
// 
// これオブジェクトとMobはなんか　明確に別物って分かる名前にした方がいいのかな
// いいか　別に
// 
// で、モブから発生する音はおそらく簡単なので、マップそのものから発生する音についてはどうする？
// 普通にアップデート時にSEを登録するか　BGS・SEリストって感じで
// 水の音ってクソうるさくなりそうなんだけどどうやって対処しようね
// ともかく、再生中の音リスト（座標付き）がおそらく必要
// 必要だよね？　うん　振りむき時に必要　え？　いや　うん　振りむきはプレイヤーの座標をいじるからあれなんだけど
// 本当か？　混乱してきた　いや　いるはず　うん
//

#include <array>
#include <memory>
#include <list>
#include "Grid.hpp"
#include "Game.hpp"

class Object
{
	virtual bool active() = 0;
};

class Mob
{
public:
	Point<int> pos;
	char rot;	// ^0,>1,v2,<3 
	virtual void routine() = 0;
};

//  0
// 3 1
//  2

class Player :public Mob
{
	void routine()override
	{
		switch (Game::pop())
		{
		case 0:	// 左振り向き
			rot -= 1;
			if (rot < 0)
				rot += 4;
			break;
		case 1:	// 前進
			(rot % 2 == 0) ? pos.y : pos.x += (rot / 2 == 0) ? 1 : -1;
			break;
		case 2:	// 右振り向き
			rot += 1;
			rot %= 4;
			break;
		case 3:	// 左移動
			(rot % 2 == 0) ? pos.x : pos.y += (rot / 2 == 0) ? -1 : 1;
			break;
		case 5:	// 右移動
			(rot % 2 == 0) ? pos.x : pos.y += (rot / 2 == 0) ? 1 : -1;
			break;
		case 7:	// 後退
			(rot % 2 == 0) ? pos.y : pos.x += (rot / 2 == 0) ? -1 : 1;
			break;
		}
	}
};

class Field
{
	enum class TileType
	{
		wall = -1,
		floor = 0,
		water = 1,
	};

	struct Tile
	{
		TileType type = TileType::floor;
		std::unique_ptr<Object> object;
	};

public:
	std::array<std::array<Tile, 35>, 19> map;
	std::list<std::unique_ptr<Mob>> mob;
	Grid grid;
	
	Field(int x, int y, int scroolX, int scroolY) :grid(x, y, scroolX, scroolY) {}

	void update();
};


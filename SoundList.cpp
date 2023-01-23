#include "SoundList.hpp"
#include <DxLib.h>

void SoundList::Listener::move(Point<float> target, int time)
{
	changePos.reset(new SmoothChange<Point<float>>(pos, target, time));
}

void SoundList::Listener::rotate(float target, int time)
{
	changeRot.reset(new SmoothChange<float>(rot, target, time));
}

void SoundList::Listener::update()
{
	if (changePos)
	{
		if (changePos->update(pos))
		{
			changePos.reset();
		}
	}
	if (changeRot)
	{
		if (changeRot->update(rot))
		{
			changeRot.reset();
		}
	}
}

void SoundList::push(int handle, int playtype, Point<int> pos)
{
	list.emplace_back(handle, playtype, pos);
}

void SoundList::update()
{
	for (auto i = list.begin(); i != list.cend();)
	{
		if (CheckSoundMem(i->handle) == 0)
		{
			i = list.erase(i);
			continue;
		}
		Set3DPositionSoundMem(VECTOR(i->pos.x, 0, i->pos.y), i->playtype);

		// 多分この辺に方向フォーカスの設定
		// ていうかVECTORのY座標変えればよくない？
		// いや調整は音量のほうがいいか

		++i;
	}
}


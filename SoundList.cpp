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

		// �������̕ӂɕ����t�H�[�J�X�̐ݒ�
		// �Ă�����VECTOR��Y���W�ς���΂悭�Ȃ��H
		// ���⒲���͉��ʂ̂ق���������

		++i;
	}
}


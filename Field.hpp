#pragma once

// ���E���̖��{��35*30
// ����͂����炭3DS�̉�ʃT�C�Y���l�����Ă̂���
// �Ȃ̂ō���͕ς��Ă��悢
// �����A�}�b�v���Y��ɂ��邽�߂ɏc���ǂ������ɂ���@�܂��A����̐����̔{���ɂ���@5�Ƃ�
// �}�b�v�𕪂���₷�����W�Ŏw�肷�邱�Ƃ��l����ƁA�A���t�@�x�b�g��26�����ɑ����ʂ����������@�܂�25
// A~Y
// ����̐����̔{���͂������񖳎��@�Ƃ��������������g��\������Ȃ�ő�T�C�Y�͂ǂ��ł�������
// �\����͍���35*19�ɂ��Ă�@����傫������悤�ȋC������@�l����̖ʓ|��������
// 
// �K�v�Ȃ̂�
// �O���b�h�A��
// �^�C�����i�ǂ��܂ށj
// �I�u�W�F�N�g���
// 
// ���X�g�Ǘ�
// Mob���
// 
// ���Ƃ͂��̕ӂ̂���O���b�h�n�}���ɕϊ�����̂�
// 
// ����I�u�W�F�N�g��Mob�͂Ȃ񂩁@���m�ɕʕ����ĕ����閼�O�ɂ������������̂���
// �������@�ʂ�
// 
// �ŁA���u���甭�����鉹�͂����炭�ȒP�Ȃ̂ŁA�}�b�v���̂��̂��甭�����鉹�ɂ��Ă͂ǂ�����H
// ���ʂɃA�b�v�f�[�g����SE��o�^���邩�@BGS�ESE���X�g���Ċ�����
// ���̉����ăN�\���邳���Ȃ肻���Ȃ񂾂��ǂǂ�����đΏ����悤��
// �Ƃ������A�Đ����̉����X�g�i���W�t���j�������炭�K�v
// �K�v����ˁH�@����@�U��ނ����ɕK�v�@���H�@����@����@�U��ނ��̓v���C���[�̍��W�������邩�炠��Ȃ񂾂���
// �{�����H�@�������Ă����@����@����͂��@����
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
		case 0:	// ���U�����
			rot -= 1;
			if (rot < 0)
				rot += 4;
			break;
		case 1:	// �O�i
			(rot % 2 == 0) ? pos.y : pos.x += (rot / 2 == 0) ? 1 : -1;
			break;
		case 2:	// �E�U�����
			rot += 1;
			rot %= 4;
			break;
		case 3:	// ���ړ�
			(rot % 2 == 0) ? pos.x : pos.y += (rot / 2 == 0) ? -1 : 1;
			break;
		case 5:	// �E�ړ�
			(rot % 2 == 0) ? pos.x : pos.y += (rot / 2 == 0) ? 1 : -1;
			break;
		case 7:	// ���
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


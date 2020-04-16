#pragma once
#include <Siv3D.hpp>
#include "ObjData.h"

struct Ability
{
	struct Param {
		int32 base;
		int32 current;
		double buff;
		double buffTime;
	};

	int32 level;
	int32 currentExp;
	int32 nextExp;
	Param hp;				// HP
	Param mp;				// MP
	Param attack;			// �U����
	Param defense;			// �h���
	Param agility;			// �f�����i����E�����E�ړ��X�s�[�h�j
	Param intel;			// ���@�U����
	Param resist;			// ���@�h���
	int32 state;			// ���
	int32 parsonality;		// ���i�i�s���p�^�[���ɉe���i�\��j�j

	Ability() {}
	Ability(const int32& value)
		: level(ObjData::getInstance().level(value))
		, currentExp(ObjData::getInstance().currentExp(value))
		, nextExp(ObjData::getInstance().nextExp(value))
		, hp({ ObjData::getInstance().hp(value), ObjData::getInstance().hp(value), 1, 0 })
		, mp({ ObjData::getInstance().mp(value), ObjData::getInstance().mp(value), 1, 0 })
		, attack({ ObjData::getInstance().attack(value), ObjData::getInstance().attack(value), 1, 0 })
		, defense({ ObjData::getInstance().defense(value), ObjData::getInstance().defense(value), 1, 0 })
		, agility({ ObjData::getInstance().agility(value), ObjData::getInstance().agility(value), 1, 0 })
		, intel({ ObjData::getInstance().intel(value), ObjData::getInstance().intel(value), 1, 0 })
		, resist({ ObjData::getInstance().resist(value), ObjData::getInstance().resist(value), 1, 0 })
		, state(ObjData::getInstance().state(value))
		, parsonality(ObjData::getInstance().parsonality(value))
	{ }

	void update()
	{
		const double delta = Scene::DeltaTime();
		if (0 >= attack.buffTime) {
			attack.current = attack.base;
			attack.buff = 1;
			attack.buffTime = 0;
		}
		else
			attack.buffTime -= delta;

		if (0 >= defense.buffTime) {
			defense.current = defense.base;
			defense.buff = 1;
			defense.buffTime = 0;
		}
		else
			defense.buffTime -= delta;

		if (0 >= agility.buffTime) {
			agility.current = agility.base;
			agility.buff = 1;
			agility.buffTime = 0;
		}
		else
			agility.buffTime -= delta;

		if (0 >= intel.buffTime) {
			intel.current = intel.base;
			intel.buff = 1;
			intel.buffTime = 0;
		}
		else
			intel.buffTime -= delta;

		if (0 >= resist.buffTime) {
			resist.current = resist.base;
			resist.buff = 1;
			resist.buffTime = 0;
		}
		else
			resist.buffTime -= delta;

		return;
	}

	// �o�t�̃A�C�R����`�悷��
	void drawBuff(const RectF& actor)
	{
		const int32 iconSize = 5;
		int32 num = 0;
		Array<HSV> color;

		if (0 < attack.buffTime) {
			1 < attack.buff ? color << HSV(0, 100, 100, 0.6) : color << HSV(0, 100, 50, 0.6);
			++num;
		}
		if (0 < defense.buffTime) {
			1 < defense.buff ? color << HSV(240, 100, 100, 0.6) : color << HSV(240, 100, 50, 0.6);
			++num;
		}
		if (0 < agility.buffTime) {
			1 < agility.buff ? color << HSV(120, 100, 100, 0.6) : color << HSV(120, 100, 50, 0.6);
			++num;
		}
		if (0 < intel.buffTime) {
			1 < intel.buff ? color << HSV(300, 100, 100, 0.6) : color << HSV(300, 100, 50, 0.6);
			++num;
		}
		if (0 < resist.buffTime) {
			1 < resist.buff ? color << HSV(60, 100, 100, 0.6) : color << HSV(60, 100, 50, 0.6);
			++num;
		}

		for (int32 i = 0; i < num; ++i) {
			if (color.at(i).v == 100) {	//�o�t
				Triangle(
					actor.pos.x - (iconSize / 2 * num - 1) + iconSize * i,
					actor.pos.y - actor.h - 3, iconSize)
					.draw(color.at(i));
			}
			else {	// �f�o�t
				Triangle(
					actor.pos.x - (iconSize / 2 * num - 1) + iconSize * i,
					actor.pos.y - actor.h - 3, iconSize)
					.rotated(180_deg)
					.draw(color.at(i));
			}
		}

		return;
	}
};
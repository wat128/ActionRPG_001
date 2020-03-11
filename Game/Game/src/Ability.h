#pragma once
#include <Siv3D.hpp>
#include "ObjData.h"
class Ability
{
public:
	Ability() {}
	Ability(const int32& value)
		: _level(ObjData::getInstance()->Level(value))
		, _currentExp(ObjData::getInstance()->CurrentExp(value))
		, _nextExp(ObjData::getInstance()->NextExp(value))
		, _hp(ObjData::getInstance()->Hp(value))
		, _mp(ObjData::getInstance()->Mp(value))
		, _power(ObjData::getInstance()->Power(value))
		, _physical(ObjData::getInstance()->Physical(value))
		, _speed(ObjData::getInstance()->Speed(value))
		, _knowledge(ObjData::getInstance()->Knowledge(value))
		, _state(ObjData::getInstance()->State(value))
		, _parsonality(ObjData::getInstance()->Parsonality(value))
	{
	}

	inline int32  getLevel() const			{ return _level; }
	inline int32  getCurrentExp() const		{ return _currentExp; }
	inline int32  getNextExp() const		{ return _nextExp; }
	inline int32  getHp() const				{ return _hp; }
	inline int32  getMp() const				{ return _mp; }
	inline int32  getPower() const			{ return _power; }
	inline int32  getPhysical() const		{ return _physical; }
	inline int32  getSpeed() const			{ return _speed; }
	inline int32  getKnowledge() const		{ return _knowledge; }
	inline int32  getState() const			{ return _state; }
	inline int32  getParsonality() const	{ return _parsonality; }

	void update(const int32& value); //レベルアップ処理 プレイヤークラスupdateでコール

private:
	int32 _level;
	int32 _currentExp;
	int32 _nextExp;
	int32 _hp;
	int32 _mp;
	int32 _power;
	int32 _physical;
	int32 _speed;
	int32 _knowledge;
	int32 _state;
	int32 _parsonality;
};


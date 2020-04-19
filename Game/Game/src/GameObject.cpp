#include "GameObject.h"

GameObject::GameObject()
	: ObjectBase(0)
	, _actor(0)
	, _name(U"No Name")
	, _value(0)
	, _texture(nullptr)
	, _tiledTexture()
	, _direction(Direction::Down)
	, _collision()
	, _collisionForMove()
	, _ability()
	, _HurtTime(0)
{ }

GameObject::GameObject(const int32& value, const Vec2& pos)
	: ObjectBase(pos.y)
	, _actor(pos, ObjData::getInstance().textureTileWH(value))
	, _name(ObjData::getInstance().name(value))
	, _value(value)
	, _texture(ObjData::getInstance().texturePass(value))
	, _tiledTexture(
		_texture,
		ObjData::getInstance().textureCharaNum(value),
		ObjData::getInstance().textureTileWH(value),
		ObjData::getInstance().textureTileXYNum(value),
		ObjData::getInstance().textureWalkTileXYNum(value),
		ObjData::getInstance().textureAttackTileXYNum(value))
	, _direction(Direction::Down)
	, _collision(ObjData::getInstance().collision(value))
	, _collisionForMove(ObjData::getInstance().collisionForMove(value))
	, _ability(value)
	, _HurtTime(0)
{ }

GameObject::~GameObject() {}

int32 GameObject::onDamage(const Skill::Data& data)
{
	// テスト用：暫定処理  ダメージ計算式：(攻撃力 * 4 - 防御力 * 2) +- 20 
	const int32 damage = (data.power * 4 - _ability.defense.current * 2 + Random(-20, 20));

	// ダメージ処理
	if (0 < data.power) {
		_ability.hp.current -= damage;
		AudioAsset(U"Damage01").playOneShot(0.7);
		if (0 < _ability.hp.current) {
			_HurtTime = HURTTIME;
		}
	}
	else if (0 > data.power) {
		_ability.hp.current -= damage;
		if (_ability.hp.current > _ability.hp.base)
			_ability.hp.current = _ability.hp.base;
	}

	// バフ処理
	if (0 < data.buff.time) {
		if (0 < data.buff.attack) {
			_ability.attack.current = _ability.attack.base * data.buff.attack;
			_ability.attack.buff = data.buff.attack;
			_ability.attack.buffTime = data.buff.time;
		}
		if (0 < data.buff.defense) {
			_ability.defense.current = _ability.defense.base * data.buff.defense;
			_ability.defense.buff = data.buff.defense;
			_ability.defense.buffTime = data.buff.time;
		}
		if (0 < data.buff.agility) {
			_ability.agility.current = _ability.agility.base * data.buff.agility;
			_ability.agility.buff = data.buff.agility;
			_ability.agility.buffTime = data.buff.time;
		}
		if (0 < data.buff.intel) {
			_ability.intel.current = _ability.intel.base * data.buff.intel;
			_ability.intel.buff = data.buff.intel;
			_ability.intel.buffTime = data.buff.time;
		}
		if (0 < data.buff.resist) {
			_ability.resist.current = _ability.resist.base * data.buff.resist;
			_ability.resist.buff = data.buff.resist;
			_ability.resist.buffTime = data.buff.time;
		}
	}

	return 20;
}

void GameObject::recieveExp(const int32& exp)
{
	// テスト用：暫定処理
	_ability.currentExp += exp;
}

void GameObject::move()
{

}

void GameObject::update()
{
}

void GameObject::draw()
{
}
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
	, _actor(pos, ObjData::getInstance().TextureTileWH(value))
	, _name(ObjData::getInstance().Name(value))
	, _value(value)
	, _texture(ObjData::getInstance().TexturePass(value))
	, _tiledTexture(
		_texture,
		ObjData::getInstance().TextureCharaNum(value),
		ObjData::getInstance().TextureTileWH(value),
		ObjData::getInstance().TextureTileXYNum(value),
		ObjData::getInstance().TextureWalkTileXYNum(value),
		ObjData::getInstance().TextureAttackTileXYNum(value))
	, _direction(Direction::Down)
	, _collision(ObjData::getInstance().Collision(value))
	, _collisionForMove(ObjData::getInstance().CollisionForMove(value))
	, _ability(value)
	, _HurtTime(0)
{ }

GameObject::~GameObject() {}

int32 GameObject::onDamage(const Skill::Data& data)
{
	// テスト用：暫定処理
	AudioAsset(U"Damage01").playOneShot(0.7);
	
	_ability._hp -= data.power;
	if (0 < _ability._hp) {
		_HurtTime = HURTTIME;
	}

	return 20;
}

void GameObject::recieveExp(const int32& exp)
{
	// テスト用：暫定処理
	_ability._currentExp += exp;
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
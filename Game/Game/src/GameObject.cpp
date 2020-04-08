#include "GameObject.h"

GameObject::GameObject()
	: _actor(0)
	, _name(U"No Name")
	, _value(0)
	, _texture(nullptr)
	, _tiledTexture()
	, _direction(Direction::Down)
	, _collision()
	, _collisionForMove()
{ }

GameObject::GameObject(const int32& value, const Vec2& pos)
	: _actor(pos, ObjData::getInstance().TextureTileWH(value))
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
{
	
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
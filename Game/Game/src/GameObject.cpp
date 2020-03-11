#include "GameObject.h"

GameObject::GameObject()
	: _value(0)
	, _texture(nullptr)
	, _actor(0)
{ }

GameObject::GameObject(const int32& value, const Vec2& pos)
	: _value(value)
	, _texture(ObjData::getInstance()->TexturePass(value))
	, _actor(pos.x, pos.y, ObjData::getInstance()->RegionW(value), ObjData::getInstance()->RegionH(value))
{
	
}

bool GameObject::move()
{
	return false;
}

void GameObject::update()
{
}

void GameObject::draw()
{
	
}
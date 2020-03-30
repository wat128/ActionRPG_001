#include "GameObject.h"

GameObject::GameObject()
	: _actor(0)
	, _name(U"No Name")
	, _value(0)
	, _texture(nullptr)
{ }

GameObject::GameObject(const int32& value, const Vec2& pos)
	: _actor(pos.x, pos.y, ObjData::getInstance()->Collision(value).x, ObjData::getInstance()->Collision(value).y)
	, _name(ObjData::getInstance()->Name(value))
	, _value(value)
	, _texture(ObjData::getInstance()->TexturePass(value))
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
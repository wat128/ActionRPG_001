#pragma once
#include <Siv3D.hpp>
#include "ObjData.h"
#include "TiledGameObjectTexture.h"

class GameObject
{
public:
	GameObject();
	GameObject(const int32& value, const Vec2& pos);
	virtual void move();
	virtual void update();
	virtual void draw();

	inline String getName() const { return _name; }
	inline Vec2 getPos() const { return _actor.pos; }
	
	template<typename Shape>
	bool withinCollisionForMove(const Shape& area) const
	{
		RectF collision(_actor.pos.x - _collisionForMove.x / 2, _actor.pos.y - _collisionForMove.y, _collisionForMove);
		if (collision.intersects(area))
			return true;

		return false;
	}
protected:
	RectF _actor;
	const String _name;
	const int32 _value;
	const Texture _texture;
	TiledGameObjectTexture _tiledTexture;
	Direction _direction;
	const Size _collision;
	const Size _collisionForMove;

};


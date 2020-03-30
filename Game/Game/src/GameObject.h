#pragma once
#include <Siv3D.hpp>
#include "ObjData.h"

class GameObject
{
public:
	GameObject();
	GameObject(const int32& value, const Vec2& pos);
	virtual bool move();
	virtual void update();
	virtual void draw();

	inline String getName() const { return _name; }
	inline Vec2 getPos() const { return _actor.pos; }
	
	template<typename Shape>
	bool withinCollision(const Shape& area) const
	{
		RectF collision(_actor.pos.x - _actor.w / 2, _actor.pos.y - _actor.h, _actor.w, _actor.h);
		if (collision.intersects(area))
			return true;

		return false;
	}
protected:
	RectF _actor;
	const String _name;
	const int32 _value;
	const Texture _texture;
};


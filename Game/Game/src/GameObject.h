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

protected:
	RectF _actor;
	const String _name;
	const int32 _value;
	const Texture _texture;
};


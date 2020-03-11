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

protected:
	RectF _actor;
	const int32 _value;
	const Texture _texture;
};


#pragma once
#include <Siv3D.hpp>
#include "ObjData.h"
#include "TiledGameObjectTexture.h"
#include "Ability.h"
#include "Skill.h"
#include "ObjectBase.h"

class GameObject : public std::enable_shared_from_this<GameObject>, public ObjectBase
{
public:
	GameObject();
	GameObject(const int32& value, const Vec2& pos);
	~GameObject();

	virtual int32 onDamage(const Skill::Data& data);
	void recieveExp(const int32& exp);
	inline Ability getAbility() const { return _ability; };
	virtual void move();
	virtual void update();
	virtual void draw();

	inline String getName() const { return _name; }
	inline Vec2 getPos() const { return _actor.pos; }
	
	template<typename Shape>
	bool withinCollision(const Shape& area) const
	{
		if (0 == _collision.y) {	// コリジョン(Circle)
			Circle collision(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collision.x);
			if (collision.intersects(area))
				return true;
		}
		else {						// コリジョン(RectF)
			RectF collision(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collision);
			if (collision.intersects(area))
				return true;
		}
\
		return false;
	}
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
	Ability _ability;

	double _HurtTime;
};


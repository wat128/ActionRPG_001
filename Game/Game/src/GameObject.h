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
	inline Vec2 getSize() const { return _actor.size; }

	void setPos(const Vec2& toPos);
	
	template<typename Shape>
	bool withinCollision(const Shape& area) const
	{
		if (0 == _collisionSize.y) {
			if (Collision<Circle>().intersects(area))
				return true;
		}
		else {
			if (Collision<RectF>().intersects(area))
				return true;
		}

		return false;
	}

	template<typename Shape>
	bool withinCollisionForMove(const Shape& area) const
	{
		if (CollisionForMove().intersects(area))
			return true;

		return false;
	}
	
	// 使用上メモ：呼び出し元でも"0 == _collisionSize.y"でコリジョンの形を判定すること
	template<typename Shape>
	Shape Collision() const
	{ 
		if (0 == _collisionSize.y)	// Circle
			return Shape(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collisionSize.x);
		else						// RectF
			return Shape(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collisionSize);
	}

	inline RectF CollisionForMove() const { return RectF(_actor.pos.x - _collisionForMoveSize.x / 2, _actor.pos.y - _collisionForMoveSize.y, _collisionForMoveSize); }

protected:
	RectF _actor;
	const String _name;
	const int32 _value;
	const Texture _texture;
	TiledGameObjectTexture _tiledTexture;
	Direction _direction;
	const Size _collisionSize;
	const Size _collisionForMoveSize;
	Ability _ability;

	double _HurtTime;
};


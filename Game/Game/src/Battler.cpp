#include "Battler.h"
#include "FieldReferee.h"

Battler::Battler()
	: _isEnemy(false)
{}

Battler::Battler(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _isEnemy(true) // 暫定
{}

void Battler::skill()
{

}

void Battler::move()
{
	// テスト用：
	int32 L, R, U, D;
	KeyQ.pressed() ?	L = 1 : L = 0;
	KeyR.pressed() ?	R = 1 : R = 0;
	KeyE.pressed() ?	U = 1 : U = 0;
	KeyW.pressed() ?	D = 1 : D = 0;

	Vec2 offset = Vec2(R - L, D - U)
		.setLength((Scene::DeltaTime() + 0.5) * _ability._speed * (KeyShift.pressed() ? 0.5 : 1.0));

	const RectF movedCollision(						// 移動した場合の衝突判定用
		_actor.pos.x - _collisionForMove.x / 2 + offset.x
		, _actor.pos.y - _collisionForMove.y + offset.y
		, _collisionForMove.x, _collisionForMove.y);

	bool ret = FieldReferee::getInstance().canMove(movedCollision , shared_from_this());
	if (ret)
		_actor.setPos(_actor.pos + offset);

	if (0 > offset.x)		_direction = Direction::Left;
	else if (0 < offset.x)	_direction = Direction::Right;
	if (0 > offset.y)		_direction = Direction::Up;
	else if (0 < offset.y)	_direction = Direction::Down;

	if (offset.x != 0 || offset.y != 0)
		_tiledTexture.walkAnime(_direction, 0.2);	// 暫定(歩行アニメーションレート)
}

void Battler::update()
{
	move();

	if (0 < _HurtTime)
		_HurtTime -= Scene::DeltaTime();

	_dispPriority = _actor.pos.y;
	
}

void Battler::draw()
{
	if (0 < _HurtTime) {
		_tiledTexture.getTile()
			.draw(_actor.pos.x - _actor.w / 2
				, _actor.pos.y - _actor.h
				, HURT_COLOR);
	}
	else {
		_tiledTexture.getTile()
			.draw(_actor.pos.x - _actor.w / 2
				, _actor.pos.y - _actor.h);
	}

	/*----------------------------------------------------------------------------*/
	/*		テスト用															　*/
	/*----------------------------------------------------------------------------*/
#if 1
	{
		// テスト用：移動用コリジョン
		RectF(_actor.pos.x - _collisionForMove.x / 2, _actor.pos.y - _collisionForMove.y, _collisionForMove).drawFrame();

		// テスト用：ベース座標
		Circle(_actor.pos, 2).draw(Palette::Red);

		if (0 == _collision.y) {
			// テスト用：コリジョン(Circle)
			Circle(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collision.x).drawFrame(0.5, Palette::Orange);
		}
		else {
			// テスト用：コリジョン(RectF)
			RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collision).drawFrame(0.5, Palette::Orange);
		}
	}
#endif
}
#include "Player.h"
#include "FieldReferee.h"

Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _ability(value)
	, _motion(Motion::Excutable)
{
	_skills.emplace_back(std::make_unique<Slash>());
}

void Player::skill()
{
	Skill::State ret = Skill::State::Complete;

	if ((Motion::Excutable == _motion && KeyD.pressed())
		|| Motion::Executing_Skill1 == _motion)
		ret = _skills.at(0)->execute(_actor,_direction, _ability, _tiledTexture);

	if ((Motion::Excutable == _motion && KeyS.pressed())
		|| Motion::Executing_Skill2 == _motion)
		ret = _skills.at(1)->execute(_actor, _direction, _ability, _tiledTexture);

	if ((Motion::Excutable == _motion && KeyA.pressed())
		|| Motion::Executing_Skill3 == _motion)
		ret = _skills.at(2)->execute(_actor, _direction, _ability, _tiledTexture);

	//テスト用：
	if (Skill::State::Continue == ret)
		_motion = Motion::Executing_Skill1;
	else if (Skill::State::Complete == ret)
		_motion = Motion::Excutable;
}

void Player::talk()
{

}

void Player::recieveDamage()
{

}

void Player::move()
{
	Vec2 offset = Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
		.setLength((Scene::DeltaTime() + 0.5) * _ability.getSpeed() *(KeyShift.pressed() ? 0.5 : 1.0));

	const RectF movedCollision(						// 移動後の衝突判定用
		_actor.pos.x - _actor.w / 2 + offset.x
		, _actor.pos.y - _actor.h + offset.y
		, _actor.w, _actor.h);
	
	bool ret = FieldReferee::getInstance().isCollision(movedCollision, this);
	if (!ret)
		_actor.setPos(_actor.pos + offset);

	if (0 > offset.x)		_direction = Direction::Left;
	else if (0 < offset.x)	_direction = Direction::Right;
	if (0 > offset.y)		_direction = Direction::Up;
	else if (0 < offset.y)	_direction = Direction::Down;

	if (offset.x != 0 || offset.y != 0) 
		_tiledTexture.walkAnime(_direction, 0.2);	// 暫定(歩行アニメーションレート)
}

void Player::update()
{
	if(Motion::Excutable ==_motion)
		move();

	skill();
}

void Player::draw()
{
	_tiledTexture.getTile()
		.draw(_actor.pos.x - _tiledTexture.getTile().size.x / 2		// 足元を_actor.posとするため、描画位置調整
			, _actor.pos.y - _tiledTexture.getTile().size.y);
	RectF(_actor.pos.x - _actor.w / 2, _actor.pos.y - _actor.h, _actor.w, _actor.h).drawFrame();	// テスト用：
	Circle(_actor.pos, 2).draw(Palette::Red);	// テスト用：
	Circle(_actor.pos.x, _actor.pos.y - _actor.h, 40).drawFrame(0.5, 0.5, Palette::Orange);	// テスト用：

	ClearPrint();
	Print << U"_actor.pos :" << _actor.pos;
	Print << U"_actor.w :" << _actor.w;
	Print << U"_actor.h :" << _actor.h;
	Print << U"_actor.size :" << _actor.size;
	Print << U"_tiledTexture.size.w :" << _tiledTexture.getTile().size.x;
	Print << U"_tiledTexture.size.h :" << _tiledTexture.getTile().size.y;
}
#include "Player.h"
#include "FieldReferee.h"
#include "FieldManager.h"// テスト用：

Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _motion(Motion::Excutable)
{
	_skills.emplace_back(std::make_unique<Slash>());
	_skills.emplace_back(std::make_unique<SonicBlade>());
	_skills.emplace_back(std::make_unique<BuildUp>());
}

void Player::skill()
{
	Skill::State ret = Skill::State::Complete;
	int32 index = -1;	// 暫定

	// 実行スキルの選定
	if ((Motion::Excutable == _motion && KeyD.pressed())
		|| Motion::Executing_Skill1 == _motion) {
		index = 0;
	}
	else if ((Motion::Excutable == _motion && KeyS.pressed())
		|| Motion::Executing_Skill2 == _motion) {
		index = 1;
	}
	else if ((Motion::Excutable == _motion && KeyA.pressed())
		|| Motion::Executing_Skill3 == _motion) {
		index = 2;
	}
	else { return; }

	// 実行スキルのジャンルから処理を分ける
	switch (_skills.at(index)->_data.genre) {
	case Skill::Data::Genre::Physical:
		ret = _skills.at(index)->execute(_actor, _direction, _ability, Group::Enemys, _tiledTexture,
			[&](const int32& exp) { this->recieveExp(exp); });
		break;
	case Skill::Data::Genre::AssistMyself:
		ret = _skills.at(index)->execute(_ability, Group::Allys, _handle, _tiledTexture);
		break;
	case Skill::Data::Genre::AssistSomeone:
	case Skill::Data::Genre::SingleEffect:
	case Skill::Data::Genre::AreaOfEffect:
	case Skill::Data::Genre::AreaOfEffectFocusingMyself:
		break;
	}

	// 実行スキルの処理が次フレームでも必要か
	if (Skill::State::Continue == ret) {
		if(0 == index)		_motion = Motion::Executing_Skill1;
		else if(1 == index)	_motion = Motion::Executing_Skill2;
		else if(2 == index)	_motion = Motion::Executing_Skill3;
	}
	else if (Skill::State::Complete == ret) {
		_motion = Motion::Excutable;
	}
}

void Player::talk()
{

}

void Player::move()
{
	double speed;
	if (_ability.agility.current < 500)
		speed = _ability.agility.current;
	else
		speed = 500;

	Vec2 offset = Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
		.setLength((Scene::DeltaTime() + 2.5) + speed * 0.003);

	const RectF movedCollision(						// 移動した場合の衝突判定用
		_actor.pos.x - _collisionForMove.x / 2 + offset.x
		, _actor.pos.y - _collisionForMove.y + offset.y
		, _collisionForMove.x, _collisionForMove.y);
	
	bool ret = FieldReferee::getInstance().canMove(movedCollision, _handle);
	if (ret)
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

	if (0 < _HurtTime)
		_HurtTime -= Scene::DeltaTime();

	_ability.update();
	_dispPriority = _actor.pos.y;
}

void Player::draw()
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

	_ability.drawBuff(_actor);

	/*----------------------------------------------------------------------------*/
	/*		テスト用															　*/
	/*----------------------------------------------------------------------------*/
#if 1
	{
		// テスト用：移動用コリジョン
		RectF(_actor.pos.x - _collisionForMove.x / 2, _actor.pos.y - _collisionForMove.y, _collisionForMove).drawFrame();

		// テスト用：ベース座標
		Circle(_actor.pos, 2).draw(Palette::Red);

		// テスト用：コリジョン
		RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), _collision).drawFrame(0.5, Palette::Orange);

		// テスト用：ソードスキル１の領域確認用

		//Circle(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), 40).drawFrame(0.5, 0.5, Palette::Red);
		//const int32 margin = 10;
		//switch (_direction) {
		//case Direction::Down:
		//	const Circle(_actor.pos.x, _actor.pos.y - _actor.h / 2 + _actor.w / 4 + margin, 20).drawFrame();
		//	break;
		//case Direction::Up:
		//	const Circle(_actor.pos.x, _actor.pos.y - _actor.h / 2 - _actor.w / 4 - margin, 20).drawFrame();
		//	break;
		//case Direction::Left:
		//	const Circle(_actor.pos.x - _actor.w / 4 - margin, _actor.pos.y - _actor.h / 2, 20).drawFrame();
		//	break;
		//case Direction::Right:
		//	const Circle(_actor.pos.x + _actor.w / 4 + margin, _actor.pos.y - _actor.h / 2, 20).drawFrame();
		//	break;
		//}

		// テスト用：ソードスキル２の領域確認用
		//const Size size(240, 20);
		//const int32 margin = 120;
		//switch (_direction) {
		//case Direction::Down:
		//	const RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2 + _actor.w / 4 + margin), size.y, size.x).drawFrame();
		//	break;
		//case Direction::Up:
		//	const RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2 - _actor.w / 4 - margin), size.y, size.x).drawFrame();
		//	break;
		//case Direction::Left:
		//	const RectF(Arg::center(_actor.pos.x - _actor.w / 4 - margin, _actor.pos.y - _actor.h / 2), size.x, size.y).drawFrame();
		//	break;
		//case Direction::Right:
		//	const RectF(Arg::center(_actor.pos.x + _actor.w / 4 + margin, _actor.pos.y - _actor.h / 2), size.x, size.y).drawFrame();
		//	break;
		//}

		// テスト用：
		ClearPrint();
		Print << U"_actor.pos :" << _actor.pos;
		Print << U"_actor.w :" << _actor.w;
		Print << U"_actor.h :" << _actor.h;
		Print << U"_actor.size :" << _actor.size;
		Print << U"_tiledTexture.size :" << _tiledTexture.getTile().size;
		Print << U"Hero_use_count :" << FieldManager::getInstance().getAllys().at(0).use_count();
		if (!FieldManager::getInstance().getEnemys().empty())
			Print << U"モンスター[0] _ HP :" << FieldManager::getInstance().getEnemys().at(0)->getAbility().hp.current;
		else
			Print << U"モンスター無し";
		Print << U"Hero_EXP :" << FieldManager::getInstance().getAllys().at(0)->getAbility().currentExp;
		//Print << U"WolF_use_count :" << FieldManager::getInstance().getEnemys().at(0).use_count();
		Print << U"Hero_attackBuffTime :" << FieldManager::getInstance().getAllys().at(0)->getAbility().attack.buffTime;
	}
#endif
}